**Zappy**

Zappy is a distributed multiplayer game developed in C++. The project consists of a server that hosts the game, a client that connects players to the server, and an AI component that simulates autonomous player behavior. The main goal is to create a virtual environment where players compete to gather resources, interact with others, and achieve team objectives in a simulated, grid-based world.<br>
**Project Components**

    Server: Manages the game world, processes client requests, and enforces game rules.
    Client: Provides an interface for human players to connect to the server and control their characters.
    AI: An autonomous agent that follows specific strategies to play the game, completing objectives without direct human intervention.

**Features**

    Real-time Game World: Players and AIs interact in a shared, grid-based world.
    Resource Management: Players gather resources essential for survival and progress.
    Team Play: Multiple players on the same team can work together to achieve objectives.
    AI Integration: Autonomous agents can join the game and make strategic decisions to compete with human players.
    Multiplayer Support: Multiple clients can connect to the server and interact in real time.

**Requirements**

    C++17 or higher - Required for language features
    CMake - For configuring the project build
    Make - For compiling the code
    SFML - Optional, for graphical client development if desired
    Network Libraries - For handling client-server communication (e.g., boost::asio)
