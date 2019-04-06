#pragma once


#include <Engine/Engine.hpp>

#include <Util/ErrorMessages.hpp>

#include <random>
#include <type_traits>


extern bool init();

namespace util
{

class Random
{
        Random() = delete;
        friend class engine::Engine;

public:

        static auto chance(const double prob = 0.5) -> bool
        {
                std::bernoulli_distribution distribution(prob);
                return distribution(rng);
        }

        template<typename T> static auto uniform(const T lo, const T hi) -> T
        {
                auto distribution = getUniformDistribution(lo, hi);
                return distribution(rng);
        }

        template<typename T> static auto normal(const T mean = 0, const T stddev = 1) -> T
        {
                static_assert(std::is_arithmetic_v<T>, typeNotArithmetic);
                std::normal_distribution<T> distribution = { mean, stddev };
                return distribution(rng);
        }

        template<typename RandomAccessIterator>
        static auto oneOf(RandomAccessIterator begin, RandomAccessIterator end)
        {
                return *(begin + uniform(0, int(end - begin)));
        }

private:

        template<typename T> static auto getUniformDistribution(const T lo, const T hi)
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

private:

        inline static auto rng = std::default_random_engine(0);
};

}