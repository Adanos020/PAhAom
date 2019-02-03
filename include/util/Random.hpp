#pragma once


#include <random>
#include <type_traits>


extern bool init();

namespace util
{

class Random
{
        Random() = delete;
        friend bool ::init();

public:

        static bool chance(const double prob = 0.5)
        {
                std::bernoulli_distribution distribution(prob);
                return distribution(rng);
        }

        template<typename T> static T uniform(const T lo, const T hi)
        {
                auto distribution = getUniformDistribution(lo, hi);
                return distribution(rng);
        }

        template<typename T> static T normal(const T mean = 0, const T stddev = 1)
        {
                static_assert(std::is_arithmetic<T>::value, "Given type must be arithmetic.");
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
                static_assert(std::is_arithmetic<T>::value, "Given type must be arithmetic.");

                if constexpr (std::is_integral<T>::value)
                {
                        return std::uniform_int_distribution<T>{ lo, hi };
                }
                else if constexpr (std::is_floating_point<T>::value)
                {
                        return std::uniform_real_distribution<T>{ lo, hi };
                }
        }

private:

        inline static auto rng = std::default_random_engine(0);
};

}