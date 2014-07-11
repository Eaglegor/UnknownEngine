#pragma once
/*
 * MainLoop.h
 *
 *  Created on: 17 июня 2014 г.
 *      Author: gorbachenko
 */

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
				MainLoop ();
				virtual ~MainLoop ();

				/**
				 * @brief Starts the main loop
				 *
				 * This call doesn't return until simulation stop
				 *
				 */
				void start();

			private:
				/**
				 * @brief Updates delta time value
				 */
				void updateTime();

				float current_time; ///< Current time
				float dt; ///< Delta time from last frame

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
