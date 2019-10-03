
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
        bits_size(size),
        array_size(ceil(size / 8.0)),
        bits(std::make_unique<uint8_t[]>(array_size))
    {
        memset(bits.get(), 0, array_size);
    }

    bitset(bitset& other):
        bits_size(other.bits_size),
        array_size(other.array_size),
        bits(std::make_unique<uint8_t[]>(array_size))
    {
        memcpy(bits.get(), other.bits.get(), array_size);
    }

    bitset(bitset&& rht) noexcept:
            bits_size(rht.bits_size),
        array_size(rht.array_size),
        bits(std::move(rht.bits))
    {}

    bitset& operator=(bitset& _) = delete;

    bitset& operator=(bitset&& rht) noexcept {
        bits_size = rht.bits_size;
        array_size = rht.array_size;
        bits = std::move(rht.bits);
        return *this;
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

    bool get(size_t pos) const {
        position p = locate_bit(pos);
        return (bool)(bits[p.base] >> p.step) & 1U;
    }

    size_t size() const {
        return bits_size;
    }

    friend std::ostream & operator<<(std::ostream &out, const bitset& rht);

private:
    struct position {
        size_t base;
        size_t step;
    };

    position locate_bit(size_t pos) const {
        size_t base = pos / 8;
        size_t step = pos % 8;

        if (base >= array_size) {
            throw std::out_of_range("Out of bitset range");
        }

        return { base, step };
    }

    size_t bits_size;
    size_t array_size;
    std::unique_ptr<uint8_t[]> bits;
};

std::ostream &operator<<(std::ostream &out, const bitset &rht) {
    using namespace std;

    ios_base::fmtflags defs(out.flags());

    for (size_t i = 0; i < rht.array_size; ++i) {
        out << setfill('0') << setw(2) << hex << (int) rht.bits[i] << ' ';
    }

    out.flags(defs);
    return out;
}
