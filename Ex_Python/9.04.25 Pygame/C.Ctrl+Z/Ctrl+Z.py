import pygame
pygame.init()
screen = pygame.display.set_mode((800, 600))
pygame.display.set_caption("Draw and Undo Rectangles")

rectangles = []
drawing = False
start_pos = None
current_rect = None

TF=True
while TF:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            TF=False


        elif event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
            drawing = True
            start_pos = event.pos


        elif event.type == pygame.MOUSEBUTTONUP and event.button == 1:
            if drawing and current_rect:
                rectangles.append(current_rect)
                current_rect = None
            drawing = False


        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_z and pygame.key.get_mods() & pygame.KMOD_CTRL:
                if rectangles:
                    rectangles.pop()


    if drawing and start_pos:
        mouse_pos = pygame.mouse.get_pos()
        x = min(start_pos[0], mouse_pos[0])
        y = min(start_pos[1], mouse_pos[1])
        width = abs(start_pos[0] - mouse_pos[0])
        height = abs(start_pos[1] - mouse_pos[1])
        current_rect = pygame.Rect(x, y, width, height)


    screen.fill((0, 0, 0))


    for rect in rectangles:
        pygame.draw.rect(screen, (0, 255, 255), rect, 1)


    if current_rect:
        pygame.draw.rect(screen, (0, 255, 255), current_rect, 1)

    pygame.display.flip()

