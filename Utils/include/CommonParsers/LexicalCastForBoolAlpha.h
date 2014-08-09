#pragma once

#include <InlineSpecification.h>
#include <boost/lexical_cast.hpp>

namespace boost {
    template<> 
    UNKNOWNENGINE_INLINE
    bool lexical_cast<bool, std::string>(const std::string& arg) {
        std::istringstream ss(arg);
        bool b;
        ss >> std::boolalpha >> b;
        return b;
    }

    template<>
    UNKNOWNENGINE_INLINE
    std::string lexical_cast<std::string, bool>(const bool& b) {
        std::ostringstream ss;
        ss << std::boolalpha << b;
        return ss.str();
    }
}