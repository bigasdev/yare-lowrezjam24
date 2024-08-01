#include "Rune.hpp"

Rune::Rune()
{
}

void Rune::set_function(std::function<void()> function)
{
    m_function = function;
}

void Rune::power()
{
    if(m_powered)
        return;

    if(m_function)
    {
        m_function();
        m_powered = true;
    }
}

void Rune::reset()
{
    m_powered = false;
}
