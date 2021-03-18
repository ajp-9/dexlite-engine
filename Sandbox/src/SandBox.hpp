#pragma once

#include <nim/Nimble.hpp>

#include "TestLayer.hpp"

class SandBox : public nim::Program
{
	virtual void begin() override;
	virtual void end() override;

	virtual void update() override;
	virtual void render() override;
};

NIMBLE_DEFINE_MAIN(SandBox);
