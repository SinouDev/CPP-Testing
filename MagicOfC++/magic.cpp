#include <iostream>
#include <iomanip>

struct Color {
    uint8_t r, g, b, a;
};

void PrintIntColor(uint32_t);
void PrintColor(const Color&);

int main(void)
{
    uint32_t colorInt = 0xFF05E785;

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
    
    std::cout << std::endl;
    std::cout << "Press ENTER to exit!";
    std::cin.get();

    return 0;
}

void PrintIntColor(uint32_t color)
{
    using namespace std;
    cout << "Color integer:___________________________________" << endl;
    cout << "0x" << uppercase << hex << setw(8) << setfill('0') << color << endl;
}

void PrintColor(const Color& color)
{
    using namespace std;
    cout << "Color struct:____________________________________" << endl;
    cout << "0x" << uppercase << hex << setw(2) << setfill('0');
    cout << setw(2) << setfill('0') << static_cast<uint16_t>(color.a);
    cout << setw(2) << setfill('0') << static_cast<uint16_t>(color.b);
    cout << setw(2) << setfill('0') << static_cast<uint16_t>(color.g);
    cout << setw(2) << setfill('0') << static_cast<uint16_t>(color.r) << endl;
}