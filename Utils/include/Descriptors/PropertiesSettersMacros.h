#pragma once

#define DESCRIPTOR_PROPERTY_SETTER(field) addSetter( Utils::PropertySetter(#field, field) )
#define DESCRIPTOR_PROPERTY_SETTER_WITH_CUSTOM_NAME(name, field) addSetter( Utils::PropertySetter(#name, field) )

#define DESCRIPTOR_NESTED_DESC_SETTER(field) addSetter( Utils::NestedDescriptorSetter(#field, field) )
#define DESCRIPTOR_NESTED_DESC_SETTER_WITH_CUSTOM_NAME(name, field) addSetter ( Utils::NestedDescriptorSetter(#name, field) )
