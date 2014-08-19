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

			Core::Transform initial_transform;
			Core::LogMessage::Severity log_level;

			MaterialDesc material_desc;

			bool throw_exception_on_missing_mesh_data;

			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;

			OgreRenderableComponentDescriptor() :
				mesh_data_provider ( nullptr ),
				initial_transform ( Core::Transform::getIdentity() ),
				log_level ( Core::LogMessage::Severity::LOG_SEVERITY_NONE ),
				throw_exception_on_missing_mesh_data ( true )
			{}
		};
	}
}
