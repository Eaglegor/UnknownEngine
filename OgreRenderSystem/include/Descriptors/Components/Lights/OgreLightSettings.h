#pragma once

#include <Scalar.h>
#include <boost/optional.hpp>
#include <OgreColourValue.h>
#include <AlignedNew.h>
#include <Descriptors/DescriptorUtils.h>
#include <Parsers/Sections/OgreColourValueParser.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		UNKNOWNENGINE_ALIGNED_STRUCT(16) OgreLightSettings : public Utils::Descriptor
		{
			using Utils::Descriptor::operator=;
			
			struct Attenuation : public Utils::Descriptor
			{
				using Utils::Descriptor::operator=;
				
				Utils::RequiredProperty<Math::Scalar> range;
				Utils::RequiredProperty<Math::Scalar> constant;
				Utils::RequiredProperty<Math::Scalar> linear;
				Utils::RequiredProperty<Math::Scalar> quadratic;
				
				Attenuation()
				{
					UEDESC_ADD_FIELD(range);
					UEDESC_ADD_FIELD(constant);
					UEDESC_ADD_FIELD(linear);
					UEDESC_ADD_FIELD(quadratic);
				}
			};

			Utils::OptionalDescriptor<Attenuation> attenuation;
			Utils::OptionalProperty<bool> cast_shadows;

			Utils::OptionalProperty<Ogre::ColourValue> diffuse_color;
			Utils::OptionalProperty<Ogre::ColourValue> specular_color;
			Utils::OptionalProperty<Math::Scalar> intensity;

			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;

			OgreLightSettings() :
				diffuse_color ( 1, 1, 1 ),
				specular_color ( 1, 1, 1 ),
				intensity ( 1 )
			{
				UEDESC_ADD_NESTED_DESCRIPTOR(attenuation);
				UEDESC_ADD_FIELD(cast_shadows);
				UEDESC_ADD_FIELD(diffuse_color);
				UEDESC_ADD_FIELD(specular_color);
				UEDESC_ADD_FIELD(intensity);
			}

		};
	}
}

#include <AlignedAnyHolder.h>
ALIGNED_BOOST_ANY_HOLDER(UnknownEngine::Graphics::OgreLightSettings);