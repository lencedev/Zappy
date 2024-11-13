/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** Tile
*/

#include "Tile.hpp"
#include <fstream>

namespace GUI {
    Tile::Tile(float posX, float posY, int foodQuantity, int linemateQuantity,
        int deraumereQuantity, int siburQuantity, int mendianeQuantity,
        int phirasQuantity, int thystameQuantity, int id) : _id(id)
    {
        _pos = {posX, 0.0f, posY};
        _foodQuantity = foodQuantity;
        _linemateQuantity = linemateQuantity;
        _deraumereQuantity = deraumereQuantity;
        _siburQuantity = siburQuantity;
        _mendianeQuantity = mendianeQuantity;
        _phirasQuantity = phirasQuantity;
        _thystameQuantity = thystameQuantity;
        _itemQuantity = _foodQuantity + _linemateQuantity + _deraumereQuantity +
            _siburQuantity + _mendianeQuantity + _phirasQuantity +
            _thystameQuantity;
        _selected = false;
    }

    Tile::~Tile()
    {
    }

    void Tile::setFoodQuantity(int quantity)
    {
        _foodQuantity = quantity;
    }

    void Tile::setLinemateQuantity(int quantity)
    {
        _linemateQuantity = quantity;
    }

    void Tile::setDeraumereQuantity(int quantity)
    {
        _deraumereQuantity = quantity;
    }

    void Tile::setSiburQuantity(int quantity)
    {
        _siburQuantity = quantity;
    }

    void Tile::setMendianeQuantity(int quantity)
    {
        _mendianeQuantity = quantity;
    }

    void Tile::setPhirasQuantity(int quantity)
    {
        _phirasQuantity = quantity;
    }

    void Tile::setThystameQuantity(int quantity)
    {
        _thystameQuantity = quantity;
    }

    void Tile::setSpawnTime(float spawnTime)
    {
        _spawnTime = spawnTime;
    }

    void Tile::setModel(Model model)
    {
        _model = model;
        _model.transform = MatrixScale(0.5f, 0.5f, 0.5f);
    }

    void Tile::setItems(Model foodModel, Model linemateModel, Model deraumereModel,
        Model siburModel, Model mendianeModel, Model phirasModel,
        Model thystameModel)
    {
        for (int i = 0; i < _foodQuantity; i++) {
            std::shared_ptr<Items> food = std::make_shared<Food>();
            food->setModel(foodModel);
            _items.push_back(food);
        }
        for (int i = 0; i < _linemateQuantity; i++) {
            std::shared_ptr<Items> linemate = std::make_shared<Stone>("linemate");
            linemate->setModel(linemateModel);
            _items.push_back(linemate);
        }
        for (int i = 0; i < _deraumereQuantity; i++) {
            std::shared_ptr<Items> deraumere = std::make_shared<Stone>("deraumere");
            deraumere->setModel(deraumereModel);
            _items.push_back(deraumere);
        }
        for (int i = 0; i < _siburQuantity; i++) {
            std::shared_ptr<Items> sibur = std::make_shared<Stone>("sibur");
            sibur->setModel(siburModel);
            _items.push_back(sibur);
        }
        for (int i = 0; i < _mendianeQuantity; i++) {
            std::shared_ptr<Items> mendiane = std::make_shared<Stone>("mendiane");
            mendiane->setModel(mendianeModel);
            _items.push_back(mendiane);
        }
        for (int i = 0; i < _phirasQuantity; i++) {
            std::shared_ptr<Items> phiras = std::make_shared<Stone>("phiras");
            phiras->setModel(phirasModel);
            _items.push_back(phiras);
        }
        for (int i = 0; i < _thystameQuantity; i++) {
            std::shared_ptr<Items> thystame = std::make_shared<Stone>("thystame");
            thystame->setModel(thystameModel);
            _items.push_back(thystame);
        }
    }

    int Tile::getFoodQuantity() const
    {
        return _foodQuantity;
    }

    int Tile::getLinemateQuantity() const
    {
        return _linemateQuantity;
    }

    int Tile::getDeraumereQuantity() const
    {
        return _deraumereQuantity;
    }

    int Tile::getSiburQuantity() const
    {
        return _siburQuantity;
    }

    int Tile::getMendianeQuantity() const
    {
        return _mendianeQuantity;
    }

