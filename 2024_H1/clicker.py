import time

import pyautogui

pyautogui.click(x=750, y=980)

for i in range(1, 11):
    pyautogui.typewrite(str(i))
    pyautogui.press("enter")
    time.sleep(0.1)
