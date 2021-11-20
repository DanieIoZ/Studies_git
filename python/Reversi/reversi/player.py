import random

class MyPlayer:
    '''Hrac hraje nahodne'''
    def __init__(self, my_color,opponent_color):
        self.name = 'kryvadan' #username studenta
        self.my_color = my_color
        self.op_color = opponent_color
 
    def move(self,board):
        move = self.choose_move(self.get_moves(board))
        print(move)
        return move #pozice kam hráč umisťuje svůj kámen

    def get_moves(self, board):
        moves = []
        for i in range(len(board)):
            for j in range(len(board[0])):
                if (board[i][j] == -1):
                    move = self.check_move(i,j, board)
                    if (move != None):
                        moves.append(move) 
        return moves

    def check_move(self, r,c, board):
        ok_move = 0
        for i in range(-1,2):
            for j in range(-1,2):
                length = 1
                while (self.in_range(r + (i*length),c + (j*length),board) and board[r + (i*length)][c + (j*length)] == self.op_color):
                    length += 1
                if (self.in_range(r + (i*length),c + (j*length), board) and board[r + (i*length)][c + (j*length)] == self.my_color and board[r + i][c + j] == self.op_color):
                    ok_move = 1
        if (ok_move):
            return (r,c)
        #else:
        #    return None

    def choose_move(self, moves):
        if (len(moves) == 0):
            return None
        else:
            return moves[random.randint(0,len(moves)-1)]

    def in_range(self, r, c, board):
        return r >=0 and r < len(board) and c >= 0 and c < len(board[0])
