#pragma once

#include <stdint.h>

template <int entries>
struct BitSet {
    BitSet<entries / 2> upper;
    BitSet<entries / 2> lower;

    bool operator[](size_t index) {
        if (index < (entries / 2)) return lower[index];
        return upper[index - (entries / 2)];
    }
};

template <>
struct BitSet<64> {
    uint64_t data;

    bool operator[](size_t index) const {
        return (bool)((data >> index) & 1);
    }
};

template <>
struct BitSet<32> {
    uint32_t data;

    bool operator[](size_t index) const {
        return (bool)((data >> index) & 1);
    }
};

template <>
struct BitSet<16> {
    uint16_t data;

    bool operator[](size_t index) const {
        return (bool)((data >> index) & 1);
    }
};

template <>
struct BitSet<8> {
    uint8_t data;

    bool operator[](size_t index) const {
        return (bool)((data >> index) & 1);
    }
};

template <>
struct BitSet<1> {
    bool data;

    bool operator[](size_t index) const {
        return data;
    }
};

template <typename T, int keyBits, int entryBits>
struct SparseTable {
    BitSet<1 << entryBits>                         presentEntries;
    SparseTable<T, keyBits - entryBits, entryBits> entries[0];

    const T *operator[](size_t index) const {
        size_t subindex = (index >> (keyBits - entryBits)) & ((1 << entryBits) - 1);
        if (!presentEntries[subindex]) return nullptr;
        size_t realIndex = 0;
        for (int i = 0; i < subindex; i++)
            if (presentEntries[subindex]) realIndex++;
        return entries[realIndex][index & ((1 << (keyBits - entryBits)) - 1)];
    }
};

template <typename T, int entryBits>
struct SparseTable<T, 0, entryBits> {
    T        value;
    const T *operator[](size_t index) const {
        return &value;
    }
};