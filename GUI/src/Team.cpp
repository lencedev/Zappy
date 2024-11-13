/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** Team
*/

#include "Team.hpp"

namespace GUI {
    Team::Team(std::string name, Texture2D trantorIcon) : _name(name), _trantorIcon(trantorIcon)
    {
        _index = 0;
    }

    Team::~Team()
    {
    }

    void Team::addPlayer(std::shared_ptr<Trantor> trantor)
    {
        _trantors.push_back(trantor);
    }

    void Team::createCanva(Color color, Vector2 pos, Font font)
    {
        _teamColor = Color{ color.r, color.g, color.b, 255 };
        _canva = Canva(pos, Vector2{200, 200}, color, Color{ color.r, color.g, color.b, 255 }, ROUNDED);
        float x = (200 - MeasureText(_name.c_str(), 20)) / 2;
        std::shared_ptr<Text> teamName = std::make_shared<Text>(20, _name, Vector2{x + 25, pos.y}, YELLOW, font);
        _pos = pos;
        _canva.addElements(teamName);
    }

    void Team::displayInfos(Font font, Camera cam, Texture2D food, Texture2D linemate, Texture2D deraumere,
        Texture2D sibur, Texture2D mendiane, Texture2D phiras, Texture2D thystame, Texture2D arrow)
    {
        _canva.displayElement();
        if (_trantors.size() > 0)
            for (size_t i = 0; i < _trantors.size(); i++) {
                std::string alive = _trantors[i]->isAlive() ? "Alive" : "Dead";
                Color color = _trantors[i]->isAlive() ? Color{0, 255, 0, 255} : Color{136, 8, 8, 255};
                DrawTextureEx(_trantorIcon, Vector2{_canva.getPos().x + 5, _canva.getPos().y + 28 + (i * 25)}, 0, 0.1, WHITE);
                DrawTextEx(font, ("Player #" + std::to_string(_trantors[i]->getId()) + ": " + alive + " | Lv. " + std::to_string(_trantors[i]->getLevel())).c_str(), Vector2{50, _canva.getPos().y + 30 + (i * 25)}, 18, 0, color);
                _trantors[i]->displayInventory(font, cam, food, linemate, deraumere, sibur, mendiane, phiras, thystame, arrow, _teamColor);
            }
    }

    void Team::drawPlayers(Model model, Camera cam)
    {
        for (size_t i = 0; i < _trantors.size(); i++) {
            if (_trantors[i]->getOrientation() == 2)
                DrawModelEx(model, Vector3{_trantors[i]->getPosition().x, _trantors[i]->getPosition().y, _trantors[i]->getPosition().z}, Vector3{ 0.0f, 0.1f, 0.0f }, 90, Vector3{ 1.0f, 1.0f, 1.0f }, _teamColor);
            else if (_trantors[i]->getOrientation() == 3)
                DrawModelEx(model, Vector3{_trantors[i]->getPosition().x, _trantors[i]->getPosition().y, _trantors[i]->getPosition().z}, Vector3{ 0.0f, 0.1f, 0.0f }, 0, Vector3{ 1.0f, 1.0f, 1.0f }, _teamColor);
            else if (_trantors[i]->getOrientation() == 4)
                DrawModelEx(model, Vector3{_trantors[i]->getPosition().x, _trantors[i]->getPosition().y, _trantors[i]->getPosition().z}, Vector3{ 0.0f, 0.1f, 0.0f }, 270, Vector3{ 1.0f, 1.0f, 1.0f }, _teamColor);
            else
                DrawModelEx(model, Vector3{_trantors[i]->getPosition().x, _trantors[i]->getPosition().y, _trantors[i]->getPosition().z}, Vector3{ 0.0f, 0.1f, 0.0f }, 180, Vector3{ 1.0f, 1.0f, 1.0f }, _teamColor);
            _trantors[i]->move();
            _trantors[i]->live(cam);
        }
    }

    std::string Team::getName() const
    {
        return _name;
    }

    std::vector<std::shared_ptr<Trantor>> Team::getTrantors() const
    {
        return _trantors;
    }
}