/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** Canva
*/

#include "Canva.hpp"

namespace GUI {
    Canva::Canva()
    {
        _pos = {0, 0};
        _size = {1, 1};
        _color1 = WHITE;
        _color2 = WHITE;
        _rect = {_pos.x, _pos.y, _size.x, _size.y};
        _rounded = false;
    }

    Canva::Canva(Vector2 pos, Vector2 size, Color color1, Color color2, bool rounded) : _pos(pos), _size(size), _color1(color1), _color2(color2), _rounded(rounded)
    {
        _rect = {_pos.x, _pos.y, _size.x, _size.y};
    }

    Canva::~Canva()
    {
    }

    void Canva::displayElement()
    {
        if (_rounded) {
            DrawRectangleRoundedLines(_rect, 0.1, 10, 10, _color2);
            DrawRectangleRounded(_rect, 0.1, 10, _color1);
        } else {
            DrawRectangleRec(_rect, _color1);
        }
        for (auto &element : _elements)
            element->displayElement();
    }

    void Canva::addElements(std::shared_ptr<UI> element)
    {
        _elements.push_back(element);
    }

    void Canva::setPos(Vector2 pos)
    {
        _pos = pos;
    }

    void Canva::setSize(Vector2 size)
    {
        _size = size;
    }

    void Canva::setColor(Color color)
    {
        _color1 = color;
    }

    void Canva::setRect(Rectangle rect)
    {
        _rect = rect;
    }
}