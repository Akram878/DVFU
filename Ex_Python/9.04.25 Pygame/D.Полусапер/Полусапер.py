import pygame
import random
import sys


pygame.init()


WHITE = (255, 255, 255)
GRAY = (200, 200, 200)
DARK_GRAY = (120, 120, 120)
RED = (255, 0, 0)
BLACK = (0, 0, 0)


CELL_SIZE = 40
ROWS = 8
COLS = 8
MINES_COUNT = 10
WIDTH = COLS * CELL_SIZE
HEIGHT = ROWS * CELL_SIZE


screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Полусапёр")

font = pygame.font.SysFont(None, 30)

class Cell:
    def __init__(self, row, col):
        self.row = row
        self.col = col
        self.is_mine = False
        self.is_revealed = False
        self.adjacent_mines = 0

    def draw(self):
        x = self.col * CELL_SIZE
        y = self.row * CELL_SIZE
        rect = pygame.Rect(x, y, CELL_SIZE, CELL_SIZE)


        if self.is_mine:
            pygame.draw.rect(screen, RED, rect)
        elif self.is_revealed:
            pygame.draw.rect(screen, GRAY, rect)
        else:
            pygame.draw.rect(screen, DARK_GRAY, rect)

        pygame.draw.rect(screen, BLACK, rect, 1)

        # إظهار الرقم إذا كانت الخلية مكشوفة وغير لغم
        if self.is_revealed and not self.is_mine and self.adjacent_mines > 0:
            text = font.render(str(self.adjacent_mines), True, BLACK)
            screen.blit(text, text.get_rect(center=rect.center))

def create_board():
    board = [[Cell(r, c) for c in range(COLS)] for r in range(ROWS)]
    all_cells = [(r, c) for r in range(ROWS) for c in range(COLS)]
    mines = random.sample(all_cells, MINES_COUNT)
    for r, c in mines:
        board[r][c].is_mine = True


    for r in range(ROWS):
        for c in range(COLS):
            if board[r][c].is_mine:
                continue
            count = 0
            for dr in [-1, 0, 1]:
                for dc in [-1, 0, 1]:
                    nr, nc = r + dr, c + dc
                    if 0 <= nr < ROWS and 0 <= nc < COLS and board[nr][nc].is_mine:
                        count += 1
            board[r][c].adjacent_mines = count
    return board

board = create_board()

def reveal_cell(row, col):
    cell = board[row][col]
    if cell.is_mine or cell.is_revealed:
        return
    cell.is_revealed = True


running = True
while running:
    screen.fill(WHITE)

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

        elif event.type == pygame.MOUSEBUTTONDOWN:
            if event.button == 1:
                mx, my = pygame.mouse.get_pos()
                col = mx // CELL_SIZE
                row = my // CELL_SIZE
                reveal_cell(row, col)

    for row in board:
        for cell in row:
            cell.draw()

    pygame.display.flip()

pygame.quit()
sys.exit()
