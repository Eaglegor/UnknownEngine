#include <stdafx.h>

#include <Listeners/OgreUpdateFrameListener.h>
#include <OgreRenderSubsystem.h>
#include <MessageSystem/PackedMessage.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		OgreUpdateFrameListener::OgreUpdateFrameListener ( const std::string &name, OgreRenderSubsystem *render_system ):
		name(name),
		render_system ( render_system )
		{
		}

		void OgreUpdateFrameListener::processMessage ( const Core::PackedMessage &msg )
		{
			render_system->onFrameUpdated ( msg.get<Core::UpdateFrameMessage>() );
		}
		
		const char* OgreUpdateFrameListener::getName() const
		{
			return name.c_str();
		}

	} // namespace Graphics
} // namespace UnknownEngine
