/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** Text
*/

#include "Text.hpp"

namespace GUI {
    Text::Text()
    {
        _size = 1;
        _text = "";
        _pos = {0, 0};
        _color = WHITE;
        _font = GetFontDefault();
    }

    Text::Text(float size, std::string text, Vector2 pos, Color color, Font font) : _size(size), _text(text), _pos(pos), _color(color), _font(font)
    {
    }

    Text::~Text()
    {
    }

    void Text::displayElement()
    {
        if (IsFontReady(_font))
            DrawTextEx(_font, _text.c_str(), _pos, _size, 1, _color);
    }

    void Text::addElements(std::shared_ptr<UI> element)
    {
        (void)element;
        return;
    }

    void Text::setSize(float size)
    {
        _size = size;
    }

    void Text::setText(std::string text)
    {
        _text = text;
    }

    void Text::setPos(Vector2 pos)
    {
        _pos = pos;
    }

    void Text::setColor(Color color)
    {
        _color = color;
    }

    void Text::setFont(Font font)
    {
        _font = font;
    }
}