# TODO: AlphaBetaAgent
import copy, sys
from exceptions import AgentException
from math import inf
from minmaxagent import basic_static_eval


class AlphaBetaAgent:
    def __init__(self, my_token="o", heuristic_func=basic_static_eval):
        self.my_token = my_token
        self.heuristic_func = heuristic_func

    def decide(self, connect4):
        if connect4.who_moves != self.my_token:
            raise AgentException("not my round")

        best_move, _ = self.alphabeta(connect4)
        return best_move

    def alphabeta(self, connect4, depth=4, alpha=-inf, beta=inf, maximizing=True):
        if depth == 0 or connect4._check_game_over():
            return None, self.heuristic_func(connect4, self.my_token)

        best_move = None

        if maximizing:
            best_score = -inf
        else:
            best_score = inf

        for move in connect4.possible_drops():
                new_board = copy.deepcopy(connect4)
                new_board.drop_token(move)
                _, score = self.alphabeta(new_board, depth - 1, alpha, beta, not maximizing)

                if maximizing and score > best_score:
                    best_score = score
                    best_move = move
                elif not maximizing and score < best_score:
                    best_score = score
                    best_move = move
                
                if maximizing:
                    alpha = max(alpha, score)
                else:
                    beta = min(beta, score)

                if beta <= alpha:
                    break

        return best_move, best_score
