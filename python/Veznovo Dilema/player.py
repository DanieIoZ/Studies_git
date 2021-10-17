import random


'''Default player with just basic functionality to play a game. Makes just a random move and doesn't analyze anything.'''
class MyPlayer:
    def __init__(self, payoff, iterations = 0):
        self.payoff = payoff
        self.moves = []
        self.iterations = iterations

    def move(self):
        return random.choice([True, False])

    def record_last_moves(self, my_last_move, opponent_last_move):
        self.moves.append((my_last_move, opponent_last_move))



'''Clever player. Can analyze payoff matrix before the game starts and opponent's moves each turn'''
class MyCleverPlayer:
    def __init__(self, payoff, iterations = 0):
        self.payoff = payoff
        self.moves = []
        self.iterations = iterations

        #Player chooses an effective strategy before the game starts. According to examples of payoff matrixes one strategy is always more effective. So it's enough for now to win. 
        #Strategy will be updated in future
        self.effective_choice = self.analyze_payoff()

    def move(self):
        return self.effective_choice

    def analyze_payoff(self):
            return (self.payoff[0][0][0] + self.payoff[0][1][0]) > (self.payoff[1][0][0] + self.payoff[1][1][0])

    def record_last_moves(self, my_last_move, opponent_last_move):
        self.moves.append((my_last_move, opponent_last_move))


    '''
    It's a function for analyzing opponent's accordance to the effective strategy. It will be needed only if the choice between "COOPERATE" and "DEFECT" won't be that obvious.

    def analyze_moves(self):
        if (self.opponent_statistics == 0):
            return 0
        return 1/(len(self.moves)/self.opponent_statistics)
    '''