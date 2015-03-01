#include <StressTest.h>
#include <NameGenerators/NameGenerator.h>
#include <ComponentSystem/ComponentsManager.h>
#include <ComponentSystem/Entity.h>
#include <ComponentSystem/ComponentDesc.h>
#include <ResourceManager/DataProviders/DataProviderDesc.h>
#include <ResourceManager/ResourceManager.h>
#include <Engine.h>
#include <iostream>

using namespace UnknownEngine::Core;
using namespace UnknownEngine::Utils;

void StressTest::init ( EngineContext* engine_context )
{
	if(update_frame_provider) update_frame_provider->addListener(this);
	
	this->engine_context = engine_context;
	
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
		UnknownEngine::RELEASE_DATA_PROVIDER(dp);
	}
	
	if(update_frame_provider) update_frame_provider->removeListener(this);
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
			
			props.set<std::string>("update_frame_provider_name", MAIN_LOOP_COMPONENT_NAME);
			
			desc.descriptor = props;
			
			transform.set<std::string>("input_context_mapping_provider_name", "System.InputContextMapper");
			
			//MessageSenderRules rules;
			//MessageSenderRule rule;
			//rule.message_type_name = "Engine.TransformChangedMessage";
			//rules.push_back(rule);
			//desc.sender_rules = rules;
			
		}
		entity->createComponent(desc);
		
		desc.name = name_generator->generateName();
		desc.type = "Ogre.Renderable";
		{
			Properties props;
			props.set<IDataProvider*>("mesh_ptr_provider", data_providers[1]);
			props.set<std::string>("log_level", "none");
			
			Properties material;
			material.set<std::string>("material_name", "BaseWhiteNoLighting");
			props.set<Properties>("Material", material);
			
			Properties transform;
			transform.set<std::string>("position", "Vector3(x: " + std::to_string(x_position) + ", y:0, z:" + std::to_string(z_position) + ")");
			props.set<Properties>("InitialTransform", transform);
			
			props.set<std::string>("transform_provider_name", rotation_component_name);
			
			desc.descriptor = props;
		}
		
		{
			//MessageListenerRules rules;
			//MessageListenerRule rule;
			//rule.message_type_name = "Engine.TransformChangedMessage";
			//rule.receive_policy_type_name = "FromSingleSender";
			//rule.receive_policy_options.set<std::string>("sender_name", rotation_component_name);
			//rules.push_back(rule);
			
			//desc.listener_rules = rules;
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

void StressTest::onUpdateFrame ( UnknownEngine::Math::Scalar dt )
{
	time_counter.tick();
	if(time_counter.getElapsedTime() > 20.0f)
	{
		time_counter.resetElapsedTime();
		generateObjects(1000);
	}
}

