/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** Menu
*/

#include "Menu.hpp"

namespace GUI {
    Menu::Menu(Camera camera, Shader shader) : _camera(camera), _shaderBG(shader)
    {
        _font = LoadFontEx("GUI/assets/fonts/font.ttf", 150, 0, 250);
        _textFont = LoadFontEx("GUI/assets/fonts/lemon.otf", 150, 0, 250);
        _timeLocationShader = GetShaderLocation(_shaderBG, "time");
        int resolutionLocation = GetShaderLocation(_shaderBG, "resolution");
        float resolution[2] = {(float)GetScreenWidth(), (float)GetScreenHeight()};
        SetShaderValue(_shaderBG, resolutionLocation, resolution, SHADER_UNIFORM_VEC2);
        Mesh mesh = GenMeshPlane(100, 100, 1, 1);
        _bg = LoadModelFromMesh(mesh);
        _bg.materials[0].shader = _shaderBG;
        _status = MAIN_MENU;
        _connecting = false;
        _code = 1;
        _loadingTexture = LoadTexture("GUI/assets/textures/loading_sheet.png");
        _loadingRect = Rectangle{0, 0, static_cast<float>(_loadingTexture.width / 30), static_cast<float>(_loadingTexture.height)};
        _currentFrame = 0;
        _frameCounter = 0;
        _frameSpeed = 30;
        _fade = Color{255, 255, 255, 1};
        _fading = false;
        _fadeTimer = 0;
        _showFPS = false;
    }

    Menu::~Menu()
    {
    }

    void Menu::createMainMenu()
    {
        _mainCanva = Canva(Vector2{0, 0}, Vector2{1920, 1080}, Color{0, 0, 0, 0}, Color{0, 0, 0, 0});
        std::shared_ptr<Text> title = std::make_shared<Text>(150, "ZAPPY", Vector2{1920 / 2 - (float)MeasureText("ZAPPY", 80), 1080 / 4 - 150}, SKYBLUE, _font);
        std::shared_ptr<Text> title2 = std::make_shared<Text>(153, "ZAPPY", Vector2{1920 / 2 - (float)MeasureText("ZAPPY", 80) - 15, 1080 / 4 - 150}, DARKBLUE, _font);
        Text joinText = Text(50, "Connect", Vector2{1920 / 4 - 100, 1080 / 4 + 100}, RAYWHITE, _textFont);
        Text settingsText = Text(50, "Settings", Vector2{1920 / 4 - 100, 1080 / 4 + 200}, RAYWHITE, _textFont);
        Text exitText = Text(50, "Exit", Vector2{1920 / 4 - 100, 1080 / 4 + 300}, RAYWHITE, _textFont);
        _connectButton = std::make_shared<Button>(joinText, Vector2{400, 150}, Vector2{1920 / 2 - 200, 1080 - 700}, Color{BEIGE.r, BEIGE.g, BEIGE.b, 220}, RAYWHITE, ROUNDED);
        _settingsButton = std::make_shared<Button>(settingsText, Vector2{400, 150}, Vector2{1920 / 2 - 200, 1080 - 500}, Color{BEIGE.r, BEIGE.g, BEIGE.b, 220}, RAYWHITE, ROUNDED);
        _quitButton = std::make_shared<Button>(exitText, Vector2{400, 150}, Vector2{1920 / 2 - 200, 1080 - 300}, Color{BEIGE.r, BEIGE.g, BEIGE.b, 220}, RAYWHITE, ROUNDED);

        _mainCanva.addElements(title2);
        _mainCanva.addElements(title);
        _mainCanva.addElements(_connectButton);
        _mainCanva.addElements(_settingsButton);
        _mainCanva.addElements(_quitButton);
    }

