#pragma once

#include <ComponentSystem/BaseComponent.h>
#include <ESInstrumentMotionAlgorithms/Descriptors/ESInstrumentPoseAlgorithmDesc.h>
#include <ComponentInterfaces/Modules/Endoscopy/Hardware/ESHardwareStateListener.h>
#include <ComponentInterfaces/Transform/TransformNotifierComponent.h>
#include <memory>
#include <ValueRangeMapper.h>
#include <ComponentSystem/ComponentInterfacePtr.h>
#include <Concurrency/DataStructures/ConcurrentSet.h>
#include <ComponentInterfaces/Modules/Endoscopy/Hardware/ESHardwareStateNotifier.h>
#include <Observer.h>

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
		public ComponentInterfaces::ESHardwareStateListener,
		public ComponentInterfaces::TransformNotifierComponent
		{
		public:
			ESInstrumentPoseAlgorithm(const char* name, const ESInstrumentPoseAlgorithmDesc& desc);

			static constexpr const char* getTypeName() {return "Endoscopy.Algorithms.InstrumentPose";}
			virtual Core::ComponentType getType() const override;
			
			virtual bool init () override;
			virtual void shutdown() override;
			
			virtual void onHardwareStickPoseChanged ( const ESHardwareStickPoseChangedEvent& evt ) override;
			virtual void onBranchesAngleChangedEvent ( const ESHardwareBranchesAngleChangedEvent& evt ) override;
			
			virtual void addListener ( ComponentInterfaces::MovableComponent* movable_component );
			virtual void removeListener ( ComponentInterfaces::MovableComponent* movable_component );
			
			virtual IComponentInterface* getInterface ( const Core::ComponentType& type );
			
		private:
			ESInstrumentPoseAlgorithmDesc desc;

			Utils::ValueRangeMapper<Math::Scalar> x_range_mapper;
			Utils::ValueRangeMapper<Math::Scalar> y_range_mapper;
			Utils::ValueRangeMapper<Math::Scalar> z_range_mapper;
			Utils::ValueRangeMapper<Math::Scalar> d_range_mapper;
			
			Utils::Observer<ComponentInterfaces::MovableComponent> transform_listeners;
			
			Core::ComponentInterfacePtr<ComponentInterfaces::ESHardwareStateNotifier> hardware_controller;
		};
	}
}