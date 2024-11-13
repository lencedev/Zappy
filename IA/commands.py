from time import sleep

def look(player, response):
    # print("[DEBUG] look response: ", response)
    player.look_response = response
    player.look(response)

def forward(player, response):
    if response == "ok\n":
        player.move_forward()

def left(player, response):
    if response == "ok\n":
        player.turn_left()

def right( player, response):
    if response == "ok\n":
        player.turn_right()

def incantation(player, response):
    if "ko" in response:
        return
    elif "Current" in response:
        player.incantation()
    else:
        player.wait = True

def waiting(player, response):
    if "ok" in response:
        player.is_freezed = True
    elif "ko" in response:
        player.already_waiting = True

def is_waiting(player, response):
    if "ok" in response:
        player.already_waiting = True
    elif "ko" in response:
        player.already_waiting = False

def broadcast(player, response):
    if response == "ok\n":
        return # broadcast envoyé, pas de problème

    # print("[DEBUG] Broadcast response:", response)
    response.split(', ')
    text = response[1]

    # ici ajouter les broadcast pouvant etre envoyé (genre level, ...)
    match text:
        case "Freeze":
            player.is_freezed = True
        case _:
            pass

def fork(player, response):
    if response == "ok\n":
        return

def take(player, response, obj):
    # print("[DEBUG] take obj: ", obj)
    if response == "ok\n":
        player.take(obj)

def set_obj(player, response, obj):
    if response == "ok\n":
        player.set(obj)

def connect_nbr(player, response):
    try:
        value = int(response)
        player.team.unused_slot = value
    except ValueError:
        print("Connect_nbr response not correct (waiting int got {})".format(response))
        exit(84)

def get_response(game, player, list_cmd):
    response = game.socket.receive_message()
    if response:
        if "message" in response:
            broadcast(player, response)

        if len(list_cmd) >= 1:
            player.wait = False

            from_cmd = list_cmd[0]
            # print("cmd:", from_cmd, "response:", response)

            if "Take" in from_cmd:
                take(player, response, from_cmd.split(' ')[1])
                list_cmd.pop(0)
                return 1
            if "Set" in from_cmd:
                set_obj(player, response, from_cmd.split(' ')[1])
                list_cmd.pop(0)
                return 1

            match from_cmd:
                case "Look":
                    look(player, response)
                    list_cmd.pop(0)
                case "Forward":
                    forward(player, response)
                    list_cmd.pop(0)
                case "Left":
                    left(player, response)
                    list_cmd.pop(0)
                case "Right":
                    right(player, response)
                    list_cmd.pop(0)
                case "Incantation":
                    incantation(player, response)
                    if "Current" in response:
                        list_cmd.pop(0)
                case "Broadcast":
                    broadcast(player, response)
                    list_cmd.pop(0)
                case "Fork":
                    fork(player, response)
                    list_cmd.pop(0)
                case "Connect_nbr":
                    connect_nbr(player, response)
                    list_cmd.pop(0)
                case "Waiting":
                    waiting(player, response)
                    list_cmd.pop(0)
                case "is_waiting":
                    is_waiting(player, response)
                    list_cmd.pop(0)
                case _:
                    pass
    return 1
