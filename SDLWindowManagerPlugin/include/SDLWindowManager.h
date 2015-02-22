#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include <Exception.h>
#include <Scalar.h>
#include <ComponentSystem/BaseComponent.h>
#include <LogHelper.h>
#include <SDLWindowManagerDescriptor.h>

struct SDL_Window;

namespace UnknownEngine
{
	namespace GUI
	{
		class SDLWindowManager : public Core::BaseComponent
		{
		public:
			
			UNKNOWNENGINE_SIMPLE_EXCEPTION(WindowNotFound);
			
			SDLWindowManager(const std::string &name, const SDLWindowManagerDescriptor &desc);
			virtual ~SDLWindowManager();
			
			constexpr static const char* getTypeName(){return "SDL.WindowManager";}
			virtual Core::ComponentType getType() const {return Core::ComponentType(getTypeName());}
			
			void init(const Core::IEntity* parent_entity) override;
			void shutdown() override;

		private:
			SDLWindowManagerDescriptor desc;
			
			Core::LogHelper logger;
			std::string name;
		};
		
	}
}