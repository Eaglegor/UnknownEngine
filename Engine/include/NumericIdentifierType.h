#pragma once

namespace UnknownEngine{
	namespace Core
	{
		/// Type for different numeric id's
		typedef int NumericIdentifierType;

		/// Constant for invalid numeric identifier values
		static const NumericIdentifierType INVALID_NUMERIC_IDENTIFIER = static_cast< NumericIdentifierType > ( -1 );

		/// Constant for initial numeric identifier value for incremental id's
		static const NumericIdentifierType NUMERIC_IDENTIFIER_INITIAL_VALUE = static_cast< NumericIdentifierType > ( 0 );
	}
}
