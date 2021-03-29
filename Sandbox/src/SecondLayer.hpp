#pragma once

#include <nim/Application/Layer/Event/Event.hpp>
#include <nim/Application/Layer/Layer.hpp>

class SecondLayer : public nim::Layer
{
	virtual void Attach() override;
	virtual void Detach() override;

	virtual void update() override;
	virtual void render() override;
	virtual void event(std::unique_ptr<nim::Event::Event>& e) override;
};
