#pragma once


#include <luapp.hpp>


namespace script
{

template<typename Return>
inline static Return hasOpt(const lua::Table& v, const std::string& name, const Return rFalse)
{
        if (v[name])
        {
                if constexpr (std::is_fundamental_v<Return>)
                {
                        return v[name].to<Return>();
                }
                else
                {
                        return Return(lua::Table(v[name]));
                }
        }
        return rFalse;
}

}