class Game:
    def __init__(self, playerA, playerB, payoff, iterations):
        self.players = playerA, playerB
        self.payoff = payoff
        self.iterations = iterations
        self.playerA_payoff = None
        self.playerB_payoff = None

    def run(self):
        self.playerA_payoff = 0
        self.playerB_payoff = 0
        playerA, playerB = self.players
        print('  I  |  A  |  B\n-----+-----+-----')
        for iteration in range(1,self.iterations+1):
            playerA_move=playerA.move()
            playerB_move=playerB.move()

            print(' ' * (2-len(str(iteration))), iteration,' | ', playerA_move, ' | ', playerB_move)
            playerA.record_last_moves(playerA_move, playerB_move)
            playerB.record_last_moves(playerB_move, playerA_move)

            self.playerA_payoff = self.playerA_payoff + \
                self.payoff[playerA_move][playerB_move][0]
            self.playerB_payoff = self.playerB_payoff + \
                self.payoff[playerA_move][playerB_move][1]

    def get_players_payoffs(self):
        return([self.playerA_payoff, self.playerB_payoff])

