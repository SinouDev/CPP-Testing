#include <iostream>
#include <iomanip>
#include <chrono>

struct Color {
    uint8_t r, g, b, a;
};

using TimeChrono = std::chrono::time_point<std::chrono::high_resolution_clock>;

void PrintIntColor(uint32_t);
int64_t GetDuration(TimeChrono, TimeChrono);

#define N 7000000000

int main(void)
{
    uint32_t colorInt = 0xFF05E785;

    TimeChrono starttime, endtime;

    std::cout << "C++ language style:" << std::endl << std::endl;
    std::cout << "Using pointer casting method with " << N << " tries" << std::endl;
    starttime = std::chrono::high_resolution_clock().now();
    for (uint64_t i = 0; i < N; i++)
    {
        Color* color = (Color*)(&colorInt);
        (*color).g = 0xD4;
    }
    endtime = std::chrono::high_resolution_clock().now();

    PrintIntColor(colorInt);
    std::cout << "Took: " << GetDuration(starttime, endtime) << "ms" << std::endl;

    std::cout << std::endl;
    std::cout << "Using bitwise operations method with " << N << " tries" << std::endl;
    starttime = std::chrono::high_resolution_clock().now();
    for (uint64_t i = 0; i < N; i++)
    {
        colorInt = (colorInt & ~(0xFF << 16)) | (0x64 << 16);
    }
    endtime = std::chrono::high_resolution_clock().now();

    PrintIntColor(colorInt);
    std::cout << "Took: " << GetDuration(starttime, endtime) << "ms" << std::endl;

    std::cout << std::endl;
    std::cout << "Press ENTER to exit!";
    std::cin.get();
    return 0;
}

/// C++ language style:
/// 
/// 
/// Results are copied from the console log.
/// 
/// 
/// Results in debug mode x64:_________________________________________________________________________________________________________
/// 
/// Using pointer casting method with 7000000000 tries
/// Color integer : ___________________________________
/// 0xFF05D485
/// Took : 10474ms
/// 
/// Using bitwise operations method with 7000000000 tries
/// Color integer : ___________________________________
/// 0xFF64D485
/// Took : 15558ms
/// 
/// 
/// Results in debug mode x86:_________________________________________________________________________________________________________
/// 
/// Using pointer casting method with 7000000000 tries
/// Color integer : ___________________________________
/// 0xFF05D485
/// Took : 7191ms
/// 
/// Using bitwise operations method with 7000000000 tries
/// Color integer : ___________________________________
/// 0xFF64D485
/// Took : 6190ms
/// 
/// 
/// Results in release mode x64:_______________________________________________________________________________________________________
/// 
/// Using pointer casting method with 7000000000 tries
/// Color integer : ___________________________________
/// 0xFF05D485
/// Took : 1906ms
/// 
/// Using bitwise operations method with 7000000000 tries
/// Color integer : ___________________________________
/// 0xFF64D485
/// Took : 3448ms
/// 
/// 
/// Results in release mode x86:_______________________________________________________________________________________________________
/// 
/// Using pointer casting method with 7000000000 tries
/// Color integer : ___________________________________
/// 0xFF05D485
/// Took : 2896ms
/// 
/// Using bitwise operations method with 7000000000 tries
/// Color integer : ___________________________________
/// 0xFF64D485
/// Took : 3466ms

void PrintIntColor(uint32_t color)
{
    using namespace std;
    cout << "Color integer:___________________________________" << endl;
    cout << "0x" << uppercase << hex << setw(8) << setfill('0') << color << endl;
    cout << nouppercase << dec;
}

int64_t GetDuration(TimeChrono start, TimeChrono end)
{
    return static_cast<int64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() * 0.001f * 0.001f);
}