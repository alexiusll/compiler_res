/*
 * @Author: linkenzone
 * @Date: 2023-08-10 11:30:52
 * @Descripttion: Do not edit
 */

// #include <iostream>

int __attribute__((noinline)) help(int a, int b)
{
    return a + b;
}

int main()
{
    int a = 1;
    int b = 2;

    if(help(a,b) > 4)
    {
        b = 0;
    }
    else
    {
        b = 1;
    }
}