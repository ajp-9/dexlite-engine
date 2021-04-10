#pragma once

#include <zim/Application/Layer/Event/Event.hpp>
#include <zim/Application/Layer/Layer.hpp>

class TestLayer : public zim::Layer
{
	virtual void Attach() override;
	virtual void Detach() override;

	virtual void update() override;
	virtual void render() override;
	virtual void event(std::unique_ptr<zim::Event::Event>& e) override;
};
