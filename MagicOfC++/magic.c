#include <stdio.h>
#include <stdint.h>

struct Color {
    uint8_t r, g, b, a;
};

void PrintIntColor(uint32_t);
void PrintColor(Color*);

int main(void)
{
    uint32_t colorInt = 0xFF05E785;

    Color* color = (Color*)(&colorInt);

    printf("C language style:\n\n");

    printf("original color channels value:\n");

    PrintIntColor(colorInt);
    PrintColor(color);
    
    printf("\nsetting green channel to 0xD4 using reinterpret_cast method:\n");
    
    (*color).g = 0xD4;

    PrintIntColor(colorInt);
    PrintColor(color);

    printf("\nsetting blue channel to 0x64 using bitwise operators method:\n");
    
    colorInt = (colorInt & ~(0xFF << 16)) | (0x64 << 16);

    PrintIntColor(colorInt);
    PrintColor(color);
    

    return 0;
}

void PrintIntColor(uint32_t color)
{
    printf("Color integer:___________________________________\n");
    printf("0x%08X\n", color);
}

void PrintColor(Color* color)
{
    printf("Color struct:____________________________________\n");
    printf("0x%02X%02X%02X%02X\n", (*color).a, (*color).b, (*color).g, (*color).r);
}