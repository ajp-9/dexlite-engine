#pragma once

#include "LayerBase.hpp"

namespace dex
{
	class ImGuiLayer : public Layer::Base
	{
		// Inherited via Layer
		virtual void Attach() override;
		virtual void Detach() override;
		virtual void update() override {}
		virtual void render() override {}
		virtual void event(std::unique_ptr<Event::Base>& e) override;
	};
}
