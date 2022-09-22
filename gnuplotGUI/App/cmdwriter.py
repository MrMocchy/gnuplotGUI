import os
import sys
import time
import pyautogui
import pyperclip

os.system('start')

time.sleep(.5)

args = pyperclip.paste()

for str in args.split('\n') :
	pyperclip.copy(str)
	pyautogui.hotkey('ctrl', 'v')
	pyautogui.press('\n')