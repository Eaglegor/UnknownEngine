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
					UEDESC_ADD_FIELD(layout_name);
					UEDESC_ADD_FIELD(parent_window);
					UEDESC_ADD_FIELD(cegui_context);
				}

		};
	}
}
