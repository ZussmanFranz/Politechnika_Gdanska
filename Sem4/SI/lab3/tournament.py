import copy
from exceptions import GameplayException
from connect4 import Connect4
from randomagent import RandomAgent
from minmaxagent import MinMaxAgent

def play(connect4, agent1, agent2, draw_in_process=True):
    while not connect4.game_over:
        if draw_in_process:
            connect4.draw()
        try:
            if connect4.who_moves == agent1.my_token:
                n_column = agent1.decide(copy.deepcopy(connect4))
            else:
                n_column = agent2.decide(copy.deepcopy(connect4))
            connect4.drop_token(n_column)
        except (ValueError, GameplayException):
            print('invalid move')

    connect4.draw()

def get_opposite_token(token):
    if token == 'x':
        return 'o'
    elif token == 'o':
        return 'x'
    else:
        raise Exception("There is no such token")

def tournament(connect4, agent1, agent2, n_games, n_changes):
    print(f"\t{type(agent1)}[{agent1.my_token}] VS {type(agent2)}[{agent2.my_token}]")

    for swap in range(0, n_changes):
        if swap != 0:
            # Token swap
            print("\n\tToken swap\n")
            tmp_token = agent1.my_token
            agent1.my_token = agent2.my_token
            agent2.my_token = tmp_token

        for game in range(1, n_games + 1):
            print("\n\tGame", game, ": ")
            play(connect4, agent1, agent2, draw_in_process=False)
            connect4 = Connect4(width=connect4.width, height=connect4.height)

        
        