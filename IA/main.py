#!/usr/bin/python3

import sys
from IA.player import Player
from IA.game import Game
from IA.server import Socket
from typing import Tuple
from IA.commands import get_response


list_cmd_send = []

def usage():
    print("USAGE: ./zappy_ai -p port -n name -h machine")
    print("\tport\tis the port number")
    print("\tname\tis the name of the team")
    print("\tmachine\tis the name of the machine; localhost by default")


def parse_args(av: list) -> Tuple[int, str, str]:
    port = None
    name = None
    machine = "localhost"
    values = ["-p", "-n", "-h"]

    for i in range(1, len(av)):
        if av[i] == "-p":
            if i + 1 < len(av) and av[i+1] not in values:
                port = int(av[i + 1])
            else:
                print("Error: missing value for -p argument", file=sys.stderr)
                exit(84)
        elif av[i] == "-n":
            if i + 1 < len(av) and av[i+1] not in values:
                name = av[i + 1]
            else:
                print("Error: missing value for -n argument", file=sys.stderr)
                exit(84)
        elif av[i] == "-h":
            if i + 1 < len(av) and av[i+1] not in values:
                machine = av[i + 1]
            else:
                print("Error: missing value for -h argument", file=sys.stderr)
                exit(84)

    if port == None or name == None:
        usage()
        print("Error: missing arguments", file=sys.stderr)
        exit(84)

    return port, name, machine


def server_connection(socket: Socket, team_name: str) -> Tuple[int, int, int]:
    socket.connect_socket()
    data = None
    while data == None:
        data = socket.receive_message()
    if data == "WELCOME\n":
        socket.send_message(team_name)
        response = None
        while not response:
            response = socket.receive_message()
        if response != "ko\n":
            parse = response.split("\n")
            slots = parse[0]
            size = parse[1].split(" ")
            x = size[0]
            y = size[1]
            return int(slots), int(x), int(y)
        else:
            print("Error: bad team name", file=sys.stderr)
            exit(84)

def loop(player: Player, game: Game) -> None:
    while True:
        if player.is_freezed:
            pass
        if not get_response(game, player, game.socket.list_cmd_send):
            break # player mort
        # IA ici
        player.try_to_level_up()


def init_player(x: int, y: int, o: int, id: int, team_name: str, game: Game) -> Player:
    player = Player(x, y, o, id, game)
    player.set_team(team_name)
    player.init_map(game)
    return player


def init_game(socket: Socket, x: int, y: int) -> Game:
    game = Game(x, y, socket)
    return game


def main():
    ac = len(sys.argv)

    if ac < 2 or sys.argv[1] == "-help":
        usage()
        exit(0)

    port, name, machine = parse_args(sys.argv)
    socket = Socket(machine, port)
    slots, x, y = server_connection(socket, name)
    game = init_game(socket, x, y)
    player = init_player(0, 0, 1, 0, name, game)
    try:
        loop(player, game)
    except KeyboardInterrupt:
        # print("KeyboardInterrupt")
        pass
    socket.close_socket()


if __name__ == "__main__":
    main()
    exit(0)
