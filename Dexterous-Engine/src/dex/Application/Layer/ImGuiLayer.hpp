#pragma once

#include "Layer.hpp"

namespace dex
{
	class ImGuiLayer : public Layer
	{
		// Inherited via Layer
		virtual void Attach() override;
		virtual void Detach() override;
		virtual void update() override {}
		virtual void render() override {}
		virtual void event(std::unique_ptr<Event::Event>& e) override;
	};
}
