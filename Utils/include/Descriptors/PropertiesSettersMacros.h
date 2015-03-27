#pragma once

#define DESCRIPTOR_PROPERTY_SETTER(field) Utils::PropertySetter(#field, field)
#define DESCRIPTOR_PROPERTY_SETTER_WITH_CUSTOM_NAME(name, field) Utils::PropertySetter(#name, field)
