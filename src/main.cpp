
#include <cassert>

#include "bitset.h"

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

    return 0;
}
