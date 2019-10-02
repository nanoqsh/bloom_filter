
#include <cassert>

#include "bitset.h"
#include "seeded_function_set.h"

int main() {

    bitset bits(45);
    bits.set(8, true);
    bits.set(9);
    bits.set(10);
    bits.set(11);
    bits.set(11, false);

    assert(!bits.get(0));
    assert(!bits.get(1));
    assert(!bits.get(2));
    assert(!bits.get(3));
    assert( bits.get(9));
    assert( bits.get(10));
    assert(!bits.get(11));
    assert(!bits.get(12));

    bitset bits2 = bits;
    assert(!bits2.get(0));
    assert(!bits2.get(1));
    assert(!bits2.get(2));
    assert(!bits2.get(3));
    assert( bits2.get(9));
    assert( bits2.get(10));
    assert(!bits2.get(11));
    assert(!bits2.get(12));

    std::cout << bits << '\n';
    std::cout << bits2 << '\n';

    bits2.set(0);
    bits = std::move(bits2);

    std::cout << bits << '\n';

    seeded_function_set<int> fn_set(12, [](const int& par, size_t seed) -> size_t {
        std::cout << seed << '\n';
        return par + seed;
    });

    for (size_t i = 0; i < 12; ++i) {
        size_t hash = fn_set[i](12);
        std::cout << "hash: " << hash << '\n';
    }

    return 0;
}
