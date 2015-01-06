#include <ESInstrumentMotionAlgorithms/ESInstrumentMotionAlgorithmsFactory.h>
#include <ESInstrumentMotionAlgorithms/Components/ESInstrumentBranchesMotionAlgorithm.h>
#include <ESInstrumentMotionAlgorithms/Components/ESInstrumentPoseAlgorithm.h>
#include <ComponentSystem/ComponentDesc.h>

namespace UnknownEngine
{
	namespace Endoscopy
	{
		ESInstrumentMotionAlgorithmsFactory::ESInstrumentMotionAlgorithmsFactory()
		{
			{
				CreatableObjectDesc desc;
				desc.type = Core::ComponentType(ESInstrumentPoseAlgorithm::getTypeName());
				desc.creator = std::bind(&ESInstrumentMotionAlgorithmsFactory::createInstrumentPoseAlgorithm, this, std::placeholders::_1);
				registerCreator(desc);
			}
			{
				CreatableObjectDesc desc;
				desc.type = Core::ComponentType(ESInstrumentBranchesMotionAlgorithm::getTypeName());
				desc.creator = std::bind(&ESInstrumentMotionAlgorithmsFactory::createInstrumentBranchesMotionAlgorithm, this, std::placeholders::_1);
				registerCreator(desc);
			}
		}

		Core::IComponent* ESInstrumentMotionAlgorithmsFactory::createInstrumentPoseAlgorithm ( const Core::ComponentDesc& desc )
		{
			ESInstrumentPoseAlgorithmDesc alg_desc;
			return new ESInstrumentPoseAlgorithm(desc.name.c_str(), alg_desc);
		}

		Core::IComponent* ESInstrumentMotionAlgorithmsFactory::createInstrumentBranchesMotionAlgorithm ( const Core::ComponentDesc& desc )
		{
			ESInstrumentBranchesMotionAlgorithmDesc alg_desc;
			return new ESInstrumentBranchesMotionAlgorithm(desc.name.c_str(), alg_desc);
		}
		
		const char* ESInstrumentMotionAlgorithmsFactory::getName() const
		{
			return "ESInstrumentAlgorithmsPlugin.ESInstrumentMotionAlgorithmsFactory";
		}
		
	}
}