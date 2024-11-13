from random import randint
from IA.player import Player


class Egg:

    def __init__(self, egg_id: int, x: int, y: int, team: str) -> None:
        self.id = egg_id
        self.pos_X = x
        self.pos_Y = y
        self.team = team
        self.available = False

    def is_available(self):
        return self.available

    def hatch(self, id_player: int) -> Player:
        direction = randint(1, 4)
        return Player(self.pos_X, self.pos_Y, direction, id_player)
