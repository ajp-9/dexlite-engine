#include "Scene.hpp"

#include "../Core/Engine.hpp"
#include "../Physics/Physics.hpp"
#include "../Util/Logging.hpp"
#include "../Renderer/Shader/ShaderManager.hpp"
#include "Entity/Entity.hpp"
#include "Component/Camera/CameraComponent.hpp"
#include "Component/LightComponents.hpp"
#include "Component/Camera/CameraComponent.hpp"
#include "Component/LightComponents.hpp"
#include "Component/ModelComponent.hpp"
#include "Components.hpp"

namespace dex
{
    Scene::Scene(Renderer* renderer, Physics* physics)
        : m_Renderer(renderer), m_Physics(physics)
    {
        Root = std::make_unique<Entity>(this, "Scene", false);
    }

    Scene::~Scene()
    {
        if (Root)
            Root->destroy();
    }

    Scene::Scene(Scene&& other) noexcept
    {
        operator=(std::move(other));
    }

    Scene& Scene::operator=(Scene&& other) noexcept
    {
        if (this != &other)
        {
            if (Root)
                Root->destroy();

            m_Renderer = other.m_Renderer;
            m_Physics = other.m_Physics;
            m_Registry = std::move(other.m_Registry);
            m_Entities = std::move(other.m_Entities);
            m_ActiveCameraID = other.m_ActiveCameraID;
            m_GlobalShaderUniforms = other.m_GlobalShaderUniforms;
            Root = std::move(other.Root);
            
            Root->m_Scene = this;

            for (auto& entity : m_Entities)
            {
                entity.m_Scene = this;

                entity.getParent().m_Scene = this;

                for (auto& child : entity.getChildren())
                    child.m_Scene = this;
            }
        }

        return *this;
    }

    Entity Scene::createEntity()
    {
        return Entity(this);
    }

    void Scene::destroyEntity(Entity entity)
    {
        if (entity.hasParent())
            entity.getParent().removeChild(entity);

        m_Registry.destroy(entity);
    }

    void Scene::update()
    {
        Root->updateChildrenTransform();
    }

    void Scene::render(const glm::vec2& viewport_size, Renderer& renderer, entt::entity camera)
    {
        renderer.setViewportSize(viewport_size);

        entt::entity main_camera_id = camera;

        if (camera == entt::null)
        {
            findAndSetActiveCamera();
            main_camera_id = m_ActiveCameraID;
        }

        if (main_camera_id != entt::null)
        {
            // Camera:
            m_GlobalShaderUniforms.setCameraPosition(m_Registry.get<Component::Transform>(main_camera_id).getWorldPosition());

            //if (Engine::Renderer.m_ChangeProjectionMatrixNext)
            m_Registry.get<Component::Camera>(main_camera_id).updateProjectionMatrix(viewport_size);

            // if proj or view changed for perf
            m_GlobalShaderUniforms.setProjectionViewMatrix(m_Registry.get<Component::Camera>(main_camera_id).getProjectionViewMatrix());

            // Ambient Light:
            {
                const auto& ambient_light_view = m_Registry.view<Component::Light::Ambient>();

                if (ambient_light_view.size() == 1)
                {
                    for (auto& ambient_light_entity : ambient_light_view)
                        m_GlobalShaderUniforms.setAmbientLight(m_Registry.get<Component::Light::Ambient>(ambient_light_entity));
                }
                else if (ambient_light_view.size() > 1)
                {
                    DEX_LOG_WARN("<dex::Scene::render()>: Only 1 ambient light per scene.");
                }
            }

            // Directional Light:
            {
                const auto& directional_light_view = m_Registry.view<Component::Light::Directional>();

                if (directional_light_view.size() == 1)
                {
                    for (auto& directional_light_entity : directional_light_view)
                        m_GlobalShaderUniforms.setDirectionalLight(m_Registry.get<Component::Light::Directional>(directional_light_entity));
                }
                else if (directional_light_view.size() > 1)
                {
                    DEX_LOG_WARN("<dex::Scene::render()>: Only 1 directional light per scene.");
                }
            }

            // Point Lights:
            {
                const auto& point_light_view = m_Registry.view<Component::Light::Point>();

                if (point_light_view.size() <= 5 && point_light_view.size() > 0)
                {
                    std::vector<dex::Light::Point> point_lights;

                    for (auto& point_light_entity : point_light_view)
                        point_lights.push_back(m_Registry.get<Component::Light::Point>(point_light_entity));

                    m_GlobalShaderUniforms.setPointLights(point_lights);
                }
                else if (point_light_view.size() > 5)
                {
                    DEX_LOG_WARN("<dex::Scene::render()>: Only 5 point lights per scene.");
                }
            }

            // manager compares n uploads in loop
            renderer.ShaderManager.updateCurrentGlobalShaderUniforms(m_GlobalShaderUniforms);

            m_GlobalShaderUniforms.setAllClean();

            renderer.ShaderManager.getShader(Shader::Type::DEFAULT_3D)->bind();
            for (auto render_model_lambda : SceneManager::m_Scene_RenderModel_Functions)
                render_model_lambda(m_Registry);

            renderer.ShaderManager.getShader(Shader::Type::LINE_3D)->bind();
            renderer.LineMesh.drawNew();
        }
        else
        {
            DEX_LOG_WARN("<dex::Renderer::renderScene()>: No active camera found.");
        }
    }

