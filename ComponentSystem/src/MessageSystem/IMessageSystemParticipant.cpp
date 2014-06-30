#include <MessageSystem/IMessageSystemParticipant.h>
#include <MessageSystem/MessageSystemParticipantDictionary.h>

namespace UnknownEngine {
	namespace Core {

		IMessageSystemParticipant::IMessageSystemParticipant(const MessageSystemParticipantId &message_system_participant_id)
			:message_system_participant_id(message_system_participant_id)
		{
			const auto &dictionary = MessageSystemParticipantDictionary::getSingleton();
			this->message_system_participant_id.id = dictionary->registerMessageParticipant(message_system_participant_id.name);
		}

		IMessageSystemParticipant::~IMessageSystemParticipant()
		{
			const auto &dictionary = MessageSystemParticipantDictionary::getSingleton();
			dictionary->unregisterMessageParticipant(message_system_participant_id.name);
		}

	} // namespace Core
} // namespace UnknownEngine
