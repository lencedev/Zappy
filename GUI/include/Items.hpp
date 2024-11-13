/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** Items
*/

#ifndef ITEMS_HPP_
    #define ITEMS_HPP_

    #include <iostream>
    #include <raylib.h>
    #include <raymath.h>

namespace GUI {
    class Items {
        public:
            virtual ~Items() = default;

            virtual std::string getName() const = 0;
            virtual Model getModel() const = 0;
            virtual Vector3 getPos() const = 0;

            virtual void setPos(Vector3 pos) = 0;
            virtual void setModel(Model model) = 0;
    };
}

#endif /* !ITEMS_HPP_ */
