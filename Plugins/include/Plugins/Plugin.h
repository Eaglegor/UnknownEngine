#pragma once

#include <Plugins/PluginError.h>
#include <InlineSpecification.h>

namespace UnknownEngine
{
	namespace Core
	{

		class PluginsManager;
		struct SubsystemDesc;

		class Plugin
		{

			public:
				virtual ~Plugin (){}

				UNKNOWNENGINE_INLINE
				std::string getName() const{ return name; }

				UNKNOWNENGINE_INLINE
				void setName(const std::string& name) {this->name = name;}

				virtual bool install (PluginsManager* plugins_manager, const SubsystemDesc &desc )  = 0;

				virtual bool init ()  = 0;

				virtual bool shutdown ()  = 0;

				virtual bool uninstall ()  = 0;

			private:
				std::string name;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
