class Inventory:

    def __init__(self) -> None:
        self.objects = {"food": 0, "linemate": 0, "deraumere": 0, "sibur": 0,
                        "mendiane": 0, "phiras": 0, "thystame": 0, "player": 0}

    def set_objects(self, key, quantity: int) -> None:
        self.objects[key] = quantity

    def add_objects(self, key, quantity: int) -> None:
        self.objects[key] += quantity

    def remove_objects(self, key, quantity: int) -> None:
        self.objects[key] -= quantity
