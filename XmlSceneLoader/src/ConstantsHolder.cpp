#include <stdafx.h>

#include <ConstantsHolder.h>

std::string UnknownEngine::Loader::ConstantsHolder::applyPlaceholderConstants(const std::string &input_string) const
{
    boost::regex regexp("\\$\\{\\w+\\}", boost::regex_constants::perl);
    return boost::regex_replace(input_string, regexp,
                                [this](const boost::smatch &match)
    {
        std::string mmatch = match.str();
        return this->getConstantValue(mmatch.substr(2, mmatch.size()-3));
    });
}

void UnknownEngine::Loader::ConstantsHolder::parseAndSaveConstant(const boost::property_tree::ptree &constant_node)
{
    const boost::property_tree::ptree &attrs = constant_node.get_child(XMLATTR);
    const std::string constant_name = attrs.get<std::string>(Attributes::CONSTANT::NAME);
    const std::string constant_value = attrs.get<std::string>(Attributes::CONSTANT::VALUE);
    setConstantValue(constant_name, constant_value);
}