    void Menu::createConnectMenu()
    {
        _connectCanva = Canva(Vector2{0, 0}, Vector2{1920, 1080}, Color{0, 0, 0, 0}, Color{0, 0, 0, 0});
        std::shared_ptr<Text> title = std::make_shared<Text>(100, "Connect to server", Vector2{1920 / 2 - (float)MeasureText("Connect to server", 60), 1080 / 4 - 100}, SKYBLUE, _font);
        std::shared_ptr<Text> title2 = std::make_shared<Text>(102, "Connect to server", Vector2{1920 / 2 - (float)MeasureText("Connect to server", 60) - 12, 1080 / 4 - 100}, DARKBLUE, _font);
        Text connectText = Text(50, "Connect", Vector2{1920 / 4 - 100, 1080 / 4 + 300}, RAYWHITE, _textFont);
        Text backText = Text(50, "Go Back", Vector2{1920 / 4 - 100, 1080 / 4 + 400}, RAYWHITE, _textFont);
        _connectButtonConnectMenu = std::make_shared<Button>(connectText, Vector2{400, 150}, Vector2{1920 / 2 + 25, 1080 - 300}, Color{BEIGE.r, BEIGE.g, BEIGE.b, 220}, RAYWHITE, ROUNDED);
        _backButtonConnectMenu = std::make_shared<Button>(backText, Vector2{400, 150}, Vector2{1920 / 2 - 475, 1080 - 300}, Color{BEIGE.r, BEIGE.g, BEIGE.b, 220}, RAYWHITE, ROUNDED);
        _portInput = std::make_shared<InputBox>(_textFont, Vector2{1920 / 2 - 200, 1080 / 2 + 50}, Vector2{400, 100}, RAYWHITE, GRAY, "port...", ROUNDED);
        _hostInput = std::make_shared<InputBox>(_textFont, Vector2{1920 / 2 - 200, 1080 / 2 - 150}, Vector2{400, 100}, RAYWHITE, GRAY, "host...", ROUNDED);

        _connectCanva.addElements(title2);
        _connectCanva.addElements(title);
        _connectCanva.addElements(_connectButtonConnectMenu);
        _connectCanva.addElements(_backButtonConnectMenu);
        _connectCanva.addElements(_portInput);
        _connectCanva.addElements(_hostInput);
    }

    void Menu::createSettingsMenu()
    {
        _settingsCanva = Canva(Vector2{0, 0}, Vector2{1920, 1080}, Color{0, 0, 0, 0}, Color{0, 0, 0, 0});
        std::shared_ptr<Text> title = std::make_shared<Text>(100, "Settings", Vector2{1920 / 2 - (float)MeasureText("Settings", 60), 1080 / 4 - 100}, SKYBLUE, _font);
        std::shared_ptr<Text> title2 = std::make_shared<Text>(102, "Settings", Vector2{1920 / 2 - (float)MeasureText("Settings", 60) - 12, 1080 / 4 - 100}, DARKBLUE, _font);
        Text backText = Text(50, "Go Back", Vector2{1920 / 4 - 100, 1080 / 4 + 300}, RAYWHITE, _textFont);
        _backButtonSettingsMenu = std::make_shared<Button>(backText, Vector2{400, 150}, Vector2{1920 / 2 - 200, 1080 - 300}, Color{BEIGE.r, BEIGE.g, BEIGE.b, 220}, RAYWHITE, ROUNDED);
        std::shared_ptr<Text> showFPSText = std::make_shared<Text>(70, "Show FPS:", Vector2{1920 / 2 - 200, 1080 / 2 - 200}, RAYWHITE, _textFont);
        std::shared_ptr<Text> showFPSText2 = std::make_shared<Text>(74, "Show FPS:", Vector2{1920 / 2 - 210, 1080 / 2 - 200}, BLACK, _textFont);
        _showFPSBox = std::make_shared<CheckBox>(Vector2{1920 / 2 + 130, 1080 / 2 - 210}, Vector2{100, 100}, Color{BEIGE.r, BEIGE.g, BEIGE.b, 255}, RAYWHITE);
        std::shared_ptr<Text> targetFpsText = std::make_shared<Text>(70, "Target FPS:", Vector2{1920 / 2 - 260, 1080 / 2 - 50}, RAYWHITE, _textFont);
        std::shared_ptr<Text> targetFpsText2 = std::make_shared<Text>(74, "Target FPS:", Vector2{1920 / 2 - 270, 1080 / 2 - 50}, BLACK, _textFont);
        Text fpsButton1 = Text(70, "60", Vector2{1920 / 2 + 130, 1080 / 2 - 50}, RAYWHITE, _textFont);
        Text fpsButton2 = Text(70, "120", Vector2{1920 / 2 + 130, 1080 / 2 + 50}, RAYWHITE, _textFont);
        Text fpsButton3 = Text(70, "144", Vector2{1920 / 2 + 130, 1080 / 2 + 150}, RAYWHITE, _textFont);
        _60fpsButton = std::make_shared<Button>(fpsButton1, Vector2{100, 100}, Vector2{1920 / 2 + 130, 1080 / 2 - 60}, Color{BEIGE.r, BEIGE.g, BEIGE.b, 255}, RAYWHITE, ROUNDED);
        _120fpsButton = std::make_shared<Button>(fpsButton2, Vector2{100, 100}, Vector2{1920 / 2 + 250, 1080 / 2 - 60}, Color{BEIGE.r, BEIGE.g, BEIGE.b, 255}, RAYWHITE, ROUNDED);
        _144fpsButton = std::make_shared<Button>(fpsButton3, Vector2{100, 100}, Vector2{1920 / 2 + 370, 1080 / 2 - 60}, Color{BEIGE.r, BEIGE.g, BEIGE.b, 255}, RAYWHITE, ROUNDED);

        _settingsCanva.addElements(title2);
        _settingsCanva.addElements(title);
        _settingsCanva.addElements(_backButtonSettingsMenu);
        _settingsCanva.addElements(showFPSText2);
        _settingsCanva.addElements(showFPSText);
        _settingsCanva.addElements(_showFPSBox);
        _settingsCanva.addElements(targetFpsText2);
        _settingsCanva.addElements(targetFpsText);
        _settingsCanva.addElements(_60fpsButton);
        _settingsCanva.addElements(_120fpsButton);
        _settingsCanva.addElements(_144fpsButton);
    }

