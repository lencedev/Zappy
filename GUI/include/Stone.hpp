/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** Stones
*/

#ifndef STONES_HPP_
    #define STONES_HPP_

    #include "Items.hpp"

namespace GUI {
    class Stone : public Items {
        public:
            Stone(std::string name);
            ~Stone();

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

#endif /* !STONES_HPP_ */
