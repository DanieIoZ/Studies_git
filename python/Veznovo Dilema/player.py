class MyPlayer:
    '''Good boy. Can analyze last moves'''
    def __init__(self, payoff, iterations = 0):
        self.payoff = payoff
        self.moves = []
        self.iterations = iterations 

        #choosing between 0 and 1 for most better result in average
        self.effective_strat = self.get_safe_strat()
        #choosing what is better according to enemies prefered move
        self.best_strat = self.get_best_strat()
        self.opponent_preference = 0

        #border, when player stops using effective strat and analyze enemies moves
        self.analyze_border = 3
        #if opponent mostly chooses just 1,0,1,0,1,0... i'll just follow safe strategy
        self.opponent_preference_deviation = 0.1
        self.opponent_statistics = 0

    def move(self):
        return self.choose_strat()

    def choose_strat(self):
        if (len(self.moves) < self.analyze_border):
            return self.effective_strat
        else:
            return self.best_strat[self.opponent_preference]

    def get_safe_strat(self):
        return (self.payoff[0][0][0] + self.payoff[0][1][0]) < (self.payoff[1][0][0] + self.payoff[1][1][0])

    #[0] - best choice when opponent prefer "0", [1] - best choice when opponent prefer "1", [2] - choice, when opponent just do 1,0,1,0...
    def get_best_strat(self):
        return ((self.payoff[0][0][0] < self.payoff[1][0][0]),(self.payoff[0][1][0] < self.payoff[1][1][0]), self.effective_strat)

    def record_last_moves(self, my_last_move, opponent_last_move):
        self.moves.append((my_last_move, opponent_last_move))
        self.opponent_statistics += opponent_last_move
        self.opponent_preference = self.analyze_moves()

    #analyzing what move opponent preferes
    def analyze_moves(self):
        #number of "1" moves in percents 
        opponent_preference = self.opponent_statistics/len(self.moves)
        if (opponent_preference < 0.5 - self.opponent_preference_deviation):
            return 0
        else: 
            if (opponent_preference > 0.5 + self.opponent_preference_deviation):
                return 1
            else:
                return 2 #abs(self.moves[-1][1] - 1)