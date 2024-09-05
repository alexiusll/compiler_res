/*
 * @Author: 
 * @Date: 2024-09-05 15:51:59
 * @Description: 
 * 
 * 代码来自
 * https://code.visualstudio.com/docs/cpp/config-mingw
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    vector<string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};

    for (const string& word : msg)
    {
        cout << word << " ";
    }
    cout << endl;
}