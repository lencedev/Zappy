/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** Trantor
*/

#ifndef TRANTOR_HPP_
    #define TRANTOR_HPP_

    #include <raylib.h>
    #include <iostream>
    #include <memory>
    #include <vector>
    #include <cmath>
    #include "Items.hpp"
    #include "Tile.hpp"
    #include "Canva.hpp"
    #include "Text.hpp"

    #define IDLE 6
    #define WALK 8
    #define EJECT 0
    #define HIT 5
    #define BROADCAST 1
    #define DEATH 2
    #define INCANTATION 4
    #define LAYEGG 7
    #define TAKE 3

namespace GUI {
    class Trantor {
        public:
            Trantor(int _id, Vector3 basePos, int level, int orientation);
            ~Trantor();

            void live(Camera cam);
            void die();
            void move();
            void take();
            void drop();
            // void incantate();
            void eject();
            void broadcast(std::string msg);
            void layEgg();

            void animate(int animIndex, bool loop);
            void displayInventory(Font font, Camera cam, Texture2D food, Texture2D linemate, Texture2D deraumere,
                Texture2D sibur, Texture2D mendiane, Texture2D phiras, Texture2D thystame, Texture2D arrow, Color color);

            void setLevel(int level);
            void setOrientation(int orientation);
            void setModel(Model model);
            void setNextPos(Vector3 nextPos);
            void setAnimation(ModelAnimation *anims);
            void updateInventory(int food, int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame);

            bool isAlive() const;
            void setAlive(bool alive);

            int getId() const;
            int getLevel() const;
            int getOrientation() const;
            std::vector<std::shared_ptr<Items>> getInventory() const;
            Vector3 getPosition() const;
            Vector3 getNextPos() const;
            Model getModel() const;
            ModelAnimation *getAnimations() const;
            ModelAnimation getCurrentAnimation() const;
            // void setCanMove(bool canMove);

            bool canMove;
        protected:
        private:
            int _id;
            int _level;
            bool _alive;
            bool _incanting;
            Vector3 _pos;
            Vector3 _nextPos;
            int _orientation;
            float _moveSpeed;
            float _t;

            int _foodStock;
            int _linemateStock;
            int _deraumereStock;
            int _siburStock;
            int _mendianeStock;
            int _phirasStock;
            int _thystameStock;

            Model _model;
            BoundingBox _bbox;
            bool _selected;

            ModelAnimation *_anims;
            ModelAnimation _currentAnim;
            float _animsCount;
            float _animationDelay;
            float _frameCounter;
            unsigned int _animCurrentFrame;
            bool _animEnded;
    };

    inline std::ostream &operator<<(std::ostream &os, const Trantor &trantor)
    {
        os << "Trantor: " << trantor.getPosition().x << ", " << trantor.getPosition().y << ", " << trantor.getPosition().z << std::endl;
        os << "Level: " << trantor.getLevel() << std::endl;
        return os;
    }

    inline std::ostream &operator<<(std::ostream &os, const std::shared_ptr<Trantor> &trantor)
    {
        if (trantor) {
            os << "Trantor: " << trantor->getPosition().x << ", " << trantor->getPosition().y << ", " << trantor->getPosition().z << std::endl;
            os << "Level: " << trantor->getLevel() << std::endl;
        }
        else
            os << "Trantor: NULL" << std::endl;
        return os;
    }
}

#endif /* !TRANTOR_HPP_ */
