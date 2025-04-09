# TODO: AlphaBetaAgent
import copy, sys
from exceptions import AgentException
from math import inf
from minmaxagent import basic_static_eval
import random

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

        valid_moves = connect4.possible_drops()
        if not valid_moves:
            print("No valid moves available.")
            return None, self.heuristic_func(connect4, self.my_token)

        if maximizing:
            best_score = -inf
        else:
            best_score = inf

        for move in valid_moves:
            # print(f"Considering move: {move}")
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
                # print("Pruning remaining moves.")
                break

        if best_move is None:
            # print("No optimal move found, falling back to the random move.")
            best_move = random.choice(valid_moves)
            new_board = copy.deepcopy(connect4)
            new_board.drop_token(best_move)
            _, best_score = self.alphabeta(new_board, depth - 1, alpha, beta, not maximizing)

        # print(f"Best move: {best_move}, Best score: {best_score}")
        return best_move, best_score
