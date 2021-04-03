#ifndef PIXEL_HPP
#define PIXEL_HPP
#include <ostream>
struct Pixel
{
    int r;
    int g;
    int b;

    Pixel()
    {}

    Pixel(int r_
         ,int g_
         ,int b_)
    :r(r_), g(g_), b(b_)
    {}

    friend auto operator<< (std::ostream& os
                           ,const Pixel& pixel) -> std::ostream&
    {
        os  << "(r{"
            << pixel.r 
            << "}, g{"
            << pixel.g
            << "}, b{"
            << pixel.b
            << "})";
        return os;
    }
};

#endif