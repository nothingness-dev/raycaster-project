#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

typedef struct {
    Vector2 position;      
    Vector2 direction;     
    Vector2 plane;         
    float moveSpeed;       
    float rotationSpeed;   
    float radius;         
    Color color;         
} Player;

void InitPlayer(Player *player);                    
void UpdatePlayer(Player *player, float deltaTime); 
void DrawPlayer2D(Player *player);                  
int IsWall(int x, int y);

#endif