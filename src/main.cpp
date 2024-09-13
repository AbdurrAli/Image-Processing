#include "image.h"

int main(int argc, char** argv) {
    /*setup test*/
    Image test("test.jpg");
    // test.write("foto-baru.jpg");
    // Image copy = test;
    // for (int i = 0; i < copy.w*copy.channel;++i){
    //     copy.data[i] = 255;
    // }
    // copy.write("foto-copy.jpg");

    Image gray_avg = test;
    gray_avg.greyscale_avg();
    gray_avg.write("grayscale_normal.jpg");

    Image gray_lum = test;
    gray_lum.greyscale_lum();
    gray_lum.write("grayscale_luminance.jpg");

    return 0;
}