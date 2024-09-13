#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image.h"
#include "stb_image_write.h"
#include "image.h"

Image::Image(const char* filename){
    if (read(filename)) {
        printf("Read %s\n", filename);
        size = w*h*channel;
    } else {
        printf("Failed to read %s\n", filename);
    }
}
Image::Image(int w, int h, int channel) : w(w), h(h), channel(channel) {
    size = w*h*channel;
    data = new uint8_t[size];

}
Image::Image(const Image& img) : Image(img.w, img.h, img.channel) {
    memcpy(data, img.data, size);
}
Image::~Image(){
    stbi_image_free(data);
}
bool Image::read(const char* filename){
    data = stbi_load(filename, &w, &h, &channel, 0);
    return data != NULL;
}
bool Image::write(const char* filename){
    ImageType type = getFileType(filename);
    int success;
    switch (type)
    {
    case PNG:
        success = stbi_write_png(filename, w, h, channel, data, w*channel);
        break;
    case JPG:
        success = stbi_write_jpg(filename, w, h, channel, data, 100);
        break;
    case BMP:
        success = stbi_write_bmp(filename, w, h, channel, data);
        break;
    case TGA:
        success = stbi_write_tga(filename, w, h, channel, data);
        break;
    }
    return success;
}

ImageType Image::getFileType(const char* filename) {
    const char* ext = strrchr(filename, '.');
    if(ext != nullptr) {
        if (strcmp(ext, ".png")==0) {
            return PNG;
        }
        else if (strcmp(ext, ".jpg")==0) {
            return JPG;
        }
        else if (strcmp(ext, ".bmp")==0) {
            return BMP;
        }
        else if (strcmp(ext, ".tga")==0) {
            return TGA;
        }
    }
    return PNG;
} 

Image& Image::greyscale_avg() {
    if (channel < 3) {
        printf("foto %p memiliki channle kurang dari 3", this);
    }
    else  {
        for(int i = 0; i < size; i+=channel){
            int gray = (data[i] + data[i+1] + data[i+2])/3;
            memset(data+i, gray, 3);
        }
    }
    return *this;
}

Image& Image::greyscale_lum() {
    if (channel < 3) {
        printf("foto %p memiliki channle kurang dari 3", this);
    }
    else  {
        for(int i = 0; i < size; i+=channel){
            int gray = 0.2126*data[i] + 0.7152*data[i+1] + 0.0722*data[i+2];
            memset(data+i, gray, 3);
        }
    }
    return *this;
}
