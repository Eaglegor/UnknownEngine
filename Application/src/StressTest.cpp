#include <StressTest.h>
#include <ResourceManager/DataProviders/IDataProvider.h>
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

void StressTest::init ()
{
	if(update_frame_provider) update_frame_provider->addListener(this);
	
	was_init = true;
	
	ResourceManager* rm = UnknownEngine::Core::ResourceManager::getSingleton();
	
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
		ComponentsManager* mgr = UnknownEngine::Core::ComponentsManager::getSingleton();
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

