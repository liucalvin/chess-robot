import chess
import chess.engine
import chess.svg
from chess import Move
import os
from dotenv import load_dotenv

load_dotenv()

STOCKFISH_LOCATION = os.getenv("STOCKFISH_LOCATION")

engine = chess.engine.SimpleEngine.popen_uci(STOCKFISH_LOCATION)

def play_chess(isPlayerWhite):
  isPlayerMove = isPlayerWhite
  move_number = 0

  board = chess.Board()
  while not board.is_game_over():
      print_readable_board(board.fen())
      move_number = move_number + 1
      if isPlayerMove:
        move_input = input("Enter your move:")
        if (move_input != ""):
          try:
            move = Move.from_uci(move_input)
            if move in board.legal_moves:  
              board.push(move)
              isPlayerMove = not isPlayerMove
            else:
              print("Move not legal.")
          except chess.InvalidMoveError:
            print("Move not valid.")
      else:
        result = engine.play(board, chess.engine.Limit(time=0.1))
        print(result)
        board.push(result.move)
        isPlayerMove = not isPlayerMove

      # chess.svg.board(
      #   board,
      #   fill=dict.fromkeys(board.attacks(chess.E4), "#cc0000cc"),\
      #   size=350,
      #  ).save('moves/chess_move_' + move_number + '.svg', 'SVG')

  engine.quit()


def print_readable_board(board_fen: str):
  board = board_fen.split(" ")[0]
  rows = board.split("/")
  print("    --------")
  for idx, row in enumerate(rows):
    readable_row = str(len(rows) - idx) + " | "
    for char in list(row):
      if char.isnumeric():
        readable_row += " " * int(char)
      else:
        readable_row += char
    print(readable_row)
  print("    --------")
  print("    abcdefgh")
  return

