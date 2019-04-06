#pragma once


#include <Util/Types.hpp>


namespace util::err
{

// Static assertion errors.
#define typeNotArithmetic "Given type must be arithmetic."

// Lua graphics-related errors.
static auto wrongDrawableDefinition(int i) -> CStr
{
        return (std::string("Error: drawable object of index ") + std::to_string(i)
                + " is not correctly defined.").c_str();
}

static constexpr auto noDrawableTypeId() -> CStr
{
        return "Error: drawable type ID was not specified.";
}

static auto badColorName(const std::string& cname) -> CStr
{
        return (std::string("Error: color name '") + cname + "' was not recognized.").c_str();
}

static auto badTextStyleName(const std::string& sname) -> CStr
{
        return (std::string("Error: text style '") + sname + "' was not recognized.").c_str();
}

static auto badFontName(const std::string& fname) -> CStr
{
        return (std::string("Error: font '") + fname + "' was not recognized.").c_str();
}

// Lua messages errors.
static constexpr auto noMessageTypeId() -> CStr
{
        return "Error: message type ID was not specified.";
}

static constexpr auto noPushStateName() -> CStr
{
        return "Error: name of the state to push was not specified.";
}

// Lua resources errors.
static constexpr auto noResourceName() -> CStr
{
        return "Error: required resource name was not specified.";
}

static constexpr auto noResourcePath() -> CStr
{
        return "Error: required resource path was not specified.";
}

}