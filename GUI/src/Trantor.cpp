/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** Trantor
*/

#include "Trantor.hpp"

namespace GUI {
    Trantor::Trantor(int id, Vector3 basePos, int level, int orientation) : _id(id), _level(level), _pos(basePos), _orientation(orientation)
    {
        _alive = true;
        _incanting = false;
        _moveSpeed = 1.1f;
        _t = 0;
        canMove = false;
        _animationDelay = 1.f;
        _frameCounter = 0;
        _animCurrentFrame = 0;
        _animEnded = false;
        _animsCount = 0;
        _nextPos = basePos;
        _selected = false;
        _foodStock = 0;
        _linemateStock = 0;
        _deraumereStock = 0;
        _siburStock = 0;
        _mendianeStock = 0;
        _phirasStock = 0;
        _thystameStock = 0;
    }

    Trantor::~Trantor()
    {
    }

    void Trantor::live(Camera cam)
    {
        // if (_alive && !canMove) {
            // animate(IDLE, true);
        // }
        _bbox.min = { _pos.x - 0.5f, _pos.y + 0.2f, _pos.z - 0.5f };
        _bbox.max = { _pos.x + 0.5f, _pos.y + 1.0f, _pos.z + 0.5f };
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (GetRayCollisionBox(GetMouseRay(GetMousePosition(), cam), _bbox).hit) _selected = !_selected;
            else _selected = false;
        }
    }

    void Trantor::die()
    {
        // if (!_alive) {
        //     static bool once = true;
        //     if (once) {
        //         animate(DEATH, false);
        //         if (_animCurrentFrame == _currentAnim.frameCount - 1)
        //             once = false;
        //     }
        // }
        _alive = false;
        _pos = {100, 40, 0};
        _nextPos = {100, 40, 0};
    }

    void Trantor::move()
    {
        if (canMove) {
            if (std::round(_pos.x) == std::round(_nextPos.x) && std::round(_pos.z) == std::round(_nextPos.z))
                canMove = false;

            if ((std::round(_pos.x) == std::round(_nextPos.x) && std::round(_pos.z) != std::round(_nextPos.z)) ||
                (std::round(_pos.z) == std::round(_nextPos.z) && std::round(_pos.x) != std::round(_nextPos.x)) ||
                (std::round(_pos.x) != std::round(_nextPos.x) && std::round(_pos.z) != std::round(_nextPos.z))) {
                    // animate(WALK, true);
                    _t += GetFrameTime() * 0.1;
                    _pos = Vector3Lerp(_pos, _nextPos, _t);
            }
        } else {
            _t = 0;
            _pos = _nextPos;
        }

    }

    void Trantor::take()
    {
        animate(TAKE, false);
    }

    void Trantor::drop()
    {
        animate(TAKE, false);
    }

    void Trantor::eject()
    {
        animate(EJECT, false);
    }

    void Trantor::broadcast(std::string msg)
    {
        // animate(BROADCAST, false);
    }

    void Trantor::layEgg()
    {
        animate(LAYEGG, false);
    }

    void Trantor::animate(int animIndex, bool loop)
    {
        _currentAnim = _anims[animIndex];

        if (loop) _animEnded = true;

        if (_animEnded) {
            _frameCounter++;
            if (_frameCounter >= _animationDelay) {
                _animCurrentFrame = (unsigned int)(_animCurrentFrame + 1) % _currentAnim.frameCount;
                if (_animCurrentFrame == _currentAnim.frameCount) _animEnded = true;
                UpdateModelAnimation(_model, _currentAnim, _animCurrentFrame);
                _frameCounter = 0;
            }
        }
    }


    void Trantor::displayInventory(Font font, Camera cam, Texture2D food, Texture2D linemate, Texture2D deraumere,
        Texture2D sibur, Texture2D mendiane, Texture2D phiras, Texture2D thystame, Texture2D arrow, Color color)
    {
        Vector2 world = GetWorldToScreen(Vector3 { _pos.x, _pos.y, _pos.z }, cam);

        if (_selected) {
            DrawRectangleRoundedLines(Rectangle { world.x - 60, world.y - 340, 120, 220 }, 0.1, 10, 5, WHITE);
            DrawRectangleRounded(Rectangle { world.x - 60, world.y - 340, 120, 220 }, 0.1, 10, Color {color.r, color.g, color.b, 170});
            DrawTextEx(font, ("Player #" + std::to_string(_id) + "'s").c_str(), Vector2 { world.x - 50, world.y - 340 }, 20, 1, WHITE);
            DrawTextEx(font, "Inventory", Vector2 { world.x - 50, world.y - 320 }, 20, 1, WHITE);
            DrawTextEx(font, (": x" + std::to_string(_foodStock)).c_str(), Vector2 { world.x - 5, world.y - 300 }, 20, 1, WHITE);
            DrawTextEx(font, (": x" + std::to_string(_linemateStock)).c_str(), Vector2 { world.x - 5, world.y - 275 }, 20, 1, WHITE);
            DrawTextEx(font, (": x" + std::to_string(_deraumereStock)).c_str(), Vector2 { world.x - 5, world.y - 250 }, 20, 1, WHITE);
            DrawTextEx(font, (": x" + std::to_string(_siburStock)).c_str(), Vector2 { world.x - 5, world.y - 225 }, 20, 1, WHITE);
            DrawTextEx(font, (": x" + std::to_string(_mendianeStock)).c_str(), Vector2 { world.x - 5, world.y - 200 }, 20, 1, WHITE);
            DrawTextEx(font, (": x" + std::to_string(_phirasStock)).c_str(), Vector2 { world.x - 5, world.y - 175 }, 20, 1, WHITE);
            DrawTextEx(font, (": x" + std::to_string(_thystameStock)).c_str(), Vector2 { world.x - 5, world.y - 150 }, 20, 1, WHITE);
            DrawTextureEx(food, Vector2 { world.x - 38, world.y - 300 }, 0, 0.2, WHITE);
            DrawTextureEx(linemate, Vector2 { world.x - 38, world.y - 275 }, 0, 0.12, WHITE);
            DrawTextureEx(deraumere, Vector2 { world.x - 38, world.y - 250 }, 0, 0.2, WHITE);
            DrawTextureEx(sibur, Vector2 { world.x - 38, world.y - 225 }, 0, 0.2, WHITE);
            DrawTextureEx(mendiane, Vector2 { world.x - 38, world.y - 200 }, 0, 0.2, WHITE);
            DrawTextureEx(phiras, Vector2 { world.x - 38, world.y - 175 }, 0, 0.2, WHITE);
            DrawTextureEx(thystame, Vector2 { world.x - 38, world.y - 150 }, 0, 0.2, WHITE);
            DrawTextureEx(arrow, Vector2 { world.x - 17, world.y - 115 }, 0, 0.5f, YELLOW);
        }
    }

    void Trantor::updateInventory(int food, int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame)
    {
        _foodStock = food;
        _linemateStock = linemate;
        _deraumereStock = deraumere;
        _siburStock = sibur;
        _mendianeStock = mendiane;
        _phirasStock = phiras;
        _thystameStock = thystame;
    }

    void Trantor::setOrientation(int orientation)
    {
        _orientation = orientation;
    }

    void Trantor::setLevel(int level)
    {
        _level = level;
    }

    void Trantor::setModel(Model model)
    {
        _model = model;
    }

    void Trantor::setNextPos(Vector3 nextPos)
    {
        _nextPos = nextPos;
    }

    void Trantor::setAnimation(ModelAnimation *anims)
    {
        _anims = anims;
    }

    void Trantor::setAlive(bool alive)
    {
        _alive = alive;
    }

    int Trantor::getId() const
    {
        return _id;
    }

    int Trantor::getLevel() const
    {
        return _level;
    }

    int Trantor::getOrientation() const
    {
        return _orientation;
    }

    Vector3 Trantor::getPosition() const
    {
        return _pos;
    }

    Vector3 Trantor::getNextPos() const
    {
        return _nextPos;
    }

    Model Trantor::getModel() const
    {
        return _model;
    }

    ModelAnimation *Trantor::getAnimations() const
    {
        return _anims;
    }

    ModelAnimation Trantor::getCurrentAnimation() const
    {
        return _currentAnim;
    }

    bool Trantor::isAlive() const
    {
        return _alive;
    }
}