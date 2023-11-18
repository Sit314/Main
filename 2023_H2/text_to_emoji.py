from __future__ import print_function

import string

import numpy as np
from PIL import Image, ImageDraw, ImageFont


def char_to_pixels(text, path="arialbd.ttf", fontsize=14):
    font = ImageFont.truetype(path, fontsize)
    # w, h = font.getsize(text) # [for pillow version 9.5.0]
    l, t, r, b = font.getbbox(text)
    w, h = r - l, b - t
    h *= 2
    image = Image.new("L", (w, h), 1)
    draw = ImageDraw.Draw(image)
    draw.text((0, 0), text, font=font)
    arr = np.asarray(image)
    arr = np.where(arr, 0, 1)
    arr = arr[(arr != 0).any(axis=1)]
    # print(len(arr), len(arr[0]))
    w, h = arr.shape[1], arr.shape[0]
    h_padding = 12 - w
    left_padding = h_padding // 2
    right_padding = h_padding - left_padding
    w_padding = 0  # max(0, 9 - w)
    arr = np.pad(arr, ((1, w_padding), (left_padding, right_padding)), mode="constant")
    return arr


def display(arr):
    # result = np.where(arr, '#', ' ')
    result = np.where(arr, "🕋", "⬜")
    print("\n".join(["".join(row) for row in result]))


# for c in 'ABCDEFGHIJKLMNOPQRSTUVWXYZ':
# for c in 'אבגדהוזחטיכלמנסעפצקרשת':
for c in "בלם רוצה לראות מה עשיתי בפייתון?":
    if c == " ":
        print(("⬜" * 12 + "\n") * 4, end="")
        continue
    arr = char_to_pixels(c, path="../Fonts/calibri.ttf", fontsize=18)
    # print(arr.shape)
    display(arr)

print("⬜" * 12)
