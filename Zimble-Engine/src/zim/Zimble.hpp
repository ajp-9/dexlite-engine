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
#include "Core/ZimbleEngine.hpp"

#include "Renderer/Camera/Camera.hpp"
#include "Renderer/Camera/OrthographicCamera.hpp"
#include "Renderer/Camera/PerspectiveCamera.hpp"

#include "Renderer/ImGui/ImGuiAPI.hpp"

#include "Renderer/Mesh/Material/Material.hpp"
#include "Renderer/Mesh/Mesh.hpp"
#include "Renderer/Mesh/Vertex.hpp"

#include "Renderer/Renderer.hpp"

#include "Renderer/Shader/Shader.hpp"
#include "Renderer/Shader/ShaderManager.hpp"
#include "Renderer/Shader/Uniform/UniformBufferObject.hpp"
#include "Renderer/Shader/Uniform/Uniforms.hpp"

#include "Renderer/Texture/Texture.hpp"

#include "Renderer/VertexArray/Buffers/Buffer.hpp"
#include "Renderer/VertexArray/Buffers/BufferLayout.hpp"
#include "Renderer/VertexArray/Buffers/Framebuffer.hpp"
#include "Renderer/VertexArray/Buffers/IndexBuffer.hpp"
#include "Renderer/VertexArray/Buffers/VertexBuffer.hpp"
#include "Renderer/VertexArray/DataTypes.hpp"
#include "Renderer/VertexArray/VertexArray.hpp"

#include "Scene/Component/OrthoCamera.hpp"
#include "Scene/Component/ModelComponent.hpp"
#include "Scene/Component/TagComponent.hpp"
#include "Scene/Component/TransformComponent.hpp"

#include "Scene/Entity/Entity.hpp"
#include "Scene/Scene.hpp"

#include "Util/Profile.hpp"
#include "Util/Time/DeltaTime.hpp"
#include "Util/Time/Timer.hpp"

#include "Util/TypeDefs.hpp"
