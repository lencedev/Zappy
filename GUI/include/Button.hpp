/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** Button
*/

#ifndef BUTTON_HPP_
    #define BUTTON_HPP_

    #include <functional>
    #include <memory>
    #include "Text.hpp"

namespace GUI {
    class Button : public UI {
        public:
            Button(Text text, Vector2 pos, Vector2 size, Color color, Color color2, bool rounded = false);
            ~Button();

            void displayElement();
            void addElements(std::shared_ptr<UI> element);

            void setText(Text text);
            void setRect(Rectangle rect);
            void setColors(Color color1, Color color2);
            // void setIsClicked(bool isClicked);
            // void setTexture(Texture2D texture);
            void setPos(Vector2 pos);
            void setSize(Vector2 size);

            void onClick(std::function<void()> const &lambda)
            {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), _rect)) {
                    lambda();
                }
            }

            void onHover(Color borderColor);

        protected:
        private:
            Text _text;
            Rectangle _rect;
            Color _color1;
            Color _color2;
            bool _rounded;
            bool _isClicked;
            // Texture2D _texture;
            Vector2 _pos;
            Vector2 _size;
    };
}

#endif /* !BUTTON_HPP_ */
