import pygame
import math
import os
import sys

pygame.init()

#colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
RED = (255, 0, 0)
BLUE = (0, 0, 255)
GREEN = (0, 255, 0)
BackgroundColor = (10, 135, 140)

winner = sys.argv[1]
if sys.argv[2] == '1':
    color = BLUE
elif sys.argv[2] == '2':
    color = RED
elif sys.argv[2] == '3':
    color = BLACK
elif sys.argv[2] == '4':
    color = GREEN

gameDisplay = pygame.display.set_mode((800,300))
pygame.display.set_caption('Game Over')

gameExit = False
font = pygame.font.Font('freesansbold.ttf', 45) 
title_text = font.render(winner + ' WON THE GAME', True, color, WHITE)
textRect = title_text.get_rect()
textRect.center = (400, 150)
mouse_pos = ()

while not gameExit:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            gameExit = True

    mouse_pos = pygame.mouse.get_pos()        

    gameDisplay.fill(WHITE)
    gameDisplay.blit(title_text, textRect)
    pygame.display.update()


pygame.quit()
quit()