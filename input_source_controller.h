#pragma once
#include <string>
#include <stdexcept>

class program_error : public std::runtime_error {
public:
    explicit program_error(const std::string& what_arg) : std::runtime_error(what_arg) {}
};

class InputSourceController {
public:
    InputSourceController();
    void showSelected() const;
    void listAvailable() const;
    void select(const std::string& isId) const;
};