import os
import time
import pyautogui
import sys

os.system('start')

time.sleep(.5)

for i in range(1,sys.argv.__len__()) :
	pyautogui.write(sys.argv[i])
	pyautogui.press('\n')