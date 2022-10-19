#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <inttypes.h>

struct Color {
    uint8_t r, g, b, a;
};

typedef struct Color Color;

void PrintIntColor(uint32_t);
int64_t GetDuration(struct timespec, struct timespec);

#define N 7000000000

int main(void)
{
    uint32_t colorInt = 0xFF05E785;

    struct timespec starttime, endtime;

    printf("Using pointer casting method with %llu tries\n", N);
    timespec_get(&starttime, TIME_UTC);
    for (uint64_t i = 0; i < N; i++)
    {
        Color* color = (Color*)(&colorInt);
        (*color).g = 0xD4;
    }
    timespec_get(&endtime, TIME_UTC);

    PrintIntColor(colorInt);
    printf("Took: %" PRId64 "ms\n", GetDuration(starttime, endtime));

    printf("\nUsing bitwise operations method with %llu tries\n", N);
    timespec_get(&starttime, TIME_UTC);
    for (uint64_t i = 0; i < N; i++)
    {
        colorInt = (colorInt & ~(0xFF << 16)) | (0x64 << 16);
    }
    timespec_get(&endtime, TIME_UTC);

    PrintIntColor(colorInt);
    printf("Took: %" PRId64 "ms\n", GetDuration(starttime, endtime));



    return 0;
}

/// Results are copied from the console log.
/// 
/// 
/// Results in debug mode x64:_________________________________________________________________________________________________________
/// 
/// Using pointer casting method with 7000000000 tries
/// Color integer : ___________________________________
/// 0xFF05D485
/// Took : 10821ms
/// 
/// Using bitwise operations method with 7000000000 tries
/// Color integer : ___________________________________
/// 0xFF64D485
/// Took : 15462ms
/// 
/// 
/// Results in debug mode x86:_________________________________________________________________________________________________________
/// 
/// Using pointer casting method with 7000000000 tries
/// Color integer : ___________________________________
/// 0xFF05D485
/// Took : 7662ms
/// 
/// Using bitwise operations method with 7000000000 tries
/// Color integer : ___________________________________
/// 0xFF64D485
/// Took : 6869ms
/// 
/// 
/// Results in release mode x64:_______________________________________________________________________________________________________
/// 
/// Using pointer casting method with 7000000000 tries
/// Color integer : ___________________________________
/// 0xFF05D485
/// Took : 1882ms
/// 
/// Using bitwise operations method with 7000000000 tries
/// Color integer : ___________________________________
/// 0xFF64D485
/// Took : 3447ms
/// 
/// 
/// Results in release mode x86:_______________________________________________________________________________________________________
/// Using pointer casting method with 7000000000 tries
/// Color integer : ___________________________________
/// 0xFF05D485
/// Took : 2900ms
/// 
/// Using bitwise operations method with 7000000000 tries
/// Color integer : ___________________________________
/// 0xFF64D485
/// Took : 3453ms

void PrintIntColor(uint32_t color)
{
    printf("Color integer:___________________________________\n");
    printf("0x%08X\n", color);
}

int64_t GetDuration(struct timespec start, struct timespec end)
{
    return ((int64_t)(end.tv_sec - start.tv_sec)) * 1000 + ((int64_t)(end.tv_nsec - start.tv_nsec)) / 1000000;
}