import copy

# postavlja i azurira gornje ogranicenje - beta
def Min(state, alpha = float("-inf"), beta = float("inf")):
    if state.end():
        return state.evaluate(), state
    
    best_move = None
    current_best_move_value = float("inf")
    for next_state in state.get_next_states():
        opponents_best_move_value, _ = Max(next_state, alpha, beta)
        if opponents_best_move_value < current_best_move_value:
            best_move = next_state
            current_best_move_value = opponents_best_move_value

        # nasli smo nesto sto je manje od donjeg ogranicenja i to nece biti prihvaceno -> izlazimo
        if current_best_move_value <= alpha:
            return current_best_move_value, best_move  

        if current_best_move_value < beta:
            beta = current_best_move_value

    return current_best_move_value, best_move

# postavlja i azurira donje ogranicenje - alpha
def Max(state, alpha = float("-inf"), beta = float("inf")):
    if state.end():
        return state.evaluate(), state
    
    best_move = None
    current_best_move_value = float("-inf")
    for next_state in state.get_next_states():
        opponents_best_move_value, _ = Min(next_state, alpha, beta)
        if opponents_best_move_value > current_best_move_value:
            best_move = next_state
            current_best_move_value = opponents_best_move_value

        # nasli smo nesto sto je vece od gornjeg ogranicenja i to nece biti prihvaceno -> izlazimo
        if current_best_move_value >= beta:
            return current_best_move_value, best_move 
        
        if current_best_move_value > alpha:
            alpha = current_best_move_value
               

    return current_best_move_value, best_move

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
        self.last_move = None
        
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
        self.last_move = move

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
    
    def evaluate(self):
        winner = self.get_winner()
        if winner == "X":
            return 1
        elif winner == "O":
            return -1
        return 0
    
    def get_next_states(self):
        for i in range(3):
            for j in range(3):
                if self.board[i][j] == XOState.empty:
                    next_state = copy.deepcopy(self)
                    next_state.play_move([i, j])
                    yield next_state

def get_next_move_from_stdin():
    move = input().split(", ")
    return [int(move[0]), int(move[1])]

if __name__ == "__main__":
    game = XOState()
    game.draw_board()

    while True:
        next_move = get_next_move_from_stdin() 
        game.play_move(next_move)
        game.draw_board()
        print()

        if game.get_winner() == "X":
            print("X won")
            break

        if game.end():
            print("Tie")
            break

        _, next_move = Min(game)
        game.play_move(next_move.last_move)
        game.draw_board()
        print()

        if game.get_winner() == "O":
            print("O won")
            break