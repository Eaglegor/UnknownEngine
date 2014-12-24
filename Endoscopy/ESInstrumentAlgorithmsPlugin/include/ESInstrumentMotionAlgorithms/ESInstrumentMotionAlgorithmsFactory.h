#pragma once

#include <ComponentSystem/BaseComponentFactory.h>

namespace UnknownEngine
{
	namespace Endoscopy
	{
		class ESInstrumentMotionAlgorithmsFactory : public Core::BaseComponentFactory
		{
		public:
			ESInstrumentMotionAlgorithmsFactory();
			virtual const char* getName() const;
			
		private:
			Core::IComponent* createInstrumentPoseAlgorithm(const Core::ComponentDesc& desc);
			Core::IComponent* createInstrumentBranchesMotionAlgorithm(const Core::ComponentDesc& desc);
			
		};
	}
}