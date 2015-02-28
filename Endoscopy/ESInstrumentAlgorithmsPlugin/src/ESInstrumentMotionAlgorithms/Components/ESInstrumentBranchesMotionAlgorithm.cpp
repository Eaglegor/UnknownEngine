#include <ESInstrumentMotionAlgorithms/Components/ESInstrumentBranchesMotionAlgorithm.h>

namespace UnknownEngine
{
	namespace Endoscopy
	{
		
		ESInstrumentBranchesMotionAlgorithm::ESInstrumentBranchesMotionAlgorithm ( const char* name, ESInstrumentBranchesMotionAlgorithmDesc& desc ):
		BaseComponent ( name )//,
		//desc(desc)
		{
		}

		Core::ComponentType ESInstrumentBranchesMotionAlgorithm::getType() const
		{
			return Core::ComponentType(getTypeName());
		}
		
		bool ESInstrumentBranchesMotionAlgorithm::init ()
		{
			return true;
		}

		void ESInstrumentBranchesMotionAlgorithm::shutdown()
		{
		}
		
	}
}