
#pragma once

#include <vector>
#include <string>
#include <functional>
#include <random>

template <
    class ArgType,
    class HashType = size_t
>
class seeded_function_set {
public:
    seeded_function_set(
        size_t size,
        std::function<HashType (ArgType, size_t)> hash_fn):
        seeds(),
        hash_fn(hash_fn)
    {
        std::default_random_engine gen;
        std::uniform_int_distribution<size_t> distribution;

        seeds.reserve(size);

        for (size_t i = 0; i < size; ++i) {
            seeds.push_back(distribution(gen));
        }
    }

    std::function<HashType (ArgType)> operator[](size_t idx) const {
        if (idx >= seeds.size()) {
            throw std::out_of_range("Out of bitset range");
        }

        size_t seed = seeds[idx];

        return [seed, this](ArgType element) -> size_t {
            return hash_fn(element, seed);
        };
    }

    size_t size() const {
        return seeds.size();
    }

private:
    std::vector<size_t> seeds;
    std::function<HashType (ArgType, size_t)> hash_fn;
};
