#pragma once

#include <nim/Application/Layer/ImGuiLayer.hpp>

class DebugLayer : public nim::ImGuiLayer
{
	virtual void update() override;
	virtual void render() override;
};