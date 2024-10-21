#pragma once

#include <Util/String.hpp>
#include <Util/Types.hpp>

#include <cstdint>
#include <string>

namespace util::err
{

// Engine errors.
inline const std::string noInitialState = "Error: no initial state was pushed.";

// Lua type errors.
inline const std::string notATable = "Error: given value was expected to be a table.";
inline const std::string notAFunction = "Error: given value was expected to be a function.";
inline const std::string notANumber = "Error: given value was expected to be a number.";

// Lua graphics-related errors.
inline const std::string matrixNotRegular = "Error: all columns in a matrix must have equal lengths.";
inline const std::string noDrawableTypeId = "Error: drawable type ID was not specified.";

inline std::string wrongDrawableDefinition(int32_t i)
{
        return format("Error: drawable object of index %d is not correctly defined.", i);
}

inline std::string badColorName(const std::string& name)
{
        return format("Error: color name '%s' was not recognized.", name.c_str());
}

inline std::string badTextStyleName(const std::string& name)
{
        return format("Error: text style '%s' was not recognized.", name.c_str());
}

inline std::string badFontName(const std::string& name)
{
        return format("Error: font '%s' was not recognized.", name.c_str());
}

inline std::string badTextureName(const std::string& name)
{
        return format("Error: texture '%s' was not recognized.", name.c_str());
}

inline const std::string noTexture      = "Error: required texture was not specified";
inline const std::string noTileSize     = "Error: required tile size was not specified";
inline const std::string noTileIconSize = "Error: required tile icon size was not specified";

// Lua messages errors.
inline const std::string noMessageTypeId = "Error: message type ID was not specified.";
inline const std::string noPushSceneName = "Error: name of the state to push was not specified.";

// Lua resources errors.
inline const std::string noResourceName = "Error: required resource name was not specified.";
inline const std::string noResourcePath = "Error: required resource path was not specified.";

}
