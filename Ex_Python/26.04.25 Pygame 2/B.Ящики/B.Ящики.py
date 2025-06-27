import pygame
import sys

pygame.init()

# إعدادات الشاشة
SCREEN_WIDTH = 800
SCREEN_HEIGHT = 600
TILE_SIZE = 50


screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption('Игра с ящиками')


GRID_WIDTH = SCREEN_WIDTH // TILE_SIZE
GRID_HEIGHT = SCREEN_HEIGHT // TILE_SIZE

def load_image(name):
    # تحميل الصورة بعد تهيئة الشاشة
    image = pygame.image.load(name)
    return image.convert_alpha()

# تحميل الصور الآن بعد تهيئة الشاشة
tile_images = {
    'wall': load_image('box.png'),
    'empty': load_image('grass.png')
}

player_image = load_image('mario.png')

# مجموعات السبرايت
all_sprites = pygame.sprite.Group()
tiles_group = pygame.sprite.Group()
player_group = pygame.sprite.Group()

class Tile(pygame.sprite.Sprite):
    def __init__(self, tile_type, grid_x, grid_y):
        super().__init__(tiles_group, all_sprites)
        self.type = tile_type
        self.image = tile_images[tile_type]
        self.rect = self.image.get_rect()
        self.rect.topleft = (grid_x * TILE_SIZE, grid_y * TILE_SIZE)
        self.grid_x = grid_x
        self.grid_y = grid_y

class Player(pygame.sprite.Sprite):
    def __init__(self, grid_x, grid_y):
        super().__init__(player_group, all_sprites)
        self.image = player_image
        self.rect = self.image.get_rect()
        self.pos_x = grid_x * TILE_SIZE
        self.pos_y = grid_y * TILE_SIZE
        self.rect.topleft = (self.pos_x, self.pos_y)

        self.grid_x = grid_x
        self.grid_y = grid_y

        self.speed = 8

        self.moving = False
        self.target_x = self.pos_x
        self.target_y = self.pos_y

        self.facing = (0, -1)

    def update(self):
        if self.moving:
            if self.pos_x < self.target_x:
                self.pos_x += self.speed
                if self.pos_x > self.target_x:
                    self.pos_x = self.target_x
            elif self.pos_x > self.target_x:
                self.pos_x -= self.speed
                if self.pos_x < self.target_x:
                    self.pos_x = self.target_x

            if self.pos_y < self.target_y:
                self.pos_y += self.speed
                if self.pos_y > self.target_y:
                    self.pos_y = self.target_y
            elif self.pos_y > self.target_y:
                self.pos_y -= self.speed
                if self.pos_y < self.target_y:
                    self.pos_y = self.target_y

            self.rect.topleft = (self.pos_x, self.pos_y)

            if self.pos_x == self.target_x and self.pos_y == self.target_y:
                self.moving = False

    def move(self, dx, dy):
        if self.moving:
            return

        new_grid_x = self.grid_x + dx
        new_grid_y = self.grid_y + dy

        if not (0 <= new_grid_x < GRID_WIDTH and 0 <= new_grid_y < GRID_HEIGHT):
            return

        for tile in tiles_group:
            if tile.type == 'wall' and tile.grid_x == new_grid_x and tile.grid_y == new_grid_y:
                return

        self.grid_x = new_grid_x
        self.grid_y = new_grid_y
        self.target_x = self.grid_x * TILE_SIZE
        self.target_y = self.grid_y * TILE_SIZE
        self.moving = True

        self.facing = (dx, dy)

    def break_box(self):
        target_x = self.grid_x + self.facing[0]
        target_y = self.grid_y + self.facing[1]

        for tile in list(tiles_group):
            if tile.type == 'wall' and tile.grid_x == target_x and tile.grid_y == target_y:
                tile.kill()
                break

def generate_level(level_map):
    new_player = None
    for y in range(len(level_map)):
        for x in range(len(level_map[y])):
            if level_map[y][x] == '.':
                Tile('empty', x, y)
            elif level_map[y][x] == '#':
                Tile('wall', x, y)
            elif level_map[y][x] == '@':
                Tile('empty', x, y)
                new_player = Player(x, y)
    return new_player

def load_level(filename):
    with open(filename, 'r') as f:
        return [line.strip() for line in f]

def main():
    clock = pygame.time.Clock()

    level_map = load_level('map.txt')
    player = generate_level(level_map)

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()

        keys = pygame.key.get_pressed()

        if not player.moving:
            if keys[pygame.K_LEFT] or keys[pygame.K_a]:
                player.move(-1, 0)
            elif keys[pygame.K_RIGHT] or keys[pygame.K_d]:
                player.move(1, 0)
            elif keys[pygame.K_UP] or keys[pygame.K_w]:
                player.move(0, -1)
            elif keys[pygame.K_DOWN] or keys[pygame.K_s]:
                player.move(0, 1)

        if keys[pygame.K_SPACE]:
            player.break_box()
            pygame.time.wait(150)

        player.update()

        screen.fill((0, 0, 0))

        # رسم العشب لجميع الخلايا كخلفية
        for y in range(GRID_HEIGHT):
            for x in range(GRID_WIDTH):
                screen.blit(tile_images['empty'], (x * TILE_SIZE, y * TILE_SIZE))

        # رسم الجدران فقط فوق العشب
        for tile in tiles_group:
            if tile.type == 'wall':
                screen.blit(tile.image, tile.rect.topleft)

        # رسم اللاعب فوق الجميع
        screen.blit(player.image, player.rect.topleft)

        pygame.display.flip()
        clock.tick(60)

if __name__ == '__main__':
    main()
