Scene [version = 0.2, name = "Test scene"]
{
	Plugins
	{
		OgreRenderSystem [name = "Graphics"]
		AssimpMeshDataLoader [name = "MeshDataLoader"]
		CEGuiPlugin [name = "HUDPlugin"]
		InputContextMapper [name = "InputContextMapper]
		PhysXPlugin [name = "Physics"]
		SDLWindowManagerPlugin [name = "WindowManager"]
		SimpleBehaviorPlugin [name = "Behaviors"]
	}
	
	${global_log_level} = debug
	
	System
	{
		WindowManager : SDLWindowManager
		{
			
		}
	
		GUIWindow : SDLWindow
		{
			title = "Hello"
			width = 800
			height = 600
			log_level = ${global_log_level}
			window_name = TestWindow
			window_title = "Test render window"
			fullscreen = false
			resizable = true
			update_frame_provider = @Engine.MainLoop
		}
		
		RenderSystem : Ogre.RenderSystem
		{
			log_level = ${global_log_level}
			update_frame_provider = @Engine.MainLoop
			
			ConfigFiles
			{
				ogre_plugins_filename = plugins.cfg
				ogre_log_filename = Ogre.log
				ogre_config_filename = ogre.cfg
				ogre_resources_filename = resources.cfg
			}
		}
		
		RenderWindow : Ogre.RenderWindow
		{
			parent_window = @System.GUIWindow
		}
		
		InputContextMapper : InputContextMapper
		{
			log_level = ${global_log_level}
			action_slots_config_file = InputContextMapperConfig/ActionSlots.xml
			input_layout_config_file = InputContextMapperConfig/InputLayout.cfg
			update_frame_provider = @Engine.MainLoop
			keyboard_input_provider = @System.GUIWindow
			mouse_input_provider = @System.GUIWindow
			joystick_input_provider = @System.GUIWindow
		}
		
		EngineStopper : Behavior.SimpleStopper
		{
			input_context_name = Generic
			action_name = StopEngine
			input_context_mapper = @System.InputContextMapper
			stoppable_component = @Engine.Starter
		}

		Physics : PhysXSubsystem
		{
			gravity = Vector3(x:0, y:-9.8, z:0)
			log_level = ${global_log_level}
			enable_profiling = false
			enable_hardware = false
			update_frame_provider = @Engine.MainLoop
		}
		
		HUD : CEGui.SeparateThreadOgreContext
		{
			render_window = @System.RenderWindow
			log_level = info
		}
		
	}
	
	Objects
	{
		EndoscopicHardwareControllers
		{
			Camera : Endoscopy.HardwareController;
		}
		
		EndoscopicPoseAlgorithms
		{
			Camera : Endoscopy.Algorithms.InstrumentPose
			{
				hardware_controller = @EndoscopicHardwareControllers.Camera
			}
		}
		
		MasterScript
		{
			MainModule : Behavior.AngelScript
			{
				script_filename = test.as
			}
		}
		
		MainCamera
		{
			Rotation : Behavior.MouseLook
			{
				input_context_name = MouseLook
				
				InitialTransform
				{
					position = Vector3(x:0, y:10, z:50)
				}
				
				update_frame_provider = @Engine.MainLoop
				input_context_mapper = @System.InputContextMapper
			}
			
			Camera : Ogre.Camera
			{
				render_window = @System.RenderWindow
				log_level = ${global_log_level}
				far_clip_distance = 100
				near_clip_distance = 0.01
				
				InitialTransform
				{
					position = Vector3(x:0, y:10, z:50)
					initial_direction = Vector3(x:0, y:0, z:-50)
				}
			}
			
			CameraTransformProxy : Behavior.TransformProxyComponent
			{
				//transform_provider = @${current_entity}.Rotation
				transform_provider = @EndoscopicPoseAlgorithms.Camera
				transform_receiver = @${current_entity}.Camera
			}
			
			LightComponentS : Ogre.SpotLight
			{
				InitialTransform
				{
					initial_direction = Vector3(x:0, y:0, z:-50)
				}
				
				transform_provider = @${current_entity}.Rotation
				log_level = ${global_log_level}
				
				LightSettings
				{
					intensity = 1
					diffuse_color = Colour(r:1, g:1, b:1)
					specular_color = Colour(r:1, g:1, b:1)
					spotlight_inner_angle = 5
					spotlight_outer_angle = 20
				}
			}
		}
		
		Lighting
		{
			LightComponentD : Ogre.DirectionalLight
			{
				InitialTransform
				{
					initial_direction = Vector3(x:0, y:-50, z:-50)
				}
				
				log_level = ${global_log_level}
				
				LightSettings
				{
					intensity = 1
					diffuse_color = Colour(r:1, g:1, b:1)
					specular_color = Colour(r:1, g:1, b:1)
				}
			}
		}
		
	}
}