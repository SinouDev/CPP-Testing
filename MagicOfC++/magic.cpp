#include <cstdint>
#include <iostream>
#include <iomanip>

struct Color {
    uint8_t r, g, b, a;
};

void PrintIntColor(uint32_t);
void PrintColor(const Color&);

int main(void)
{
    uint32_t colorInt = 0x0F05E785;

    Color& color = *reinterpret_cast<Color*>(&colorInt);

    std::cout << "C++ language style:" << std::endl << std::endl;
    std::cout << "original color channels value:" << std::endl;

    PrintIntColor(colorInt);
    PrintColor(color);
    
    std::cout << std::endl;
    std::cout << "setting green channel to 0xD4 using reinterpret_cast method:" << std::endl;
    
    color.g = 0xD4;

    PrintIntColor(colorInt);
    PrintColor(color);

    std::cout << std::endl;
    std::cout << "setting blue channel to 0x64 using bitwise operators method:" << std::endl;
    
    colorInt = (colorInt & ~(0xFF << 16)) | (0x64 << 16);

    PrintIntColor(colorInt);
    PrintColor(color);
    

    return 0;
}

void PrintIntColor(uint32_t color)
{
    std::cout << "Color integer:___________________________________" << std::endl;
    std::cout << "0x" << std::uppercase << std::hex << std::setw(8) << std::setfill('0');
    std::cout << color << std::endl;
}

void PrintColor(const Color& color)
{
    std::cout << "Color struct:____________________________________" << std::endl;
    std::cout << "0x" << std::uppercase << std::hex << std::setw(2) << std::setfill('0');
    std::cout << std::setw(2) << std::setfill('0') << static_cast<uint16_t>(color.a);
    std::cout << std::setw(2) << std::setfill('0') << static_cast<uint16_t>(color.b);
    std::cout << std::setw(2) << std::setfill('0') << static_cast<uint16_t>(color.g);
    std::cout << std::setw(2) << std::setfill('0') << static_cast<uint16_t>(color.r) << std::endl;
}