    void Menu::createAnswerTab()
    {
        _answerTabCanva = Canva(Vector2{0, 0}, Vector2{1920, 1080}, Color{0, 0, 0, 100}, Color{0, 0, 0, 0});
        _loadingCanva = std::make_shared<Canva>(Vector2{1920 / 2 - 250, 1080 / 2 - 250}, Vector2{500, 500}, Color{BEIGE.r, BEIGE.g, BEIGE.b, 220}, Color{BEIGE.r, BEIGE.g, BEIGE.b, 255}, ROUNDED);
        _okCanva = std::make_shared<Canva>(Vector2{1920 / 2 - 250, 1080 / 2 - 250}, Vector2{500, 500}, Color{BEIGE.r, BEIGE.g, BEIGE.b, 220}, Color{BEIGE.r, BEIGE.g, BEIGE.b, 255}, ROUNDED);
        _koCanva = std::make_shared<Canva>(Vector2{1920 / 2 - 250, 1080 / 2 - 250}, Vector2{500, 500}, Color{BEIGE.r, BEIGE.g, BEIGE.b, 220}, Color{BEIGE.r, BEIGE.g, BEIGE.b, 255}, ROUNDED);

        std::shared_ptr<Text> conntecting = std::make_shared<Text>(60, "Connecting", Vector2{1920 / 2 - 160, 1080 / 2 - 200}, RAYWHITE, _textFont);
        std::shared_ptr<Text> server = std::make_shared<Text>(60, " to server...", Vector2{1920 / 2 - 150, 1080 / 2 - 140}, RAYWHITE, _textFont);
        _answerTabText = std::make_shared<Text>(60, "", Vector2{1920 / 2 - 160, 1080 / 2 - 200}, RAYWHITE, _textFont);
        Text backText = Text(50, "OK", Vector2{1920 / 2 - 100, 1080 / 2 - 200}, RAYWHITE, _textFont);
        _okButton = std::make_shared<Button>(backText, Vector2{350, 100}, Vector2{1920 / 2 - 175, 1080 / 2 + 50}, Color{BEIGE.r, BEIGE.g, BEIGE.b, 220}, RAYWHITE, ROUNDED);
        _koButton = std::make_shared<Button>(backText, Vector2{350, 100}, Vector2{1920 / 2 - 175, 1080 / 2 + 50}, Color{BEIGE.r, BEIGE.g, BEIGE.b, 220}, RAYWHITE, ROUNDED);
        
        _loadingCanva->addElements(conntecting);
        _loadingCanva->addElements(server);
        _okCanva->addElements(_answerTabText);
        _okCanva->addElements(_okButton);
        _koCanva->addElements(_answerTabText);
        _koCanva->addElements(_koButton);
    }

    void Menu::createMenus()
    {
        createMainMenu();
        createConnectMenu();
        createSettingsMenu();
        createAnswerTab();
    }

