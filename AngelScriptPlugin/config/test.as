// Funcdefs for callbacks
funcdef void UpdateFrameCallback(const Core::UpdateFrameMessage&in);

std::string module_name;

class State
{
	void processMessage(const Core::UpdateFrameMessage&in msg){};
};


State @current_state;

State @first_state;
State @second_state;
State @third_state;

Core::ILogger@ logger;

class FirstState : State
{
	FirstState(){}
	
	void processMessage(const Core::UpdateFrameMessage&in msg)
	{
		Core::ResourceManager@ rm = engine_context.getResourceManager();
	
		LOG_INFO(logger, "Info message");
		LOG_WARNING(logger, "Warning message");
		LOG_ERROR(logger, "Error message");
		LOG_DEBUG(logger, "Debug message");
	
		Core::DataProviderDesc dp_desc;
		dp_desc.name = "TeapotMesh";
		dp_desc.type = "Loader.MeshData.AssimpMeshDataLoader";
		{
			Core::Properties props;
			props.setString("filename", "media/models/teapot.obj");
			props.setString("log_level", "none");
			
			Core::Properties postprocessing;
			postprocessing.setString("generate_normals", "true");
			
			props.setNestedProperties("Postprocessing", postprocessing);
			dp_desc.descriptor = props;
		}
		Core::IDataProvider@ dp = rm.createDataProvider(dp_desc);
		dp.startLoading();

		
		dp_desc.name = "OgreAdaptedTeapotMesh";
		dp_desc.type = "Loader.OgreMeshPtr.OgreMeshPtrFromMeshDataProvider";
		{
			Core::Properties props;
			props.setDataProvider("mesh_data_provider", dp);
			props.setString("log_level", "none");
			dp_desc.descriptor = props;
		}
		@dp = rm.createDataProvider(dp_desc);
		dp.startLoading();
		
		
		Core::ComponentsManager@ mgr = engine_context.getComponentsManager();
		Utils::NameGenerator@ name_generator = mgr.getNameGenerator();
		Core::IEntity@ entity = mgr.createEntity(name_generator.generateName());
		
		std::string rotation_component_name;
		
		Core::ComponentDesc desc;
		rotation_component_name = name_generator.generateName();
		desc.name = rotation_component_name;
		desc.type = "Behavior.SimpleRotation";
		{
			Core::Properties props;

			Core::Properties transform;
			transform.setString("position", "Vector3(x:0, y:20, z:0)");
			props.setNestedProperties("InitialTransform", transform);
			
			desc.descriptor = props;
		}
		{
			Core::MessageSenderRules rules;
			Core::MessageSenderRule rule;
			rule.message_type_name = "Engine.TransformChangedMessage";
			rules.push_back(rule);
			
			engine_context.getMessageDispatcher().setSenderRules(desc.name, rules);
		}
		entity.createComponent(desc);

		desc.name = name_generator.generateName();
		desc.type = "Graphics.Renderable";
		{
			Core::Properties props;
			props.setDataProvider("mesh_ptr_provider", dp);
			props.setString("log_level", "none");
			
			Core::Properties material;
			material.setString("material_name", "Simple");
			props.setNestedProperties("Material", material);
			
			Core::Properties transform;
			transform.setString("position", "Vector3(x: 0, y:20, z:0)");
			props.setNestedProperties("InitialTransform", transform);
			
			desc.descriptor = props;
		}
		
		{
			Core::MessageListenerRules rules;
			Core::MessageListenerRule rule;
			rule.message_type_name = "Engine.TransformChangedMessage";
			rule.receive_policy_type_name = "FromSingleSender";
			rule.receive_policy_options.setString("sender_name", rotation_component_name);
			rules.push_back(rule);
			
			engine_context.getMessageDispatcher().setListenerRules(desc.name, rules);
		}
		
		entity.createComponent(desc);

		@current_state = second_state;
	}
}

class SecondState : State
{
	SecondState(){}
	
	void processMessage(const Core::UpdateFrameMessage&in msg)
	{
		//print("2");
		//@current_state = third_state;
	}
};

class ThirdState : State
{
	ThirdState(){}
	
	void processMessage(const Core::UpdateFrameMessage&in msg)
	{
		print("3");
		//@current_state = first_state;
	}
}

class Listener
{
	Listener()
	{
		@update_frame = Core::MessageListener<Core::UpdateFrameMessage>(module_name);
		UpdateFrameCallback @cb = UpdateFrameCallback(this.onMessage);
		update_frame.setMessageProcessingCallback(cb);
		update_frame.registerAtDispatcher();
	}

	~Listener()
	{
		update_frame.unregisterAtDispatcher();
	}
	
	void onMessage(const Core::UpdateFrameMessage&in msg){
		current_state.processMessage(msg);
	}
	
	Core::MessageListener<Core::UpdateFrameMessage>@ update_frame;
};

Listener@ listener;

void init(const std::string &in name)
{
	// Store out name
	module_name = name;

	// Initializing states
	@first_state = FirstState();
	@second_state = SecondState();
	@third_state = ThirdState();
	@current_state = first_state;
	
	// Initializing listener
	@listener = Listener();
	
	@logger = CREATE_LOGGER(module_name, Core::LogSeverity::DEBUG);
}

void shutdown()
{
	
}

int counter = 0;
