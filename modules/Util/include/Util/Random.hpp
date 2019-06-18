#pragma once


#include <Util/ErrorMessages.hpp>

#include <cstdint>
#include <random>
#include <type_traits>


namespace util
{

static auto rng = std::default_random_engine(0);

template<typename T>
inline auto getUniformDistribution(const T lo, const T hi)
{
        static_assert(std::is_arithmetic_v<T>, typeNotArithmetic);

        if constexpr (std::is_integral_v<T>)
        {
                return std::uniform_int_distribution<T>{ lo, hi };
        }
        else if constexpr (std::is_floating_point_v<T>)
        {
                return std::uniform_real_distribution<T>{ lo, hi };
        }
}

inline bool chance(const double prob = 0.5)
{
        std::bernoulli_distribution distribution(prob);
        return distribution(rng);
}

template<typename T>
inline T uniform(const T lo, const T hi)
{
        auto distribution = getUniformDistribution(lo, hi);
        return distribution(rng);
}

template<typename T>
inline T normal(const T mean = 0, const T stddev = 1)
{
        static_assert(std::is_floating_point_v<T>, typeNotFloatingPoint);
        auto distribution = std::normal_distribution<T>(mean, stddev);
        return distribution(rng);
}

template<typename RandomAccessIterator>
inline decltype(auto) oneOf(RandomAccessIterator begin, RandomAccessIterator end)
{
        return *(begin + uniform(0, static_cast<std::int32_t>(end - begin)));
}

}