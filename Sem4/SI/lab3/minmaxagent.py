import copy, sys
from exceptions import AgentException
from math import inf


def basic_static_eval(connect4, player="o"):
    # TODO

    # If wygrana przegrana remis: +infinity -infinity 0
    over = connect4._check_game_over()
    if over:
        if connect4.wins == None:
            return 0    # remis
        elif connect4.wins == player:
            return inf  # wygrana
        else:
            return -inf # przegrana

    # Else: Nczwórek (mój token) z trzema moimi znakami - Nczwórek (oponent) z trzema znakami (funkcja iter_fours)

    return 0  # return score for player


def advanced_static_eval(connect4, player="o"):
    # TODO
    return 0  # return score for player


class MinMaxAgent:
    def __init__(self, my_token="o", heuristic_func=basic_static_eval):
        self.my_token = my_token
        self.heuristic_func = heuristic_func

    def decide(self, connect4):
        if connect4.who_moves != self.my_token:
            raise AgentException("not my round")

        best_move, best_score = self.minmax(connect4)
        return best_move

    def minmax(self, connect4, depth=4, maximizing=True):
        # TODO

        # Używamy basic static eval

        best_move = None
        best_score = 0
        return best_move, best_score