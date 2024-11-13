/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** Team
*/

#ifndef TEAM_HPP_
    #define TEAM_HPP_

    #include <iostream>
    #include <memory>
    #include <vector>
    #include <algorithm>
    #include "Trantor.hpp"
    #include "Canva.hpp"
    #include "Text.hpp"

namespace GUI {
    class Team {
        public:
            Team(std::string name, Texture2D trantorIcon);
            ~Team();

            void addPlayer(std::shared_ptr<Trantor> trantor);

            void createCanva(Color color, Vector2 pos, Font font);

            void displayInfos(Font font, Camera cam, Texture2D food, Texture2D linemate, Texture2D deraumere,
                Texture2D sibur, Texture2D mendiane, Texture2D phiras, Texture2D thystame, Texture2D arrow);
            void drawPlayers(Model model, Camera cam);

            std::string getName() const;
            std::vector<std::shared_ptr<Trantor>> getTrantors() const;

        protected:
        private:
            std::string _name;
            Texture2D _trantorIcon;
            std::vector<std::shared_ptr<Trantor>> _trantors;
            Canva _canva;
            Vector2 _pos;
            Color _teamColor;

            int _index;
    };
}

#endif /* !TEAM_HPP_ */
