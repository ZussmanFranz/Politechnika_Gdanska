from exceptions import GameplayException
from connect4 import Connect4
from randomagent import RandomAgent
from minmaxagent import MinMaxAgent, advanced_static_eval
from alphabetaagent import AlphaBetaAgent
from tournament import tournament

connect4 = Connect4(width=7, height=6)
# agent1 = AlphaBetaAgent('x')
agent1 = MinMaxAgent('x', heuristic_func=advanced_static_eval)
agent2 = RandomAgent('o')

print("\t\tMinMax tournament:\n")
# tournament(connect4, agent1, agent2, 5, 2)

agent1 = AlphaBetaAgent('x')
agent2 = RandomAgent('o')

print("\t\tAlphaBeta tournament:\n")
tournament(connect4, agent1, agent2, 5, 2)

agent1 = MinMaxAgent('x')
# agent1 = AlphaBetaAgent('x', heuristic_func=advanced_static_eval)
agent2 = AlphaBetaAgent('o')
# agent2 = RandomAgent('o')

print("\t\tAlphaBeta advanced vs basic")
tournament(connect4, agent1, agent2, 5, 2)
