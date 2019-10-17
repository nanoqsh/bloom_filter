
#include <iostream>
#include <string>
#include <vector>

#include "bloom.h"

int main() {

    std::vector<std::string> list = {
            "baz",
            "bar",
            "foo",
            "text",
            "test",
            "abc",
            "def",
            "fun",
            "jk",
            "qwerty"
    };

    auto hash_fn = [](const std::string &str, size_t seed) -> size_t {
        size_t hash = seed;

        for (char c : str) {
            hash = ((hash << 5) + hash) + c;
        }

        return hash;
    };

    bloom bl = bloom<const std::string &>::optimal_bloom(list.size() * 2, 0.01, hash_fn);

    for (const std::string &str : list) {
        bl.add(str);
    }

    std::cout << bl.error_probability() << '\n';
    std::cout << bl.bits_count() << '\n';
    std::cout << bl.elements_count() << '\n';

    for (const std::string &str : list) {
        if (bl.possibly_contains(str)) {
            std::cout << str << " - contains\n";
        } else {
            std::cout << str << " - NOT\n";
        }
    }

    std::vector<std::string> extra_list = {
            "NOT_baz",
            "NOT_bar",
            "NOT_foo",
            "NOT_text",
            "NOT_test",
            "NOT_abc",
            "NOT_def",
            "NOT_fun",
            "NOT_jk",
            "NOT_qwerty"
    };

    for (const std::string &str : extra_list) {
        if (bl.possibly_contains(str)) {
            std::cout << str << " - contains\n";
        } else {
            std::cout << str << " - NOT\n";
        }
    }

    return 0;
}
