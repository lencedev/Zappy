/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** Food
*/

#ifndef FOOD_HPP_
    #define FOOD_HPP_

    #include "Items.hpp"

namespace GUI {
    class Food : public Items {
        public:
            Food();
            ~Food();

            std::string getName() const;
            Model getModel() const;
            Vector3 getPos() const;

            void setPos(Vector3 pos);
            void setModel(Model model);

        private:
            std::string _name;
            Model _model;
            Vector3 _pos;
    };
}

#endif /* !FOOD_HPP_ */
