import pygame
import math
import sys
import os
from queue import Queue
from sys import stderr

pygame.init()

mode = int(sys.argv[1])
arg2 = int(sys.argv[2])
pve = True if arg2 == 1 else False

#screen_layout
screen_size = 1000 if mode == 8 else 800
boundary_top = (100, 100)
boundary_bottom = (900, 900) if mode == 8 else (700, 700)

#colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
RED = (255, 0, 0)
BLUE = (0, 0, 255)
GREEN = (0, 255, 0)
YELLOW = (255, 255, 0)
BackgroundColor = (10, 135, 140)
P1 = (220, 93, 73)
P2 = (68, 68, 206)

#boards
board = [[0]*mode for i in range(mode)]
board2 =  [[0]*mode for i in range(mode)]

for i in range(mode):
    for j in range(mode):
        if i == 0 or i == mode-1:
            if j != 0 or j != mode-1:
                board[i][j] = 2
        else:
            if j == 0 or j == mode-1:
                board[i][j] = 1 

board[0][0] = board[0][mode-1] = board[mode-1][0] = board[mode-1][mode-1] = 0

moves = [(1,0), (1,1), (0,1), (-1,1), (-1,0), (-1,-1), (0,-1), (1,-1)]


def valid_click(m_pos, top, bottom):
    if(m_pos[0] < top[0] or m_pos[1] < top[1] or m_pos[0] > bottom[0] or m_pos[1] > bottom[1]):
        return False
    else:
        return True

def playerCount(playerVal):
    count = 0
    first = (999, 999)
    for i in range(mode):
        for j in range(mode):
            if board[i][j] == playerVal:
                count += 1
                if i < first[0] and j < first[0]:
                    first = (i, j)
    return (count, first[0], first[1])

def bfs(x, y, p):
    length = 0
    q = []
    d = dict()
    q.append((x,y))
    while len(q) != 0:
        (a, b) = q.pop(0)
        if d.get((a,b)) is None:
            d[(a,b)] = True
            length += 1
        for move in moves:
            if 0 <= a+ move[0] < mode and 0 <= b+move[1] < mode:
                if board[a+move[0]][b+move[1]] == p and d.get((a+move[0],b+move[1])) is None:
                    q.append((a+move[0], b+move[1]))
    return length
                

def winCheck():
    (c1, x1, y1) = playerCount(1)
    (c2, x2, y2) = playerCount(2)

    l1 = bfs(x1, y1, 1)
    l2 = bfs(x2, y2, 2)

    if l1 < c1 and l2 == c2:
        return (True, 2)
    elif l1 == c1 and l2 < c2:
        return (True, 1)
    else:
        return (False, -1)

gameDisplay = pygame.display.set_mode((screen_size, screen_size))
pygame.display.set_caption('Line Game')

gameExit = False
gameStarted = False
move_from = (-1,-1)
move_to = (-2,-2)
opp_from = (-1, -1)
opp_to = (-2, -2)
me = int(sys.argv[3])
opponent = int(sys.argv[4])
turn = 2
opposite = 1
a = b = 0
loop_breaker = False

