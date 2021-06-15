#pragma once

#include <dex/Application/Layer/ImGuiLayer.hpp>

class DebugLayer : public dex::ImGuiLayer
{
	//virtual void update() override;
	virtual void render() override;
};
