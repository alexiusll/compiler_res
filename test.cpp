/*
 * @Author: linkenzone
 * @Date: 2023-08-30 10:59:11
 * @Descripttion: Do not edit
 */

#include <iostream>
#include <cmath>

// typedef struct _VIR_OPCODE_INFO
// {
//     int opcode : 10;
//     int : 0;
//     int flags;
// } info;

int main()
{
    float l = 0.891772985458374;
    float r = 0.056712977588177;

    float temp = l * (1 / r);

    float ans = -r * floor(temp) + l;

    printf("fmod   : %.15f \n", fmod(l, r));
    printf("answer : %.15f", ans);
}