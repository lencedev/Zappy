/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** Menu
*/

#ifndef MENU_HPP_
    #define MENU_HPP_

    #include "Canva.hpp"
    #include "Button.hpp"
    #include "Text.hpp"
    #include "InputBox.hpp"
    #include "CheckBox.hpp"
    #include "Client.hpp"
    #include <raylib.h>
    #include <mutex>

    #define MAIN_MENU 0
    #define SETTINGS_MENU 1
    #define CONNECT_MENU 2

namespace GUI {
    class Menu {
        public:
            Menu(Camera camera, Shader shader);
            ~Menu();

            void createMainMenu();
            void createConnectMenu();
            void createSettingsMenu();
            void createAnswerTab();
            void createMenus();

            void connectToServerOnce(std::string port, std::string host);
            void drawAnswerTab();
            void drawMenu(int gameState);

            int getMenuPort();
            std::string getMenuHost();
            int getGameState();
            int getTargetFPS();
            bool getShowFPS();

        protected:
        private:
            std::once_flag _flag;

            Camera _camera;
            Canva _mainCanva;
            Canva _settingsCanva;
            Canva _connectCanva;
            Canva _answerTabCanva;
            Shader _shaderBG;
            Font _font;
            Font _textFont;
            Color _fade;
            bool _fading;
            float _fadeTimer;
            int _status;
            int _timeLocationShader;
            float _loadingTimer;
            Model _bg;
            std::shared_ptr<Button> _connectButton;
            std::shared_ptr<Button> _settingsButton;
            std::shared_ptr<Button> _quitButton;
            bool _connecting;

            Texture2D _loadingTexture;
            Rectangle _loadingRect;
            int _currentFrame;
            int _frameCounter;
            int _frameSpeed;
        
            //Connect menu
            std::string _port;
            std::string _host;
            std::shared_ptr<InputBox> _portInput;
            std::shared_ptr<InputBox> _hostInput;
            std::shared_ptr<Button> _connectButtonConnectMenu;
            std::shared_ptr<Button> _backButtonConnectMenu;
            int _code;
            int _gameState;

            //Answer tab
            std::shared_ptr<Canva> _loadingCanva;
            std::shared_ptr<Canva> _okCanva;
            std::shared_ptr<Canva> _koCanva;
            std::shared_ptr<Button> _okButton;
            std::shared_ptr<Button> _koButton;
            std::shared_ptr<Text> _answerTabText;

            //Settings menu
            int _targetFPS;
            bool _showFPS;
            bool _fullscreen;
            std::shared_ptr<Button> _backButtonSettingsMenu;
            std::shared_ptr<CheckBox> _showFPSBox;
            std::shared_ptr<Button> _60fpsButton;
            std::shared_ptr<Button> _120fpsButton;
            std::shared_ptr<Button> _144fpsButton;
            std::shared_ptr<CheckBox> _fullscreenBox;
    };
}

#endif /* !MENU_HPP_ */
