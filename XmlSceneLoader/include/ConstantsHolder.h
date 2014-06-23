/*
 * ConstantsHolder.h
 *
 *  Created on: 22 июня 2014 г.
 *      Author: Eaglegor
 */

#ifndef CONSTANTSHOLDER_H_
#define CONSTANTSHOLDER_H_

#include <map>
#include <list>
#include <InlineSpecification.h>

namespace UnknownEngine
{
	namespace Loader
	{

		class ConstantsHolder
		{
			public:

				typedef std::exception LoaderConstantNotFoundException;

				ConstantsHolder()
				{
				}

				virtual ~ConstantsHolder()
				{
				}

				UNKNOWNENGINE_INLINE
				std::string getConstantValue(std::string constant_name) throw (LoaderConstantNotFoundException)
				{
					for(auto iter = constants_maps.rbegin(); iter != constants_maps.rend(); ++iter)
					{
						auto value = iter->find(constant_name);
						if (value == iter->end())
						return value->second;
					}
					throw LoaderConstantNotFoundException();
				}

				UNKNOWNENGINE_INLINE
				void setConstantValue(std::string constant_name, std::string value)
				{
					constants_maps.back()[constant_name] = value;
				}

				UNKNOWNENGINE_INLINE
				void pushScope()
				{
					constants_maps.emplace_back();
				}

				UNKNOWNENGINE_INLINE
				void popScope()
				{
					constants_maps.pop_back();
				}

			private:
				typedef std::map<std::string, std::string> ConstantsMap;
				std::list<ConstantsMap> constants_maps;

		};

	} /* namespace Loader */
} /* namespace UnknownEngine */

#endif /* CONSTANTSHOLDER_H_ */
