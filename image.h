#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include <fstream>
using std::ifstream;

#include <vector>
using std::vector;

#include "string"
using std::string;

class image{
    public:

        class pixel{
            public:

                unsigned char blue;
                unsigned char green;
                unsigned char red;

                pixel();
                pixel(unsigned char b, unsigned char g, unsigned char r);
                double getLuminance();
        };


        int height;
        int width;
        unsigned int pixelDepth;

        image();
        image(string inputFile);

        vector< vector<pixel> > vec;

        int swap(unsigned char b1, unsigned char b2);
        void toFile(string name);
        void invert();
        void flipX();
        void flipY();
        void blur();
        void greyScale();
        void rotateRight();
        void rotateLeft();
        void edgeDetect();
};

#endif // IMAGE_H_INCLUDED
