import pygame
import random
import math

# إعدادات أولية
WIDTH, HEIGHT = 800, 600
BALL_RADIUS = 20
FPS = 60

# ألوان
BLACK = (0, 0, 0)
RED = (200, 20, 255)

# تهيئة Pygame
pygame.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))
clock = pygame.time.Clock()

# قائمة الكرات
balls = []

# كائن يمثل كرة
class Ball:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.vx = random.uniform(-4, 4)
        self.vy = random.uniform(-4, 4)

    def move(self):
        # تحريك الكرة
        self.x += self.vx
        self.y += self.vy

        # الارتداد من الجدران
        if self.x - BALL_RADIUS < 0 or self.x + BALL_RADIUS > WIDTH:
            self.vx *= -1
        if self.y - BALL_RADIUS < 0 or self.y + BALL_RADIUS > HEIGHT:
            self.vy *= -1

    def draw(self):
        pygame.draw.circle(screen, RED, (int(self.x), int(self.y)), BALL_RADIUS)

    def collide_with(self, other):
        dx = other.x - self.x
        dy = other.y - self.y
        distance = math.hypot(dx, dy)

        if distance < 2 * BALL_RADIUS and distance != 0:
            # تبادل السرعة البسيط (قانون حفظ الزخم)
            self.vx, other.vx = other.vx, self.vx
            self.vy, other.vy = other.vy, self.vy

            # تحريك بسيط لإبعاد الكرتين عن بعض
            overlap = 2 * BALL_RADIUS - distance
            dx /= distance
            dy /= distance
            self.x -= dx * overlap / 2
            self.y -= dy * overlap / 2
            other.x += dx * overlap / 2
            other.y += dy * overlap / 2

# الحلقة الرئيسية
running = True
while running:
    clock.tick(FPS)
    screen.fill(BLACK)

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        # إضافة كرة عند النقر بالفأرة
        elif event.type == pygame.MOUSEBUTTONDOWN:
            x, y = event.pos
            balls.append(Ball(x, y))

    # تحريك الكرات والتحقق من التصادم
    for ball in balls:
        ball.move()

    # التحقق من تصادم الكرات ببعض
    for i in range(len(balls)):
        for j in range(i + 1, len(balls)):
            balls[i].collide_with(balls[j])

    # رسم الكرات
    for ball in balls:
        ball.draw()

    pygame.display.flip()

pygame.quit()
