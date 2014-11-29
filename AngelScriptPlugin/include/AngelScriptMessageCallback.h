#pragma once

#include <LogHelper.h>

#include <ASIncludes.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		Utils::LogHelper* angel_script_error_logger = nullptr;
		
		void angelScriptMessageCallback(const asSMessageInfo *msg, void *param)
		{
			switch(msg->type)
			{
				case asMSGTYPE_WARNING:
				{
					LOG_WARNING(angel_script_error_logger, "Section: " + std::string(msg->section) + " Row: " + std::to_string(msg->row) + " Column: " + std::to_string(msg->col) + "\n" + std::string(msg->message) + "\n");
					break;
				}
				case asMSGTYPE_INFORMATION:
				{
					LOG_INFO(angel_script_error_logger, "Section: " + std::string(msg->section) + " Row: " + std::to_string(msg->row) + " Column: " + std::to_string(msg->col) + "\n" + std::string(msg->message) + "\n");
					break;
				}
				case asMSGTYPE_ERROR:
				{
					LOG_ERROR(angel_script_error_logger, "Section: " + std::string(msg->section) + " Row: " + std::to_string(msg->row) + " Column: " + std::to_string(msg->col) + "\n" + std::string(msg->message) + "\n");
					break;
				}
			}
		}
	}
}