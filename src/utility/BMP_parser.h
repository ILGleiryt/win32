/* Simple BMP file parser
*  Usage:
*   BMPImage img = bmp_load(path, name); bmp_free(img);
* 
*   02.07.2026 // dd mm yyyy
*/

#ifndef BMP_PARSER_H
#define BMP_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Stores type of structure if != 0x4d42 its not bmp file
#pragma pack(push, 1)
typedef struct {
    uint16_t type; 
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
} BitmapFileHeader;
// stores all parameters of bmp file, colors, width, height
typedef struct {
    uint32_t dib_header_size;
    int32_t  width;
    int32_t  height;
    uint16_t planes;
    uint16_t bits_per_pixel;
    uint32_t compression;
    uint32_t image_size;
    int32_t  x_ppm;
    int32_t  y_ppm;
    uint32_t colors;
    uint32_t important_colors;
} BitmapInfoHeader;
#pragma pack(pop)

typedef struct {
    BitmapFileHeader file_header;
    BitmapInfoHeader info_header;
    unsigned char* data;
} BMPImage;

typedef enum BMPError {
    BMP_OK = 0,
    BMP_ERR_FILE = -1,
    BMP_ERR_HEADER = -2,
    BMP_ERR_MEMORY = -3,
    BMP_ERR_FORMAT = -4,
} BMPError;

BMPError bmp_load(const char* path, BMPImage* img) 
{
    FILE* file = fopen(path, "rb");
    if (!file) return BMP_ERR_FILE;

    if (fread(&img->file_header, sizeof(BitmapFileHeader), 1, file) != 1) 
    {
        fclose(file);
        return BMP_ERR_HEADER;
    }

    if (img->file_header.type != 0x4D42) 
    {
        fclose(file);
        return BMP_ERR_HEADER;
    }

    if (fread(&img->info_header, sizeof(BitmapInfoHeader), 1, file) != 1) 
    {
        fclose(file);
        return BMP_ERR_HEADER;
    }

    if (img->info_header.dib_header_size != 40) 
    {
        fclose(file);
        return BMP_ERR_FORMAT;
    }

    if (!((img->info_header.bits_per_pixel == 24 || img->info_header.bits_per_pixel == 32) &&
        img->info_header.compression == 0)) 
    {
        fclose(file);
        return BMP_ERR_FORMAT;
    }

    int row_size = ((img->info_header.bits_per_pixel * img->info_header.width + 31) / 32) * 4;
    int height = img->info_header.height;
    if (height < 0) height = -height;
    int data_size = row_size * height;

    img->data = (unsigned char*)malloc(data_size);
    if (!img->data) 
    {
        fclose(file);
        return BMP_ERR_MEMORY;
    }

    fseek(file, img->file_header.offset, SEEK_SET);
    if (fread(img->data, 1, data_size, file) != (size_t)data_size) 
    {
        free(img->data);
        img->data = NULL;
        fclose(file);
        return BMP_ERR_HEADER;
    }

    fclose(file);
    return BMP_OK;
}

void bmp_free(BMPImage* img)
{
    if (img->data) 
    {
        free(img->data);
        img->data = NULL;
    }
}

#endif // BMP_PARSER_H