/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** Food
*/

#include "Food.hpp"

namespace GUI {
    Food::Food()
    {
        _name = "food";
    }

    Food::~Food()
    {
    }

    std::string Food::getName() const
    {
        return _name;
    }

    Model Food::getModel() const
    {
        return _model;
    }

    Vector3 Food::getPos() const
    {
        return _pos;
    }

    void Food::setModel(Model model)
    {
        _model = model;
        _model.transform = MatrixMultiply(MatrixRotateXYZ((Vector3){ DEG2RAD * 90.0f , 0.0f, 0.0f }), MatrixTranslate(0.0f, 0.25f, 0.0f));
    }

    void Food::setPos(Vector3 pos)
    {
        _pos = pos;
    }
}