#pragma once

#include <unordered_map>
#include <Singleton.h>
#include <Exception.h>

namespace UnknownEngine {
	namespace Utils {

		template <typename KeyType, typename ValueType>
		class Dictionary
		{
			public:

				UNKNOWNENGINE_SIMPLE_EXCEPTION(EntryNotFoundInDictionary);
				UNKNOWNENGINE_SIMPLE_EXCEPTION(ValueAlreadyExists);

				Dictionary(const std::string& name, const KeyType &initial_key_value, const KeyType &invalid_key_value):
					next_key_value(initial_key_value),
					invalid_key_value(invalid_key_value),
					name(name)
				{
				}

				virtual ~Dictionary(){}

				KeyType registerNewValue(const ValueType &value) throw(ValueAlreadyExists)
				{
					if ( valueIsRegistered( value ) ) throw ValueAlreadyExists("Can't add value to dictionary " + name + " - already exists");
					key_value_mapping.insert ( std::make_pair ( next_key_value, value ) );
					value_key_mapping.insert ( std::make_pair ( value, next_key_value ) );
					return next_key_value++;
				}

				bool valueIsRegistered(const ValueType &value) const
				{
					return value_key_mapping.find(value) != value_key_mapping.end();
				}

				bool keyIsRegistered(const KeyType &key) const
				{
					return key_value_mapping.find(key) != key_value_mapping.end();
				}

				const ValueType& getValueByKey(const KeyType &key) const throw(EntryNotFoundInDictionary)
				{
					if(keyIsRegistered(key)) return key_value_mapping.find( key )->second;
					throw EntryNotFoundInDictionary("Can't find requested key in dictionary " + name);
				}

				const KeyType& getKeyByValue(const ValueType &value) const
				{
					if(valueIsRegistered(value)) return value_key_mapping.find( value )->second;
					return invalid_key_value;
				}

				void deleteEntryByKey(const KeyType &key)
				{
					auto key_iter = key_value_mapping.find(key);
					if(key_iter == key_value_mapping.end()) throw EntryNotFoundInDictionary("Can't find entry in dictionary " + name);
					auto value_iter = value_key_mapping.find(key_iter->second);
					key_value_mapping.erase(key_iter);
					value_key_mapping.erase(value_iter);
				}

				void deleteEntryByValue(const ValueType &value)
				{
					auto value_iter = value_key_mapping.find(value);
					if(value_iter == value_key_mapping.end()) throw EntryNotFoundInDictionary("Can't find entry in dictionary" + name);
					auto key_iter = key_value_mapping.find(value_iter->second);
					key_value_mapping.erase(key_iter);
					value_key_mapping.erase(value_iter);
				}

			private:
				std::unordered_map<KeyType, ValueType> key_value_mapping;
				std::unordered_map<ValueType, KeyType> value_key_mapping;

				std::string name;
				KeyType next_key_value;
				const KeyType invalid_key_value;

		};

	} // namespace Core
} // namespace UnknownEngine
