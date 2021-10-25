# This script creates two (identical) players, 
# lets them play for some number of iterations and 
# then displays their scores. 
#
# For running this script, you need to put the 'game.py'
# as well as your 'player.py' to the python path, e.g. 
# to the the working directory. 
#
# A very simple testing script, feel free to modify it
# according to your needs
#
# example code for students of B4B33RPH course
# Author: Tomas Svoboda, and the RPH team

import Game 
import player
 



if __name__ == "__main__":
    payoff = (((4,4),(1,6)),((6,1),(2,2)))
    playerA = player.MyPlayer2(payoff)
    playerB = player.MyPlayer(payoff)
    number_of_iterations = 20

    my_game = Game.Game(playerA, playerB, payoff, number_of_iterations)
    my_game.run()
    
    scores = my_game.get_players_payoffs()

    print('playerA got:',scores[0], '\nplayerB got:', scores[1])