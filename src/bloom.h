
#pragma once

#include <functional>
#include <cmath>

#include "bitset.h"
#include "seeded_function_set.h"

template <
    class ArgType,
    class HashType = size_t,
    class FuncSet = seeded_function_set<ArgType, HashType>
>
class bloom {
public:

    bloom(
        size_t size,
        size_t num_hash_functions,
        std::function<HashType (ArgType, size_t)> hash_fn
        ):
        bits(size),
        function_set(num_hash_functions, hash_fn)
    {}

    static bloom optimal_bloom(
        size_t max_elements,
        double error_probability,
        std::function<HashType (ArgType, size_t)> hash_fn
        )
    {
        double ln2 = log(2.0);
        size_t size = ceil(-(max_elements * log(error_probability)) / (ln2 * ln2));
        size_t num_hash_functions = ceil((size / (double)max_elements) * ln2);

        return bloom(size, num_hash_functions, hash_fn);
    }

    bloom(bloom&) = delete;
    bloom& operator=(bloom) = delete;

    void add(ArgType element) {
        for (size_t i = 0; i < function_set.size(); ++i) {
            HashType hash = function_set[i](element);
            bits.set(hash % bits.size());
        }

        count++;
    }

    bool possibly_contains(ArgType element) const {
        for (size_t i = 0; i < function_set.size(); ++i) {
            HashType hash = function_set[i](element);
            if (!bits.get(hash % bits.size())) {
                return false;
            }
        }

        return true;
    }

    double error_probability() const {
        double k = function_set.size();
        return pow(1.0 - exp(-k * count / (double)bits.size()), k);
    }

    size_t elements_count() const {
        return count;
    }

private:
    bitset bits;
    FuncSet function_set;
    size_t count = 0;
};
