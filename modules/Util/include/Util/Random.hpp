#pragma once


#include <Util/Concepts.hpp>
#include <Util/ErrorMessages.hpp>

#include <cstdint>
#include <random>
#include <type_traits>


namespace util
{

static auto rng = std::default_random_engine(0);

inline bool chance(const double prob = 0.5)
{
        std::bernoulli_distribution distribution(prob);
        return distribution(rng);
}

template<Arithmetic T>
inline T uniform(const T lo, const T hi)
{
        if constexpr (std::is_integral_v<T>)
        {
                return std::uniform_int_distribution<T>{ lo, hi }(rng);
        }
        else
        {
                return std::uniform_real_distribution<T>{ lo, hi }(rng);
        }
}

template<Floating T>
inline T normal(const T mean = 0, const T stddev = 1)
{
        auto distribution = std::normal_distribution<T>(mean, stddev);
        return distribution(rng);
}

template<typename RandomAccessIterator>
inline decltype(auto) oneOf(RandomAccessIterator begin, RandomAccessIterator end)
{
        return *(begin + uniform(0, static_cast<std::int32_t>(end - begin)));
}

}