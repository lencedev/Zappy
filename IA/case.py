from IA.player import Inventory
from IA.team import Team

class Case(Inventory, Team):

    def __init__(self) -> None:
        Inventory.__init__(self)
        self.players = []
        self.eggs = []

    def __str__(self):
        if len(self.players) > 0:
            print("P", end=' ')
        for key, value in self.objects.items():
            if value > 0:
                print(key, end=' ')
        return ""

    def add_egg(self, egg):
        self.eggs.append(egg)

    def remove_egg(self, egg):
        self.eggs.pop(self.eggs.index(egg))

    def add_player(self, player):
        self.players.append(player)

    def remove_player(self, player):
        self.players.pop(self.players.index(player))
