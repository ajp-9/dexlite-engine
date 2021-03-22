#pragma once

#include <nim/Nimble.hpp>

#include "TestLayer.hpp"

class SandBox : public nim::Program
{
	virtual void Begin() override;
	virtual void End() override;

	virtual void update() override;
	virtual void render() override;
};

NIMBLE_DEFINE_MAIN(SandBox);
