#!/usr/bin/python3

import socket
from time import sleep
from IA.commands import get_response


class Socket:

    def __init__(self, machine: str, port: int) -> None:
        self.machine = machine
        self.port = port
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.list_cmd_send = []

    def connect_socket(self) -> None:
        try:
            self.socket.connect((self.machine, self.port))
            self.socket.setblocking(False)
        except ConnectionRefusedError:
            print(f"Connection to {self.machine}:{self.port} failed")
            exit(84)

    def close_socket(self) -> None:
        self.socket.close()

    def send_message(self, message: str) -> None:
        try:
            print("[SENDING]", message)
            if message[-1:] != "\n":
                message += "\n"
            message = bytes(message, 'utf-8')
            self.socket.sendall(message)
        finally:
            pass

    def receive_message(self) -> str:
        try:
            data = self.socket.recv(1024)
            data = str(data.decode('utf-8'))
            print("[RECEIVE]", data, end='')
            if "dead" in data:
                exit(0)
            return data
        except BlockingIOError:
            return None
        except KeyboardInterrupt:
            self.close_socket()
            exit(84)

    def send_cmd(self, game, cmd, player):
        self.send_message(cmd)
        cmd_need_wait = ["Look", "Fork", "Incantation", "Left", "Right", "Forward", "is_waiting", "Wait"]
        if cmd in cmd_need_wait or "Take" in cmd or "Set" in cmd:
            player.wait = True
        if "Broadcast" in cmd:
            self.list_cmd_send.append("Broadcast")
        else:
            self.list_cmd_send.append(cmd)
        while (len(self.list_cmd_send) >= 9 or player.wait):
            sleep(0.3)
            # print("Waiting...")
            get_response(game, player, game.socket.list_cmd_send)
