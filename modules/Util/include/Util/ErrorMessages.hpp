#pragma once


#include <Util/Types.hpp>


namespace util::err
{

// Static assertion errors.
#define typeNotArithmetic "Given type must be arithmetic."

// Lua errors.
static constexpr CStr noDrawableTypeId()
{
        return "Error: drawable type ID was not specified.";
}

static CStr badColorName(const std::string& cname)
{
        return (std::string("Error: color name '") + cname + "' was not recognized.").c_str();
}

static CStr badTextStyleName(const std::string& sname)
{
        return (std::string("Error: text style '") + sname + "' was not recognized.").c_str();
}

static CStr badFontName(const std::string& fname)
{
        return (std::string("Error: font '") + fname + "' was not recognized.").c_str();
}

}