#pragma once

#include <string>
#include <boost/any.hpp>

namespace UnknownEngine
{
	namespace Loader
	{
		class ResourceContainer
		{
			public:
				template<typename T>
				const T& getData() const
				{
					return boost::any_cast<const T&>(data);
				}

				template<typename T>
				void setData(T&& data)
				{
					this->data = std::move(data);
				}

				template<typename T>
				void setData(const T& data)
				{
					this->data = data;
				}

			private:
				boost::any data;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
