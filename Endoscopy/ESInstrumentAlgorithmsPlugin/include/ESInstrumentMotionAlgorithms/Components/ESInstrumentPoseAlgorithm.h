#pragma once

#include <ComponentSystem/BaseComponent.h>
#include <ESInstrumentMotionAlgorithms/Descriptors/ESInstrumentPoseAlgorithmDesc.h>
#include <memory>

namespace UnknownEngine
{
	namespace Core
	{
		class BaseMessageListener;
	}

	namespace Endoscopy
	{

		struct ESHardwareOrientationChangedMessage;
		
		class ESInstrumentPoseAlgorithm : public Core::BaseComponent
		{
		public:
			ESInstrumentPoseAlgorithm(const char* name, const ESInstrumentPoseAlgorithmDesc& desc);

			static constexpr const char* getTypeName() {return "Endoscopy.Algorithms.InstrumentPose";}
			virtual Core::ComponentType getType() const;
			
			virtual void init ( const Core::IEntity* parent_entity );
			virtual void shutdown();
			
		private:
			
			void onHardwarePoseUpdate(const ESHardwareOrientationChangedMessage& msg);
			
			ESInstrumentPoseAlgorithmDesc desc;
			std::unique_ptr<Core::BaseMessageListener> listener;
		};
	}
}