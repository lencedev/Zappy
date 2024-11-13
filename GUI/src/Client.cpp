/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** Client
*/

#include "Client.hpp"
#include "Game.hpp"
#include <fcntl.h>
#include <thread>
#include <chrono>
#include <sys/poll.h>
#include <sys/socket.h>

namespace GUI {
    Client::Client()
    {
        _receiving = false;
        _socket = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
        if (_socket == -1) {
            std::cerr << "Could not create socket" << std::endl;
            exit(84);
        }
        int flags = fcntl(_socket, F_GETFL, 0);
        if (flags == -1)
            std::cerr << "Failed to get socket flags." << std::endl;;
        if (fcntl(_socket, F_SETFL, flags | O_NONBLOCK) == -1)
            std::cerr << "Failed to set socket to non-blocking." << std::endl;
        _serv.sin_family = AF_INET;
    }

    Client::Client(int port, std::string host) : _port(port), _host(host)
    {
        _receiving = false;
        _socket = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
        if (_socket == -1) {
            std::cerr << "Could not create socket" << std::endl;
            exit(84);
        }
        int flags = fcntl(_socket, F_GETFL, 0);
        if (flags == -1)
            std::cerr << "Failed to get socket flags." << std::endl;;
        if (fcntl(_socket, F_SETFL, flags | O_NONBLOCK) == -1)
            std::cerr << "Failed to set socket to non-blocking." << std::endl;
        _serv.sin_family = AF_INET;
        _serv.sin_port = htons(_port);
        if (host == "localhost")
            _host = "127.0.0.1";
        if (inet_pton(AF_INET, _host.c_str(), &(_serv.sin_addr)) <= 0) {
            if (errno == EAFNOSUPPORT)
                std::cerr << "Address family not supported." << std::endl;
            else if (errno == EFAULT)
                std::cerr << "Invalid address pointer." << std::endl;
            else if (errno == EINVAL)
                std::cerr << "Invalid argument." << std::endl;
            else
                std::cerr << "Failed to convert address." << std::endl;
            exit(84);
        }
    }

    Client::Client(Client &other)
    {
        _port = other._port;
        _host = other._host;
        _socket = other._socket;
        _serv = other._serv;
    }

    Client::~Client()
    {
    }

    int Client::connectToServer()
    {
        int connectionResult = connect(_socket, reinterpret_cast<struct sockaddr*>(&_serv), sizeof(_serv));
        if (connectionResult == 0) {
            std::string receive = receiveFromServer();
            if (receive != "WELCOME\n") {
                std::cerr << "Connection failed. Wrong code" << std::endl;
                return -1;
            }
            sendMessage("GRAPHIC\n");
            parsedInfo = splitString(receiveFromServer(), '\n');
            return 0;
        } else if (errno == EINPROGRESS) {
            struct pollfd fds[1];
            fds[0].fd = _socket;
            fds[0].events = POLLOUT;

            int pollResult = poll(fds, 1, 10);
            if (pollResult == -1) {
                std::cerr << "Poll failed." << std::endl;
                return -1;
            } else if (pollResult == 0) {
                std::cerr << "Connection timeout." << std::endl;
                return -1;
            }

            int optVal;
            socklen_t optLen = sizeof(optVal);
            if (getsockopt(_socket, SOL_SOCKET, SO_ERROR, &optVal, &optLen) == -1) {
                std::cerr << "Failed to get socket option." << std::endl;
                return -1;
            }

            if (optVal == 0) {
                std::string receive = receiveFromServer();
                if (receive != "WELCOME\n") {
                    std::cerr << "Connection failed. Wrong code" << std::endl;
                    return -1;
                }
                sendMessage("GRAPHIC\n");
                parsedInfo = splitString(receiveFromServer(), '\n');
                return 0;
            } else {
                std::cerr << "Connection failed. Error code: " << optVal << std::endl;
                return -1;
            }
        } else {
            std::cerr << "Connection failed. Error code: " << errno << std::endl;
            return -1;
        }
    }


    int Client::sendMessage(std::string message)
    {
        if (send(_socket, message.c_str(), message.size(), 0) < 0) {
            std::cerr << "Send failed." << std::endl;
            return 1;
        }
        usleep(1000);
        return 0;
    }

