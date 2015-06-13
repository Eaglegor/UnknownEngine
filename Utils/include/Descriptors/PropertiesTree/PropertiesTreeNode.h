#pragma once

#include <unordered_map>
#include <memory>

namespace UnknownEngine
{
	namespace Utils
	{
		class PropertiesTreeNode 
		{
		public:
			virtual ~PropertiesTreeNode(){}
			
			void setValue(const char* value)
			{
				this->value = value;
			}
			
			const char* getValue() const
			{
				return value.c_str();
			}
			
			PropertiesTreeNode* getChild(const char* name) const
			{
				auto iter = children.find(name);
				if(iter == children.end()) return nullptr;
				return iter->second.get();
			}
			
			PropertiesTreeNode* createChild(const char* name)
			{
				return children.emplace(name, std::make_shared<PropertiesTreeNode>()).first->second.get();
			}

		private:
			std::string value;
			std::unordered_map<std::string, std::shared_ptr<PropertiesTreeNode> > children;
		};
	}
}