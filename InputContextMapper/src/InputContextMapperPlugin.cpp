#include <stdafx.h>
#include <InputContextMapper.h>
#include <InputContextMapperPlugin.h>
#include <InputContextMapperDescriptorGetter.h>
#include <ExportedMessages/InputContext/AddSimpleActionMessage.h>
#include <ExportedMessages/InputContext/AddRangeActionMessage.h>
#include <InputContextMapperFactory.h>
#include <Logging.h>
#include <MessageSystem/MessageDictionary.h>

namespace UnknownEngine
{
    namespace IO
    {

		InputContextMapperPlugin::InputContextMapperPlugin(const char* name):
		Core::BasePlugin(name)
		{}
		
		InputContextMapperPlugin::~InputContextMapperPlugin(){}

        bool InputContextMapperPlugin::install(Core::PluginsManager *plugins_manager, Core::SubsystemDesc const &desc) {
            
			factory.reset(new InputContextMapperFactory());
			
			Core::ComponentsManager::getSingleton()->addComponentFactory(factory.get());
			
            return true;
        }

        bool InputContextMapperPlugin::init() {
            return true;
        }

        bool InputContextMapperPlugin::shutdown() {
            return true;
        }

        bool InputContextMapperPlugin::uninstall() {
			
			Core::ComponentsManager::getSingleton()->removeComponentFactory(factory.get());
			factory.reset();
            return true;
        }

    }
}