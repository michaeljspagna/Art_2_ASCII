#include "image_utils.hpp"
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb-master/stb_image.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "../include/stb-master/stb_image_resize.h"

auto utils::generate_pixel_image(Image<Pixel>& image
                                ,std::string& filename) -> void
{
    unsigned char* data = utils::load_image(image
                                           ,filename);

    
    utils::create_pixels(image, data);
}

auto utils::load_image(Image<Pixel>& image
                      ,std::string& filename) -> unsigned char*
{
    return stbi_load(filename.c_str()
                    ,&image.width
                    ,&image.height
                    ,&image.pixel_size
                    ,3);
}

auto validate_image(Image<Pixel>& image) -> void
{
    if(image.width >= 1000 || image.height >= 1000){
        std::cout << "image too large" << '\n';
        throw 1;
    }else if(image.pixel_size != 3){
        std::cout << "Invalid format" << '\n';
        throw 2;
    }
}

auto utils::generate_ascii_image(Image<Pixel>& pixel_image
                                ,Image<char>& ascii_image) -> void
{
    std::transform(pixel_image.elements.begin()
                  ,pixel_image.elements.end()
                  ,std::back_inserter(ascii_image.elements)
                  ,utils::rgb_to_ascii);
}

auto utils::create_pixels(Image<Pixel>& image
                    ,unsigned char* data) -> void
{
    auto end(image.height*image.width*image.pixel_size), adjuster(0), row_len(image.width*image.pixel_size);
    while(adjuster < end){
        auto cur(0);
        while(cur < row_len) {
            Pixel p;
            utils::ptr_to_pixel(p, data, cur+adjuster);
            image.elements.push_back(p);
            cur += image.pixel_size;
        }
        adjuster += row_len;
        image.elements.push_back(Pixel(-1,-1,-1));
    }
}

auto utils::ptr_to_pixel(Pixel& p
                        ,unsigned char* data
                        ,int start) -> void
{
    p = Pixel((int) data[start]
             ,(int) data[start+1]
             ,(int) data[start+2]);

}

auto utils::rgb_to_ascii(Pixel& pix) -> char
{
    auto brightness(utils::rgb_to_brightness(pix));
    // std::cout << brightness << " ";
    return utils::brightness_to_ascii(brightness);
}

auto utils::rgb_to_brightness(Pixel& pix) -> int
{

    return std::round(0.21*pix.r
           +0.72*pix.g
           +0.07*pix.b);
}

auto utils::brightness_to_ascii(int brightness) -> char
{
    /* Map [0-255] -> [0-64]; f(brightness) = (ascii_max/brightness_max) * brightness */
    if(brightness < 0) 
        return '\n';
    double brightness_max(255), ascii_max(utils::ascii.size()-1);
    auto slope = ascii_max / brightness_max;
    auto index = std::round(brightness * slope);
    return utils::ascii[index];
}

int main(int argc, char const *argv[])
{
    std::string filename = "../img/pineapple.jpg";
    Image<Pixel> pixel_image;
    utils::generate_pixel_image(pixel_image, filename);
    Image<char> ascii_image;
    utils::generate_ascii_image(pixel_image, ascii_image);
    std::cout << ascii_image;
    return 0;
}
