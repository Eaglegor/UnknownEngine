#pragma once
#include <Components/BaseOgreLightComponent.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		class OgreLightSettingsParser
		{
		public:
			static OgreLightSettings parse( const Core::Properties& light_settings_section );
		};
	}
}
