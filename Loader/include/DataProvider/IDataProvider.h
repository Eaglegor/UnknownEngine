/*
 * IDataProvider.h
 *
 *  Created on: 22 θώνÿ 2014 γ.
 *      Author: Eaglegor
 */

#ifndef IDATAPROVIDER_H_
#define IDATAPROVIDER_H_

#include <string>

namespace UnknownEngine
{
	namespace Loader
	{

		template<typename T>
		class Properties;

		class IDataProvider
		{
			public:
				virtual ~IDataProvider();
				virtual void addDataToPropertiesList(Properties<std::string> &in_out_options) = 0;

			protected:
				IDataProvider(const Properties<std::string> &options);

		};

	} /* namespace Core */
} /* namespace UnknownEngine */

#endif /* IDATAPROVIDER_H_ */
