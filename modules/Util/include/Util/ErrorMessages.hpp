#pragma once


#include <Util/String.hpp>
#include <Util/Types.hpp>

#include <string>


namespace util::err
{

#define ErrMsg static const std::string

// Static assertion errors.
#define typeNotArithmetic "Given type must be arithmetic."
#define typeNotFloatingPoint "Given type must be a floating point number."
#define typeNotDrawable "Given class must derive from sf::Drawable."
#define typeNotResource "Resource type is not recognised."

// Engine errors.
ErrMsg noInitialState = "Error: no initial state was pushed.";

// Lua type errors.
ErrMsg notATable = "Error: given value was expected to be a table.";
ErrMsg notAFunction = "Error: given value was expected to be a function.";

// Lua graphics-related errors.
ErrMsg matrixNotRegular = "Error: all columns in a matrix must have equal lengths.";
ErrMsg noDrawableTypeId = "Error: drawable type ID was not specified.";

inline std::string wrongDrawableDefinition(int i)
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

ErrMsg noTexture      = "Error: required texture was not specified";
ErrMsg noTileSize     = "Error: required tile size was not specified";
ErrMsg noTileIconSize = "Error: required tile icon size was not specified";

// Lua messages errors.
ErrMsg noMessageTypeId = "Error: message type ID was not specified.";
ErrMsg noPushSceneName = "Error: name of the state to push was not specified.";

// Lua resources errors.
ErrMsg noResourceName = "Error: required resource name was not specified.";
ErrMsg noResourcePath = "Error: required resource path was not specified.";

#undef ErrMsg

}