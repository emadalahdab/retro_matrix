#!/bin/bash
python /home/pi/Desktop/test.py
python /home/pi/Desktop/retro_matrix.resetmatrix.py
/home/pi/Desktop/retro_matrix/run_retro_matrix --led-slowdown-gpio=4 --led-gpio-mapping=regular --led-no-hardware-pulse --led-parallel=2 --led-cols=64 --led-rows=32

