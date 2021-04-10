#pragma once

#include <zim/Application/Layer/ImGuiLayer.hpp>

class DebugLayer : public zim::ImGuiLayer
{
	virtual void update() override;
	virtual void render() override;
};