#pragma once

#include <Actions/ActionPerformerDescriptor.h>
#include <Actions/SimpleAction.h>
#include <memory>

namespace UnknownEngine
{
	namespace IO
	{
		class ActionsFactory
		{
		public:
			static std::unique_ptr<SimpleAction> createSimpleAction( const UnknownEngine::IO::SimpleActionPerformerDescriptor& desc );
		};
	}
}