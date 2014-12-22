#include <ESInstrumentMotionAlgorithms/Components/ESInstrumentPoseAlgorithm.h>

namespace UnknownEngine
{
	namespace Endoscopy
	{
		
		ESInstrumentPoseAlgorithm::ESInstrumentPoseAlgorithm ( const char* name, const ESInstrumentPoseAlgorithmDesc& desc ):
		BaseComponent ( name ),
		desc(desc)
		{
		}

		Core::ComponentType ESInstrumentPoseAlgorithm::getType() const
		{
			return Core::ComponentType(getTypeName());
		}

		void ESInstrumentPoseAlgorithm::init ( const Core::IEntity* parent_entity )
		{
		}

		void ESInstrumentPoseAlgorithm::shutdown()
		{
		}

	}
}