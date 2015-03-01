#pragma once

#include <ComponentSystem/BaseComponent.h>
#include <ESInstrumentMotionAlgorithms/Descriptors/ESInstrumentPoseAlgorithmDesc.h>
#include <ComponentInterfaces/ESHardware/ESHardwareStateListener.h>
#include <memory>
#include <ValueRangeMapper.h>
#include <ComponentSystem/ComponentInterfacePtr.h>

namespace UnknownEngine
{
	namespace Core
	{
		class BaseMessageListener;
	}

	namespace Endoscopy
	{

		class ESInstrumentPoseAlgorithm : 
		public Core::BaseComponent,
		public ComponentInterfaces::ESHardwareStateListener
		{
		public:
			ESInstrumentPoseAlgorithm(const char* name, const ESInstrumentPoseAlgorithmDesc& desc);

			static constexpr const char* getTypeName() {return "Endoscopy.Algorithms.InstrumentPose";}
			virtual Core::ComponentType getType() const override;
			
			virtual bool init () override;
			virtual void shutdown() override;
			
			virtual void onHardwareStateUpdate ( Math::Scalar x, Math::Scalar y, Math::Scalar z, Math::Scalar d ) override;
			
		private:
			ESInstrumentPoseAlgorithmDesc desc;

			Utils::ValueRangeMapper<Math::Scalar> x_range_mapper;
			Utils::ValueRangeMapper<Math::Scalar> y_range_mapper;
			Utils::ValueRangeMapper<Math::Scalar> z_range_mapper;
			Utils::ValueRangeMapper<Math::Scalar> d_range_mapper;
		};
	}
}