    int Tile::getPhirasQuantity() const
    {
        return _phirasQuantity;
    }

    int Tile::getThystameQuantity() const
    {
        return _thystameQuantity;
    }

    int Tile::getItemQuantity() const
    {
        return _itemQuantity;
    }

    Vector3 Tile::getPosition() const
    {
        return _pos;
    }

    void Tile::createTileCanva(Font font)
    {
        Vector2 canvaSize = { 1920 / 5, 300 };
        Vector2 canvaPos = { 1920 - (canvaSize.x + 40), 1080 - (canvaSize.y + (canvaSize.y / 2) - 40)};
        _tileCanva = Canva(canvaPos, canvaSize, Color{DARKBROWN.r, DARKBROWN.g, DARKBROWN.b, 220}, GOLD, ROUNDED);
        std::string tileStr = "Tile #" + std::to_string(_id) + " at x:" + std::to_string((int)_pos.x) + " y:" + std::to_string((int)_pos.z);
        std::shared_ptr<Text> text1 = std::make_shared<Text>(30, tileStr, Vector2{canvaPos.x + 20, canvaPos.y + 20}, WHITE, font);
        std::shared_ptr<Text> text2 = std::make_shared<Text>(30, "Contains:", Vector2{canvaPos.x + 20, canvaPos.y + 55}, WHITE, font);
        _tileCanva.addElements(text1);
        _tileCanva.addElements(text2);
    }

    void Tile::distributeItems(float xPos, float yPos)
    {
        float numRows = std::sqrt(_itemQuantity);
        float numCols = std::ceil(static_cast<float>(_itemQuantity) / numRows);

        float cellWidth = 1.0f / numCols;
        float cellHeight = 1.0f / numRows;

        for (int i = 0; i < _itemQuantity; i++) {
            float row = i / numCols;
            float col = i % (int)numCols;
            
            float offsetX = (cellWidth - 1) / 2;
            float offsetY = (cellHeight - 1) / 2;

            float x = col * cellWidth + offsetX + xPos;
            float y = row * cellHeight + offsetY + yPos;

            if (_items[i]->getName() == "thystame")
                _items[i]->setPos({static_cast<float>(x), 0.70f, static_cast<float>(y)});
            else
                _items[i]->setPos({static_cast<float>(x), 0.5f, static_cast<float>(y)});
        }
    }

