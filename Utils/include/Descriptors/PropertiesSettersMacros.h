#pragma once

#define UEDESC_ADD_FIELD(field) addSetter( Utils::PropertySetter(#field, field) )
#define UEDESC_ADD_FIELD_WITH_CUSTOM_NAME(name, field) addSetter( Utils::PropertySetter(#name, field) )

#define UEDESC_ADD_NESTED_DESCRIPTOR(field) addSetter( Utils::NestedDescriptorSetter(#field, field) )
#define UEDESC_ADD_NESTED_DESCRIPTOR_WITH_CUSTOM_NAME(name, field) addSetter ( Utils::NestedDescriptorSetter(#name, field) )
