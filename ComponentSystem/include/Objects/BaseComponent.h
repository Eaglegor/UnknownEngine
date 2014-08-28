#pragma once

#include <Objects/IComponent.h>

namespace UnknownEngine
{
	namespace Core
	{
		class BaseComponent: public Core::IComponent
		{
			public:
				
				BaseComponent(const std::string& name):
				name(name){}
				
				virtual const char* getName()
				{
					return name.c_str();
				}

			private:
				std::string name;
		};
	}
}