    void Tile::drawTile(Vector3 pos, Camera camera)
    {
        DrawModel(_model, pos, 1, WHITE);
        for (const auto &item : _items) {
            DrawModel(item->getModel(), item->getPos(), .5f, WHITE);
        }
        _bbox.min = {pos.x - 0.4f, pos.y + 0.4f, pos.z - 0.4f};
        _bbox.max = {pos.x + 0.4f, pos.y + 0.5f, pos.z + 0.4f};
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (GetRayCollisionBox(GetMouseRay(GetMousePosition(), camera), _bbox).hit) _selected = !_selected;
            else _selected = false;
        }
        if (_selected) DrawCubeWires(pos, 1, 1.15f, 1, YELLOW);
        else DrawCubeWires(pos, 1, 1, 1, RAYWHITE);
    }

    void Tile::drawTileInfo(Texture2D _foodTexture, Texture2D _linemateTexture,
        Texture2D _deraumereTexture, Texture2D _siburTexture, Texture2D _mendianeTexture,
        Texture2D _phirasTexture, Texture2D _thystameTexture, Font font)
    {
        if (_selected) {
            _tileCanva.displayElement();
            DrawTextEx(font, (": " + std::to_string(_foodQuantity) + "\n: " + std::to_string(_linemateQuantity) + "\n: " + std::to_string(_deraumereQuantity)).c_str(), Vector2{ _tileCanva.getPos().x + 40, _tileCanva.getPos().y + 95}, 30, 0, WHITE);
            DrawTextEx(font, (": " + std::to_string(_siburQuantity) + "\n: " + std::to_string(_mendianeQuantity) + "\n: " + std::to_string(_phirasQuantity)).c_str(), Vector2{ _tileCanva.getPos().x + 140, _tileCanva.getPos().y + 95}, 30, 0, WHITE);
            DrawTextEx(font, (": " + std::to_string(_thystameQuantity)).c_str(), Vector2{ _tileCanva.getPos().x + 240, _tileCanva.getPos().y + 95}, 30, 0, WHITE);
            DrawTextureEx(_foodTexture, Vector2{_tileCanva.getPos().x, _tileCanva.getPos().y + 92}, 0, 0.25f, WHITE);
            DrawTextureEx(_linemateTexture, Vector2{_tileCanva.getPos().x, _tileCanva.getPos().y + 92 + 40}, 0, 0.17f, WHITE);
            DrawTextureEx(_deraumereTexture, Vector2{_tileCanva.getPos().x, _tileCanva.getPos().y + 100 + 80}, 0, 0.25f, WHITE);
            DrawTextureEx(_siburTexture, Vector2{_tileCanva.getPos().x + 100, _tileCanva.getPos().y + 92}, 0, 0.25f, WHITE);
            DrawTextureEx(_mendianeTexture, Vector2{_tileCanva.getPos().x + 100, _tileCanva.getPos().y + 92 + 40}, 0, 0.25f, WHITE);
            DrawTextureEx(_phirasTexture, Vector2{_tileCanva.getPos().x + 100, _tileCanva.getPos().y + 95 + 80}, 0, 0.25f, WHITE);
            DrawTextureEx(_thystameTexture, Vector2{_tileCanva.getPos().x + 200, _tileCanva.getPos().y + 92}, 0, 0.25f, WHITE);
        }
    }

    void Tile::update(int food, int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame,
        Model foodModel, Model linemateModel, Model deraumereModel, Model siburModel, Model mendianeModel,
        Model phirasModel, Model thystameModel, Vector2 posOffset)
    {
        _foodQuantity = food;
        _linemateQuantity = linemate;
        _deraumereQuantity = deraumere;
        _siburQuantity = sibur;
        _mendianeQuantity = mendiane;
        _phirasQuantity = phiras;
        _thystameQuantity = thystame;
        _itemQuantity = _foodQuantity + _linemateQuantity + _deraumereQuantity + _siburQuantity + _mendianeQuantity + _phirasQuantity + _thystameQuantity;
        _items.clear();
        for (int i = 0; i < _foodQuantity; i++) {
            std::shared_ptr<Items> food = std::make_shared<Food>();
            food->setModel(foodModel);
            _items.push_back(food);
        }
        for (int i = 0; i < _linemateQuantity; i++) {
            std::shared_ptr<Items> linemate = std::make_shared<Stone>("linemate");
            linemate->setModel(linemateModel);
            _items.push_back(linemate);
        }
        for (int i = 0; i < _deraumereQuantity; i++) {
            std::shared_ptr<Items> deraumere = std::make_shared<Stone>("deraumere");
            deraumere->setModel(deraumereModel);
            _items.push_back(deraumere);
        }
        for (int i = 0; i < _siburQuantity; i++) {
            std::shared_ptr<Items> sibur = std::make_shared<Stone>("sibur");
            sibur->setModel(siburModel);
            _items.push_back(sibur);
        }
        for (int i = 0; i < _mendianeQuantity; i++) {
            std::shared_ptr<Items> mendiane = std::make_shared<Stone>("mendiane");
            mendiane->setModel(mendianeModel);
            _items.push_back(mendiane);
        }
        for (int i = 0; i < _phirasQuantity; i++) {
            std::shared_ptr<Items> phiras = std::make_shared<Stone>("phiras");
            phiras->setModel(phirasModel);
            _items.push_back(phiras);
        }
        for (int i = 0; i < _thystameQuantity; i++) {
            std::shared_ptr<Items> thystame = std::make_shared<Stone>("thystame");
            thystame->setModel(thystameModel);
            _items.push_back(thystame);
        }
        distributeItems(posOffset.x, posOffset.y);
    }

    void Tile::updateInfo(int food, int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame)
    {
        _foodQuantity = food;
        _linemateQuantity = linemate;
        _deraumereQuantity = deraumere;
        _siburQuantity = sibur;
        _mendianeQuantity = mendiane;
        _phirasQuantity = phiras;
        _thystameQuantity = thystame;
        _itemQuantity = _foodQuantity + _linemateQuantity + _deraumereQuantity + _siburQuantity + _mendianeQuantity + _phirasQuantity + _thystameQuantity;
    }
}