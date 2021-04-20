#pragma once

#include "Application/Layer/Event/Event.hpp"
#include "Application/Layer/Event/EventManager.hpp"
#include "Application/Layer/Event/KeyEvent.hpp"
#include "Application/Layer/Event/MouseEvent.hpp"

#include "Application/Layer/ImGuiLayer.hpp"
#include "Application/Layer/Layer.hpp"
#include "Application/Layer/LayerManager.hpp"

#include "Application/Window/Window.hpp"

#include "Core/Program/Program.hpp"
#include "Core/Program/EntryPoint.hpp"
#include "Core/Engine.hpp"

#include "Renderer/Camera/CameraBase.hpp"
#include "Renderer/Camera/OrthographicCamera.hpp"
#include "Renderer/Camera/PerspectiveCamera.hpp"

#include "Renderer/ImGui/ImGuiAPI.hpp"

#include "Renderer/Material/Material.hpp"
#include "Renderer/Mesh/Mesh.hpp"
#include "Renderer/Mesh/Vertex/Vertex2D.hpp"
#include "Renderer/Mesh/Vertex/Vertex3D.hpp"

#include "Renderer/Renderer.hpp"

#include "Renderer/Material/Shader/ShaderBase.hpp"
#include "Renderer/Material/Shader/ShaderManager.hpp"
#include "Renderer/Material/Shader/Uniform/UniformBufferObject.hpp"
#include "Renderer/Material/Shader/Uniform/Uniforms.hpp"

#include "Renderer/Material/Texture/Texture.hpp"

#include "Renderer/Mesh/VertexArray/Buffers/BufferLayout.hpp"
#include "Renderer/Framebuffer/Framebuffer.hpp"
#include "Renderer/Mesh/VertexArray/Buffers/IndexBuffer.hpp"
#include "Renderer/Mesh/VertexArray/Buffers/VertexBuffer.hpp"
#include "Renderer/Mesh/DataTypes/DataTypes.hpp"
#include "Renderer/Mesh/VertexArray/VertexArray.hpp"

#include "Scene/Component/Camera/OrthographicCamComponent.hpp"
#include "Scene/Component/Camera/PerspectiveCamComponent.hpp"
#include "Scene/Component/ModelComponent.hpp"
#include "Scene/Component/TagComponent.hpp"
#include "Scene/Component/TransformComponent.hpp"

#include "Scene/Entity/Entity.hpp"
#include "Scene/Scene.hpp"

#include "Util/Profile.hpp"
#include "Util/Time/DeltaTime.hpp"
#include "Util/Time/Timer.hpp"

#include "Util/TypeDefs.hpp"