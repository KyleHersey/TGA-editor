#include "image.h"

#include "iostream"
using std::cout;
using std::endl;

#include "cmath"
using std::abs;

#include <cstdlib>
#include <time.h>

#include <fstream>
using std::ifstream;
using std::ofstream;

#include "string"
using std::string;

//zero parameter constructor
image::image(){}

//creates an imagefril from a string
image::image(string inputFile){

    ifstream strm(inputFile.c_str(), std::ios::binary);

    //move to correct place in file
    for(int i = 0; i <= 11; i ++){
        strm.get();
    }

    //determines the width and height of the image
    unsigned char widthF1 = strm.get();
    unsigned char widthF2 = strm.get();
    unsigned char heightF1 = strm.get();
    unsigned char heightF2 = strm.get();

    width = swap(widthF1, widthF2);
    height = swap(heightF1, heightF2);
    pixelDepth = strm.get();

    //move 1 place in file
    strm.get();

    vec.resize(width, vector<pixel>(height));

//assigns pixel objects to a two-dimensional vector
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            unsigned char blue = strm.get();
            unsigned char green = strm.get();
            unsigned char red = strm.get();
            strm.get();

            pixel tempPixel(blue, green, red);

            vec[i][j] = tempPixel;

        }
    }
}

int image::swap(unsigned char b1, unsigned char b2){
    int result = 0;
    result = (b2 << 8) | b1;
    return result;
}

void image::toFile(string name){
    ifstream strm("flower.tga");
    ofstream out(name.c_str());

//copy through 1 after size
    for(int i = 0; i < 18; i++){
        char temp = strm.get();
        out.write(&temp, 1);
    }
    for(int i = 0; i < 3; i++){
        strm.get();
    }

    char ff = strm.get();

    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            char blue = vec[i][j].blue;
            char green = vec[i][j].green;
            char red = vec[i][j].red;

            out.write(&blue,1);
            out.write(&green,1);
            out.write(&red,1);
            out.write(&ff,1);
        }
    }

    out.close();
    strm.close();
}

//inverts each pixel
void image::invert(){
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            vec[i][j].blue = 255 - vec[i][j].blue;
            vec[i][j].green = 255 - vec[i][j].green;
            vec[i][j].red = 255 - vec[i][j].red;
        }
    }
}

//flips the pixel's position horizontally
void image::flipX(){
    image tempImage = *this;

    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            vec[i][j] = tempImage.vec[i][width-1 -j];
        }
    }
}

//fl;ips the pixel's position vertically
void image::flipY(){
    image tempImage = *this;

    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            vec[i][j] = tempImage.vec[height-1 -i][j];
        }
    }
}

//makes each pixel the average of its surrounding cells
void image::blur(){
    //make original image copy
    vector< vector<pixel> > backup;

    backup.resize(height, vector<pixel>(width));

    for(int i = 0; i <  height; i++){
        for(int j = 0; j < width; j++){
            backup[i][j] = vec[i][j];
        }
    }

    //find average pixel in 3x3 square
    for(int i = 1; i < width-1; i++){
        for(int j = 1; j < height-1; j++){

            unsigned char sumBlue = backup[i-1][j-1].blue*1/9;
            sumBlue += backup[i-1][j].blue*1/9;
            sumBlue += backup[i-1][j+1].blue*1/9;
            sumBlue += backup[i][j-1].blue*1/9;
            sumBlue += backup[i][j].blue*1/9;
            sumBlue += backup[i][j+1].blue*1/9;
            sumBlue += backup[i+1][j-1].blue*1/9;
            sumBlue += backup[i+1][j].blue*1/9;
            sumBlue += backup[i+1][j+1].blue*1/9;


            unsigned char sumGreen = backup[i-1][j-1].green*1/9;
            sumGreen += backup[i-1][j].green*1/9;
            sumGreen += backup[i-1][j+1].green*1/9;
            sumGreen += backup[i][j-1].green*1/9;
            sumGreen += backup[i][j].green*1/9;
            sumGreen += backup[i][j+1].green*1/9;
            sumGreen += backup[i+1][j-1].green*1/9;
            sumGreen += backup[i+1][j].green*1/9;
            sumGreen += backup[i+1][j+1].green*1/9;

            unsigned char sumRed = backup[i-1][j-1].red*1/9;
            sumRed += backup[i-1][j].red*1/9;
            sumRed += backup[i-1][j+1].red*1/9;
            sumRed += backup[i][j-1].red*1/9;
            sumRed += backup[i][j].red*1/9;
            sumRed += backup[i][j+1].red*1/9;
            sumRed += backup[i+1][j-1].red*1/9;
            sumRed += backup[i+1][j].red*1/9;
            sumRed += backup[i+1][j+1].red*1/9;

            pixel tempPixel(sumBlue,sumGreen, sumRed);

            vec[i][j] = tempPixel;
        }
    }
}

//makes the rgb values of each pixel equal, and scale to the total luminosity
void image::greyScale(){
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){

            double luminance = vec[i][j].getLuminance();

            unsigned char all = luminance*255;
            vec[i][j].blue = all;
            vec[i][j].green = all;
            vec[i][j].red = all;
        }
    }
}

void image::rotateRight(){

    vector< vector<pixel> > backup;
    backup.resize(height, vector<pixel>(width));

    for(int i = 0; i <  height; i++){
        for(int j = 0; j < width; j++){
            backup[i][j] = vec[i][j];
        }
    }

    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            vec[i][j] = backup[j][width-1 -i];
        }
    }
}

void image::rotateLeft(){

    vector< vector<pixel> > backup;
    backup.resize(height, vector<pixel>(width));

    for(int i = 0; i <  height; i++){
        for(int j = 0; j < width; j++){
            backup[i][j] = vec[i][j];
        }
    }

    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            vec[i][j] = backup[height-1 -j][i];
        }
    }
}

//make the brightness of each pixel relative to the change in luminosity near it
void image::edgeDetect(){
    vector< vector<pixel> > backup;
    backup.resize(height, vector<pixel>(width));

    for(int i = 0; i <  height; i++){
        for(int j = 0; j < width; j++){
            backup[i][j] = vec[i][j];
        }
    }

    //acquire the changes in luminosity
    for(int i = 1; i <  height-1; i++){
        for(int j = 1; j < width-1; j++){

            double upLeftLuminance = backup[i+1][j-1].getLuminance();
            double downRightluminance = backup[i-1][j+1].getLuminance();
            double dif1 = abs(upLeftLuminance-downRightluminance);

            double upRightLuminance = backup[i+1][j+1].getLuminance();
            double downLeftLuminance = backup[i-1][j-1].getLuminance();
            double dif2 = abs(upRightLuminance - downLeftLuminance);

            double totalDiff = sqrt(dif1*dif2);

            vec[i][j].blue = totalDiff*255;
            vec[i][j].green = totalDiff*255;
            vec[i][j].red = totalDiff*255;
        }
    }
}


/*
*   Pixel Constructors
*/
image::pixel::pixel(){}

image::pixel::pixel(unsigned char b, unsigned char g, unsigned char r){
    blue = b;
    green = g;
    red = r;
}

double image::pixel::getLuminance(){
    double luminance = 0.2126*(red/255.0) + 0.7152*(green/255.0) + 0.0722*(blue/255.0);
    return luminance;
}




