#pragma once

#include <cstdint>
#include <string>

namespace mce {

    struct Color {
        float r;
        float g;
        float b;
        float a;

        static class mce::Color fromHexString(std::string const &);

        bool operator==(class mce::Color const &) const;

        int toABGR(void) const;

        int toARGB(void) const;

        std::string toHexString(void) const;
    };

}
