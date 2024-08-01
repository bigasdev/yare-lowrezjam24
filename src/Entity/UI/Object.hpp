#pragma once

#include "../../Utils/Common.hpp"
#include <functional>

enum ObjectType{
    OBJECT,
    BUTTON,
    TEXT,
    IMAGE
};

enum ObjectModifier{
    NILL = 0,
    HOVERABLE = 1 << 0,
    DRAGGABLE = 1 << 1,
    CLICKABLE = 1 << 2
};

class Object{
public:
    Object(Area object_area = Area{0,0,50,50}, ObjectType type = OBJECT, int modifier = NILL);
    ~Object();

    void set_type(ObjectType type);
    void set_modifier(ObjectModifier modifier);
    void set_area(Area object_area);
    void set_on_click(std::function<void()> on_click);
    void set_on_hover(std::function<void()> on_hover);
    void set_on_drag(std::function<void()> on_drag);
    void set_on_drop(std::function<void()> on_drop);

    void set_hovering(bool is_hovering);

    void on_click();
    void on_hover();
    void on_drag();
    void on_drop();
    ObjectType get_type();
    bool has_modifier(ObjectModifier modifier) const;
    Area get_area();
    bool is_hovering();

private:
    ObjectType m_type;
    int m_modifier;

    Area m_area;

    std::function<void()> m_on_click;
    std::function<void()> m_on_hover;
    std::function<void()> m_on_drag;
    std::function<void()> m_on_drop;

    bool m_is_hovering = false;
};
