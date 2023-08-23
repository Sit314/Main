import numpy as np
from graphics import GraphWin, Point, Rectangle, Text

N, TILE = 5, 100
grid = np.zeros((N, N), list)

win = GraphWin("Lights Out", N * TILE, N * TILE)

for x in range(N):
    for y in range(N):
        r = Rectangle(Point(x * TILE, y * TILE), Point((x + 1) * TILE, (y + 1) * TILE))
        r.setFill("#D9F1FF")
        r.draw(win)
        grid[x, y] = [False, r]


def flip(x, y):
    grid[x, y][0] = not grid[x, y][0]
    grid[x, y][1].setFill("#004788" if grid[x, y][0] else "#D9F1FF")


def check_win():
    for x in range(N):
        for y in range(N):
            if not grid[x, y][0]:
                return False
    return True


while not check_win():
    mouse = win.getMouse()
    x, y = int(mouse.getX()) // TILE, int(mouse.getY()) // TILE
    flip(x, y)
    if x > 0:
        flip(x - 1, y)
    if x < N - 1:
        flip(x + 1, y)
    if y > 0:
        flip(x, y - 1)
    if y < N - 1:
        flip(x, y + 1)


def set_letter(dx, letter):
    text = Text(Point((N / 2 + dx) * TILE, (N / 2) * TILE), letter)
    text.setFill("#D9F1FF")
    text.setSize(36)
    text.draw(win)


set_letter(-1, "W")
set_letter(0, "I")
set_letter(1, "N")

mouse = win.getMouse()
