#pragma once

#include <InlineSpecification.h>
#include <Plugins/BasePlugin.h>
#include <Plugins/SubsystemDesc.h>
#include <LogHelper.h>
#include <memory>

namespace UnknownEngine
{

	namespace Core
	{
		struct SubsystemDesc;
	}

	namespace Endoscopy
	{
		class ESGUIComponentsFactory;
		
		class ESGUIPlugin: public Core::BasePlugin
		{
			public:
				ESGUIPlugin(const char* name);
				virtual ~ESGUIPlugin();

				virtual bool install(Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc)  override;
				virtual bool init()  override;
				virtual bool shutdown()  override;
				virtual bool uninstall()  override;

			private:
				Core::SubsystemDesc desc;
				std::unique_ptr<ESGUIComponentsFactory> components_factory;
		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
