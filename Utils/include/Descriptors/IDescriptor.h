#pragma once

#include <Descriptors/IProperty.h>
#include <string>
#include <Properties/Properties.h>
#include <unordered_map>

namespace UnknownEngine
{
    namespace Utils
    {
        class IDescriptor
        {
            public:
                virtual bool isValid() = 0;
                virtual operator Core::Properties() = 0;
                virtual IDescriptor& operator=(const Core::Properties& props) = 0;
        };
    }
}
