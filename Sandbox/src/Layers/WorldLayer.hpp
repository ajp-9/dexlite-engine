#pragma once

#include <zim/Zimble.hpp>

class WorldLayer : public zim::Layer
{
public:
	virtual void Attach() override;
	virtual void Detach() override;

	virtual void update() override;
	virtual void render() override;
	virtual void event(std::unique_ptr<zim::Event::Event>& e) override;
};
