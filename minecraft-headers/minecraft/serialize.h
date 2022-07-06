#pragma once

struct BinaryStream;
struct ReadOnlyBinaryStream;

template<typename T>
struct serialize {
    static void write(T const &, BinaryStream &);

    static T read(ReadOnlyBinaryStream &);
};
