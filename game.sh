mkfifo pipe
g++ ai.cpp -o ai
python3 game.py 8 < pipe | ./ai > pipe
rm pipe