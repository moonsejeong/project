#include <iostream>
#include <array>
#include <vector>

int main(void)
{
    std::string a;
    std::cout << "input" << std::endl;
    std::cin >> a;

    if (a == "abc")
        std::cout << "success\n";
    else
        std::cout << "fail\n";

    return 0;
}