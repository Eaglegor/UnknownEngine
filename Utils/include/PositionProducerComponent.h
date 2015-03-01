#pragma once

namespace UnknownEngine
{
	namespace Utils
	{
		class PositionProducerComponent : public Core::IComponent
		{
		public:

			static Core::ComponentType getCType()
			{
				return Core::ComponentType("PositionProducerComponent");
			}

		};
	}
}