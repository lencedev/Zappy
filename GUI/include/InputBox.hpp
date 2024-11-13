/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** InputBox
*/

#ifndef INPUTBOX_HPP_
    #define INPUTBOX_HPP_

    #include "UI.hpp"
    #include "Text.hpp"
    #include <algorithm>

namespace GUI {
    class InputBox : public UI {
        public:
            InputBox(Font font, Vector2 pos, Vector2 size, Color color, Color color2, std::string baseString = "...", bool rounded = false);
            ~InputBox();

            void displayElement();
            void addElements(std::shared_ptr<UI> element);

            void onClick(void);
            void onType(void);

            std::string getInput() const;
            void setInput(std::string input);
        protected:
        private:
            Text _text;
            Text _inputText;
            std::string _input;
            bool _typing;
            bool _clicked;
            Rectangle _rect;
            Color _color1;
            Color _color2;
            bool _rounded;
            Vector2 _pos;
            Vector2 _size;

    };
}

#endif /* !INPUTBOX_HPP_ */
