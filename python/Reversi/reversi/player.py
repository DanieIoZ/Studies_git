import random

class MyPlayer:
    '''Plays by "Minimal Value strategy" '''

    #Cell values
    mat_cell_values = [
        [100,-50,50,15,15,50,-50,100], 
        [-50,-25,-15,-10,-10,-15,-25,-50], 
        [50,-15,4,4,4,4,-15,50], 
        [15,-10,4,0,0,4,-10,15], 
        [15,-10,4,0,0,4,-10,15],
        [50,-15,4,4,4,4,-15,50], 
        [-50,-25,-15,-10,-10,-15,-25,-50], 
        [100,-50,50,15,15,50,-50,100]] 

    def __init__(self, my_color,opponent_color):
        self.name = 'kryvadan' #username studenta
        self.my_color = my_color
        self.op_color = opponent_color
 
    def move(self,board):
        move = self.choose_move(self.get_moves(board, self.my_color, self.op_color))
        return move #pozice kam hráč umisťuje svůj kámen

    #Get all possible moves and count their value
    def get_moves(self, board, color, op_color):
        moves = []
        for i in range(len(board)):
            for j in range(len(board[0])):
                if (board[i][j] == -1):
                    move = self.check_move_possibility_and_value(i,j, board, color, op_color)
                    if (move != None):
                        moves.append(move) 
        return moves

    #Choose the best possible move
    def choose_move(self, moves):
        if (len(moves) == 0):
            return None

        else:
            #if minimal cell value ( from mat_cell_value ) is >= 10, i choose from moves, which give me the biggest number of enemy points i can take, otherwise i play by min. move value strategy,
            #so i choose a move, which will give me less points on the beginning, so the opponent has less possibilities at the beginning and loses more points in the end of the game
            min_cv = min([d[2] for d in moves])
            if (abs(min_cv) >= 15):
                possible_moves = self.get_biggest_moves(moves)
            else:
                possible_moves = self.get_smallest_moves(moves)

            #choosing a move from possible moves, which is less dangerous on the next enemy move
            #i decided to give priority to the cell value, so at first i select moves by smallest cell value my opponent may get

            # possile_moves element is built of: [0] (r,c)  | [1] move value | [2] cell value | [3] opponent biggest move value | [4] opponent biggest cell value
            min_opponent_cell_value = min([d[4] for d in moves])
            for i in range(len(possible_moves), 0):
                if (possible_moves[i][4] != min_opponent_cell_value):
                    possible_moves.remove(possible_moves[i])

            min_opponent_move_value = min(d[3] for d in possible_moves)
            for i in range(len(possible_moves), 0):
                if (possible_moves[i][3] != min_opponent_move_value):
                    possible_moves.remove(possible_moves[i])

            if (len(possible_moves) == 1):
                return possible_moves[0][0]
            else:
                return possible_moves[random.randint(0, len(possible_moves)-1)][0]

    #Check the possibility of move to (r,c) point and its cell value and how much enemy points it will take
    def check_move_possibility_and_value(self, r,c, board, color, op_color):
        ok_move = 0
        move_value = 0
        
        for i in range(-1,2):
            for j in range(-1,2):
                length = 1
                value_tmp = 0
                #while i didn't got to the border and didn't met empty cell increase the length and increase the possible move value by 1 
                while (self.in_range(r + (i*length),c + (j*length),board) and board[r + (i*length)][c + (j*length)] == op_color):
                    length += 1
                    value_tmp += 1

                #if met enemy color point, this move is possible and the final value of this move is increased by value_tmp
                if (self.in_range(r + (i*length),c + (j*length), board) and board[r + (i*length)][c + (j*length)] == color and board[r + i][c + j] == op_color):
                    ok_move = 1
                    move_value += value_tmp

        if (ok_move):
            #This part of the code checks the most dangerous enemy move, that may come if i place a point to the (r,c) point
            if (color == self.my_color):
                board[r][c] = color
                op_moves = self.get_biggest_moves(self.get_moves(board, op_color, color))
                board[r][c] = -1
                if (op_moves == None):
                    return [(r,c), move_value, self.mat_cell_values[r][c], -100, -100]

                max_op_val = max([d[1] for d in op_moves])
                return [(r,c), move_value, self.mat_cell_values[r][c], max_op_val, op_moves[0][2]]

            return [(r,c), move_value, self.mat_cell_values[r][c]]    

    #Get moves selected by maximum cell value and maximum move value (taken enemy points) 
    def get_biggest_moves(self, moves):
        best_moves = []
        if (len(moves) == 0):
            return None

        max_cv = max([d[2] for d in moves])
        for i in range(len(moves)):
            if (moves[i][2] == max_cv):
                best_moves.append(moves[i])

        max_mv = max([d[1] for d in best_moves])
        for i in range(len(best_moves), 0):
            if (best_moves[i][1] != max_mv):
                best_moves.remove(moves[i])
        return best_moves

    #Get moves selected by maximum cell value and minimum move value
    def get_smallest_moves(self, moves):
        best_moves = []
        if (len(moves) == 0):
            return None

        max_cv = max([d[2] for d in moves])
        for i in range(len(moves)):
            if (moves[i][2] == max_cv):
                best_moves.append(moves[i])

        min_mv = min([d[1] for d in best_moves])
        for i in range(len(best_moves), 0):
            if (best_moves[i][1] != min_mv):
                best_moves.remove(moves[i])
        return best_moves

    #If the point is not out of the board
    def in_range(self, r, c, board):
        return r >=0 and r < len(board) and c >= 0 and c < len(board[0])