while not gameExit:
    if pve:
        if turn == opponent:
            print("{} {} {} {}".format(move_from[0], move_from[1], move_to[0], move_to[1]))
            a = int(input())
            b = int(input())
            c = int(input())
            d = int(input())
            opp_from = (a, b)
            opp_to = (c, d)
            board[a][b] = 0
            board[c][d] = opponent
            turn, opposite = opposite, turn
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            gameExit = True
        elif event.type == pygame.MOUSEBUTTONUP:
            mouse_pos = pygame.mouse.get_pos()
            if valid_click(mouse_pos, boundary_top, boundary_bottom):
                x1 = int(math.floor(mouse_pos[0]/100)) 
                y1 = int(math.floor(mouse_pos[1]/100))
                if turn == 2 or turn == 1:
                    move_from = (y1-1,x1-1)
                if turn == 1.5 or turn == 0.5:
                    move_to = (y1-1,x1-1)
                if board[y1-1][x1-1] == turn:
                    horizontal = 0
                    vertical = 0
                    primary = 0
                    secondary = 0
                    for i in range(mode):
                        if board[y1-1][i] != 0:
                            horizontal = horizontal + 1

                    for i in range(mode):
                        if board[i][x1-1] !=0:
                            vertical = vertical + 1
                    
                    p1 = (y1-1,x1-1)
                    p2 = (y1-1,x1-1)
                    s1 = (y1-1,x1-1)
                    s2 = (y1-1,x1-1)
                    
                    while True:
                        if p1[0]-1 >= 0 and p1[1]-1 >= 0:
                            p1 = (p1[0]-1, p1[1]-1)
                        else:
                            break

                    while True:
                        if p2[0]+1 < mode and p2[1]+1 < mode :
                            p2 = (p2[0]+1, p2[1]+1)
                        else:
                            break

                    while True:
                        if s2[0]-1 >= 0 and s2[1]+1 < mode:
                            s2 = (s2[0]-1, s2[1]+1)
                        else:
                            break

                    while True:
                        if s1[0]+1 < mode and s1[1]-1 >= 0:
                            s1 = (s1[0]+1, s1[1]-1)
                        else:
                            break

                    while p1 != p2:
                        if board[p1[0]][p1[1]] !=0:
                            primary = primary + 1
                        p1 = (p1[0] + 1, p1[1] + 1)

                    if board[p2[0]][p2[1]] != 0:
                        primary += 1

                    while s1 != s2:
                        if board[s1[0]][s1[1]] !=0:
                            secondary = secondary + 1
                        s1 = (s1[0] - 1, s1[1] + 1)

                    if board[s2[0]][s2[1]] != 0:
                        secondary += 1

                    move_count = 0

                    #horizontal
                    valid = True
                    for j in range(1,horizontal+1):
                        if x1-1+j > mode-1:
                            valid = False
                            break
                        elif j!=horizontal and board[y1-1][x1-1+j] == opposite:
                            valid = False
                            break
                        elif j==horizontal and board[y1-1][x1-1+j] ==turn:
                            valid = False
                            break
                    
                    if valid:
                        move_count += 1
                        board2[y1-1][x1-1+horizontal] = board[y1-1][x1-1] - 0.5

                    valid = True
                    for j in range(1,horizontal+1):
                        if x1-1-j < 0:
                            valid = False
                            break
                        elif j!=horizontal and board[y1-1][x1-1-j] == opposite:
                            valid = False
                            break
                        elif j==horizontal and board[y1-1][x1-1-j] == turn:
                            valid = False
                            break

                    if valid:
                        move_count += 1
                        board2[y1-1][x1-1-horizontal] = board[y1-1][x1-1] - 0.5

                    #vertical
                    valid = True
                    for j in range(1,vertical+1):
                        if y1-1+j > mode-1:
                            valid = False
                            break
                        elif j!=vertical and board[y1-1+j][x1-1] == opposite:
                            valid = False
                            break
                        elif j==vertical and board[y1-1+j][x1-1] == turn:
                            valid = False
                            break

                    if valid:
                        move_count += 1
                        board2[y1-1+vertical][x1-1] = board[y1-1][x1-1] - 0.5

                    valid = True
                    for j in range(1,vertical+1):
                        if y1-1-j < 0:
                            valid = False
                            break
                        elif j!=vertical and board[y1-1-j][x1-1] == opposite:
                            valid = False
                            break
                        elif j==vertical and board[y1-1-j][x1-1] == turn:
                            valid = False
                            break

                    if valid:
                        move_count += 1
                        board2[y1-1-vertical][x1-1] = board[y1-1][x1-1] - 0.5

                    #primary
                    valid = True
                    for j in range(1,primary+1):
                        if y1-1-j < 0 or x1-1-j < 0:
                            valid = False
                            break
                        elif j!= primary and board[y1-1-j][x1-1-j] == opposite:
                            valid = False
                            break
                        elif j== primary and board[y1-1-j][x1-1-j] == turn:
                            valid = False
                            break

                    if valid:
                        move_count += 1
                        board2[y1-1-primary][x1-1-primary] = board[y1-1][x1-1] - 0.5

                    valid = True
                    for j in range(1,primary+1):
                        if y1-1+j >= mode or x1-1+j >= mode:
                            valid = False
                            break
                        elif j!= primary and board[y1-1+j][x1-1+j] == opposite:
                            valid = False
                            break
                        elif j== primary and board[y1-1+j][x1-1+j] == turn:
                            valid = False
                            break

                    if valid:
                        move_count += 1
                        board2[y1-1+primary][x1-1+primary] = board[y1-1][x1-1] - 0.5

                    #secondary
                    valid = True
                    for j in range(1,secondary+1):
                        if y1-1+j >= mode or x1-1-j < 0 :
                            valid = False
                            break
                        elif j!= secondary and board[y1-1+j][x1-1-j] == opposite:
                            valid = False
                            break
                        elif j== secondary and board[y1-1+j][x1-1-j] == turn:
                            valid = False
                            break
                    
                    if valid:
                        move_count += 1
                        board2[y1-1+secondary][x1-1-secondary] = board[y1-1][x1-1] - 0.5

                    valid = True
                    for j in range(1,secondary+1):
                        if y1-1-j < 0 or x1-1+j >= mode:
                            valid = False
                            break
                        elif j!= secondary and board[y1-1-j][x1-1+j] == opposite:
                            valid = False
                            break
                        elif j== secondary and board[y1-1-j][x1-1+j] == turn:
                            valid = False
                            break

                    if valid:
                        move_count += 1
                        board2[y1-1-secondary][x1-1+secondary] = board[y1-1][x1-1] - 0.5

                    if move_count == 0:
                        loop_breaker = True
                        break

                    a = y1-1
                    b = x1-1

                elif board2[y1-1][x1-1] == turn:
                    board[y1-1][x1-1] = board2[y1-1][x1-1] + 0.5
                    board[a][b] = 0
                    board2 =  [[0]*mode for i in range(mode)]

                else:
                    continue

                if turn == 1 or turn == 2:
                    turn -= 0.5
                elif turn == 0.5:
                    turn = 2
                    opposite = 1
                else:
                    turn = 1
                    opposite = 2                
                    
    if loop_breaker:
        loop_breaker = False
        continue

    base = (screen_size-200)/mode

    gameDisplay.fill(BackgroundColor)
    for i in range(mode):
        y = (i+1)*base
        for j in range(mode):
            x = (j+1)*base
            if (i+j)%2 == 0:
                pygame.draw.rect(gameDisplay, BLACK, [x,y,100,100])
            else:
                pygame.draw.rect(gameDisplay, WHITE, [x,y,100,100])
    for i in range(mode):
        for j in range(mode):
            if board[i][j] == 2:
                pygame.draw.circle(gameDisplay, P2, ((j+1) * 100 + 50, (i+1) * 100 + 50) , 35)
            elif board[i][j] == 1:
                pygame.draw.circle(gameDisplay, P1, ((j+1) * 100 + 50, (i+1) * 100 + 50) , 35)
        for j in range(mode):
            if board2[i][j] == 0.5:
                pygame.draw.circle(gameDisplay, GREEN, ((j+1) * 100 + 50, (i+1) * 100 + 50) , 35)
            elif board2[i][j] == 1.5:
                pygame.draw.circle(gameDisplay, YELLOW, ((j+1) * 100 + 50, (i+1) * 100 + 50) , 35)

    pygame.display.update()
    if not gameStarted:
        gameStarted = True
    if gameStarted:
        (finished, player) = winCheck()
        if finished:
            if not pve:
                if player == 2:
                    os.system('python3 endScreen.py BLUE 1')
                elif player == 1:
                    os.system('python3 endScreen.py RED 2')
            else:
                if player == me:
                    os.system('python3 endScreen.py YOU 4')
                else:
                    os.system('python3 endScreen.py CPU 3')
            quit()
    
pygame.quit()
quit()