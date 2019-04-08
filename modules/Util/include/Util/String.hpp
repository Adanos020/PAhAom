#pragma once


#include <Util/Types.hpp>

#include <cstdio>


// Operator overloads.

std::string operator+(util::CStr lhs, const std::string& rhs)
{
        return std::string(lhs) + rhs;
}

// Functions.

namespace util
{

template<typename... Args>
std::string format(CStr fmt, Args... args)
{
        size_t size = std::snprintf(nullptr, 0, fmt, std::forward<Args...>(args...)) + 1;
        auto buf = std::make_unique<char[]>(size);
        std::snprintf(buf.get(), size, fmt, std::forward<Args...>(args...));
        return std::string(buf.get(), buf.get() + size - 1);
}

}