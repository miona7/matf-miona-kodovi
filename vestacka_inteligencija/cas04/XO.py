class XOState:
    empty = " "

    def __init__(self):
        self.board = [
            [XOState.empty, XOState.empty, XOState.empty],
            [XOState.empty, XOState.empty, XOState.empty],
            [XOState.empty, XOState.empty, XOState.empty],
        ]
        self.curr_player = "X"
        self.move_count = 0
        
    def draw_board(self):
        for i in range(3):
            print(" | ".join(self.board[i]))

    def play_move(self, move):
        i, j = move[0], move[1]

        if self.curr_player == "X":
            self.board[i][j] = "X"
        else:
            self.board[i][j] = "O"

        self.curr_player = "X" if self.curr_player == "O" else "O"
        self.move_count += 1

    def get_winner(self):
        board = self.board
        
        # vrste
        for i in range(3):
            if board[i][0] != XOState.empty and board[i][0] == board[i][1] == board[i][2]:
                return board[i][0]

        # kolone
        for j in range(3):
            if board[0][j] != XOState.empty and board[0][j] == board[1][j] == board[2][j]:
                return board[0][j]

        # glavna dijagonala
        if board[0][0] != XOState.empty and board[0][0] == board[1][1] == board[2][2]:
            return board[0][0]
        
        # sporedna dijagonala
        if board[2][0] != XOState.empty and board[2][0] == board[1][1] == board[0][2]:
            return board[2][0]

    def end(self):
        winner = self.get_winner()
        return winner is not None or self.move_count == 9


def get_next_move_from_stdin():
    move = input().split(", ")
    return [int(move[0]), int(move[1])]

if __name__ == "__main__":
    game = XOState()
    game.draw_board()

    while True:
        next_move = get_next_move_from_stdin() # [1, 2] 
        game.play_move(next_move)
        game.draw_board()

        if game.get_winner() == "X":
            print("X won")
            break

        if game.end():
            print("Tie")
            break

        next_move = get_next_move_from_stdin()
        game.play_move(next_move)
        game.draw_board()

        if game.get_winner() == "O":
            print("O won")
            break