    void Scene::physics(Physics* physics)
    {
        const auto& rigidbody_view = m_Registry.view<Component::RigidBody>();

        for (auto& rigidbody_id : rigidbody_view)
        {
            Component::RigidBody& rigidbody = m_Registry.get<Component::RigidBody>(rigidbody_id);

            //DEX_LOG_INFO(rigidbody.CollidedWith_Handles.size());

            rigidbody.CollidedWith_Handles.clear();

            if (rigidbody.Active)
            {
                Component::Transform& transform = m_Registry.get<Component::Transform>(rigidbody_id);

                switch (rigidbody.Type)
                {
                case RigidBodyType::STATIC:
                case RigidBodyType::KINEMATIC:
                    rigidbody.setTransform(transform.getPosition(), transform.getOrientationQuat());
                    break;
                case RigidBodyType::DYNAMIC:
                    transform.setPosition(rigidbody.getPosition());
                    transform.setOrientationQuat(rigidbody.getOrientation());
                    break;
                }
            }
            // Inefficient
            rigidbody.Body->setActivationState(rigidbody.Active);
        }

        const int num_manifolds = physics->m_CollisionDispatcher->getNumManifolds();
        for (int manifold_idx = 0; manifold_idx < num_manifolds; ++manifold_idx) {
            const btPersistentManifold* const manifold = physics->m_CollisionDispatcher->getManifoldByIndexInternal(manifold_idx);
            
            const btRigidBody* const object1 = static_cast<const btRigidBody*>(manifold->getBody0());
            const btRigidBody* const object2 = static_cast<const btRigidBody*>(manifold->getBody1());

            //if (manifold->getNumContacts()) //avg these out
            //    printf("Collisiton between %u, %u. #contacts:%f\n", object1->getUserIndex(), object2->getUserIndex(), manifold->getContactPoint(0).getAppliedImpulse());
            
            if (manifold->getNumContacts())
            {
                m_Registry.get<Component::RigidBody>(static_cast<const entt::entity>(object1->getUserIndex())).CollidedWith_Handles.push_back(object2->getUserIndex());
                m_Registry.get<Component::RigidBody>(static_cast<const entt::entity>(object2->getUserIndex())).CollidedWith_Handles.push_back(object1->getUserIndex());
            }
        }
    }

    Entity Scene::getEntity(const std::string& tag)
    {
        for (const auto& entity : m_Entities)
        {
            if (entity.getComponent<Component::Tag>().m_Tag == tag)
                return entity;
        }

        DEX_LOG_WARN("dex::Scene::getEntity(): Entity wasn't found with tag: {}", tag);

        return Entity();
    }

    void Scene::findAndSetActiveCamera()
    {
        uint32 enabled_cameras_size = 0;
        const auto& cameraView = m_Registry.view<Component::Camera>();

        for (auto& eID : cameraView)
        {
            Entity entity = Entity(eID, this);

            if (entity.getComponent<Component::Camera>().IsEnabled)
            {
                m_ActiveCameraID = eID;
                enabled_cameras_size += 1;
            }
        }
        
        if (enabled_cameras_size > 1)
        {
            DEX_LOG_ERROR("<Scene::findNSetMainCamera>(): Too many main cameras.");
        }
        else if (enabled_cameras_size < 1)
        {
            DEX_LOG_ERROR("<Scene::findNSetMainCamera()>: No cameras found.");
        }
    }
}
