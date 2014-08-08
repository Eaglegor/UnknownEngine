#pragma once
/*
 * MainLoop.h
 *
 *  Created on: 17 июня 2014 г.
 *      Author: gorbachenko
 */

#include <Engine_export.h>
#include <vector>
#include <MessageSystem/IMessageSystemParticipant.h>

namespace UnknownEngine
{
	namespace Core
	{

		/**
		 * @brief The main loop
		 */
		class MainLoop : public IMessageSystemParticipant
		{
			public:
				/**
				 * @brief Constructor. Called by Engine
				 */
				ENGINE_EXPORT
				MainLoop ();

				ENGINE_EXPORT
				virtual ~MainLoop ();

				/**
				 * @brief Starts the main loop
				 *
				 * This call doesn't return until simulation stop
				 *
				 */
				ENGINE_EXPORT
				void start();
				void stop();
			private:
				/**
				 * @brief Updates delta time value
				 */
				void updateTime();

				bool stopped;

				float current_time; ///< Current time
				float dt; ///< Delta time from last frame

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
