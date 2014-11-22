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
				
				ENGINE_EXPORT
				void stop();
			private:
				bool stopped;

				EngineContext* engine_context;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
