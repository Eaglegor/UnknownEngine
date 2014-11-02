#pragma once

#include <AlignedNew.h>
#include <string>
#include <DataProviders/OgreMeshPtrProvider.h>
#include <ExportedMessages/LogMessage.h>
#include <Transform/Transform.h>

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

			Math::Transform initial_transform;
			Utils::LogSeverity log_level;

			MaterialDesc material_desc;

			bool throw_exception_on_missing_mesh_data;

			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;

			OgreRenderableComponentDescriptor() :
				mesh_data_provider ( nullptr ),
				initial_transform ( Math::Transform::getIdentity() ),
				log_level ( Utils::LogSeverity::NONE ),
				throw_exception_on_missing_mesh_data ( true )
			{}
		};
	}
}
