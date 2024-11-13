/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** UI
*/

#ifndef UI_HPP_
    #define UI_HPP_
    
    #include <iostream>
    #include <raylib.h>
    #include <vector>
    #include <memory>

    #define ROUNDED true

namespace GUI {
    class UI {
        public:
            virtual ~UI() = default;

            virtual void displayElement() = 0;
            virtual void addElements(std::shared_ptr<UI> element) = 0;

        protected:
        private:
    };

    inline void myDrawFPS(Vector2 pos, int size, Color color)
    {
        DrawText(TextFormat("FPS: %i", GetFPS()), pos.x, pos.y, size, color);
    }
}

#endif /* !UI_HPP_ */
