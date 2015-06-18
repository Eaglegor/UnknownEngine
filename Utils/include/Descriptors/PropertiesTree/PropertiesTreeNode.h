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
			PropertiesTreeNode();
			PropertiesTreeNode(const PropertiesTreeNode &node);

			PropertiesTreeNode& operator=(const PropertiesTreeNode &node);

			virtual ~PropertiesTreeNode();
			
			void setValue(const char* value)
			{
				this->value = value;
			}
			
			const char* getValue() const
			{
				return value.c_str();
			}
			
			PropertiesTreeNode* getChild(const char* name) const;
			
			PropertiesTreeNode* createChild(const char* name);

		private:
			std::string value;
			void* childen; // void* inspired by boost::property_tree (we have incomplete PropertiesTreeNode there and can't use direct container declaration)
		};

		namespace details
		{
			typedef std::unordered_multimap<std::string, PropertiesTreeNode > PropertiesTreeInternalContainerType;
		}

		PropertiesTreeNode::PropertiesTreeNode():
			children(new details::PropertiesTreeInternalContainerType())
		{
		}

		PropertiesTreeNode::PropertiesTreeNode(const PropertiesTreeNode &node):
			children(new details::PropertiesTreeInternalContainerType(*static_cast<details::PropertiesTreeInternalContainerType*>(node.childen)))
		{
		}

		PropertiesTreeNode &PropertiesTreeNode::operator=(const PropertiesTreeNode &node)
		{
			value = node.value;
			*(static_cast<details::PropertiesTreeInternalContainerType*>(children)) = *(static_cast<details::PropertiesTreeInternalContainerType*>(node.children));
		}

		PropertiesTreeNode::~PropertiesTreeNode(){
			details::PropertiesTreeInternalContainerType *children = static_cast<details::PropertiesTreeInternalContainerType*>(this->children);
			delete children;
		}

		PropertiesTreeNode *PropertiesTreeNode::getChild(const char *name) const
		{
			details::PropertiesTreeInternalContainerType& children = *static_cast<details::PropertiesTreeInternalContainerType*>(this->children);
			auto iter = children.find(name);
			if(iter == children.end()) return nullptr;
			return &iter->second.get();
		}

		PropertiesTreeNode *PropertiesTreeNode::createChild(const char *name)
		{
			details::PropertiesTreeInternalContainerType& children = *static_cast<details::PropertiesTreeInternalContainerType*>(this->children);
			return children.emplace(name, PropertiesTreeNode()).first->second.get();
		}



	}
}
