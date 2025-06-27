import pygame
import math
import colorsys

# إعدادات الشاشة
width = 600
height = 600
center = (width // 2, height // 2)
radius = 200
points_count = 360

# تهيئة Pygame
pygame.init()
screen = pygame.display.set_mode((width, height))
pygame.display.set_caption("Multiplication Circle Table")
clock = pygame.time.Clock()

# إنشاء نقاط الدائرة
points = []
for i in range(points_count):
    angle = math.radians(i)
    x = int(math.cos(angle) * radius) + center[0]
    y = int(math.sin(angle) * radius) + center[1]
    points.append((x, y))

# متغيرات التحكم
running = True
paused = False
multiplier = 0.0

# دالة لتحويل HSV إلى RGB
def hsv2rgb(h, s, v):
    r, g, b = colorsys.hsv_to_rgb(h, s, v)
    return int(r * 255), int(g * 255), int(b * 255)

# حلقة البرنامج الرئيسية
while running:
    screen.fill((0, 0, 0))  # خلفية سوداء

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_SPACE:
                paused = not paused

    # رسم الخطوط بين النقاط
    for i in range(points_count):
        a = points[i]
        j = int((i * multiplier) % points_count)
        b = points[j]
        hue = i / points_count
        color = hsv2rgb(hue, 1, 1)
        pygame.draw.aaline(screen, color, a, b)

    pygame.display.flip()
    clock.tick(60)

    if not paused:
        multiplier += 0.01

pygame.quit()
