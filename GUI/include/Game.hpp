/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** Game
*/

#ifndef GAME_HPP_
    #define GAME_HPP_

    #include "Team.hpp"
    #include "Canva.hpp"
    #include "Text.hpp"
    #include "Button.hpp"
    #include "UI.hpp"
    #include <raylib.h>
    #include <memory>
    #include <vector>
    #include <algorithm>
    #include <iomanip>

namespace GUI {
    class Client;
    class Game {
        public:
            Game(Camera camera, Shader shader);
            Game(Vector2 mapSize, std::vector<std::shared_ptr<Tile>> tiles,
                float timeUnit, std::vector<std::string> teams, Client *client, Camera camera, Shader shader);
            ~Game();

            void setAllTiles(Model tileModel, Model foodModel, Model linemateModel, Model deraumereModel,
                Model siburModel, Model mendianeModel, Model phirasModel,
                Model thystameModel);
            void setTimeUnit(float timeUnit);
            void createTeams(Font font);

            void updateMapInfo();
            void createMapInfoUI();
            void displayMapInfo();
            void createEndScreen(Font font);

            void initGame();
            void drawGame();

            void createAndAddNewPlayer(std::string newPlayer);
            void updatePlayersPos(std::string newPos);
            void updatePlayersLevel(std::string newLevel);
            void updatePlayersInventory(std::string newInventory);
            void removePlayer(std::string player);
            void endGame(std::string winningTeam);  

            void getUpdatesFromServer();
            void askPlayersPosition();
            void askPlayersLevel();
            void askPlayersInventory();
            void askUpdatesToServer();

            void updateTile(std::string tile);
            void setShowFps(bool showFps);
        private:
            Vector2 _mapSize;
            std::vector<std::shared_ptr<Tile>> _tiles;
            std::vector<std::string> _teamsName;
            std::vector<std::shared_ptr<Team>> _teams;
            std::vector<std::shared_ptr<UI>> _UI;
            Client *_client;
            float _timeUnit;
            float _sendTimer;
            float _getTimer;
            float _mapTimer;
            float _plvTimer;
            float _pinTimer;
            float _ppoTimer;
            bool _showFps;
            bool _clientConnected;

            Camera _camera;
            Vector3 _cameraPos[4];
            int _currentCameraPos;

            Canva _endScreen;
            bool _endScreenActive;
            std::shared_ptr<Button> _quitButton;
            std::string _winningTeam;

            Color _fade;
            bool _fading;
            float _fadeTimer;

            Model _trantorModel;
            Model _eggModel;
            Model _tileModel;
            Model _foodModel;
            Model _linemateModel;
            Model _deraumereModel;
            Model _siburModel;
            Model _mendianeModel;
            Model _phirasModel;
            Model _thystameModel;

            Shader _shader;
            int _timeLocationShader;
            Model _sea;
            Font _textFont;

            // Map info
            Canva _mapInfoCanva;
            std::shared_ptr<Button> _mapInfoButton;
            bool _showInfo;
            int _foodTotal;
            int _linemateTotal;
            int _deraumereTotal;
            int _siburTotal;
            int _mendianeTotal;
            int _phirasTotal;
            int _thystameTotal;

            Texture2D _foodTexture;
            Texture2D _linemateTexture;
            Texture2D _deraumereTexture;
            Texture2D _siburTexture;
            Texture2D _mendianeTexture;
            Texture2D _phirasTexture;
            Texture2D _thystameTexture;
            Texture2D _trantorTexture;
            Texture2D _arrowTexture;
    };
}

#endif /* !GAME_HPP_ */
