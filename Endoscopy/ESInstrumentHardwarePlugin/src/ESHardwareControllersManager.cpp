#include <ESHardwareControllersManager.h>
#include <Controllers/IESController.h>
#include <Controllers/ESControllersFactory.h>

namespace UnknownEngine
{
	namespace Endoscopy
	{
		ESHardwareControllersManager::ESHardwareControllersManager ( const Core::LogHelper& log_helper ):
		log_helper(log_helper)
		{}

		ESHardwareControllersManager::~ESHardwareControllersManager()
		{}

		void ESHardwareControllersManager::init()
		{
			ESControllersFactory factory;
			IESController* controller = factory.createBestController("ESHardware.CameraController");
			if(controller) controllers.emplace(ESInstrumentPort::CAMERA, controller);
		}

		void ESHardwareControllersManager::shutdown()
		{
			ESControllersFactory factory;
			for(auto &iter : controllers )
			{
				factory.destroyController(iter.second);
			}
			controllers.clear();
		}
	}
}