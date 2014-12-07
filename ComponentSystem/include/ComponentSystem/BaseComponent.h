#pragma once

#include <ComponentSystem/IComponent.h>

namespace UnknownEngine
{
	namespace Core
	{
		class BaseComponent: public Core::IComponent
		{
			public:
				
				BaseComponent(const char* name):
				name(name){}
				
				virtual const char* getName() const override
				{
					return name.c_str();
				}

			private:
				std::string name;
		};
	}
}
