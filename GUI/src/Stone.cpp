/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** Stone
*/

#include "Stone.hpp"

namespace GUI {
    Stone::Stone(std::string name) : _name(name)
    {
    }

    Stone::~Stone()
    {
    }

    std::string Stone::getName() const
    {
        return _name;
    }

    Model Stone::getModel() const
    {
        return _model;
    }

    Vector3 Stone::getPos() const
    {
        return _pos;
    }

    void Stone::setModel(Model model)
    {
        _model = model;
        if (_name == "mendiane")
            _model.transform = MatrixMultiply(MatrixScale(35.0f, 35.0f, 35.0f), MatrixRotateXYZ((Vector3){ DEG2RAD * 90.0f , 0.0f, 0.0f }));
        else
            _model.transform = MatrixRotateXYZ((Vector3){ DEG2RAD * 90.0f , 0.0f, 0.0f });
    }

    void Stone::setPos(Vector3 pos)
    {
        _pos = pos;
    }
}