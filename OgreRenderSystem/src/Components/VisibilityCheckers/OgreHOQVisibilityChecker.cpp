#include <Components/VisibilityCheckers/OgreHOQVisibilityChecker.h>
#include <OgreRenderSubsystem.h>
#include <OgreRoot.h>
#include <OgreEntity.h>
#include <OgreHardwareOcclusionQuery.h>
#include <OgreSubEntity.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		OgreHOQVisibilityChecker::OgreHOQVisibilityChecker ( const char* name, const OgreHOQVisibilityCheckerDesc& desc, OgreRenderSubsystem* render_subsystem ):
		BaseOgreComponent (name , render_subsystem ),
		desc(desc),
		checkable_object(desc.checkable_object),
		render_window(desc.render_window),
		area_query(nullptr),
		visible_part_query(nullptr),
		active_query(nullptr),
		area_entity(nullptr),
		visible_part_entity(nullptr),
		scene_node(nullptr),
		area_renderable(nullptr),
		visible_part_renderable(nullptr),
		area_query_is_running(false),
		visible_part_query_is_running(false),
		logger(name, desc.log_level),
		render_target_active(false)
		{
		}
		
		void OgreHOQVisibilityChecker::internalInit()
		{
			if(!render_window) {
				LOG_ERROR(logger, "No render window was provided");
				return;
			}
			
			Ogre::RenderSystem* render_system = getRenderSubsystem()->getRoot()->getRenderSystem();
			area_query = render_system->createHardwareOcclusionQuery();
			visible_part_query = render_system->createHardwareOcclusionQuery();
			
			Ogre::MaterialPtr base_material = Ogre::MaterialManager::getSingleton().getByName("BaseWhiteNoLighting");
			
			area_material = base_material->clone(std::string(getName()) + "_HOQAreaMaterial");
			area_material->setDepthWriteEnabled(false);
			area_material->setColourWriteEnabled(false);
			area_material->setDepthCheckEnabled(false);
			
			visible_part_material = base_material->clone(std::string(getName()) + "_HOQVisiblePartMaterial");
			visible_part_material->setDepthWriteEnabled(false);
			visible_part_material->setColourWriteEnabled(false);
			visible_part_material->setDepthCheckEnabled(true);
			
			area_entity = checkable_object->getEntity()->clone(std::string(getName()) + "_HOQAreaEntity");
			area_entity->setMaterial(area_material);
			area_entity->setRenderQueueGroup(desc.render_queue_group);
			area_renderable = area_entity->getSubEntity(0);
			
			visible_part_entity = checkable_object->getEntity()->clone(std::string(getName()) + "_HOQVisiblePartEntity");
			visible_part_entity->setMaterial(visible_part_material);
			visible_part_entity->setRenderQueueGroup(desc.render_queue_group);
			visible_part_renderable = visible_part_entity->getSubEntity(0);
			
			scene_node = checkable_object->getSceneNode();
			scene_node->attachObject(area_entity);
			scene_node->attachObject(visible_part_entity);
			
			getRenderSubsystem()->getSceneManager()->addRenderObjectListener(this);
			getRenderSubsystem()->getSceneManager()->addRenderQueueListener(this);
			render_window->getOgreRenderWindow()->addListener(this);
		}

		void OgreHOQVisibilityChecker::internalShutdown()
		{
			if(!render_window) return;
			
			render_window->getOgreRenderWindow()->removeListener(this);
			getRenderSubsystem()->getSceneManager()->removeRenderQueueListener(this);
			getRenderSubsystem()->getSceneManager()->removeRenderObjectListener(this);
			
			scene_node->detachObject(visible_part_entity);
			scene_node->detachObject(area_entity);
			
			
			visible_part_renderable = nullptr;
			getRenderSubsystem()->getSceneManager()->destroyEntity(visible_part_entity);
			visible_part_entity = nullptr;
			
			area_renderable = nullptr;
			getRenderSubsystem()->getSceneManager()->destroyEntity(area_entity);
			area_entity = nullptr;
			
			Ogre::String visible_part_material_name = visible_part_material->getName();
			Ogre::String area_material_name = area_material->getName();
			
			area_material.setNull();
			visible_part_material.setNull();
			
			Ogre::MaterialManager::getSingleton().remove(visible_part_material_name);
			Ogre::MaterialManager::getSingleton().remove(area_material_name);
			
			Ogre::RenderSystem* render_system = getRenderSubsystem()->getRoot()->getRenderSystem();
			
			render_system->destroyHardwareOcclusionQuery(visible_part_query);
			visible_part_query = nullptr;
			
			render_system->destroyHardwareOcclusionQuery(area_query);
			area_query = nullptr;
		}

		bool OgreHOQVisibilityChecker::objectIsNotRendered()
		{
			if(!checkable_object->getEntity()->isVisible()) return false;
			if(render_window->getOgreRenderWindow()->isActive() && render_window->getOgreRenderWindow()->getNumViewports() > 0)
			{
				
				const Ogre::AxisAlignedBox &box = checkable_object->getEntity()->getWorldBoundingBox(true);
				return !render_window->getOgreRenderWindow()->getViewport(0)->getCamera()->isVisible(box);
			}
			else
			{
				return false;
			}
		}
		
		void OgreHOQVisibilityChecker::_update()
		{
			if(area_query_is_running && visible_part_query_is_running && !area_query->isStillOutstanding() && !visible_part_query->isStillOutstanding())
			{
				unsigned int area_pixels_count;
				unsigned int visible_pixels_count;
				Math::Scalar ratio;
				
				area_query->pullOcclusionQuery(&area_pixels_count);
				visible_part_query->pullOcclusionQuery(&visible_pixels_count);
				ratio = visible_pixels_count / static_cast<Math::Scalar>(area_pixels_count);

				//LOG_DEBUG(logger, "Visible pixels: " + std::to_string(visible_pixels_count));
				//LOG_DEBUG(logger, "Total pixels: " + std::to_string(area_pixels_count));
				
				if(visible_pixels_count > 0 && current_visibility_data.is_visible == false)
				{
					LOG_INFO(logger, "Object visible");
					
					listeners.doForAllListeners(
						[this](ComponentInterfaces::VisibilityCheckerListener* listener)
						{
							listener->onObjectVisible(component_cast<ComponentInterfaces::IRenderable*>(this->desc.checkable_object));
						}
					);
				}
				
				if(visible_pixels_count == 0 && current_visibility_data.is_visible == true)
				{
					LOG_INFO(logger, "Object invisible");
					
					listeners.doForAllListeners(
						[this](ComponentInterfaces::VisibilityCheckerListener* listener)
						{
							listener->onObjectInvisible(component_cast<ComponentInterfaces::IRenderable*>(this->desc.checkable_object));
						}
					);
				}
				
				current_visibility_data.is_visible = visible_pixels_count > 0;
				current_visibility_data.visibility_ratio = ratio;
				
				area_query_is_running = false;
				visible_part_query_is_running = false;
			}

			if(objectIsNotRendered() && current_visibility_data.is_visible == true)
			{
				LOG_INFO(logger, "Object invisible");
				
				listeners.doForAllListeners(
					[this](ComponentInterfaces::VisibilityCheckerListener* listener)
					{
						listener->onObjectInvisible(component_cast<ComponentInterfaces::IRenderable*>(this->desc.checkable_object));
					}
				);
				
				current_visibility_data.is_visible = false;
				current_visibility_data.visibility_ratio = 0;
			}
		}
		
		ComponentInterfaces::VisibilityData OgreHOQVisibilityChecker::getVisibilityData() const
		{
			return current_visibility_data;
		}

		bool OgreHOQVisibilityChecker::isVisible() const
		{
			return current_visibility_data.is_visible;
		}
		
		void OgreHOQVisibilityChecker::addListener ( ComponentInterfaces::VisibilityCheckerListener* listener )
		{
			listeners.addListener(listener);
		}

		void OgreHOQVisibilityChecker::removeListener ( ComponentInterfaces::VisibilityCheckerListener* listener )
		{
			listeners.removeListener(listener);
		}
		
		void OgreHOQVisibilityChecker::notifyRenderSingleObject ( Ogre::Renderable* rend, const Ogre::Pass* pass, const Ogre::AutoParamDataSource* source, const Ogre::LightList* pLightList, bool suppressRenderStateChanges )
		{
			if(active_query)
			{
				active_query->endOcclusionQuery();
				active_query = nullptr;
			}

			if(!render_target_active) return;
			
			if(rend != area_renderable && rend != visible_part_renderable) return;
			else if(rend == area_renderable)
			{
				if(!area_query_is_running)
				{
					area_query_is_running = true;
					active_query = area_query;
					area_query->beginOcclusionQuery();
				}
			}
			else if(rend == visible_part_renderable)
			{
				if(!visible_part_query_is_running)
				{
					visible_part_query_is_running = true;
					active_query = visible_part_query;
					visible_part_query->beginOcclusionQuery();
				}
			}
		}
		
		void OgreHOQVisibilityChecker::renderQueueEnded ( Ogre::uint8 queueGroupId, const Ogre::String& invocation, bool& repeatThisInvocation )
		{
			if(active_query){
				active_query->endOcclusionQuery();
				active_query = nullptr;
			}
		}

		void OgreHOQVisibilityChecker::preRenderQueues()
		{
			render_target_active = true;
		}

		void OgreHOQVisibilityChecker::postRenderQueues()
		{
			render_target_active = false;
		}
		
	}
}