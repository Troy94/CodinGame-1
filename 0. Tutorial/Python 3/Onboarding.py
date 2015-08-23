import sys
import math

# CodinGame planet is being attacked by slimy insectoid aliens.
# <---
# Hint:To protect the planet, you can implement the pseudo-code provided in the statement, below the player.


# game loop
while 1:
    enemy1 = input()  # name of enemy 1
    dist1 = int(input())  # distance to enemy 1
    enemy2 = input()  # name of enemy 2
    dist2 = int(input())  # distance to enemy 2
    if(dist1<dist2) :
        print(enemy1)
    else :
        print(enemy2)
