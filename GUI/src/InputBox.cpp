/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** InputBox
*/

#include "InputBox.hpp"

namespace GUI {
    InputBox::InputBox(Font font, Vector2 pos, Vector2 size, Color color1, Color color2, std::string baseString, bool rounded) : _color1(color1), _color2(color2), _rounded(rounded), _pos(pos), _size(size)
    {
        _text = Text(50, baseString, Vector2{0, 0}, GRAY, font);
        _inputText = Text(50, "", Vector2{0, 0}, BLACK, font);
        float xPos = _pos.x + _size.x / (_size.y / 10);
        float yPos = _pos.y + (_size.y / 2) - (_text.getSize() / 2);
        _text.setPos({xPos, yPos});
        _inputText.setPos({xPos, yPos});
        _rect = {pos.x, pos.y, size.x, size.y};
        _typing = false;
        _clicked = false;
        _input = "";
    }

    InputBox::~InputBox()
    {
    }

    void InputBox::displayElement()
    {
        if (_rounded) {
            DrawRectangleRounded(_rect, 1, 0, _color1);
            DrawRectangleRoundedLines(_rect, 1, 0, 5, _color2);
            if (!_typing && _input.length() == 0) {
                _text.displayElement();
            } else {
                _inputText.displayElement();
                onType();
            }
        } else {
            DrawRectangleRec(_rect, _color1);
            if (!_typing && _input.length() == 0) {
                _text.displayElement();
            } else {
                _inputText.displayElement();
                onType();
            }
        }
    }

    void InputBox::addElements(std::shared_ptr<UI> element)
    {
        (void)element;
    }

    void InputBox::onClick(void)
    {
        static Color save = _color2;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), _rect)) {
            _typing = true;
            _color2 = YELLOW;
        } else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !CheckCollisionPointRec(GetMousePosition(), _rect)) {
            _typing = false;
            _color2 = save;
        }
    }

    void InputBox::onType(void)
    {
        int key = GetKeyPressed();
        if (_typing) {
            while (key > 0) {
                if ((key >= 32) && (key <= 125) && (_input.length() < 20)) {
                    _input += (char)key;
                }
                key = GetKeyPressed();
            }
            std::transform(_input.begin(), _input.end(), _input.begin(), ::tolower);
            if (IsKeyPressed(KEY_BACKSPACE))
                if (_input.length() > 0)
                    _input.pop_back();
            if (IsKeyPressed(KEY_ENTER)) {
                if (_typing) _typing = false;
            }
            _inputText.setText(_input);
        }
    }

    std::string InputBox::getInput() const
    {
        if (_input.length() > 0)
            return _input;
        else
            return "";
    }

    void InputBox::setInput(std::string input)
    {
        _input = input;
        _inputText.setText(_input);
    }
}