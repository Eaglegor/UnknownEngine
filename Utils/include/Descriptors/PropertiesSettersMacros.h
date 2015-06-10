#pragma once

#define UEDESC_ADD_FIELD(field) addSetter( Utils::PropertySetter(#field, field) )
#define UEDESC_ADD_FIELD_WITH_CUSTOM_NAME(name, field) addSetter( Utils::PropertySetter(#name, field) )

#define UEDESC_ADD_NESTED_DESCRIPTOR(field) addSetter( Utils::NestedDescriptorSetter(#field, field) )
#define UEDESC_ADD_NESTED_DESCRIPTOR_WITH_CUSTOM_NAME(name, field) addSetter ( Utils::NestedDescriptorSetter(#name, field) )

#define UEDESC_ADD_PROPERTIES_LIST(field) addSetter( Utils::PropertiesListSetter(#field, field) )
#define UEDESC_ADD_PROPERTIES_LIST_WITH_CUSTOM_NAME(name, field) addSetter ( Utils::PropertiesListSetter(#name, field) )

#define UEDESC_ADD_COMPONENTS_LIST(field) addSetter( Utils::ComponentDependenciesListSetter(#field, field) )
#define UEDESC_ADD_COMPONENTS_LIST_WITH_CUSTOM_NAME(name, field) addSetter ( Utils::ComponentDependenciesListSetter(#name, field) )

#define UEDESC_ADD_NESTED_DESCRIPTORS_LIST(field) addSetter( Utils::NestedDescriptorsListSetter(#field, field) )
#define UEDESC_ADD_NESTED_DESCRIPTORS_LIST_WITH_CUSTOM_NAME(name, field) addSetter ( Utils::NestedDescriptorsListSetter(#name, field) )
