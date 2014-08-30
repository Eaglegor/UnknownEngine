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

#include <chrono>

namespace UnknownEngine
{
	namespace Core
	{

		class EngineContext;

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
				MainLoop (EngineContext* engine_context);

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

				typedef std::chrono::steady_clock ClockType;
				
				ClockType::time_point current_time; ///< Current time
				std::chrono::duration<float> dt; ///< Delta time from last frame
				
				EngineContext* engine_context;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
