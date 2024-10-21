#pragma once

#include <cstdio>
#include <memory>
#include <string>

// Functions.

namespace util
{

using CStr = const char*;

template<typename... Args>
std::string format(CStr fmt, Args... args)
{
        std::size_t size = std::snprintf(nullptr, 0, fmt, std::forward<Args>(args)...) + 1;
        auto buf = std::make_unique<char[]>(size);
        std::snprintf(buf.get(), size, fmt, std::forward<Args>(args)...);
        return std::string(buf.get(), buf.get() + size - 1);
}

}
