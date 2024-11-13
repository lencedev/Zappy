/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** Game
*/

#include "Game.hpp"
#include "Client.hpp"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

namespace GUI {
    Game::Game(Camera camera, Shader shader) : _camera(camera), _shader(shader),
        _cameraPos{{ 6.0f, 5.0f, 6.0f }, { 6.0f, 5.0f, -6.0f }, { -6.0f, 5.0f, -6.0f }, { -6.0f, 5.0f, 6.0f }}
    {
        _sendTimer = 0.0f;
        _getTimer = 0.0f;
        _mapTimer = 0.0f;
        _plvTimer = 0.0f;
        _pinTimer = 0.0f;
        _ppoTimer = 0.0f;
        _currentCameraPos = 0;
        _endScreenActive = false;

        _timeLocationShader = GetShaderLocation(_shader, "time");
        int resolutionLocation = GetShaderLocation(_shader, "resolution");
        float resolution[2] = { (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT };
        SetShaderValue(_shader, resolutionLocation, resolution, SHADER_UNIFORM_VEC2);
        Mesh mesh = GenMeshPlane(100, 100, 1, 1);
        _sea = LoadModelFromMesh(mesh);
        _sea.materials[0].shader = _shader;

        _winningTeam = "";

        _showInfo = false;
        _foodTotal = 0;
        _linemateTotal = 0;
        _deraumereTotal = 0;
        _siburTotal = 0;
        _mendianeTotal = 0;
        _phirasTotal = 0;
        _thystameTotal = 0;

        _fade = {255, 255, 255, 254};
        _fading = true;
        _fadeTimer = 0;

        _showFps = false;
        _clientConnected = false;
    }

    Game::Game(Vector2 mapSize, std::vector<std::shared_ptr<Tile>> tiles,
        float timeUnit, std::vector<std::string> teams, Client *client, Camera camera, Shader shader) : _mapSize(mapSize), _tiles(tiles), _timeUnit(timeUnit), _client(client), _teamsName(teams),
        _camera(camera), _cameraPos{{ 6.0f, 5.0f, 6.0f }, { 6.0f, 5.0f, -6.0f }, { -6.0f, 5.0f, -6.0f }, { -6.0f, 5.0f, 6.0f }}
    {
        _sendTimer = 0.0f;
        _getTimer = 0.0f;
        _mapTimer = 0.0f;
        _plvTimer = 0.0f;
        _pinTimer = 0.0f;
        _ppoTimer = 0.0f;
        _currentCameraPos = 0;
        _endScreenActive = false;

        _trantorModel = LoadModel("GUI/assets/models/trantor/trantor.glb");
        _eggModel = LoadModel("GUI/assets/models/egg/egg.glb");
        _tileModel = LoadModel("GUI/assets/models/tile/cube.glb");
        _foodModel = LoadModel("GUI/assets/models/food/banana.glb");
        _linemateModel = LoadModel("GUI/assets/models/stones/linemate/op.glb");
        _deraumereModel = LoadModel("GUI/assets/models/stones/deraumere/top.glb");
        _siburModel = LoadModel("GUI/assets/models/stones/sibur/sapp.glb");
        _mendianeModel = LoadModel("GUI/assets/models/stones/mendiane/rub.glb");
        _phirasModel = LoadModel("GUI/assets/models/stones/phiras/dia.glb");
        _thystameModel = LoadModel("GUI/assets/models/stones/thystame/star.glb");

        _foodTexture = LoadTexture("GUI/assets/textures/banana_icon.png");
        _linemateTexture = LoadTexture("GUI/assets/textures/opal_icon.png");
        _deraumereTexture = LoadTexture("GUI/assets/textures/topaz_icon.png");
        _siburTexture = LoadTexture("GUI/assets/textures/sapphire_icon.png");
        _mendianeTexture = LoadTexture("GUI/assets/textures/ruby_icon.png");
        _phirasTexture = LoadTexture("GUI/assets/textures/diamond_icon.png");
        _thystameTexture = LoadTexture("GUI/assets/textures/star_icon.png");
        _trantorTexture = LoadTexture("GUI/assets/textures/trantor_icon.png");
        _arrowTexture = LoadTexture("GUI/assets/textures/arrow.png");

        _eggModel.transform = MatrixRotateX(90 * DEG2RAD);
        _shader = shader;
        _timeLocationShader = GetShaderLocation(_shader, "time");
        int resolutionLocation = GetShaderLocation(_shader, "resolution");
        float resolution[2] = { (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT };
        SetShaderValue(_shader, resolutionLocation, resolution, SHADER_UNIFORM_VEC2);
        Mesh mesh = GenMeshPlane(100, 100, 1, 1);
        _sea = LoadModelFromMesh(mesh);
        _sea.materials[0].shader = _shader;
        _textFont = LoadFontEx("GUI/assets/fonts/lemon.otf", 120, 0, 250);

        _showInfo = false;
        _foodTotal = 0;
        _linemateTotal = 0;
        _deraumereTotal = 0;
        _siburTotal = 0;
        _mendianeTotal = 0;
        _phirasTotal = 0;
        _thystameTotal = 0;

        _fade = {255, 255, 255, 254};
        _fading = true;
        _fadeTimer = 0;

        _showFps = false;
        _clientConnected = false;
    }

    Game::~Game()
    {
    }

    void Game::setAllTiles(Model tileModel, Model foodModel, Model linemateModel, Model deraumereModel,
        Model siburModel, Model mendianeModel, Model phirasModel,
        Model thystameModel)
    {
        for (const auto &tile : _tiles) {
            tile->setItems(foodModel, linemateModel, deraumereModel,
                siburModel, mendianeModel, phirasModel, thystameModel);
            tile->distributeItems(-(_mapSize.x /2) + 0.5f + tile->getPosition().x, -(_mapSize.y /2) + 0.5f + tile->getPosition().z);
            tile->createTileCanva(_textFont);
            tile->setModel(tileModel);
        }
    }

    void Game::setTimeUnit(float timeUnit)
    {
        _timeUnit = timeUnit;
    }

    void Game::createTeams(Font font)
    {
        Color color[4] = {
            Color{128, 0, 128, 170},
            Color{220, 20, 60, 170},
            Color{100, 149, 237, 170},
            Color{255, 165, 0, 170}
        };

        for (size_t i = 0; i < _teamsName.size(); i++) {
            std::shared_ptr<Team> newTeam = std::make_shared<Team>(_teamsName[i], _trantorTexture);
            newTeam->createCanva(color[i], Vector2{20, (float)80 + (i * (250 - 20))},font);
            _teams.push_back(newTeam);
        }
    }

    void Game::updateMapInfo()
    {
        _foodTotal = 0;
        _linemateTotal = 0;
        _deraumereTotal = 0;
        _siburTotal = 0;
        _mendianeTotal = 0;
        _phirasTotal = 0;
        _thystameTotal = 0;

        for (const auto &tile : _tiles) {
            _foodTotal += tile->getFoodQuantity();
            _linemateTotal += tile->getLinemateQuantity();
            _deraumereTotal += tile->getDeraumereQuantity();
            _siburTotal += tile->getSiburQuantity();
            _mendianeTotal += tile->getMendianeQuantity();
            _phirasTotal += tile->getPhirasQuantity();
            _thystameTotal += tile->getThystameQuantity();
        }
    }

    void Game::createMapInfoUI()
    {
        Vector2 infoSize = { SCREEN_WIDTH / 5, SCREEN_HEIGHT / 2 };
        Vector2 infoPos = { SCREEN_WIDTH - (infoSize.x + 40), 50.0f };
        _mapInfoCanva = Canva(infoPos, infoSize, Color{BEIGE.r, BEIGE.g, BEIGE.b, 220}, RAYWHITE, ROUNDED);
        std::string mapSizeStr = "Map size: " + std::to_string((int)_mapSize.x) + "x" + std::to_string((int)_mapSize.y);
        std::shared_ptr<Text> mapSize = std::make_shared<Text>(40, mapSizeStr, Vector2{ infoPos.x + 60, infoPos.y + 50 }, Color{ 255, 255, 255, 255 }, _textFont);
        
        Text mapInfoText = Text(60, "Map info", Vector2{ infoPos.x + 10, infoPos.y + 10 }, Color{ 255, 255, 255, 255 }, _textFont);
        _mapInfoButton = std::make_shared<Button>(mapInfoText, Vector2{ infoSize.x + 5, 50 }, Vector2{ infoPos.x - 2.5f, infoPos.y - 5}, Color{BEIGE.r, BEIGE.g, BEIGE.b, 220}, RAYWHITE, ROUNDED);
    
        _mapInfoCanva.addElements(mapSize);
    }

    void Game::displayMapInfo()
    {
        _mapInfoCanva.displayElement();
        DrawTextEx(_textFont, ("x" + std::to_string(_foodTotal) + " (food)").c_str(), Vector2{ _mapInfoCanva.getPos().x + 70, _mapInfoCanva.getPos().y + 100 }, 30, 0, WHITE);
        DrawTextEx(_textFont, ("x" + std::to_string(_linemateTotal) + " (linemate)").c_str(), Vector2{ _mapInfoCanva.getPos().x + 70, _mapInfoCanva.getPos().y + 155 }, 30, 0, WHITE);
        DrawTextEx(_textFont, ("x" + std::to_string(_deraumereTotal) + " (deraumere)").c_str(), Vector2{ _mapInfoCanva.getPos().x + 70, _mapInfoCanva.getPos().y + 210 }, 30, 0, WHITE);
        DrawTextEx(_textFont, ("x" + std::to_string(_siburTotal) + " (sibur)").c_str(), Vector2{ _mapInfoCanva.getPos().x + 70, _mapInfoCanva.getPos().y + 265 }, 30, 0, WHITE);
        DrawTextEx(_textFont, ("x" + std::to_string(_mendianeTotal) + " (mendiane)").c_str(), Vector2{ _mapInfoCanva.getPos().x + 70, _mapInfoCanva.getPos().y + 320 }, 30, 0, WHITE);
        DrawTextEx(_textFont, ("x" + std::to_string(_phirasTotal) + " (phiras)").c_str(), Vector2{ _mapInfoCanva.getPos().x + 70, _mapInfoCanva.getPos().y + 375 }, 30, 0, WHITE);
        DrawTextEx(_textFont, ("x" + std::to_string(_thystameTotal) + " (thysthame)").c_str(), Vector2{ _mapInfoCanva.getPos().x + 70, _mapInfoCanva.getPos().y + 430 }, 30, 0, WHITE);
        DrawTextureEx(_foodTexture, Vector2{ _mapInfoCanva.getPos().x + 10, _mapInfoCanva.getPos().y + 85 }, 0, 0.4f, WHITE);
        DrawTextureEx(_linemateTexture, Vector2{ _mapInfoCanva.getPos().x + 10, _mapInfoCanva.getPos().y + 140 }, 0, 0.25f, WHITE);
        DrawTextureEx(_deraumereTexture, Vector2{ _mapInfoCanva.getPos().x + 10, _mapInfoCanva.getPos().y + 195 }, 0, 0.4f, WHITE);
        DrawTextureEx(_siburTexture, Vector2{ _mapInfoCanva.getPos().x + 10, _mapInfoCanva.getPos().y + 250 }, 0, 0.4f, WHITE);
        DrawTextureEx(_mendianeTexture, Vector2{ _mapInfoCanva.getPos().x + 10, _mapInfoCanva.getPos().y + 305 }, 0, 0.4f, WHITE);
        DrawTextureEx(_phirasTexture, Vector2{ _mapInfoCanva.getPos().x + 10, _mapInfoCanva.getPos().y + 360 }, 0, 0.4f, WHITE);
        DrawTextureEx(_thystameTexture, Vector2{ _mapInfoCanva.getPos().x + 10, _mapInfoCanva.getPos().y + 415 }, 0, 0.4f, WHITE);
    }

    void Game::createEndScreen(Font font)
    {
        _endScreen = Canva(Vector2{ 0, 0 }, Vector2{ SCREEN_WIDTH, SCREEN_HEIGHT }, Color{ 0, 0, 0, 170 }, Color{ 0, 0, 0, 0});
        std::shared_ptr<Text> endScreenText = std::make_shared<Text>(100, "GAME OVER", Vector2{ static_cast<float>(SCREEN_WIDTH / 2) - 250, 100 }, MAROON, font);
        Text quitText = Text(50, "            QUIT GAME", Vector2{ 0, 0 }, Color{ 255, 255, 255, 255 }, font);
        _quitButton = std::make_shared<Button>(quitText, Vector2{400, 150}, Vector2{ (SCREEN_WIDTH / 2) - 200, (SCREEN_HEIGHT / 2) + 75}, Color{ 0, 0, 0, 255 }, Color{ 255, 255, 255, 255 }, true);
        _endScreen.addElements(endScreenText);
        _endScreen.addElements(_quitButton);
    }

    void Game::initGame()
    {
        setAllTiles(_tileModel, _foodModel, _linemateModel, _deraumereModel,
            _siburModel, _mendianeModel, _phirasModel, _thystameModel);
        updateMapInfo();
        createTeams(_textFont);
        createMapInfoUI();
        createEndScreen(_textFont);
        Text temp = Text(1, "", Vector2{ 0, 0 }, BLANK, _textFont);
        std::shared_ptr<Button> timerCanva = std::make_shared<Button>(temp, Vector2{ 150, 50 }, Vector2{ (SCREEN_WIDTH / 2) - 75, 10 }, Color{BEIGE.r, BEIGE.g, BEIGE.b, 220}, WHITE, ROUNDED);
        _UI.push_back(timerCanva);
    }


    void Game::updateTile(std::string tiles)
    {
        std::vector<std::string> tilesArray = splitString(tiles, '\n');
        for (std::string tile : tilesArray) {
            if (tile.substr(0, 3) != "bct") continue;
            std::istringstream iss(tile);
            std::string temp, x, y, food, linemate, deraumere, sibur, mendiane, phiras, thystame;
            iss >> temp >> x >> y >> food >> linemate >> deraumere >> sibur >> mendiane >> phiras >> thystame;
            for (size_t i = 0; i < _tiles.size(); i++) {
                if (_tiles[i]->getPosition().x == std::stof(x) && _tiles[i]->getPosition().z == std::stof(y)) {
                    _tiles[i]->update(std::stoi(food), std::stoi(linemate), std::stoi(deraumere), std::stoi(sibur), std::stoi(mendiane), std::stoi(phiras), std::stoi(thystame),
                    _foodModel, _linemateModel, _deraumereModel, _siburModel, _mendianeModel, _phirasModel, _thystameModel, Vector2{-(_mapSize.x /2) + 0.5f + _tiles[i]->getPosition().x, -(_mapSize.y /2) + 0.5f + _tiles[i]->getPosition().z});
                    _tiles[i]->updateInfo(std::stoi(food), std::stoi(linemate), std::stoi(deraumere), std::stoi(sibur), std::stoi(mendiane), std::stoi(phiras), std::stoi(thystame));
                }
            }
        }
    }

    void Game::createAndAddNewPlayer(std::string playerInfo)
    {
        std::istringstream iss(playerInfo);
        std::string temp, id, x, y, orientation, level, teamName;
        iss >> temp >> id >> x >> y >> orientation >> level >> teamName;
        Vector3 pos = Vector3{ -(_mapSize.x /2) + 0.5f + std::stof(x), 0.5f, -(_mapSize.y /2) + 0.5f + std::stof(y) };
        std::shared_ptr<Trantor> newPlayer = std::make_shared<Trantor>(std::stoi(id), pos, std::stoi(level), std::stoi(orientation));
        newPlayer->setModel(_trantorModel);
        for (const auto &team : _teams) {
            if (team->getName() == teamName) {
                team->addPlayer(newPlayer);
            }
        }
    }

    void Game::updatePlayersPos(std::string newPos)
    {
        std::istringstream iss(newPos);
        std::string temp, id, x, y, orientation;
        iss >> temp >> id >> x >> y >> orientation;
        Vector3 targetPos = Vector3{ -(_mapSize.x /2) + 0.5f + std::stof(x), 0.5f, -(_mapSize.y /2) + 0.5f + std::stof(y) };
        for (const auto &team : _teams) {
            for (const auto &trantor : team->getTrantors()) {
                if (trantor->getId() == std::stoi(id)) {
                    trantor->setNextPos(targetPos);
                    trantor->setOrientation(std::stoi(orientation));
                    trantor->canMove = true;
                }
            }
        }
    }

    void Game::updatePlayersLevel(std::string newLevel)
    {
        std::istringstream iss(newLevel);
        std::string temp, id, level;
        iss >> temp >> id >> level;
        for (const auto &team : _teams) {
            for (const auto &trantor : team->getTrantors()) {
                if ((trantor->getId() == std::stoi(id)) && trantor->isAlive()) {
                    trantor->setLevel(std::stoi(level));
                }
            }
        }
    }

    void Game::updatePlayersInventory(std::string newInventory)
    {
        std::istringstream iss(newInventory);
        std::string temp, id, x, y, food, linemate, deraumere, sibur, mendiane, phiras, thystame;
        iss >> temp >> id >> x >> y >> food >> linemate >> deraumere >> sibur >> mendiane >> phiras >> thystame;
        for (const auto &team : _teams) {
            for (const auto &trantor : team->getTrantors()) {
                if ((trantor->getId() == std::stoi(id)) && trantor->isAlive()) {
                    trantor->updateInventory(std::stoi(food), std::stoi(linemate), std::stoi(deraumere), std::stoi(sibur), std::stoi(mendiane), std::stoi(phiras), std::stoi(thystame));
                }
            }
        }
    }

    void Game::removePlayer(std::string playerInfo)
    {
        std::istringstream iss(playerInfo);
        std::string temp, id;
        iss >> temp >> id;
        for (const auto &team : _teams) {
            for (const auto &trantor : team->getTrantors()) {
                if ((trantor->getId() == std::stoi(id)) && trantor->isAlive()) {
                    trantor->die();
                }
            }
        }
    }

    void Game::endGame(std::string winningTeam)
    {
        std::istringstream iss(winningTeam);
        std::string temp, team;
        iss >> temp >> team;
        _winningTeam = team;
        _endScreenActive = true;
    }

    void Game::getUpdatesFromServer()
    {
        std::vector<std::string> tmp = splitString(_client->receiveFromServer(), '\n');

        for (const auto &got : tmp) {
            if (!got.empty()) {
                if (got.substr(0, 3) == "pnw") {
                    if (!_clientConnected) _clientConnected = true;
                    createAndAddNewPlayer(got);
                }
                else if (got.substr(0, 3) == "plv") updatePlayersLevel(got);
                else if (got.substr(0, 3) == "pin") updatePlayersInventory(got);
                else if (got.substr(0, 3) == "ppo") updatePlayersPos(got);
                else if (got.substr(0, 3) == "pdi") removePlayer(got);
                else if (got.substr(0, 3) == "seg") endGame(got);
                else if (got.substr(0, 3) == "bct") {
                    updateTile(got);
                    updateMapInfo();
                }
                else _getTimer += 0.6f;
            }
        }
    }

    void Game::askPlayersPosition()
    {
        for (const auto &team : _teams) {
            for (const auto &trantor : team->getTrantors()) {
                if (trantor->isAlive()) _client->sendMessage("ppo " + std::to_string(trantor->getId()) + "\n");
            }
        }
    }

    void Game::askPlayersLevel()
    {
        for (size_t i = 0; i < _teams.size(); i++) {
            if (_teams[i]->getTrantors().size() == 0) {
                continue;
            } else {
                for (size_t j = 0; j < _teams[i]->getTrantors().size(); j++) {
                    if (_teams[i]->getTrantors()[j]->isAlive()) _client->sendMessage("plv " + std::to_string(_teams[i]->getTrantors()[j]->getId()) + "\n");
                }
            }
        }
    }

    void Game::askPlayersInventory()
    {
        for (size_t i = 0; i < _teams.size(); i++) {
            if (_teams[i]->getTrantors().size() == 0) {
                continue;
            } else {
                for (size_t j = 0; j < _teams[i]->getTrantors().size(); j++) {
                    if (_teams[i]->getTrantors()[j]->isAlive()) _client->sendMessage("pin " + std::to_string(_teams[i]->getTrantors()[j]->getId()) + "\n");
                }
            }
        }
    }

    void Game::askUpdatesToServer()
    {
        _plvTimer += GetFrameTime();
        _pinTimer += GetFrameTime();
        _ppoTimer += GetFrameTime();

        if (_ppoTimer > 0.66f) {
            askPlayersPosition();
            _ppoTimer = 0.0f;
        }
        if (_pinTimer > 1.88f) {
            askPlayersInventory();
            _pinTimer = 0.0f;
        }
        if (_plvTimer > 2.33f) {
            askPlayersLevel();
            _plvTimer = 0.0f;
        }
    }

    std::string formatToTime(float seconds)
    {
        int minutes = static_cast<int>(seconds) / 60;
        int secondsRemainder = static_cast<int>(seconds) % 60;

        std::stringstream ss;
        ss << std::setw(2) << std::setfill('0') << minutes << ":" << std::setw(2) << std::setfill('0') << secondsRemainder;
        return ss.str();
    }

    void Game::drawGame()
    {
        _camera.position = Vector3Lerp(_camera.position, _cameraPos[_currentCameraPos], 0.1f);

        if (IsKeyPressed(KEY_RIGHT)) _currentCameraPos++;
        else if (IsKeyPressed(KEY_LEFT)) _currentCameraPos--;

        if (_currentCameraPos >= 4) _currentCameraPos = 0;
        else if (_currentCameraPos < 0) _currentCameraPos = 3;

        if (IsKeyPressed(KEY_F2)) {
            endGame("Team epitech");
        }

        _mapTimer += GetFrameTime();

        if (_clientConnected) askUpdatesToServer();

        if (_mapTimer > 1.5f) {
            _client->sendMessage("mct\n");
            _mapTimer = 0.0f;
        }
        getUpdatesFromServer();

        static float gameTimer = 0.0f;
        gameTimer += GetFrameTime();

        float time = (float)GetTime();
        SetShaderValue(_shader, _timeLocationShader, &time, SHADER_UNIFORM_FLOAT);

        BeginDrawing();
            ClearBackground(SKYBLUE);
            BeginMode3D(_camera);
                DrawModel(_sea, Vector3{ 0.0f, 0.2f, 0.0f }, 1.0f, WHITE);
                for (const auto &tile : _tiles)
                    tile->drawTile({-(_mapSize.x /2) + 0.5f + tile->getPosition().x, 0.0f, -(_mapSize.y /2) + 0.5f + tile->getPosition().z}, _camera);
                for (const auto &team : _teams) {
                    team->drawPlayers(_trantorModel, _camera);
                }
            EndMode3D();
            for (const auto &tile : _tiles)
                tile->drawTileInfo(_foodTexture, _linemateTexture, _deraumereTexture, _siburTexture, _mendianeTexture, _phirasTexture, _thystameTexture, _textFont);
            for (const auto &team : _teams)
                team->displayInfos(_textFont, _camera, _foodTexture, _linemateTexture, _deraumereTexture, _siburTexture, _mendianeTexture, _phirasTexture, _thystameTexture, _arrowTexture);
            if (_showInfo) {
                displayMapInfo();
            }
            _mapInfoButton->displayElement();
            _mapInfoButton->onClick([this](){
                _showInfo = !_showInfo;
            });
            _mapInfoButton->onHover(YELLOW);
            DrawTextEx(_textFont, formatToTime(gameTimer).c_str(), Vector2{1920 / 2 - MeasureTextEx(_textFont, formatToTime(gameTimer).c_str(), 50, 1).x / 2, 10}, 50, 1, WHITE);
            if (_endScreenActive) {
                _endScreen.displayElement();
                _quitButton->onClick([this](){
                    CloseWindow();
                    exit(0);
                });
                DrawTextEx(_textFont, (_winningTeam + " is the winning team!").c_str(), Vector2{1920 / 2 - MeasureTextEx(_textFont, (_winningTeam +  + " is the winning team!").c_str(), 120, 1).x / 2, 1080 / 2 - 200}, 120, 1, YELLOW);
                _quitButton->onHover(YELLOW);
            }
            if (_fading) {
                DrawRectangle(0, 0, 1920, 1080, _fade);
                _fadeTimer += GetFrameTime();
                if (_fadeTimer > 0.01f && _fade.a > 0) {
                    _fade.a -= 2;
                    _fadeTimer = 0.0f;
                }
                if (_fade.a <= 0) _fading = false;
            }
            if (_showFps) myDrawFPS(Vector2{10, 10}, 30, YELLOW);
        EndDrawing();
    }

    void Game::setShowFps(bool showFps)
    {
        _showFps = showFps;
    }
}
