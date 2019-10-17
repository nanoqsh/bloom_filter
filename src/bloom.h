
#pragma once

#include <functional>
#include <cmath>
#include <stdexcept>
#include <utility>

#include "bitset.h"
#include "seeded_function_set.h"

template<
        class ArgType,
        class FuncSet = seeded_function_set<ArgType>
>
class bloom {
public:

    bloom(
            size_t size,
            size_t num_hash_functions,
            std::function<size_t(ArgType, size_t)> hash_fn
    ) :
            bits(size),
            function_set(num_hash_functions, hash_fn) {}

    bloom(bloom &) = delete;
    bloom &operator=(bloom) = delete;

    bloom(bloom&&) = default;
    bloom& operator=(bloom&&) = default;

    void add(ArgType item) {
        for (size_t i = 0; i < function_set.size(); ++i) {
            size_t hash = function_set[i](item);
            bits.set(hash % bits.size());
        }

        ++count;
    }

    bool possibly_contains(ArgType item) const {
        for (size_t i = 0; i < function_set.size(); ++i) {
            size_t hash = function_set[i](item);
            if (!bits.get(hash % bits.size())) {
                return false;
            }
        }

        return true;
    }

    double error_probability() const {
        double k = function_set.size();
        return pow(1.0 - exp(-k * count / (double) bits.size()), k);
    }

    size_t elements_count() const {
        return count;
    }

    size_t bits_count() const {
        return bits.size();
    }

    static bloom optimal_bloom(
            size_t max_elements,
            double error_probability,
            std::function<size_t(ArgType, size_t)> hash_fn
    ) {
        if (error_probability <= 0 || error_probability > 1) {
            throw std::invalid_argument(
                    "'error_probability' must be between 0 (exclusively) and 1 (inclusively)"
                    );
        }

        double ln2 = log(2.0);
        size_t size = ceil(-(max_elements * log(error_probability)) / (ln2 * ln2));
        size_t num_hash_functions = ceil((size / (double) max_elements) * ln2);

        return bloom(size, num_hash_functions, hash_fn);
    }

private:
    bitset bits;
    FuncSet function_set;
    size_t count = 0;
};
