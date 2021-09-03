#include "../Material.hpp"
#include "../../Shader/3D/ShaderNew.hpp"

namespace dex
{
    namespace Material
    {
        struct MaterialNew : BaseNew<Shader::New3D>
        {
            MaterialNew()
                : BaseNew()
            {

            }
        };
    }
}
