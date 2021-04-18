#pragma once

#include <dex/Core/Engine.hpp>

class WorldLayer : public dex::Layer
{
public:
	virtual void Attach() override;
	virtual void Detach() override;

	virtual void update() override;
	virtual void render() override;
	virtual void event(std::unique_ptr<dex::Event::Event>& e) override;
};
