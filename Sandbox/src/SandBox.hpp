#pragma once

#include <nim/Nimble.hpp>

#include "TestLayer.hpp"

class SandBox : public nim::Program
{
public:
	virtual void Init() override;
	virtual void Shutdown() override;

	virtual void update() override;
	virtual void render() override;

private:
	uint m_VAO, m_VBO, m_IBO;
};

NIMBLE_DEFINE_MAIN(SandBox);
