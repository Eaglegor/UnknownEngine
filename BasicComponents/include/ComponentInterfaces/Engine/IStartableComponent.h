#pragma once

#include <ComponentSystem/IComponentInterface.h>

namespace UnknownEngine
{
    namespace ComponentInterfaces
    {
        class IStartableComponent : public Core::IComponentInterface
        {
        public:
            constexpr static const char* getTypeName(){return "IStartableComponent";}

            virtual void start() = 0;
            virtual void stop() = 0;
        };
    }
}