import random

class MyPlayer:
    '''Default player with just basic functionality to play a game.'''
    def __init__(self, payoff, iterations = 0):
        self.payoff = payoff
        self.moves = []
        self.iterations = iterations

    def move(self):
        return random.choice([True, False])

    def record_last_moves(self, my_last_move, opponent_last_move):
        self.moves.append((my_last_move, opponent_last_move))