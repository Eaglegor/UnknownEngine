#pragma once

#include <Descriptors/Components/Lights/OgreLightSettings.h>
#include <Transform/Transform.h>
#include <AlignedNew.h>
#include <LogSeverity.h>
#include <Descriptors/DescriptorUtils.h>
#include <Descriptors/CommonDescriptors/TransformDescriptor.h>

namespace UnknownEngine
{
	namespace Core
	{
		class IComponent;
	}

	namespace Graphics
	{
	UNKNOWNENGINE_ALIGNED_STRUCT ( 16 ) OgreDirectionalLightComponentDescriptor :
		public Utils::Descriptor
		{
			using Utils::Descriptor::operator=;
			
			OgreLightSettings light_settings;

			Utils::OptionalDescriptor<Utils::TransformDescriptor> initial_transform;
			Utils::OptionalProperty<Core::LogSeverity> log_level;

			Utils::OptionalProperty<Math::Vector3> initial_look_at;
			Utils::OptionalProperty<Math::Vector3> initial_direction;

			Utils::OptionalComponentDependency transform_provider;

			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;

			OgreDirectionalLightComponentDescriptor() :
				log_level ( Core::LogSeverity::NONE )
			{
				UEDESC_ADD_NESTED_DESCRIPTOR ( light_settings );
				UEDESC_ADD_NESTED_DESCRIPTOR ( initial_transform );
				UEDESC_ADD_FIELD ( initial_look_at );
				UEDESC_ADD_FIELD ( initial_direction );
				UEDESC_ADD_FIELD ( transform_provider );
			}
		};
	}
}

#include <AlignedAnyHolder.h>
ALIGNED_BOOST_ANY_HOLDER ( UnknownEngine::Graphics::OgreDirectionalLightComponentDescriptor );
