/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** CheckBox
*/

#ifndef CHECKBOX_HPP_
    #define CHECKBOX_HPP_

    #include "UI.hpp"

namespace GUI {
    class CheckBox : public UI {
        public:
            CheckBox(Vector2 pos, Vector2 size, Color color1 = RAYWHITE, Color color2 = BLACK);
            ~CheckBox();

            void displayElement();
            void addElements(std::shared_ptr<UI> element);

            void onClick(bool &value);
        protected:
        private:
            Texture2D _box;
            Texture2D _check;
            Rectangle _boxRec;
            Vector2 _pos;
            Vector2 _size;
            Color _color1;
            Color _color2;
            bool _checked;
            bool _value;
    };
}

#endif /* !CHECKBOX_HPP_ */
