#pragma once

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
				/**
				 * @brief Constructor. Automatically fills id for **already registered** object
				 * @param object_name - name of object
				 *
				 * Tries to automatically set the id. If object name wasn't registered at dictionaty throws an exception
				 *
				 * @throw Utils::Dictionary::EntryNotFoundInDictionary - Is thrown when trying to get id for unregistered name
				 *
				 */
				explicit MessageSystemParticipantId(const std::string &object_name);

				/**
				 * @brief Default constructor. Doesn't fill anything. Address is empty.
				 */
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
				MessageSystemParticipantId(const std::string &object_name, const NumericIdentifierType &id);

				/**
				 * @brief Compares to another address
				 * @param rhs - address to compare
				 * @return true if internal ids are equal
				 */
				bool operator==(const MessageSystemParticipantId& rhs) const
				{
					return id == rhs.id;
				}

				NumericIdentifierType id; ///< Numeric address identifier
				std::string name; ///< String object name
		};
	}
}