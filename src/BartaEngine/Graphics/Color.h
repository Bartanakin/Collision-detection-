#pragma once

namespace Barta{
    struct Color {
    public:
        Color() noexcept = default;
        Color(
            unsigned char r,
            unsigned char g,
            unsigned char b,
            unsigned char a
        ) noexcept :
            r(r),
            g(g),
            b(b),
            a(a)
        {}
        ~Color() noexcept = default;
        
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    };
}

