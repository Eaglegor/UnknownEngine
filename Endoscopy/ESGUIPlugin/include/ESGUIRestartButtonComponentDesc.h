#pragma once

#include <Descriptors/Descriptor.h>
#include <Descriptors/Property.h>
#include <Descriptors/ComponentDependency.h>
#include <Descriptors/PropertySetter.h>
#include <Descriptors/PropertiesSettersMacros.h>

namespace UnknownEngine
{
	namespace Endoscopy
	{
		class ESGUIRestartButtonComponentDesc : public Utils::Descriptor
		{
			public:
				using Utils::IProperty;
				using Utils::Property;

				Property<std::string, IProperty::REQUIRED> layout_name;
				ComponentDependency<IProperty::REQUIRED> parent_window;
				ComponentDependency<IProperty::REQUIRED> cegui_context;

				ESGUIRestartButtonComponentDesc():
				Utils::Descriptor({
					DESCRIPTOR_PROPERTY_SETTER(layout_name),
					DESCRIPTOR_PROPERTY_SETTER(parent_window),
					DESCRIPTOR_PROPERTY_SETTER(cegui_context)
				})
				{}

		};
	}
}
