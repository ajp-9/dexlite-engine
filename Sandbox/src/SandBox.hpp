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

//NIMBLE_DEFINE_MAIN(SandBox);

int main() { nim::NimbleEngine engine; std::shared_ptr<nim::Program> program = std::make_shared<SandBox>(); 
program->m_EngineHandle = std::make_shared<nim::EngineHandle>(engine); engine.setProgram(program);	engine.run(); return 0;}
