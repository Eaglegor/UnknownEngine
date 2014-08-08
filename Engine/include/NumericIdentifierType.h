#pragma once

namespace UnknownEngine
{
	namespace Core
	{
		/** \var typedef int NumericIdentifierType
		 * @brief Alias for numeric identifier type
		 */
		typedef int NumericIdentifierType;

		/** @brief Constant value indicating a invalid identifier */
		static const NumericIdentifierType INVALID_NUMERIC_IDENTIFIER = static_cast< NumericIdentifierType > ( -1 );

		/** @brief Constant value indicating a start index for incremental numeric identifiers */
		static const NumericIdentifierType NUMERIC_IDENTIFIER_INITIAL_VALUE = static_cast< NumericIdentifierType > ( 0 );
	}
}
