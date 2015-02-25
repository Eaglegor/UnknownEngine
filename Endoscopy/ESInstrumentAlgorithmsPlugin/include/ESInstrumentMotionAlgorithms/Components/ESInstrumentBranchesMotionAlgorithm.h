#pragma once

#include <ComponentSystem/BaseComponent.h>
#include <ESInstrumentMotionAlgorithms/Descriptors/ESInstrumentBranchesMotionAlgorithmDesc.h>

namespace UnknownEngine
{
	namespace Endoscopy
	{
		class ESInstrumentBranchesMotionAlgorithm : public Core::BaseComponent
		{
		public:
			ESInstrumentBranchesMotionAlgorithm(const char* name, ESInstrumentBranchesMotionAlgorithmDesc &desc);
			
			static constexpr const char* getTypeName(){return "Endoscopy.Algorithms.BranchesMotion";}
			virtual Core::ComponentType getType() const;

			virtual bool init ();
			virtual void shutdown();

		private:
			ESInstrumentBranchesMotionAlgorithmDesc desc;
			
		};
	}
}