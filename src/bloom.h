
#pragma once

#include <functional>
#include <iostream>
#include <utility>
#include <bitset>

#include "bitset.h"
#include "seeded_function_set.h"

template <
    class ElemType,
    class HashType = size_t,
    class ArgType = const ElemType&,
    class FuncSet = seeded_function_set<ElemType, HashType, ArgType>
>
class bloom {
public:

    explicit bloom(
        size_t size,
        std::function<HashType (ArgType, size_t)> hash_fn
        ):
        bits(size),
        function_set(FuncSet(size + - 1, hash_fn))
        {}

    bloom(bloom&) = delete;
    bloom& operator=(bloom) = delete;

private:
    bitset bits;
    FuncSet function_set;
};
