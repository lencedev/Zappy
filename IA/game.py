#!/usr/bin/python3

from IA.server import Socket
from IA.case import Case


class Game:

    def __init__(self, x: int, y: int, socket: Socket) -> None:
        self.socket = socket
        self.X = x
        self.Y = y
        self.players = []

    def get_players_count_with_elevation(self, elevation: int) -> int:
        return sum(1 for player in self.players if player.elevation == elevation)
