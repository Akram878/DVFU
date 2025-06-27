import pygame
import sys


pygame.init()


Size = 300, 300
screen = pygame.display.set_mode(Size)
pygame.display.set_caption("Перетаскиваемый квадрат")


square_size = 50
square_color = (255, 0, 0)  # لون أزرق فاتح
square_rect = pygame.Rect(0, 0, square_size, square_size)

# حالة السحب
dragging = False
offset_x = 0
offset_y = 0

running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running=False


        elif event.type == pygame.MOUSEBUTTONDOWN:
            if event.button == 1:  # زر الفأرة الأيسر
                if square_rect.collidepoint(event.pos):
                    dragging = True
                    mouse_x, mouse_y = event.pos
                    offset_x = square_rect.x - mouse_x
                    offset_y = square_rect.y - mouse_y


        elif event.type == pygame.MOUSEBUTTONUP:
            if event.button == 1:
                dragging = False

        # أثناء السحب
        elif event.type == pygame.MOUSEMOTION:
            if dragging:
                mouse_x, mouse_y = event.pos
                square_rect.x = mouse_x + offset_x
                square_rect.y = mouse_y + offset_y


    screen.fill((0, 0, 0))


    pygame.draw.rect(screen, square_color, square_rect)


    pygame.display.flip()
