#pragma once

#include <ExportedMessages/UpdateFrameMessage.h>
#include <EngineContext.h>
#include <MessageSystem/BaseMessageListener.h>
#include <DataProvider/IDataProvider.h>

class StressTest
{
public:
	StressTest():
	was_init(false),
	counter(0),
	x_position(0.0f),
	z_position(0.0f),
	objects_count(0)
	{}
	
	void init(UnknownEngine::Core::EngineContext* engine_context);
	void shutdown();
	void onUpdate(const UnknownEngine::Core::UpdateFrameMessage &msg);

	void generateObjects(size_t count);
	
private:
	std::vector<UnknownEngine::Loader::IDataProvider*> data_providers;
	
	UnknownEngine::Core::EngineContext* engine_context;
	size_t counter;
	float x_position;
	float z_position;
	bool was_init;
	size_t objects_count;
	std::unique_ptr<UnknownEngine::Core::BaseMessageListener> listener;
};