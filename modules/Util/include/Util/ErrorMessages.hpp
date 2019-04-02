#pragma once


#include <Util/Types.hpp>


namespace util::err
{

// Static assertion errors.
#define typeNotArithmetic "Given type must be arithmetic."

// Lua errors.
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

}