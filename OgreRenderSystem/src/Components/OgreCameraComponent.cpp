#include <Components/OgreCameraComponent.h>
#include <OgreRenderSubsystem.h>
#include <OgreSceneManager.h>
#include <Converters/OgreVector3Converter.h>
#include <Converters/OgreQuaternionConverter.h>
#include <Listeners/OgreCameraComponentListener.h>
#include <MessageSystem/MessageListenerDesc.h>
#include <EngineContext.h>
#include <MessageSystem/MessageDispatcher.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		UnknownEngine::Core::ComponentType OgreCameraComponent::getType()
		{
		  return type;
		}

		void OgreCameraComponent::shutdown()
		{
		  this->scene_node->detachObject(this->camera);
		}

		void OgreCameraComponent::start()
		{
		  this->scene_node->attachObject(this->camera);
		}

		void OgreCameraComponent::init ( const UnknownEngine::Core::Entity* parent_entity )
		{
		  this->camera = render_subsystem->getSceneManager()->createCamera(getName()+".Camera");
		  this->scene_node = render_subsystem->getSceneManager()->getRootSceneNode()->createChildSceneNode(getName()+".SceneNode");
		}

		OgreCameraComponent::OgreCameraComponent ( const std::string& name, const OgreCameraComponent::Descriptor& desc, OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context )
		:Component(name),
		  type(OGRE_CAMERA_COMPONENT_TYPE),
		  render_subsystem(render_subsystem),
		  engine_context(engine_context),
		  listener(nullptr),
		  messaging_policies_manager(engine_context)
		{
		}
		
		OgreCameraComponent::~OgreCameraComponent()
		{
		  render_subsystem->getSceneManager()->destroyCamera(this->camera);
		  render_subsystem->getSceneManager()->destroySceneNode(this->scene_node);
		}
		
		void OgreCameraComponent::onTransformChanged ( const Core::TransformChangedMessage& msg )
		{
		  this->scene_node->setPosition( OgreVector3Converter::toOgreVector(msg.new_transform.getPosition()) );
		  this->scene_node->setOrientation( OgreQuaternionConverter::toOgreQuaternion(msg.new_transform.getOrientation()) );
		}

		void OgreCameraComponent::addReceivedMessageType(const Core::ReceivedMessageDesc &received_message)
		{
			if(listener==nullptr) listener = new OgreCameraComponentListener(getName()+".Listener", this, engine_context);
			if(listener->supportsMessageTypeName(received_message.message_type_name))
			{
				engine_context->getMessageDispatcher()->addListener(
							received_message.message_type_name, listener,
							messaging_policies_manager.createPrefabReceiveMessagePolicy(received_message.receive_policy_type_name, received_message.receive_policy_options)
							);
			}
			else
			{
				throw Core::IMessageListener::MessageTypeNotSupportedByListener("Listener of component " + getName() + " doesn't support message type " + received_message.message_type_name);
			}
		}

	}
}