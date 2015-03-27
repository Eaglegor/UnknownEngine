#pragma once

#include <Descriptors/DescriptorUtils.h>
#include <Logging.h>

namespace UnknownEngine
{
	namespace Endoscopy
	{
		class ESGUIRestartButtonComponentDesc : public Utils::Descriptor
		{
			public:
				using Utils::Descriptor::operator=;
				
				Utils::RequiredProperty<std::string> layout_name;
				Utils::RequiredComponentDependency parent_window;
				Utils::RequiredComponentDependency cegui_context;

				ESGUIRestartButtonComponentDesc()
				{
					DESCRIPTOR_PROPERTY_SETTER(layout_name);
					DESCRIPTOR_PROPERTY_SETTER(parent_window);
					DESCRIPTOR_PROPERTY_SETTER(cegui_context);
				}

		};
	}
}