    std::string Client::receiveFromServer()
    {
        char *buffer = new char[BUFFER_SIZE];
        int totalReceived = 0;
        int bufferSize = BUFFER_SIZE;
        struct pollfd fds[1];

        fds[0].fd = _socket;
        fds[0].events = POLLIN;
        while (true) {
            int ret = poll(fds, 1, 5);
            if (ret == -1) {
                std::cerr << "Poll failed." << std::endl;
                delete[] buffer;
                return "";
            } else if (ret == 0) {
                break;
            }
            int bytesReceived = recv(_socket, buffer + totalReceived, bufferSize - totalReceived, 0);

            if (bytesReceived > 0) {

                totalReceived += bytesReceived;
                if (totalReceived >= bufferSize) {
                    if (bufferSize >= MAX_MESSAGE_SIZE) {
                        std::cerr << "Message too large." << std::endl;
                        delete[] buffer;
                        return "";
                    }

                    bufferSize *= 2;
                    if (bufferSize >= MAX_MESSAGE_SIZE) {
                        bufferSize = MAX_MESSAGE_SIZE;
                    }

                    char *newBuffer = new char[bufferSize];
                    std::memcpy(newBuffer, buffer, totalReceived);

                    delete[] buffer;
                    buffer = newBuffer;
                }
                if (buffer[totalReceived - 1] == '\n') {
                    break;
                }
            } else if (bytesReceived == 0) {
                    break;
            } else if (bytesReceived == -1) {
                if (errno == EAGAIN || errno == EWOULDBLOCK) {
                    continue;
                } else {
                    std::cerr << "Receive failed. Error code: " << errno << std::endl;
                    delete[] buffer;
                    return "";
                }
            }
        }
        std::string message(buffer, totalReceived);
        delete[] buffer;
        return message;
    }

    void Client::closeConnection()
    {
        close(_socket);
    }

    Vector2 Client::getMapSizeFromServer()
    {
        for (const auto &i : parsedInfo) {
            if (i.substr(0, 3) == "msz") {
                std::istringstream iss(i);
                std::string temp, x, y;
                iss >> temp >> x >> y;
                return Vector2{std::stof(x), std::stof(y)};
            }
        }
        return Vector2{0, 0};
    }

    float Client::getTimeUnitFromServer()
    {
        for (const auto &i : parsedInfo) {
            if (i.substr(0, 3) == "sgt") {
                std::string timeUnit = i.substr(4, i.size() - 4);
                return std::stof(timeUnit);
            }
        }
        return 0;
    }

    std::vector<std::shared_ptr<Tile>> Client::getTilesFromServer()
    {
        std::vector<std::shared_ptr<Tile>> tiles;
        int id = 1;
        for (const auto &i : parsedInfo) {
            if (i.substr(0, 3) == "bct") {
                std::istringstream iss(i);
                std::string temp, x, y, food, linemate, deraumere, sibur, mendiane, phiras, thystame;
                iss >> temp >> x >> y >> food >> linemate >> deraumere >> sibur >> mendiane >> phiras >> thystame;
                std::shared_ptr<Tile> tile = std::make_shared<Tile>(std::stof(x), std::stof(y), std::stoi(food), std::stoi(linemate), std::stoi(deraumere), std::stoi(sibur), std::stoi(mendiane), std::stoi(phiras), std::stoi(thystame), id);
                tiles.push_back(tile);
                id++;
            }
        }
        return tiles;
    }

    std::vector<std::string> Client::getTeamsNameFromServer()
    {
        std::vector<std::string> teamsName;
        for (const auto &i : parsedInfo) {
            if (i.substr(0, 3) == "tna") {
                std::string teamName = i.substr(4, i.size() - 4);
                teamsName.push_back(teamName);
            }
        }
        return teamsName;
    }

    Game Client::createGameFromServer(Camera cam, Shader shader)
    {
        Vector2 mapSize = getMapSizeFromServer();
        float timeUnit = getTimeUnitFromServer();
        std::vector<std::shared_ptr<Tile>> tiles = getTilesFromServer();
        std::vector<std::string> teamsName = getTeamsNameFromServer();
        return Game(mapSize, tiles, timeUnit, teamsName, this, cam, shader);
    }

    int Client::getPort() const
    {
        return _port;
    }

    std::string Client::getHost() const
    {
        return _host;
    }

    int Client::getSocket() const
    {
        return _socket;
    }

    bool Client::isReceiving() const
    {
        return _receiving;
    }

    void Client::setPort(int port)
    {
        _port = port;
        _serv.sin_port = htons(_port);
    }

    void Client::setHost(std::string host)
    {
        _host = host;
        if (host == "localhost")
            _host = "127.0.0.1";
        if (inet_pton(AF_INET, _host.c_str(), &(_serv.sin_addr)) <= 0) {
            if (errno == EAFNOSUPPORT)
                std::cerr << "Address family not supported." << std::endl;
            else if (errno == EFAULT)
                std::cerr << "Invalid address pointer." << std::endl;
            else if (errno == EINVAL)
                std::cerr << "Invalid argument." << std::endl;
            else
                std::cerr << "Failed to convert address." << std::endl;
            _host = "127.0.0.1";
        }
    }
}