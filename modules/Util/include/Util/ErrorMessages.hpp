#pragma once


#include <Util/Types.hpp>

#include <string>


namespace util::err
{

// Static assertion errors.
#define typeNotArithmetic "Given type must be arithmetic."

// Lua graphics-related errors.
static std::string wrongDrawableDefinition(int i)
{
        return std::string("Error: drawable object of index ") + std::to_string(i)
               + " is not correctly defined.";
}

static constexpr CStr noDrawableTypeId()
{
        return "Error: drawable type ID was not specified.";
}

static std::string badColorName(const std::string& cname)
{
        return std::string("Error: color name '") + cname + "' was not recognized.";
}

static std::string badTextStyleName(const std::string& sname)
{
        return std::string("Error: text style '") + sname + "' was not recognized.";
}

static std::string badFontName(const std::string& fname)
{
        return std::string("Error: font '") + fname + "' was not recognized.";
}

static std::string badTextureName(const std::string& fname)
{
        return std::string("Error: texture '") + fname + "' was not recognized.";
}

// Lua messages errors.
static constexpr CStr noMessageTypeId()
{
        return "Error: message type ID was not specified.";
}

static constexpr CStr noPushStateName()
{
        return "Error: name of the state to push was not specified.";
}

// Lua resources errors.
static constexpr CStr noResourceName()
{
        return "Error: required resource name was not specified.";
}

static constexpr CStr noResourcePath()
{
        return "Error: required resource path was not specified.";
}

}