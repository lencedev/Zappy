/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-owen1.bolling
** File description:
** Client
*/

#ifndef CLIENT_HPP_
    #define CLIENT_HPP_

    #include <iostream>
    #include <vector>
    #include <cstring>
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <sstream>
    #include <raylib.h>
    #include <memory>
    #include <queue>
    #include <mutex>
    #include <condition_variable>
    #include "Tile.hpp"

    #define BUFFER_SIZE 1024
    #define MAX_MESSAGE_SIZE 10 * 1024 * 1024

namespace GUI {
    class Game;
    class Client {
        public:
            Client();
            Client(int port, std::string host);
            Client(Client &other);
            ~Client();

            int connectToServer();
            int sendMessage(std::string message);
            std::string receiveFromServer();
            void closeConnection();

            Vector2 getMapSizeFromServer();
            float getTimeUnitFromServer();
            std::vector<std::shared_ptr<Tile>> getTilesFromServer();
            std::vector<std::string> getTeamsNameFromServer();

            Game createGameFromServer(Camera cam, Shader shader);

            int getPort() const;
            std::string getHost() const;
            int getSocket() const;
            bool isReceiving() const;

            void setPort(int port);
            void setHost(std::string host);

        protected:
        private:
            int _port;
            std::string _host;
            std::string *_messages;
            std::vector<std::string> parsedInfo;
            int _socket;
            sockaddr_in _serv;
            bool _receiving;

            std::queue<std::string> _messageQueue;
            std::mutex _mutex;
            std::condition_variable _queueCondition;
    };

    inline std::vector<std::string> splitString(std::string str, const char delimiter)
    {
        std::vector<std::string> stringSplitted;
        std::stringstream ss(str);
        std::string token;

        while (std::getline(ss, token, delimiter))
            stringSplitted.push_back(token);
        return stringSplitted;
    }
}

#endif /* !CLIENT_HPP_ */
