#ifndef IMAGE_UTILS_HPP
#define IMAGE_UTILS_HPP

#include <string>
#include "image.hpp"
#include "pixel.hpp"


namespace utils
{
    std::string ascii = "`^\",:;Il!i~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";

    auto generate_pixel_image(Image<Pixel>&
                             ,std::string&) -> void;

    auto generate_ascii_image(Image<Pixel>&
                             ,Image<char>&) -> void;

    auto load_image(Image<Pixel>&
                   ,std::string&) -> unsigned char*;

    auto validate_image(Image<Pixel>&) -> void;

    auto create_pixels(Image<Pixel>&
                      ,unsigned char*) -> void;

    

    auto ptr_to_pixel(Pixel&
                     ,unsigned char*
                     ,int) -> void;

    auto rgb_to_ascii(Pixel&) -> char;

    auto rgb_to_brightness(Pixel&) -> int;

    auto brightness_to_ascii(int) -> char;
    

};

#endif