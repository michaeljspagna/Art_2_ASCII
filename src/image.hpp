#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <vector>
#include <ostream>

template<class T>
struct Image
{
    std::vector<T> elements;
    int height;
    int width;
    int pixel_size;

    Image()
    {}

    friend auto operator<< (std::ostream& os
                           ,const Image& image) -> std::ostream&
    {
        for(auto element: image.elements) {
            if(element != '\n')
                os << element << element;
            os << element;
        }
        return os;
    }
};
#endif