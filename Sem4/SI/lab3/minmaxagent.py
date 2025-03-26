import copy, sys
from exceptions import AgentException
from math import inf


def basic_static_eval(connect4, player="o"):
    # TODO
    opponent = "x" if player == "o" else "o"

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
    N3player = 0
    N3opponent = 0
    
    fours = connect4.iter_fours()
    
    for four in fours:
        player_count = four.count(player)
        opponent_count = four.count(opponent)
        empty_count = 4 - (player_count + opponent_count)

        if player_count == 3 and empty_count == 1:
            N3player += 1
        elif opponent_count == 3 and empty_count == 1:
            N3opponent += 1


    return (N3player - N3opponent)  # return score for player


def advanced_static_eval(connect4, player="o", bigScore=10, smallScore=1):
    # TODO
    opponent = "x" if player == "o" else "o"

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
    scorePlayer = 0
    scoreOpponent = 0
    
    fours = connect4.iter_fours()
    
    for four in fours:
        player_count = four.count(player)
        opponent_count = four.count(opponent)
        empty_count = 4 - (player_count + opponent_count)

        if player_count == 3 and empty_count == 1:
            scorePlayer += bigScore
        elif player_count == 2 and empty_count == 2:
            scorePlayer += smallScore

        if opponent_count == 3 and empty_count == 1:
            scoreOpponent += bigScore
        elif opponent_count == 2 and empty_count == 2:
            scoreOpponent += smallScore


    return (scorePlayer - scoreOpponent)  # return score for player


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
        if depth == 0 or connect4._check_game_over():
            return None, self.heuristic_func(connect4, self.my_token)
        
        best_move = None
        best_score = 0

        # Używamy basic static eval
        score = self.heuristic_func(connect4, self.my_token)

        if maximizing:
            best_score = -inf
        else:
            best_score = inf

        for move in connect4.possible_drops():
            new_board = copy.deepcopy(connect4)
            new_board.drop_token(move)

            _, score = self.minmax(new_board, depth - 1, not maximizing)
            
            if maximizing:
                if score > best_score:
                    best_score = score
                    best_move = move
            else:
                if score < best_score:
                    best_score = score
                    best_move = move

        return best_move, best_score