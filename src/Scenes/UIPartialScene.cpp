#include "UIPartialScene.hpp"
#include "../Entity/UI/Object.hpp"
#include "../Entity/UI/ImageObject.hpp"
#include "../Utils/Mouse.hpp"
#include "../Core/App.hpp"
#include "../Resources/Resources.hpp"
#include "../Resources/AssetData.hpp"
#include "../Utils/Gizmos.hpp"
#include <functional>
#include "../Renderer/Atlas.hpp"

//drag stuff
ImageObject* drag_object = nullptr;
vec2f drag_start_pos;

UIPartialScene::UIPartialScene(App *app, Logger *logger, Cooldown *cooldown, Camera *camera) : PartialScene(app, logger, cooldown, camera)
{
    init();
}


void UIPartialScene::init()
{

}

void UIPartialScene::input(SDL_Event event)
{
    switch (event.type) {
		case SDL_MOUSEBUTTONDOWN:
			switch (event.button.button) {
				case SDL_BUTTON_LEFT:
					m_mouse_down = true;
                    m_mouse_drag = true;
				break;
			}

		case SDL_MOUSEBUTTONUP:
			if(event.type == SDL_MOUSEBUTTONDOWN)return;
			switch (event.button.button) {
				case SDL_BUTTON_LEFT:			
					m_mouse_down = false;
                    m_mouse_drag = false;
                    
                    if(drag_object != nullptr){

                        drag_object->on_drop();
                        drag_object = nullptr;
                    }
				break;
			}

		case SDL_KEYDOWN:
			switch (event.key.keysym.scancode) {
				case SDL_SCANCODE_D:
					{
						
					}

				break;
				case SDL_SCANCODE_E:

				break;
				case SDL_SCANCODE_A:

				break;
                case SDL_SCANCODE_B:
                    
                break;
				case SDL_SCANCODE_T:

				break;
				case SDL_SCANCODE_RETURN:
					
				break;
				case SDL_SCANCODE_ESCAPE:
					
				break;
				case SDL_SCANCODE_TAB:
					
					
				break;
			}
		break;
		case SDL_KEYUP:
			switch (event.key.keysym.scancode) {
				case SDL_SCANCODE_D:
				break;
				case SDL_SCANCODE_RETURN:
					
				break;
				case SDL_SCANCODE_TAB:
					
				break;
			}
		break;
	}
}

void UIPartialScene::update(double deltaTime)
{
    //if the mouse pos is different than the last mouse pos we can drag
    if(m_last_mouse_position.x != Mouse::get_mouse_pos().x || m_last_mouse_position.y != Mouse::get_mouse_pos().y)
    {
        if(drag_object != nullptr)
        {
            drag_object->on_drag();
            drag_object->set_area({Mouse::get_mouse_pos().x, Mouse::get_mouse_pos().y, drag_object->get_area().w, drag_object->get_area().h});
        }
    }

    for(auto& object : m_image_objects)
    {
        if(object.get()->has_modifier(HOVERABLE)){
            if(Mouse::is_at_area(object.get()->get_area(), m_app->get_window_size().x, m_app->get_window_size().y))
            {
                object.get()->on_hover();
                object.get()->set_hovering(true);
            }else{
                object.get()->set_hovering(false);
            }
        }
    }

    if(m_mouse_down){
        for(auto& object : m_image_objects)
        {
            if(object.get()->has_modifier(CLICKABLE)){
                if(Mouse::is_at_area(object.get()->get_area(), m_app->get_window_size().x, m_app->get_window_size().y))
                {
                    object.get()->on_click();
                }
            }

            if(object.get()->has_modifier(DRAGGABLE)){
                if(Mouse::is_at_area(object.get()->get_area(), m_app->get_window_size().x, m_app->get_window_size().y)){
                    if(m_mouse_drag){
                        drag_start_pos = {object.get()->get_area().x, object.get()->get_area().y};
                        drag_object = object.get();
                    }
                }
            }
        }
        m_mouse_down = false;
    }

    m_last_mouse_position = Mouse::get_mouse_pos(); 
}

void UIPartialScene::draw()
{
    for(auto& object : m_image_objects)
    {
        if(object.get()->is_hovering()) {
        }

        m_atlas->draw_texture(object.get()->get_texture(), vec2f(16,16), {object.get()->get_area().x, object.get()->get_area().y}, false, 2, true);

#if F_ENABLE_DEBUG
        if(object.get()->has_modifier(CLICKABLE))
        {
            Gizmos::draw_area({object.get()->get_area().x, object.get()->get_area().y}, object.get()->get_area().w, m_atlas, {255,0,0});
        }

        if(object.get()->has_modifier(DRAGGABLE))
        {
            Gizmos::draw_area({object.get()->get_area().x, object.get()->get_area().y}, object.get()->get_area().w, m_atlas, {255,0,0});
        }
#endif
    }

}

void UIPartialScene::clean()
{
}
