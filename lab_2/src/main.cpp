#include <iostream>

#include "list/list.hpp"

void test_constructors();
void test_foreach();
void test_clear();

int main()
{
    test_constructors();
    test_foreach();

    test_clear();

    return 0;
}

void test_constructors()
{
    list<double> list_double;
    // list<double> list_double_2(list_double); // DONT USE IT

    list<int> list_init_list = {};
    list<int> list_init_list_2 = {1, 2, 4, 2, 3};
}

void test_foreach()
{
    list<int> list = { 3, 5, 2, 0, 4 };

    // test for each loop (non-const)
    for (auto& value : list)
        std::cout << "value : " << value << std::endl;
    std::cout << std::endl;

    // test for each loop (const)
    for (const auto& value : list)
        std::cout << "const value : " << value << std::endl;
    std::cout << std::endl;
}

void test_clear()
{
    list<char> syms = {'c', 'd', 'a'};

    std::cout << "syms: ";
    for (const auto& sym : syms) std::cout << "'" << sym << "' ";
    std::cout << std::endl;
    std::cout << "size = " << syms.size() << std::endl;

    syms.clear();

    std::cout << "syms after clear: ";
    for (const auto& sym : syms) std::cout << "'" << sym << "' ";
    std::cout << std::endl;
    std::cout << "size = " << syms.size() << std::endl;
}
