#pragma once

#include <Properties/Properties_fwd.h>
#include <Descriptors/Components/Lights/OgreLightSettings.h>

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
