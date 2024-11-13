/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** Button
*/

#include "Button.hpp"

namespace GUI {
    Button::Button(Text text, Vector2 size, Vector2 pos, Color color1, Color color2, bool rounded) : _text(text), _color1(color1), _color2(color2), _rounded(rounded), _pos(pos), _size(size)
    {
        float xPos = _pos.x + (_size.x / 2) - (MeasureText(_text.getText().c_str(), _text.getSize() / 2));
        float yPos = _pos.y + (_size.y / 2) - (_text.getSize() / 2);
        _text.setPos({xPos, yPos});
        _rect = {pos.x, pos.y, size.x, size.y};
    }

    Button::~Button()
    {
    }

    void Button::displayElement()
    {
        if (_rounded) {
            DrawRectangleRounded(_rect, 1, 0, _color1);
            DrawRectangleRoundedLines(_rect, 1, 0, 5, _color2);
            _text.displayElement();
        } else {
            DrawRectangleRec(_rect, _color1);
            _text.displayElement();
        }
    }

    void Button::addElements(std::shared_ptr<UI> element)
    {
        (void)element;
    }

    void Button::setText(Text text)
    {
        _text = text;
        float xPos = _pos.x + (_size.x / 2) - (MeasureText(_text.getText().c_str(), _text.getSize()) / 2);
        float yPos = _pos.y + (_size.y / 2) - (_text.getSize() / 2);
        _text.setPos({xPos, yPos});
    }

    void Button::setRect(Rectangle rect)
    {
        _rect = rect;
    }

    void Button::setColors(Color color1, Color color2)
    {
        _color1 = color1;
        _color2 = color2;
    }

    void Button::setPos(Vector2 pos)
    {
        _pos = pos;
    }

    void Button::setSize(Vector2 size)
    {
        _size = size;
    }

    void Button::onHover(Color borderColor)
    {
        static Color storeColor = _color2;
        if (CheckCollisionPointRec(GetMousePosition(), _rect))
            _color2 = borderColor;
        else
            _color2 = storeColor;
    }
}