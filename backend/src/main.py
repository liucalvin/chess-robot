from gameplay import play_chess

invalid_input = True
while (invalid_input):
  invalid_input = False
  color_input = input("Is user playing white or black pieces? (Enter W/B)")

  if (color_input == "W"):
    play_chess(isPlayerWhite=True)
  elif (color_input == "B"):
    play_chess(isPlayerWhite=False)
  else:
    invalid_input = True


