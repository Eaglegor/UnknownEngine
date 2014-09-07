#pragma once

#include <ComponentSystem_export.h>
#include <string>
#include <NumericIdentifierType.h>

namespace UnknownEngine
{
	namespace Core
	{

		/**
		* @brief Address of some object at the message bus
		*
		* Unknown %Engine uses a message bus to let subsystems communicate with each other.
		* To do this effectively every object must have a **unique** address. Such address
		* consists of the **unique** object's string name and the according numeric identifier.
		*
		* **Note that all interactions are done based on numeric address identifier.**
		* **If your name/id pair is incorrect it might cause some unexpected behavior.**
		*
		* We want to guarantee that our name/id is unique across all objects at message bus.
		* To do this we use a MessageSystemParticipantDictionary to assign numeric identifiers to addresses.
		* Registering a new object at dictionary and getting numeric id may be peformed manually by the call to
		* MessageSystemParticipantDictionary::registerNewMessageSystemParticipant() method.
		*
		* The simplier way is just to inherit your class from which you will be sending messages from
		* IMessageSystemParticipant base class. The bus address is automatically registered in the
		* constructor of this class and unregistered in the destructor.
		*
		*/
		struct MessageSystemParticipantId
		{
			
			enum class AutoRegistrationPolicy
			{
				AUTO_REGISTER,
				DONT_AUTO_REGISTER
			};
			
			/**
			 * @brief Constructor. Automatically fills id for **already registered** object
			 * @param object_name - name of object
			 * @param auto_registration_policy - defines if the object name must be automatically registered in the system if it doesn't exist yet
			 *
			 * Tries to automatically set the id. If object name wasn't registered at dictionaty throws an exception
			 *
			 * @throw Utils::Dictionary::EntryNotFoundInDictionary - Is thrown when trying to get id for unregistered name
			 *
			 */
			COMPONENTSYSTEM_EXPORT
			explicit MessageSystemParticipantId ( const std::string &object_name, AutoRegistrationPolicy auto_registration_policy = AutoRegistrationPolicy::DONT_AUTO_REGISTER );

			/**
			 * @brief Default constructor. Doesn't fill anything. Address is empty.
			 */
			COMPONENTSYSTEM_EXPORT
			MessageSystemParticipantId();

			/**
			 * @brief Constructor. Fills the address with the name/id passed as arguments. **Doesn't check anything**
			 * @param object_name - name of object
			 * @param id - numeric identifier of object
			 *
			 * Use on your own risk because there are no checks. Really. **It's dangerous**
			 *
			 *
			 */
			COMPONENTSYSTEM_EXPORT
			MessageSystemParticipantId ( const std::string &object_name, const NumericIdentifierType &id );

			/**
			 * @brief Compares to another address
			 * @param rhs - address to compare
			 * @return true if internal ids are equal
			 */
			bool operator== ( const MessageSystemParticipantId& rhs ) const
			{
				return id == rhs.id;
			}

			NumericIdentifierType id; ///< Numeric address identifier
			std::string name; ///< String object name
		};
	}
	
	static Core::MessageSystemParticipantId GET_OR_CREATE_MESSAGE_SYSTEM_PARTICIPANT_ID(const std::string &name)
	{
		return std::move(Core::MessageSystemParticipantId(name, Core::MessageSystemParticipantId::AutoRegistrationPolicy::AUTO_REGISTER));
	}
	
}
