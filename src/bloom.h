
#pragma once

#include <functional>
#include <iostream>
#include <utility>
#include <bitset>

#include "bitset.h"

template <
    class ElemType,
    class HashType = size_t,
    class SeedType = size_t
>
class bloom {
public:

    bloom(
        size_t size,
        std::function<HashType (ElemType, SeedType)> hash_family
        ):
        hash_family(std::move(hash_family)),
        bits(size)
        {}

    bloom(bloom&) = delete;
    bloom& operator=(bloom) = delete;

private:
    std::function<HashType (ElemType, SeedType)> hash_family;
    bitset bits;
};
