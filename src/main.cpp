
#include <iostream>

#include "bloom.h"

int main() {

    const char* strings[] = {
        "baz",
        "bar",
        "foo",
        "text",
        "test",
        "abc",
        "def"
    };

    const size_t size = sizeof(strings) / sizeof(*strings);

    auto hash_fn = [](const char* str, size_t seed) -> size_t {
        size_t hash = seed;

        while (char c = *str++) {
            hash = ((hash << 5) + hash) + c;
        }

        return hash;
    };

    bloom bl = bloom<const char*>::optimal_bloom(size, 0.1, hash_fn);

    for (size_t i = 0; i < size; ++i) {
        bl.add(strings[i]);
    }

    std::cout << bl.error_probability() << '\n';
    std::cout << bl.elements_count() << '\n';

    for (size_t i = 0; i < size; ++i) {
        if (bl.possibly_contains(strings[i])) {
            std::cout << strings[i] << " - contains\n";
        } else {
            std::cout << strings[i] << " - NOT\n";
        }
    }

    return 0;
}