    void Menu::drawAnswerTab()
    {
        _loadingTimer += GetFrameTime();
        _answerTabCanva.displayElement();
        if (_loadingTimer < 1.5f) {
            _loadingCanva->displayElement();
            DrawTextureRec(_loadingTexture, _loadingRect, Vector2{ 1920 / 2 - (_loadingRect.width / 2), 1080 / 2 }, RAYWHITE);
        } else {
            if (_code == 0) {
                _answerTabText->setText("Connection\nsuccessfull!");
                _answerTabText->setColor(GREEN);
                _okCanva->displayElement();
                _okButton->onClick([this](){
                    _fading = true;
                });
                _okButton->onHover(YELLOW);
            } else if (_code == -1){
                _answerTabText->setText("Connection\n     failed!");
                _answerTabText->setColor(RED);
                _koCanva->displayElement();
                _koButton->onClick([this](){
                    _connecting = false;
                });
                _koButton->onHover(YELLOW);
            }
        }
    }

    void Menu::connectToServerOnce(std::string port, std::string host)
    {
        Client client(atoi(port.c_str()), host);
        _code = client.connectToServer();
    }

    void Menu::drawMenu(int gameState)
    {
        _gameState = gameState;
        float time = (float)GetTime();
        _frameCounter++;
        if (_frameCounter >= (60/_frameSpeed)) {
            _frameCounter = 0;
            _currentFrame++;
            if (_currentFrame > 29) _currentFrame = 0;
            _loadingRect.x = (float)_currentFrame * (float)_loadingTexture.width / 30;
        }
        SetShaderValue(_shaderBG, _timeLocationShader, &time, SHADER_UNIFORM_FLOAT);
        BeginDrawing();
            ClearBackground(SKYBLUE);
            BeginMode3D(_camera);
                DrawModel(_bg, Vector3{0, 0, 0}, 1.0f, WHITE);
            EndMode3D();
            if (_status == MAIN_MENU) {
                _mainCanva.displayElement();
                _connectButton->onClick([this](){ _status = CONNECT_MENU; });
                _connectButton->onHover(YELLOW);
                _settingsButton->onClick([this](){ _status = SETTINGS_MENU; });
                _settingsButton->onHover(YELLOW);
                _quitButton->onClick([this](){
                    std::cout << "Quitting game" << std::endl;
                    CloseWindow();
                    exit(0);
                });
                _quitButton->onHover(YELLOW);
            }
            else if (_status == CONNECT_MENU) {
                _connectCanva.displayElement();
                _connectButtonConnectMenu->onClick([this]() {
                    _connecting = true;
                    _loadingTimer = 0;
                });
                _connectButtonConnectMenu->onHover(YELLOW);
                _backButtonConnectMenu->onClick([this]() {
                    _status = MAIN_MENU;
                });
                _backButtonConnectMenu->onHover(YELLOW);
                _hostInput->onClick();
                _portInput->onClick();
                _port = _portInput->getInput();
                _host = _hostInput->getInput();
                if (_connecting) {
                    std::call_once(_flag, &Menu::connectToServerOnce, this, _port, _host);
                    drawAnswerTab();
                }
            }
            else if (_status == SETTINGS_MENU) {
                _settingsCanva.displayElement();
                _backButtonSettingsMenu->onClick([this]() {
                    _status = MAIN_MENU;
                });
                _backButtonSettingsMenu->onHover(YELLOW);
                _showFPSBox->onClick(_showFPS);
                _60fpsButton->onClick([this]() {
                    SetTargetFPS(60);
                });
                _60fpsButton->onHover(YELLOW);
                _120fpsButton->onClick([this]() {
                    SetTargetFPS(120);
                });
                _120fpsButton->onHover(YELLOW);
                _144fpsButton->onClick([this]() {
                    SetTargetFPS(144);
                });
                _144fpsButton->onHover(YELLOW);
            }
            if (_fading) {
                _fadeTimer += GetFrameTime();
                if (_fadeTimer >= 0.01f && _fade.a < 255) {
                    _fade.a += 2;
                    _fadeTimer = 0.0f;
                }
                if (_fade.a >= 255) _gameState = 1;
            }
            if (_showFPS) myDrawFPS(Vector2{10, 10}, 30, YELLOW);
            DrawRectangle(0, 0, 1920, 1080, _fade);
        EndDrawing();
    }

    std::string Menu::getMenuHost()
    {
        return _host;
    }

    int Menu::getMenuPort()
    {
        return atoi(_port.c_str());
    }

    int Menu::getGameState()
    {
        return _gameState;
    }

    int Menu::getTargetFPS()
    {
        return _targetFPS;
    }

    bool Menu::getShowFPS()
    {
        return _showFPS;
    }
}
