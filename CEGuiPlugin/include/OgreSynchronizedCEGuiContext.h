#pragma once

#include <OgreCEGuiContext.h>

namespace CEGUI
{
	class OgreRenderer;
}

namespace UnknownEngine
{
	namespace GUI
	{
		struct OgreCEGuiContextDesc;
		
		class OgreSynchronizedCEGuiContext : 
		public OgreCEGuiContext
		{
		public:
			OgreSynchronizedCEGuiContext(const char* name, const OgreCEGuiContextDesc &desc);
			~OgreSynchronizedCEGuiContext();
			
			constexpr static const char* getTypeName(){ return "CEGui.SynchronizedOgreContext"; }
			virtual Core::ComponentType getType() const {return getTypeName();}
			
			virtual bool init();
			virtual void shutdown();
		};
	}
}