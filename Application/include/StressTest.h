#pragma once

#include <ExportedMessages/UpdateFrameMessage.h>
#include <EngineContext.h>
#include <MessageSystem/BaseMessageListener.h>
#include <ResourceManager/DataProviders/IDataProvider.h>
#include <Profiling/TimeCounter.h>

class StressTest
{
public:
	StressTest():
	x_position(0.0f),
	z_position(0.0f),
	was_init(false),
	objects_count(0)
	{}
	
	void init(UnknownEngine::Core::EngineContext* engine_context);
	void shutdown();
	void onUpdate(const UnknownEngine::Core::UpdateFrameMessage &msg);

	void generateObjects(size_t count);
	
private:
	std::vector<UnknownEngine::Core::IDataProvider*> data_providers;
	
	UnknownEngine::Core::EngineContext* engine_context;
	float x_position;
	float z_position;
	bool was_init;
	size_t objects_count;
	std::unique_ptr<UnknownEngine::Core::BaseMessageListener> listener;
	
	UnknownEngine::Utils::TimeCounter time_counter;
};