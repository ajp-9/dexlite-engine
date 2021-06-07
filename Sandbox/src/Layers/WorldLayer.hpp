#pragma once

#include <dex/Core/Engine.hpp>

class WorldLayer : public dex::Layer::Base
{
public:
	virtual void Attach() override;
	virtual void Detach() override;

	virtual void update() override;
	virtual void render() override;
	virtual void event(dex::Event::Base& e) override;
};
