
#include <cassert>

#include "bitset.h"

int main() {

    bitset bits(45);
    bits.set(8);
    bits.set(9);
    bits.set(10);
    bits.set(11);
    bits.unset(11);

    assert(!bits.get(0));
    assert(!bits.get(1));
    assert(!bits.get(2));
    assert(!bits.get(3));
    assert(bits.get(9));
    assert(bits.get(10));
    assert(!bits.get(11));
    assert(!bits.get(12));

    return 0;
}
