#pragma once

#include <exception>
#include <string>

class base_list_exception : public std::exception
{
public:
    base_list_exception(const char* filename, const char* classname, int line, const char* info)
    {
        message = std::string(info)
            + " at line " + std::to_string(line)
            + " in class \"" + classname + "\""
            + " in file \"" + filename + "\"";
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

class base_list_iterator_exception : public std::exception
{
public:
    base_list_iterator_exception(const char* filename, const char* classname, int line, const char* info)
    {
        message = std::string(info)
            + " at line " + std::to_string(line)
            + " in class \"" + classname + "\""
            + " in file \"" + filename + "\"";
    }

    virtual const char* what() const override { return message.c_str(); }

private:
    std::string message;
};

class invalid_state_iterator_exception : public base_list_iterator_exception
{
public:
    invalid_state_iterator_exception(const char* filename, const char* classname, int line)
        : base_list_iterator_exception(filename, classname, line, "invalid iterator state") {}
};
