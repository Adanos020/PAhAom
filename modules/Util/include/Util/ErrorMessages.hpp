#pragma once


#include <Util/Types.hpp>

#include <string>


namespace util::err
{

// Static assertion errors.
#define typeNotArithmetic "Given type must be arithmetic."

// Lua type errors.
static const std::string notATable = "Error: given value was expected to be a table.";

// Lua graphics-related errors.
static const std::string matrixNotRegular = "Error: all columns in a matrix must have equal lengths.";
static const std::string noDrawableTypeId = "Error: drawable type ID was not specified.";

inline std::string wrongDrawableDefinition(int i)
{
        return std::string("Error: drawable object of index ") + std::to_string(i)
               + " is not correctly defined.";
}

inline std::string badColorName(const std::string& cname)
{
        return std::string("Error: color name '") + cname + "' was not recognized.";
}

inline std::string badTextStyleName(const std::string& sname)
{
        return std::string("Error: text style '") + sname + "' was not recognized.";
}

inline std::string badFontName(const std::string& fname)
{
        return std::string("Error: font '") + fname + "' was not recognized.";
}

inline std::string badTextureName(const std::string& fname)
{
        return std::string("Error: texture '") + fname + "' was not recognized.";
}

static const std::string noTexture      = "Error: required texture was not specified";
static const std::string noTileSize     = "Error: required tile size was not specified";
static const std::string noTileIconSize = "Error: required tile icon size was not specified";

// Lua messages errors.
static const std::string noMessageTypeId = "Error: message type ID was not specified.";
static const std::string noPushStateName = "Error: name of the state to push was not specified.";

// Lua resources errors.
static const std::string noResourceName = "Error: required resource name was not specified.";
static const std::string noResourcePath = "Error: required resource path was not specified.";

}