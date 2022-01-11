#pragma once

#include <dex/Dexlite.hpp>
#include <memory>

class SandBox : public dex::Program
{
public:
    virtual void SetEngineConfig() override;

    virtual void Init() override;
    virtual void Shutdown() override; 

    virtual void update() override;
    virtual void render() override;
private:
};

DEXLITE_DEFINE_MAIN(SandBox);
