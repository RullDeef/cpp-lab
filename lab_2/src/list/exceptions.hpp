#pragma once

#include <exception>
#include <string>
#include <chrono>

class base_list_exception : public std::exception
{
public:
    base_list_exception(const char* filename, const char* classname, int line, const char* info)
    {
        time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        message = std::string(info)
            + " at line " + std::to_string(line)
            + " in class \"" + classname + "\""
            + " in file \"" + filename + "\""
            + " in " + ctime(&time);
    }

    virtual const char* what() const override { return message.c_str(); }

private:
    std::string message;
};

class memory_list_exception : public base_list_exception
{
public:
    memory_list_exception(const char* filename, const char* classname, int line)
        : base_list_exception(filename, classname, line, "memory error occured") {}
};

class invalid_rawptr_list_exception : public base_list_exception
{
public:
    invalid_rawptr_list_exception(const char* filename, const char* classname, int line)
        : base_list_exception(filename, classname, line, "invalid raw pointer with non-zero array size") {}
};

class out_of_bounds_list_exception : public base_list_exception
{
public:
    out_of_bounds_list_exception(const char* filename, const char* classname, int line)
        : base_list_exception(filename, classname, line, "list index out of bounds") {}
};

class invalid_list_node_exception : public base_list_exception
{
public:
    invalid_list_node_exception(const char* filename, const char* classname, int line)
        : base_list_exception(filename, classname, line, "invalid list node state") {}
};

class base_list_iterator_exception : public base_list_exception
{
public:
    base_list_iterator_exception(const char *filename, const char *classname, int line, const char* message)
        : base_list_exception(filename, classname, line, message) {}
};

class invalid_state_iterator_exception : public base_list_iterator_exception
{
public:
    invalid_state_iterator_exception(const char* filename, const char* classname, int line)
        : base_list_iterator_exception(filename, classname, line, "invalid iterator state") {}
};

class out_of_bounds_iterator_exception : public base_list_iterator_exception
{
public:
    out_of_bounds_iterator_exception(const char* filename, const char* classname, int line)
        : base_list_iterator_exception(filename, classname, line, "iterator out of bounds") {}
};