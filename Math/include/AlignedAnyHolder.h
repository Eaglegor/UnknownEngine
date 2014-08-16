#pragma once

// This is ugly hack to properly store aligned data types in boost::any

#include <boost/any.hpp>

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES

#define ALIGNED_BOOST_ANY_HOLDER(TypeName) namespace boost \
	{ \
	template<> \
	class any::holder<TypeName> : public boost::any::placeholder \
		{ \
		public: \
		holder(const TypeName & value) \
		: held(value) \
			{ \
			} \
			holder(TypeName&& value) \
			: held(static_cast< TypeName&& >(value)) \
			{ \
			} \
		public: \
		virtual const std::type_info & type() const BOOST_NOEXCEPT \
			{ \
			return typeid(TypeName); \
			} \
			virtual placeholder * clone() const \
			{ \
			return new holder(held); \
			} \
			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR; \
		public:  \
		TypeName held; \
		private:  \
		holder & operator=(const holder &); \
		}; \
	template<> \
	class any::holder<const TypeName> : public boost::any::placeholder \
	{ \
		public: \
		holder(const TypeName & value) \
		: held(value) \
						{ \
						} \
			holder(TypeName&& value) \
			: held(static_cast< TypeName&& >(value)) \
						{ \
						} \
		public: \
		virtual const std::type_info & type() const BOOST_NOEXCEPT \
						{ \
			return typeid(TypeName); \
						} \
			virtual placeholder * clone() const \
						{ \
			return new holder(held); \
						} \
			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR; \
		public:  \
		TypeName held; \
		private:  \
		holder & operator=(const holder &); \
	}; \
}

#else

	#define ALIGNED_BOOST_ANY_HOLDER(TypeName) namespace boost \
	{ \
	template<> \
	class any::holder<TypeName> : public boost::any::placeholder \
	{ \
		public: \
		holder(const TypeName & value) \
		: held(value) \
			{ \
			} \
		public: \
		virtual const std::type_info & type() const BOOST_NOEXCEPT \
			{ \
			return typeid(TypeName); \
			} \
			virtual placeholder * clone() const \
			{ \
			return new holder(held); \
			} \
			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR; \
		public:  \
		TypeName held; \
		private:  \
		holder & operator=(const holder &); \
	}; \
	template<> \
	class any::holder<const TypeName> : public boost::any::placeholder \
	{ \
	public: \
	holder(const TypeName & value) \
	: held(value) \
					{ \
					} \
	public: \
	virtual const std::type_info & type() const BOOST_NOEXCEPT \
					{ \
		return typeid(TypeName); \
					} \
		virtual placeholder * clone() const \
					{ \
		return new holder(held); \
					} \
		UNKNOWNENGINE_ALIGNED_NEW_OPERATOR; \
	public:  \
	TypeName held; \
	private:  \
	holder & operator=(const holder &); \
	}; \
}

#endif 
