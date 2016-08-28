/**
 * @file src/program/funcs/strings.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef FUNCS_STRINGS_HPP
#define FUNCS_STRINGS_HPP

#include <string>
#include <sstream>
#include <vector>

namespace rr
{

    ////////////////////////////////////////////////////////////////////////
    /// \brief Converts a given wide string to a string.
    ////////////////////////////////////////////////////////////////////////
    inline std::string
    wtoa(const std::wstring& wide)
    {
        std::string out;
        std::transform(wide.begin(), wide.end(), std::back_inserter(out), [](wchar_t ch) -> char { return static_cast<char>(ch); });
        return out;
    }

    ////////////////////////////////////////////////////////////////////////
    /// \brief Converts a given string to a wide string.
    ////////////////////////////////////////////////////////////////////////
    inline std::wstring
    atow(const std::string& str)
    {
        std::wstring out;
        std::transform(str.begin(), str.end(), std::back_inserter(out), [](char ch) -> wchar_t { return static_cast<wchar_t>(ch); });
        return out;
    }

    ////////////////////////////////////////////////////////////////////////
    /// \brief Splits a given string into a vector.
    ////////////////////////////////////////////////////////////////////////
    inline std::vector<std::string>&
    split(const std::string &s, char delim, std::vector<std::string> &elems)
    {
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delim))
        {
            elems.push_back(item);
        }
        return elems;
    }

    ////////////////////////////////////////////////////////////////////////
    /// \brief Splits a given string into a vector.
    ////////////////////////////////////////////////////////////////////////
    inline std::vector<std::string>
    split(const std::string &s, char delim)
    {
        std::vector<std::string> elems;
        split(s, delim, elems);
        return elems;
    }

    ////////////////////////////////////////////////////////////////////////
    /// \brief Converts an UTF-8 string to an UTF-32 string.
    ////////////////////////////////////////////////////////////////////////
    inline sf::String
    utf8ToUtf32(const std::string& str)
    {
        sf::String res;
        sf::Uint32 c;

        auto it=str.begin();
        while (it!=str.end())
        {
            it = sf::Utf8::decode(it, str.end(), c, 0u);
            if (c!=0u)
                res += c;
        }
        return res;
    }

    ////////////////////////////////////////////////////////////////////////
    /// \brief Converts an UTF-32 string to an UTF-8 string.
    ////////////////////////////////////////////////////////////////////////
    inline std::string
    utf32toUtf8(const sf::String& str)
    {
        std::string res;
        char buf[5];

        for (auto it=str.begin(); it!=str.end(); ++it)
        {
            auto end = sf::Utf8::encode(*it, buf);
            *end = '\0';
            res += buf;
        }
        return res;
    }

}

#endif // FUNCS_STRINGS_HPP
