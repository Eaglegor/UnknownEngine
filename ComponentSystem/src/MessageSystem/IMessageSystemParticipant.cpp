#include <MessageSystem/IMessageSystemParticipant.h>
#include <MessageSystem/MessageSystemParticipantDictionary.h>

namespace UnknownEngine {
	namespace Core {

		IMessageSystemParticipant::IMessageSystemParticipant(const std::string &object_name)
		{
			const auto &dictionary = MessageSystemParticipantDictionary::getSingleton();
			this->message_system_participant_id.name = object_name;
			this->message_system_participant_id.id = dictionary->registerNewMessageParticipant(message_system_participant_id.name);
		}

		IMessageSystemParticipant::~IMessageSystemParticipant()
		{
			const auto &dictionary = MessageSystemParticipantDictionary::getSingleton();
			dictionary->unregisterMessageParticipant(message_system_participant_id.name);
		}

	} // namespace Core
} // namespace UnknownEngine
