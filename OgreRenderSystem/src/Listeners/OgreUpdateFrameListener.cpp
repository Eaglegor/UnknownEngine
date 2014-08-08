#include <stdafx.h>

#include <Listeners/OgreUpdateFrameListener.h>
#include <OgreRenderSubsystem.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		OgreUpdateFrameListener::OgreUpdateFrameListener ( const std::string &name, OgreRenderSubsystem *render_system )
			: IMessageListener ( name ),
			  render_system ( render_system )
		{
		}

		void OgreUpdateFrameListener::processMessage ( const Core::PackedMessage &msg )
		{
			render_system->onFrameUpdated ( message_unpacker.unpackMessage ( msg ) );
		}

	} // namespace Graphics
} // namespace UnknownEngine
