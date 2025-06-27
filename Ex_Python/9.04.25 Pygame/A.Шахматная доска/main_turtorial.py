import pygame, sys

pygame.init()

# قراءة المدخلات من المستخدم
W, N = map(int, input("size and num of squares ").split())
WIDTH = HEIGHT = W
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("chessboard")

# التحقق من أن W قابل للقسمة على N
if W % N != 0:
    print("wrong")
    sys.exit()

# حساب حجم الخلية
cell_size = W // N

def mainloop():
    running = True
    while running:
        screen.fill((255, 255, 255))
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        # رسم لوحة الشطرنج
        for i in range(N):
            for j in range(N):
                # تحديد اللون بناءً على موقع الخلية
                if (i + j) % 2 == 0:
                    color = (0, 0, 0)  # أسود
                else:
                    color = (255, 255, 255)  # أبيض

                # رسم الخلية
                pygame.draw.rect(
                    screen,
                    color,
                    (j * cell_size, i * cell_size, cell_size, cell_size)
                )

        # تحديث الشاشة
        pygame.display.flip()


    pygame.quit()

mainloop()