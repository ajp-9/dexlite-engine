#pragma once

#include <nim/Application/Layer/Event/Event.hpp>
#include <nim/Application/Layer/Layer.hpp>

class SecondLayer : public nim::Layer
{
	virtual void attach() override;
	virtual void detach() override;

	virtual void update() override;
	virtual void render() override;
	virtual void event(std::unique_ptr<nim::event::Event>& e) override;
};
