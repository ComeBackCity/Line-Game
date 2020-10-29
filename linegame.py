import pygame
import math
import os

pygame.init()

screen_size = 1000

#colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
RED = (255, 0, 0)
BLUE = (0, 0, 255)
GREEN = (0, 255, 0)
BackgroundColor = (10, 135, 140)


gameDisplay = pygame.display.set_mode((screen_size, screen_size))
pygame.display.set_caption('Line Game')

gameExit = False
font = pygame.font.Font('freesansbold.ttf', 40) 
title_text = font.render('Line Game', True, WHITE, BLACK)
button1_text = font.render('8X8', True, BLACK, WHITE)
button2_text = font.render('6X6', True, BLACK, WHITE) 
textRect = title_text.get_rect()
buttonRect1 = button1_text.get_rect() 
buttonRect2 = button2_text.get_rect() 
textRect.center = (500, 300)
buttonRect1.center = (350,687.5)
buttonRect2.center = (650,687.5)
mouse_pos = ()

while not gameExit:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            gameExit = True
        if event.type == pygame.MOUSEBUTTONDOWN:
            if 250 <= mouse_pos[0] <= 450 and 650 <= mouse_pos[1] <= 725:
                os.system('python3 game.py 8')
            elif 550 <= mouse_pos[0] <= 750 and 650 <= mouse_pos[1] <= 725:
                os.system('python3 game.py 6')
            pygame.quit()
            quit()


    mouse_pos = pygame.mouse.get_pos()        

    gameDisplay.fill(BLACK)
    gameDisplay.blit(title_text, textRect)
    pygame.draw.rect(gameDisplay, WHITE, [250,650,200,75])
    pygame.draw.rect(gameDisplay, WHITE, [550,650,200,75])
    gameDisplay.blit(button1_text, buttonRect1)
    gameDisplay.blit(button2_text, buttonRect2)
    pygame.display.update()


pygame.quit()
quit()