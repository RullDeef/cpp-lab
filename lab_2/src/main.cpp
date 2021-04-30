#include <iostream>
#include "list/list.hpp"

#define TEST_BEGIN \
    std::cout << "============= Test: " << __func__ << " =============" << std::endl; \
    int failed = 0;

#define TEST_END \
    if (failed > 0) std::cout << __func__ << ": FAILED." << std::endl; \
    else std::cout << __func__ << ": PASSED." << std::endl; \
    return failed;

#define SUB_TEST(func) \
    failed += func();

#define ASSERT(expr) \
    if (!(expr)) { \
        std::cout << "ASSERTION FAILED: \n  " << __LINE__ << std::endl; \
        failed++; \
    }

int test_constructors();
int test_foreach();
int test_clear();
int test_operators();

int main()
{
    TEST_BEGIN;

    SUB_TEST(test_constructors);
    SUB_TEST(test_foreach);
    SUB_TEST(test_clear);
    SUB_TEST(test_operators);

    TEST_END;
}

int test_constructors()
{
    TEST_BEGIN;

    list<double> list_double;
    list<double> list_double_2(list_double);
    list<double> list_double_3 = list_double_2;

    ASSERT(list_double == list_double_2);
    ASSERT(list_double == list_double_3);

    list<float> list_float = list<int>(list_double);

    list<int> list_init_list = {};
    list<int> list_init_list_2 = {1, 2, 4, 2, 3};

    ASSERT(list_init_list.size() == 0);
    ASSERT(list_init_list_2.size() == 5);

    TEST_END;
}

int test_foreach()
{
    TEST_BEGIN;

    list<int> int_list = { 3, 5, 2, 0, 4 };

    // test for each loop (non-const)
    for (auto& value : int_list)
        std::cout << "value : " << value << std::endl;
    std::cout << std::endl;

    // test for each loop (const)
    for (const auto& value : static_cast<const list<int>&>(int_list))
        std::cout << "const value : " << value << std::endl;
    std::cout << std::endl;

    TEST_END;
}

int test_clear()
{
    TEST_BEGIN;

    list<char> syms = {'c', 'd', 'a'};

    ASSERT(syms.size() == 3);

    std::cout << "syms: ";
    for (const auto& sym : syms) std::cout << "'" << sym << "' ";
    std::cout << std::endl;
    std::cout << "size = " << syms.size() << std::endl;

    syms.clear();
    ASSERT(syms.size() == 0);

    std::cout << "syms after clear: ";
    for (const auto& sym : syms) std::cout << "'" << sym << "' ";
    std::cout << std::endl;
    std::cout << "size = " << syms.size() << std::endl;

    TEST_END;
}

int test_operators()
{
    TEST_BEGIN;

    list<float> floats = { 1.0f, 2.0f, 3.0f };
    list<float> floats_2 = floats + 4.0f;

    ASSERT(floats.size() == 3);
    ASSERT(floats_2.size() == 4);

    ASSERT((floats_2 + floats).size() == 7);

    floats = floats_2 + 1.2f + floats + 1.3f + 4.5f;
    ASSERT(floats.size() == 10);

    for (const auto& value : floats)
        std::cout << value << " ";
    std::cout << std::endl;

    TEST_END;
}
