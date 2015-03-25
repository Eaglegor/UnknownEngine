#pragma once

#include <InlineSpecification.h>
#include <Plugins/BasePlugin.h>
#include <Plugins/SubsystemDesc.h>
#include <LogHelper.h>

namespace UnknownEngine
{

	namespace Core
	{
		struct SubsystemDesc;
	}

	namespace Endoscopy
	{
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
		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
