#include "Object.hpp"

Object::Object(Area area, ObjectType type, int modifier)
{
    m_area = area;
    m_type = type;
    m_modifier = modifier;
}

Object::~Object()
{
}

void Object::set_type(ObjectType type)
{
}

void Object::set_modifier(ObjectModifier modifier)
{
}

void Object::set_area(Area object_area)
{
    m_area = object_area;
}

void Object::set_on_click(std::function<void()> on_click)
{
    m_on_click = on_click;
}

void Object::set_on_hover(std::function<void()> on_hover)
{
    m_on_hover = on_hover;
}

void Object::set_on_drag(std::function<void()> on_drag)
{
    m_on_drag = on_drag;
}

void Object::set_on_drop(std::function<void()> on_drop)
{
    m_on_drop = on_drop;
}

void Object::set_hovering(bool is_hovering)
{
    m_is_hovering = is_hovering;
}

void Object::on_click()
{
    if (m_on_click)
    {
        m_on_click();
    }
}

void Object::on_hover()
{
    if(m_on_hover)
    {
        m_on_hover();
    }
}

void Object::on_drag()
{
    if(m_on_drag)
    {
        m_on_drag();
    }
}

void Object::on_drop()
{
    if(m_on_drop)
    {
        m_on_drop();
    }
}

ObjectType Object::get_type()
{
    return m_type;
}

bool Object::has_modifier(ObjectModifier modifier) const
{
    return (m_modifier & modifier) != 0;
}

Area Object::get_area()
{
    return m_area;
}

bool Object::is_hovering()
{
    return m_is_hovering;
}
