#pragma once

#include "Application/Event/EventBase.hpp"
#include "Application/Event/KeyEvent.hpp"
#include "Application/Event/MouseEvent.hpp"

#include "Application/Layer/ImGuiLayer.hpp"
#include "Application/Layer/LayerBase.hpp"
#include "Application/Layer/LayerManager.hpp"

#include "Application/Window/Window.hpp"

#include "Core/Program/Program.hpp"
#include "Core/Program/EntryPoint.hpp"
#include "Core/Engine.hpp"

#include "Renderer/ImGui/ImGuiAPI.hpp"

#include "Renderer/Material/Material.hpp"
#include "Renderer/Mesh/Mesh.hpp"
#include "Renderer/Mesh/Vertex/Vertex2D.hpp"
#include "Renderer/Mesh/Vertex/Vertex3D.hpp"

#include "Renderer/Renderer.hpp"

#include "Renderer/Shader/ShaderManager.hpp"
#include "Renderer/Shader/ShaderBase.hpp"
#include "Renderer/Shader/3D/ShaderNew.hpp"
#include "Renderer/Shader/Uniform/UniformBufferObject.hpp"
#include "Renderer/Shader/Uniform/Uniforms.hpp"

#include "Renderer/Material/Texture/Texture.hpp"

#include "Renderer/Framebuffer/Framebuffer.hpp"
#include "Renderer/Mesh/VertexArray/Buffers/IndexBuffer.hpp"
#include "Renderer/Mesh/VertexArray/Buffers/VertexBuffer.hpp"
#include "Renderer/DataTypes/DataTypes.hpp"
#include "Renderer/Mesh/VertexArray/VertexArray.hpp"

#include "Scene/Component/ModelComponent.hpp"
#include "Scene/Component/TagComponent.hpp"
#include "Scene/Component/TransformComponent.hpp"

#include "Scene/Entity/Entity.hpp"
#include "Scene/Scene.hpp"

#include "Util/Profile.hpp"
#include "Util/Time/DeltaTime.hpp"
#include "Util/Time/Timer.hpp"

#include "Util/TypeDefs.hpp"
