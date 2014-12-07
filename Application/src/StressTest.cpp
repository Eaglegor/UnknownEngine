#include <StressTest.h>
#include <MessageBuffers/InstantForwardMessageBuffer.h>
#include <NameGenerators/NameGenerator.h>
#include <ComponentSystem/ComponentsManager.h>
#include <ComponentSystem/Entity.h>
#include <ComponentSystem/ComponentDesc.h>
#include <DataProvider/DataProviderDesc.h>
#include <ResourceManager.h>
#include <MessageSystem/MessageDispatcher.h>

using namespace UnknownEngine::Core;
using namespace UnknownEngine::Utils;
using namespace UnknownEngine::Loader;

void StressTest::init ( EngineContext* engine_context )
{
	this->engine_context = engine_context;
	
	MessageListenerRules rules;
	MessageListenerRule rule;
	rule.message_type_name = UpdateFrameMessage::getTypeName();
	rules.push_back(rule);
	
	listener.reset(new BaseMessageListener("StressTest", engine_context));

	engine_context->getMessageDispatcher()->setListenerRules(listener->getName(), rules);
	
	{
		typedef UpdateFrameMessage MessageType;
		typedef InstantForwardMessageBuffer<UpdateFrameMessage> BufferType;
		
		listener->createMessageBuffer<MessageType, BufferType>(this, &StressTest::onUpdate);
	}
	
	listener->registerAtDispatcher();
	was_init = true;
	
	ResourceManager* rm = engine_context->getResourceManager();
	
	DataProviderDesc dp_desc;
	dp_desc.name = "TeapotMesh";
	dp_desc.type = "Loader.MeshData.AssimpMeshDataLoader";
	{
		Properties props;
		props.set<std::string>("filename", "media/models/teapot.obj");
		props.set<std::string>("log_level", "none");
		
		Properties postprocessing;
		postprocessing.set<std::string>("generate_normals", "true");
		
		props.set<Properties>("Postprocessing", postprocessing);
		dp_desc.descriptor = props;
	}
	IDataProvider* dp = rm->createDataProvider(dp_desc);
	dp->startLoading();
	data_providers.push_back(dp);
	
	
	dp_desc.name = "OgreAdaptedTeapotMesh";
	dp_desc.type = "Loader.OgreMeshPtr.OgreMeshPtrFromMeshDataProvider";
	{
		Properties props;
		props.set<IDataProvider*>("mesh_data_provider", data_providers[0]);
		props.set<std::string>("log_level", "none");
		dp_desc.descriptor = props;
	}
	dp = rm->createDataProvider(dp_desc);
	dp->startLoading();
	data_providers.push_back(dp);
	
}

void StressTest::shutdown()
{
	if(!was_init) return;
	for(IDataProvider* dp : data_providers)
	{
		dp->release();
	}
	listener->unregisterAtDispatcher();
}

void StressTest::generateObjects ( size_t count )
{
	for(size_t i = 0; i < count; ++i)
	{
		ComponentsManager* mgr = engine_context->getComponentsManager();
		NameGenerator* name_generator = mgr->getNameGenerator();
		IEntity* entity = mgr->createEntity(name_generator->generateName());
		
		std::string rotation_component_name;
		
		ComponentDesc desc;
		rotation_component_name = name_generator->generateName();
		desc.name = rotation_component_name;
		desc.type = "Behavior.SimpleRotation";
		{
			Properties props;

			Properties transform;
			transform.set<std::string>("position", "Vector3(x: " + std::to_string(x_position) + ", y:0, z:" + std::to_string(z_position) + ")");
			props.set<Properties>("InitialTransform", transform);
			
			desc.descriptor = props;
		}
		entity->createComponent(desc);
		
		desc.name = name_generator->generateName();
		desc.type = "Graphics.Renderable";
		{
			Properties props;
			props.set<IDataProvider*>("mesh_ptr_provider", data_providers[1]);
			props.set<std::string>("log_level", "none");
			
			Properties material;
			material.set<std::string>("material_name", "Simple");
			props.set<Properties>("Material", material);
			
			Properties transform;
			transform.set<std::string>("position", "Vector3(x: " + std::to_string(x_position) + ", y:0, z:" + std::to_string(z_position) + ")");
			props.set<Properties>("InitialTransform", transform);
			
			desc.descriptor = props;
		}
		
		{
			MessageListenerRules rules;
			MessageListenerRule rule;
			rule.message_type_name = "Engine.TransformChangedMessage";
			rule.receive_policy_type_name = "FromSingleSender";
			rule.receive_policy_options.set<std::string>("sender_name", rotation_component_name);
			rules.push_back(rule);
			
			engine_context->getMessageDispatcher()->setListenerRules(desc.name.c_str(), rules);
		}
		
		entity->createComponent(desc);
		
		x_position += 10;
		if(x_position > 200) {
			z_position -= 10;
			x_position = 0;
		}
		objects_count++;
	}
	std::cout << "Objects count: " << objects_count << std::endl;
}

void StressTest::onUpdate ( const UpdateFrameMessage& msg )
{
	time_counter.tick();
	if(time_counter.getElapsedTime() > 0.2f)
	{
		time_counter.resetElapsedTime();
		generateObjects(10);
	}
}
