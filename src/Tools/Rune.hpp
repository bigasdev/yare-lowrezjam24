#pragma once

#include <functional>

class Rune
{
public:
    Rune();

    void set_function(std::function<void()> function);

    void power();

    void reset();
    
private:
    std::function<void()> m_function;

    bool m_powered = false;
};
