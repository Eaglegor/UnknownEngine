#pragma once

#include <Profiling/TimeCounter.h>
#include <ComponentInterfaces/Engine/UpdateFrameListenerComponent.h>
#include <ComponentInterfaces/Engine/FrameUpdaterComponent.h>
#include <ComponentSystem/ComponentInterfacePtr.h>
#include <vector>

namespace UnknownEngine
{
	namespace Core
	{
		class IDataProvider;
	}
}

class StressTest : public UnknownEngine::ComponentInterfaces::UpdateFrameListenerComponent
{
public:
	StressTest(UnknownEngine::Core::IComponent *update_frame_provider):
	x_position(0.0f),
	z_position(0.0f),
	was_init(false),
	objects_count(0),
	update_frame_provider(update_frame_provider)
	{}
	
	void init();
	void shutdown();

	void generateObjects(size_t count);
	
	virtual void onUpdateFrame ( UnknownEngine::Math::Scalar dt );
	
private:
	std::vector<UnknownEngine::Core::IDataProvider*> data_providers;
	
	float x_position;
	float z_position;
	bool was_init;
	size_t objects_count;
	
	UnknownEngine::Utils::TimeCounter time_counter;
	
	UnknownEngine::Core::ComponentInterfacePtr<UnknownEngine::ComponentInterfaces::FrameUpdaterComponent> update_frame_provider;
};