/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** Tile
*/

#ifndef TILE_HPP_
    #define TILE_HPP_

    #include <raylib.h>
    #include <iostream>
    #include <memory>
    #include <vector>
    #include <cmath>
    #include "Items.hpp"
    #include "Food.hpp"
    #include "Stone.hpp"
    #include "UI.hpp"
    #include "Canva.hpp"
    #include "Text.hpp"

namespace GUI {
    class Tile {
        public:
            Tile(float posX, float posY, int foodQuantity, int linemateQuantity,
                int deraumereQuantity, int siburQuantity, int mendianeQuantity,
                int phirasQuantity, int thystameQuantity, int id);
            ~Tile();

            void setFoodQuantity(int foodQuantity);
            void setLinemateQuantity(int linemateQuantity);
            void setDeraumereQuantity(int deraumereQuantity);
            void setSiburQuantity(int siburQuantity);
            void setMendianeQuantity(int mendianeQuantity);
            void setPhirasQuantity(int phirasQuantity);
            void setThystameQuantity(int thystameQuantity);
            void setSpawnTime(float spawnTime);
            void setModel(Model model);
            void setItems(Model foodModel, Model linemateModel, Model deraumereModel,
                Model siburModel, Model mendianeModel, Model phirasModel,
                Model thystameModel);

            int getFoodQuantity() const;
            int getLinemateQuantity() const;
            int getDeraumereQuantity() const;
            int getSiburQuantity() const;
            int getMendianeQuantity() const;
            int getPhirasQuantity() const;
            int getThystameQuantity() const;
            int getItemQuantity() const;
            int getId() const;
            Vector3 getPosition() const;

            void createTileCanva(Font font);
            void distributeItems(float x, float y);
            void drawTile(Vector3 pos, Camera camera);
            void drawTileInfo(Texture2D _foodTexture, Texture2D _linemateTexture,
                Texture2D _deraumereTexture, Texture2D _siburTexture,
                Texture2D _mendianeTexture, Texture2D _phirasTexture,
                Texture2D _thystameTexture, Font font);
            void update(int food, int linemate, int deraumere, int sibur,
                int mendiane, int phiras, int thystame, Model foodModel, Model linemateModel,
                Model deraumereModel, Model siburModel, Model mendianeModel, Model phirasModel,
                Model thystameModel, Vector2 posOffset);
            void updateInfo(int food, int linemate, int deraumere, int sibur,
                int mendiane, int phiras, int thystame);

        private:
            Vector3 _pos;
            int _foodQuantity;
            int _linemateQuantity;
            int _deraumereQuantity;
            int _siburQuantity;
            int _mendianeQuantity;
            int _phirasQuantity;
            int _thystameQuantity;
            int _itemQuantity;
            float _spawnTime;
            int _id;
            Texture2D _texture;
            Model _model;
            std::vector<std::shared_ptr<Items>> _items;
            bool _selected;
            BoundingBox _bbox;

            Canva _tileCanva;
    };

    inline std::ostream &operator<<(std::ostream &os, const std::shared_ptr<Tile> &tile)
    {
        if (tile) {
            os << "Tile: {" << tile->getPosition().x << ", " << tile->getPosition().z;
            os << "} Contains: x" << tile->getFoodQuantity() << " food, x";
            os << tile->getLinemateQuantity() << " linemate, x";
            os << tile->getDeraumereQuantity() << " deraumere, x";
            os << tile->getSiburQuantity() << " sibur, x";
            os << tile->getMendianeQuantity() << " mendiane, x";
            os << tile->getPhirasQuantity() << " phiras, x";
            os << tile->getThystameQuantity() << " thystame";
        } else {
            os << "Tile: NULL";
        }
        return os;
    }
}

#endif /* !TILE_HPP_ */
