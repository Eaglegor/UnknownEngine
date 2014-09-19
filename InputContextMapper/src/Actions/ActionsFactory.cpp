#include <Actions/ActionsFactory.h>

#include <Actions/SimpleSingleEventAction.h>
#include <Actions/SimpleContinuousEventAction.h>

namespace UnknownEngine
{
	namespace IO
	{
		std::unique_ptr< SimpleAction > ActionsFactory::createSimpleAction( const SimpleActionPerformerDescriptor& desc )
		{
			switch(desc.type)
			{
				case ActionType::SINGLE_ACTION:
				{
					return std::move( std::unique_ptr<SimpleAction>(new SimpleSingleEventAction(desc.callback)) );
				}
				case ActionType::CONTINUOUS_ACTION:
				{
					return std::move( std::unique_ptr<SimpleAction>(new SimpleContinuousAction(desc.callback)) );
				}
			}
		}
	}
}