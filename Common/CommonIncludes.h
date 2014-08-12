#include <string>
#include <iostream>

#include <unordered_map>
#include <unordered_set>
#include <map>

#include <list>
#include <vector>

#include <time.h>
#ifdef _MSC_VER
	#define constexpr 
#endif


#ifdef _MSC_VER 
	#pragma warning(push)
	#pragma warning(disable:4290) // Disable warning about not supported exception specifications in MSVC
	#pragma warning(disable:4661) // Disable warning about singleton instance instantiation (@TODO - investigate - there is something dangerous possible)
	#pragma warning(disable:4996) // Disable warning from boost::is_any_of used in parsers to split tokens
#endif 