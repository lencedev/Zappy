/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** Canva
*/

#ifndef CANVA_HPP_
    #define CANVA_HPP_

    #include "UI.hpp"

namespace GUI {
    class Canva : public UI {
        public:
            Canva();
            Canva(Vector2 pos, Vector2 size, Color color1, Color color2, bool rounded = false);
            ~Canva();

            void displayElement();
            void addElements(std::shared_ptr<UI> element);
            std::vector<std::shared_ptr<UI>> getElements() {return std::vector<std::shared_ptr<UI>>(_elements);};

            void setPos(Vector2 pos);
            void setSize(Vector2 size);
            void setColor(Color color);
            void setRect(Rectangle rect);

            Vector2 getPos() {return _pos;};
            Vector2 getSize() {return _size;};
            Rectangle getRect() {return _rect;};

        protected:
        private:
            Vector2 _pos;
            Vector2 _size;
            Color _color1;
            Color _color2;
            Rectangle _rect;
            std::vector<std::shared_ptr<UI>> _elements;
            bool _rounded;
    };
}

#endif /* !CANVA_HPP_ */
