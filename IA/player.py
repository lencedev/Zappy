#!/usr/bin/python3

from time import sleep
import os
import sys
import subprocess
from IA.inventory import Inventory
from IA.team import Team
from IA.case import Case
from IA.game import Game
from IA.commands import get_response


class Player:

    def __init__(self, x: int, y: int, orientation: int, id_player: int, game: Game) -> None:
        self.id_player = id_player
        self.inventory = Inventory()
        self.pos_X = x
        self.pos_Y = y
        self.orientation = orientation  # 1(N), 2(E), 3(S), 4(W)
        self.elevation = 1
        self.team = None
        self.life_units = 10
        self.alive = True
        self.map = []
        self.wait = False
        self.look_response = ""
        self.game = game
        self.look_around = 0 # nombre de left fait
        self.is_freezed = False
        self.already_waiting = False


    def init_map(self, game):
        self.map = []
        for i in range(0, game.X):
            self.map.append([])
            for j in range(0, game.Y):
                self.map[i].append(Case())

    def objects_needed_to_level_up(self):
        level_up_requirements = {
            1: {'linemate': 1, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0, 'thystame': 0},
            2: {'linemate': 1, 'deraumere': 1, 'sibur': 1, 'mendiane': 0, 'phiras': 0, 'thystame': 0},
            3: {'linemate': 2, 'deraumere': 0, 'sibur': 1, 'mendiane': 0, 'phiras': 2, 'thystame': 0},
            4: {'linemate': 1, 'deraumere': 1, 'sibur': 2, 'mendiane': 0, 'phiras': 1, 'thystame': 0},
            5: {'linemate': 1, 'deraumere': 2, 'sibur': 1, 'mendiane': 3, 'phiras': 0, 'thystame': 0},
            6: {'linemate': 1, 'deraumere': 2, 'sibur': 3, 'mendiane': 0, 'phiras': 1, 'thystame': 0},
            7: {'linemate': 2, 'deraumere': 2, 'sibur': 2, 'mendiane': 2, 'phiras': 2, 'thystame': 1}
        }
        if self.elevation in level_up_requirements:
            return level_up_requirements[self.elevation]
        else:
            return None

    def nb_player_needed(self) -> int:
        current_elevation = self.elevation
        required_players = {
            1: 1,
            2: 2,
            3: 2,
            4: 4,
            5: 4,
            6: 6,
            7: 6
        }
        if current_elevation not in required_players:
            return 0
        return required_players[current_elevation]

    def nb_player_at_level(self, game) -> int:
        required_players = {
            1: 1,
            2: 2,
            3: 2,
            4: 4,
            5: 4,
            6: 6,
            7: 6
        }
        if self.elevation not in required_players:
            return 0

        matching_players_count = game.get_players_count_with_elevation(self.elevation)
        return matching_players_count

    def drop_items(self):
        objects_needed = self.objects_needed_to_level_up()
        for key, value in objects_needed.items():
            if (self.inventory.objects[key] >= value):
                for i in range(value):
                    self.game.socket.send_cmd(self.game, f"Set {key}", self)

    def try_to_level_up(self):
        self.game.socket.send_cmd(self.game, "is_waiting", self)
        if (self.already_waiting):
            self.is_freezed = False
            print("[DEBUG] Look for player")
            self.game.socket.send_cmd(self.game, "Look", self)
            self.look_for_player()
            return
        items_missing = {}
        items_missing_in_inv = {}
        objects_needed = self.objects_needed_to_level_up()
        for key, value in objects_needed.items():
            if (self.inventory.objects[key] + self.map[self.pos_X][self.pos_Y].objects[key] < value):
                items_missing[key] = value - self.inventory.objects[key] - self.map[self.pos_X][self.pos_Y].objects[key]
            if (self.inventory.objects[key] < value):
                items_missing_in_inv[key] = value - self.inventory.objects[key]
        print("[DEBUG] try to level up : items missing:", items_missing)
        if items_missing == {}:
            nb_player_needed = self.nb_player_needed()
            if (nb_player_needed > 1):
                self.game.socket.send_cmd(self.game, "Look", self)
            #! Verif que assez de joueurs sont présent pour l'incantation
            if (nb_player_needed <= 1 or self.map[self.pos_X][self.pos_Y].objects["player"] >= nb_player_needed):
                self.eat_food()
                self.drop_items()
                self.game.socket.send_cmd(self.game, "Incantation", self)
                self.eat_food()
                self.game.socket.send_cmd(self.game, "Fork", self)
            else:
                print("[DEBUG] WAITING")
                self.game.socket.send_cmd(self.game, "Waiting", self)
        else:
            if (self.is_freezed):
                print("[DEBUG] Player freezed")
                self.eat_food()
                return
            self.game.socket.send_cmd(self.game, "Look", self)
            for item in items_missing_in_inv:
                for i in range(items_missing_in_inv[item]):
                    if self.map[self.pos_X][self.pos_Y].objects[item] > 0:
                        self.game.socket.send_cmd(self.game, f"Take {item}", self)
            self.look_for_items(items_missing)

    def eat_food(self):
        self.game.socket.send_cmd(self.game, "Look", self)
        if self.map[self.pos_X][self.pos_Y].objects["food"] > 0:
            for i in range(3):
                if self.map[self.pos_X][self.pos_Y].objects["food"] > 0:
                    self.game.socket.send_cmd(self.game, "Take food", self)
        else:
            self.look_for_items({'food': 1})

    def go_to_coords(self, coords):
        target_x, target_y = coords
        # print("ACTUAL", self.pos_X, self.pos_Y)
        # print("TO GO", target_x, target_y)

        if target_x < self.pos_X:
            if self.pos_X - target_x < self.game.X - self.pos_X + target_x: # traverser la map ou pas
                if self.orientation == 2:
                    self.game.socket.send_cmd(self.game, "Left", self)
                elif self.orientation == 3:
                    self.game.socket.send_cmd(self.game, "Left", self)
                    self.game.socket.send_cmd(self.game, "Left", self)
                elif self.orientation == 4:
                    self.game.socket.send_cmd(self.game, "Right", self)
            else:
                if self.orientation == 4:
                    self.game.socket.send_cmd(self.game, "Left", self)
                elif self.orientation == 1:
                    self.game.socket.send_cmd(self.game, "Left", self)
                    self.game.socket.send_cmd(self.game, "Left", self)
                elif self.orientation == 2:
                    self.game.socket.send_cmd(self.game, "Right", self)
            self.game.socket.send_cmd(self.game, "Forward", self)
            return

        if target_x > self.pos_X:
            if target_x - self.pos_X < self.game.X - target_x + self.pos_X: # traverser la map ou pas
                if self.orientation == 2:
                    self.game.socket.send_cmd(self.game, "Right", self)
                elif self.orientation == 4:
                    self.game.socket.send_cmd(self.game, "Left", self)
                elif self.orientation == 1:
                    self.game.socket.send_cmd(self.game, "Left", self)
                    self.game.socket.send_cmd(self.game, "Left", self)
            else:
                if self.orientation == 4:
                    self.game.socket.send_cmd(self.game, "Right", self)
                elif self.orientation == 2:
                    self.game.socket.send_cmd(self.game, "Left", self)
                elif self.orientation == 3:
                    self.game.socket.send_cmd(self.game, "Left", self)
                    self.game.socket.send_cmd(self.game, "Left", self)
            self.game.socket.send_cmd(self.game, "Forward", self)
            return

        if target_y < self.pos_Y:
            if self.pos_Y - target_y < self.game.Y - self.pos_Y + target_y:
                if self.orientation == 1:
                    self.game.socket.send_cmd(self.game, "Left", self)
                elif self.orientation == 2:
                    self.game.socket.send_cmd(self.game, "Left", self)
                    self.game.socket.send_cmd(self.game, "Left", self)
                elif self.orientation == 3:
                    self.game.socket.send_cmd(self.game, "Right", self)
                self.game.socket.send_cmd(self.game, "Forward", self)
            else:
                if self.orientation == 3:
                    self.game.socket.send_cmd(self.game, "Left", self)
                elif self.orientation == 4:
                    self.game.socket.send_cmd(self.game, "Left", self)
                    self.game.socket.send_cmd(self.game, "Left", self)
                elif self.orientation == 1:
                    self.game.socket.send_cmd(self.game, "Right", self)
                self.game.socket.send_cmd(self.game, "Forward", self)
            return

        if target_y > self.pos_Y:
            if target_y - self.pos_Y < self.game.Y - target_y + self.pos_Y:
                if self.orientation == 3:
                    self.game.socket.send_cmd(self.game, "Left", self)
                elif self.orientation == 1:
                    self.game.socket.send_cmd(self.game, "Right", self)
                elif self.orientation == 4:
                    self.game.socket.send_cmd(self.game, "Left", self)
                    self.game.socket.send_cmd(self.game, "Left", self)
                self.game.socket.send_cmd(self.game, "Forward", self)
            else:
                if self.orientation == 1:
                    self.game.socket.send_cmd(self.game, "Left", self)
                elif self.orientation == 3:
                    self.game.socket.send_cmd(self.game, "Right", self)
                elif self.orientation == 2:
                    self.game.socket.send_cmd(self.game, "Left", self)
                    self.game.socket.send_cmd(self.game, "Left", self)
                self.game.socket.send_cmd(self.game, "Forward", self)
            return

    def look_around_func(self):
        if (self.look_around == 3):
            self.look_around = 0
            for _i in range(5):
                self.game.socket.send_cmd(self.game, "Forward", self)
        else:
            self.game.socket.send_cmd(self.game, "Left", self)
            self.look_around += 1

    def look_for_player(self):
        prob_coord = []
        item_needed = self.objects_needed_to_level_up()
        for item in item_needed:
            for x in range(len(self.map)):
                for y in range(len(self.map[x])):
                    if self.map[x][y].objects[item] > 0 and item_needed[item] > 0:
                        item_needed[item] -= 1
                        prob_coord.append((x, y))
        # verifie si tous les objets sont à disposition
        for item in item_needed:
            if item_needed[item] > 0:
                self.look_around_func()
                return
        # verifie si tous les objets sont sur la meme cases
        item_needed = self.objects_needed_to_level_up()
        found = False
        final_coord = None
        for coord in prob_coord:
            for item in item_needed:
                if self.map[coord[0]][coord[1]].objects[item] < item_needed[item]:
                    break
                found = True
                final_coord = coord
            if found:
                break
        if not found:
            self.look_around_func()
        # verifie si un joueur est sur la case
        if final_coord is not None:
            if self.map[final_coord[0]][final_coord[1]].objects["player"] > 0:
                self.go_to_coords(final_coord)
                return

    def look_for_items(self, items_missing):
        # print("[DEBUG] items missing: ", items_missing)
        coord_to_go = []
        for item in items_missing:
            for x in range(len(self.map)):
                for y in range(len(self.map[x])):
                    if self.map[x][y].objects[item] > 0 and items_missing[item] > 0:
                        coord_to_go.append((x, y))
                        items_missing[item] -= 1
        if (coord_to_go == []):
            self.look_around_func()
            return
        for coord in coord_to_go:
            while not (self.pos_X == coord[0] and self.pos_Y == coord[1]):
                self.go_to_coords(coord)
                for i in range(3):
                    if self.map[self.pos_X][self.pos_Y].objects["food"] > 0:
                        self.game.socket.send_cmd(self.game, "Take food", self)
            for item in items_missing:
                if self.map[self.pos_X][self.pos_Y].objects[item] > 0:
                    self.game.socket.send_cmd(self.game, f"Take {item}", self)
        return coord_to_go

    def incantation(self):
        self.elevation += 1
        self.is_freezed = False

    def is_alive(self):
        return self.alive

    def set_team(self, team_name: str):
        self.team = Team(team_name)

    def move_forward(self):
        if self.orientation == 1:  # Nord
            if self.pos_X > 1:
                self.pos_X -= 1
            else:
                self.pos_X = self.game.X - 1
        elif self.orientation == 2:  # Est
            if self.pos_Y < self.game.Y - 1:
                self.pos_Y += 1
            else:
                self.pos_Y = 0
        elif self.orientation == 3:  # Sud
            if self.pos_X < self.game.X - 1:
                self.pos_X += 1
            else:
                self.pos_X = 0
        elif self.orientation == 4:  # Ouest
            if self.pos_Y > 0:
                self.pos_Y -= 1
            else:
                self.pos_Y = self.game.Y - 1

    def turn_right(self):
        if self.orientation == 4:
            self.orientation = 1
        else:
            self.orientation += 1

    def turn_left(self):
        if self.orientation == 1:
            self.orientation = 4
        else:
            self.orientation -= 1

    def parse_elem(self, elem, case):
        elements = elem.split(" ")
        for i in elements:
            if i in case.objects.keys():
                case.set_objects(i, 1)
        return case

    def look(self, resp):
        x = self.pos_X
        y = self.pos_Y
        i = 0
        ind_elem = 0
        self.init_map(self.game)
        resp = resp[1:-2]
        response = resp.split(',')

        if self.orientation == 1:  # Nord
            mid = y
            while ind_elem < len(response):
                a = i * 2 + 1
                if a > 1:
                    y = mid
                    y -= int(a/2)
                    if y < 0:
                        y = self.game.Y + y
                    for n in range(0, a):
                        if (ind_elem >= len(response)):
                            break
                        self.map[x][y] = self.parse_elem(
                            response[ind_elem], self.map[x][y])
                        if y < self.game.Y - 1:
                            y += 1
                        else:
                            y = 0
                        ind_elem += 1
                else:
                    self.map[x][y] = self.parse_elem(
                        response[ind_elem], self.map[x][y])
                    ind_elem += 1
                if x > 1:
                    x -= 1
                else:
                    x = self.game.X - 1
                i += 1

        if self.orientation == 2:  # Est
            mid = x
            while ind_elem < len(response):
                a = i * 2 + 1
                if a > 1:
                    x = mid
                    x -= int(a/2)
                    if x > self.game.X - 1:
                        x = x - self.game.X
                    for n in range(0, a):
                        if (ind_elem >= len(response)):
                            break
                        self.map[x][y] = self.parse_elem(
                            response[ind_elem], self.map[x][y])
                        if x < self.game.X - 1:
                            x += 1
                        else:
                            x = 0
                        ind_elem += 1
                else:
                    self.map[x][y] = self.parse_elem(
                        response[ind_elem], self.map[x][y])
                    ind_elem += 1
                if y < self.game.Y - 1:
                    y += 1
                else:
                    y = 0
                i += 1

        if self.orientation == 3:  # Sud
            mid = y
            while ind_elem < len(response):
                a = i * 2 + 1
                if a > 1:
                    y = mid
                    y += int(a/2)
                    if y > self.game.Y - 1:
                        y = y - self.game.Y
                    for n in range(0, a):
                        if (ind_elem >= len(response)):
                            break
                        self.map[x][y] = self.parse_elem(
                            response[ind_elem], self.map[x][y])
                        if y > 0:
                            y -= 1
                        else:
                            y = self.game.Y - 1
                        ind_elem += 1
                else:
                    self.map[x][y] = self.parse_elem(
                        response[ind_elem], self.map[x][y])
                    ind_elem += 1
                if x < self.game.X - 1:
                    x += 1
                else:
                    x = 0
                i += 1

        if self.orientation == 4:  # Ouest
            mid = x
            while ind_elem < len(response):
                a = i * 2 + 1
                if a > 1:
                    x = mid
                    x += int(a/2)
                    if x > self.game.X - 1:
                        x = x - self.game.X
                    for n in range(0, a):
                        if (ind_elem >= len(response)):
                            break
                        self.map[x][y] = self.parse_elem(
                            response[ind_elem], self.map[x][y])
                        if x > 0:
                            x -= 1
                        else:
                            x = self.game.X - 1
                        ind_elem += 1
                else:
                    self.map[x][y] = self.parse_elem(
                        response[ind_elem], self.map[x][y])
                    ind_elem += 1
                if y > 0:
                    y -= 1
                else:
                    y = self.game.Y - 1
                i += 1
        return resp


    def take(self, object):
        self.inventory.add_objects(object, 1)
        self.map[self.pos_X][self.pos_Y].add_objects(object, -1)

    def set(self, object):
        self.inventory.remove_objects(object, 1)

