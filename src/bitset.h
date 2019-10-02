
#pragma once

#include <cinttypes>
#include <cstdlib>
#include <memory>
#include <cstring>
#include <cmath>
#include <stdexcept>
#include <iomanip>
#include <iostream>

class bitset
{
public:
    explicit bitset(size_t size):
        size(size),
        array_size(ceil(size / 8.0)),
        bits(std::make_unique<uint8_t[]>(array_size))
    {
        memset(bits.get(), 0, array_size);
    }

    bitset(bitset& other):
        size(other.size),
        array_size(other.array_size),
        bits(std::make_unique<uint8_t[]>(array_size))
    {
        memcpy(bits.get(), other.bits.get(), array_size);
    }

    bitset& operator=(bitset& _) = delete;

    void dump() {
        using namespace std;

        ios_base::fmtflags defs(cout.flags());

        for (size_t i = 0; i < array_size; ++i)
            cout << setfill('0') << setw(2) << hex << (int)bits[i] << ' ';

        cout << '\n';
        cout.flags(defs);
    }

    void set(size_t pos) {
        position p = locate_bit(pos);
        bits[p.base] |= 1U << p.step;
    }

    void set(size_t pos, bool value) {
        if (value) {
            set(pos);
        } else {
            unset(pos);
        }
    }

    void unset(size_t pos) {
        position p = locate_bit(pos);
        bits[p.base] &= ~(1U << p.step);
    }

    uint8_t get(size_t pos) {
        position p = locate_bit(pos);
        return (uint8_t)(bits[p.base] >> p.step) & 1U;
    }

private:
    struct position {
        size_t base;
        size_t step;
    };

    position locate_bit(size_t pos) {
        size_t base = pos / 8;
        size_t step = pos % 8;

        if (base >= array_size)
            throw std::out_of_range("Out of bitset range");

        return {base, step};
    }

    size_t size;
    size_t array_size;
    std::unique_ptr<uint8_t[]> bits;
};
