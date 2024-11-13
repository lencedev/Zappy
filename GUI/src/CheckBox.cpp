/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** CheckBox
*/

#include "CheckBox.hpp"

namespace GUI {
    CheckBox::CheckBox(Vector2 pos, Vector2 size, Color color1, Color color2) : _pos(pos), _size(size), _color1(color1), _color2(color2)
    {
        _box = LoadTexture("GUI/assets/textures/checkBox.png");
        _check = LoadTexture("GUI/assets/textures/checkBox_check.png");
        _box.width = _size.x;
        _box.height = _size.y;
        _check.width = _size.x;
        _check.height = _size.y;
        _boxRec = {_pos.x + 9, _pos.y + 9, static_cast<float>(_box.width) - 15, static_cast<float>(_box.height) - 15};
        _checked = false;
    }

    CheckBox::~CheckBox()
    {
    }

    void CheckBox::displayElement()
    {
        DrawRectangleRounded(_boxRec, 0.2, 0, _color1);
        DrawTexture(_box, _pos.x, _pos.y, _color2);
        if (_checked) DrawTexture(_check, _pos.x, _pos.y, _color2);
    }

    void CheckBox::addElements(std::shared_ptr<UI> element)
    {
        (void)element;
    }

    void CheckBox::onClick(bool &value)
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), _boxRec)) {
            _checked = !_checked;
            value = _checked;
        }
    }
}