/*
 * XmlSceneLoader.h
 *
 *  Created on: 22 ���� 2014 �.
 *      Author: Eaglegor
 */

#ifndef XMLSCENELOADER_H_
#define XMLSCENELOADER_H_

#include <ISceneLoader.h>

namespace UnknownEngine
{

	namespace Loader
	{

		class XmlSceneLoader : public ISceneLoader
		{
			public:
				XmlSceneLoader();
				virtual ~XmlSceneLoader();
		};

	} /* namespace Loader */
} /* namespace UnknownEngine */

#endif /* XMLSCENELOADER_H_ */
