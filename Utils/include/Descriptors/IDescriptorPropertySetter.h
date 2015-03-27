#pragma once

#include <Properties/Properties.h>

namespace UnknownEngine
{
    namespace Utils
    {
        class IDescriptorPropertySetter
        {
            public:
                virtual bool isValid() = 0;
                virtual void parseValue(const Core::Properties &props) = 0;
                virtual void writeValue(Core::Properties &props) = 0;
        };
    }
}
