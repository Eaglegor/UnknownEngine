#pragma once

#include <string>
#include <set>
#include <memory>

namespace UnknownEngine
{
	namespace Core
	{
		class ComponentType
		{
		public:
			ComponentType();
			ComponentType(const ComponentType& type);
			ComponentType(const char* name);
			ComponentType(const char* name, const ComponentType& base);
			ComponentType(const char* name, const std::set<ComponentType>& bases);

			ComponentType& operator=(const ComponentType& rhs);

			bool operator!=(const ComponentType& rhs) const;
			bool operator==(const ComponentType& rhs) const;
			bool operator<(const ComponentType& rhs) const;

			size_t getTypeId() const;
			const char* getTypeName() const;
			const std::set<ComponentType>& getBases() const;

			bool is(const ComponentType& type) const;

		private:
			static size_t retrieveTypeId(const char* name);

			std::set<ComponentType> base_types;
			std::string name;
			size_t type_id;
		};

		std::string operator+(const std::string& str, const ComponentType &type);
		std::string operator+(const ComponentType &type, const std::string& str);

	}
}


namespace std {
	template<>
	class hash<UnknownEngine::Core::ComponentType> {
	public:
		size_t operator()(const UnknownEngine::Core::ComponentType &s) const
		{
			return std::hash<size_t>()(s.getTypeId());
		}
	};
}