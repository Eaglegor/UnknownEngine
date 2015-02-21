#pragma once

#include <AlignedNew.h>
#include <string>
#include <DataProviders/OgreMeshPtrProvider.h>
#include <ExportedMessages/LogMessage.h>
#include <Transform/Transform.h>
#include <ComponentInterfaces/Transform/TransformHolderComponent.h>
#include <ComponentSystem/IComponent.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		UNKNOWNENGINE_ALIGNED_STRUCT ( 16 ) OgreRenderableComponentDescriptor
		{

			struct MaterialDesc
			{
				std::string name;

				MaterialDesc() : name ( "BaseWhiteNoLighting" ) {};
			};

			OgreMeshPtrProvider* mesh_data_provider;

			Core::IComponent* transform_provider;
			
			Math::Transform initial_transform;
			Core::LogSeverity log_level;

			MaterialDesc material_desc;

			bool throw_exception_on_missing_mesh_data;

			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;

			OgreRenderableComponentDescriptor() :
				mesh_data_provider ( nullptr ),
				transform_provider(nullptr),
				initial_transform ( Math::Transform::getIdentity() ),
				log_level ( Core::LogSeverity::NONE ),
				throw_exception_on_missing_mesh_data ( true )
			{}
		};
	}
}

#include <AlignedAnyHolder.h>
ALIGNED_BOOST_ANY_HOLDER(UnknownEngine::Graphics::OgreRenderableComponentDescriptor);