#pragma once

#include <string>
#include <set>
#include <memory>
#include <ComponentSystem_export.h>

namespace UnknownEngine
{
	namespace Core
	{
		class ComponentType
		{
		public:
			COMPONENTSYSTEM_EXPORT
			ComponentType();

			COMPONENTSYSTEM_EXPORT
			ComponentType(const ComponentType& type);

			COMPONENTSYSTEM_EXPORT
			ComponentType(const char* name);

			COMPONENTSYSTEM_EXPORT
			ComponentType(const char* name, const ComponentType& base);

			COMPONENTSYSTEM_EXPORT
			ComponentType(const char* name, const std::set<ComponentType>& bases);

			COMPONENTSYSTEM_EXPORT
			ComponentType& operator=(const ComponentType& rhs);

			COMPONENTSYSTEM_EXPORT
			bool operator!=(const ComponentType& rhs) const;

			COMPONENTSYSTEM_EXPORT
			bool operator==(const ComponentType& rhs) const;

			COMPONENTSYSTEM_EXPORT
			bool operator<(const ComponentType& rhs) const;

			COMPONENTSYSTEM_EXPORT
			size_t getTypeId() const;

			COMPONENTSYSTEM_EXPORT
			const char* getTypeName() const;

			COMPONENTSYSTEM_EXPORT
			const std::set<ComponentType>& getBases() const;

			COMPONENTSYSTEM_EXPORT
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
	struct hash<UnknownEngine::Core::ComponentType> {
	public:
		size_t operator()(const UnknownEngine::Core::ComponentType &s) const
		{
			return std::hash<size_t>()(s.getTypeId());
		}
	};
}