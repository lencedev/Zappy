/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** Text
*/

#ifndef TEXT_HPP_
    #define TEXT_HPP_

    #include "UI.hpp"

namespace GUI {
    class Text : public UI {
        public:
            Text();
            Text(float size, std::string text, Vector2 pos, Color color, Font font);
            ~Text();

            void displayElement();
            void addElements(std::shared_ptr<UI> element);
            
            void setSize(float size);
            void setText(std::string text);
            void setPos(Vector2 pos);
            void setColor(Color color);
            void setFont(Font font);

            float getSize() const {return _size;};
            std::string getText() const {return _text;};
            Vector2 getPos() const {return _pos;};
            Color getColor() const {return _color;};
            Font getFont() const {return _font;};

        protected:
        private:
            float _size;
            std::string _text;
            Vector2 _pos;
            Color _color;
            Font _font;
    };
}

#endif /* !TEXT_HPP_ */
