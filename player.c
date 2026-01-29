#include "player.h"
#include <math.h>

#define TILE_SIZE 30
#define MAP_WIDTH 20
#define MAP_HEIGHT 20

extern int worldMap[MAP_HEIGHT][MAP_WIDTH];

int IsWall(int x, int y) {
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)
        return 1;
    return worldMap[y][x] == 1;
}

void InitPlayer(Player *player) {
    player->position = (Vector2){TILE_SIZE * 2.5f, TILE_SIZE * 2.5f};
    player->direction = (Vector2){0.0f, -1.0f};
    player->plane = (Vector2){0.66f, 0.0f};
    player->moveSpeed = 150.0f;
    player->rotationSpeed = 2.5f;
    player->radius = 8.0f;
    player->color = RED;
}

void NormalizeVector(Vector2 *vec) {
    float length = sqrtf(vec->x * vec->x + vec->y * vec->y);
    if (length > 0) {
        vec->x /= length;
        vec->y /= length;
    }
}

void UpdatePlayer(Player *player, float deltaTime) {
    Vector2 moveDir = {0.0f, 0.0f};
    
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
        moveDir.x += player->direction.x;
        moveDir.y += player->direction.y;
    }
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
        moveDir.x -= player->direction.x;
        moveDir.y -= player->direction.y;
    }
    if (IsKeyDown(KEY_A)) {
        moveDir.x += player->direction.y;
        moveDir.y -= player->direction.x;
    }
    if (IsKeyDown(KEY_D)) {
        moveDir.x -= player->direction.y;
        moveDir.y += player->direction.x;
    }
    
    if (moveDir.x != 0 || moveDir.y != 0) {
        NormalizeVector(&moveDir);
        
        Vector2 newPos = {
            player->position.x + moveDir.x * player->moveSpeed * deltaTime,
            player->position.y + moveDir.y * player->moveSpeed * deltaTime
        };
        
        int mapX = (int)(newPos.x / TILE_SIZE);
        int mapY = (int)(newPos.y / TILE_SIZE);
        
        if (!IsWall(mapX, mapY)) {
            player->position = newPos;
        } else {
            Vector2 newPosX = {newPos.x, player->position.y};
            mapX = (int)(newPosX.x / TILE_SIZE);
            mapY = (int)(newPosX.y / TILE_SIZE);
            if (!IsWall(mapX, mapY)) {
                player->position.x = newPosX.x;
            }
            
            Vector2 newPosY = {player->position.x, newPos.y};
            mapX = (int)(newPosY.x / TILE_SIZE);
            mapY = (int)(newPosY.y / TILE_SIZE);
            if (!IsWall(mapX, mapY)) {
                player->position.y = newPosY.y;
            }
        }
    }
    
    float rotation = 0.0f;
    
    if (IsKeyDown(KEY_LEFT)) {
        rotation = -player->rotationSpeed * deltaTime;
    }
    if (IsKeyDown(KEY_RIGHT)) {
        rotation = player->rotationSpeed * deltaTime;
    }
    
    if (rotation != 0.0f) {
        float cosRot = cosf(rotation);
        float sinRot = sinf(rotation);
        
        float oldDirX = player->direction.x;
        player->direction.x = oldDirX * cosRot - player->direction.y * sinRot;
        player->direction.y = oldDirX * sinRot + player->direction.y * cosRot;
        
        float oldPlaneX = player->plane.x;
        player->plane.x = oldPlaneX * cosRot - player->plane.y * sinRot;
        player->plane.y = oldPlaneX * sinRot + player->plane.y * cosRot;
        
        NormalizeVector(&player->direction);
    }
}

void DrawPlayer2D(Player *player) {
    DrawCircleV(player->position, player->radius, player->color);
    DrawLineV(player->position, 
              (Vector2){player->position.x + player->direction.x * 35.0f,
                       player->position.y + player->direction.y * 35.0f}, 
              YELLOW);
}