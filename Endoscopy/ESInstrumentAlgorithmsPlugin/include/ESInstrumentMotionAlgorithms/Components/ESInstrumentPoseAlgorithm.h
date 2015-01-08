#pragma once

#include <ComponentSystem/BaseComponent.h>
#include <ESInstrumentMotionAlgorithms/Descriptors/ESInstrumentPoseAlgorithmDesc.h>
#include <MessageSystem/MessageSender.h>
#include <ExportedMessages/TransformChangedMessage.h>
#include <memory>
#include <ValueRangeMapper.h>

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
			Core::MessageSender<Core::TransformChangedMessage> transform_changed_message_sender;

			Utils::ValueRangeMapper<Math::Scalar> x_range_mapper;
			Utils::ValueRangeMapper<Math::Scalar> y_range_mapper;
			Utils::ValueRangeMapper<Math::Scalar> z_range_mapper;
			Utils::ValueRangeMapper<Math::Scalar> d_range_mapper;
		};
	}
}