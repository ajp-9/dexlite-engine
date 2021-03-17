#pragma once

#include <nim/Nimble.hpp>

class SandBox : public nim::Program
{
	virtual void onBegin() override;
	virtual void onEnd() override;
	virtual void onUpdate() override;
	virtual void onRender() override;
};

NIMBLE_DEFINE_MAIN(SandBox);
