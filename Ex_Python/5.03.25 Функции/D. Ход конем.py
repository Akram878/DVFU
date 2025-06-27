def chess_to_coords(pos):

    col = ord(pos[0].upper()) - ord('A') + 1
    row = int(pos[1])
    return (col, row)

def coords_to_chess(x, y):

    return chr(ord('A') + x - 1) + str(y)

def is_inside_board(x, y):

    return 1 <= x <= 8 and 1 <= y <= 8

def list_of_turns(cell):
    x, y = chess_to_coords(cell)
    moves = [(-2, -1), (-2, 1), (-1, -2), (-1, 2),
             (1, -2), (1, 2), (2, -1), (2, 1)]
    results = []

    for dx, dy in moves:
        nx, ny = x + dx, y + dy
        if is_inside_board(nx, ny):
            results.append(coords_to_chess(nx, ny))

    return sorted(results)


print(list_of_turns('B1'))
