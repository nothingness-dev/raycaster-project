#include "raylib.h"
#include "raycaster.h"
#include "player.h"
#include "map.h"
#include <math.h>


#define TILE_SIZE 30

#define MINIMAP_SIZE 120           
#define MINIMAP_SCALE 0.15f        
#define MINIMAP_MARGIN 10          
#define MINIMAP_X (GetScreenWidth() - MINIMAP_SIZE - MINIMAP_MARGIN) 
#define MINIMAP_Y MINIMAP_MARGIN  

extern int worldMap[20][20];

void Render3DView(Player *player) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    

    for (int x = 0; x < screenWidth; x++) {
        float cameraX = 2 * x / (float)screenWidth - 1;
        
        Vector2 rayDir = {
            player->direction.x + player->plane.x * cameraX,
            player->direction.y + player->plane.y * cameraX
        };
        
        int mapX = (int)(player->position.x / TILE_SIZE);
        int mapY = (int)(player->position.y / TILE_SIZE);
        
        Vector2 deltaDist = {
            (rayDir.x == 0) ? 1e30 : fabsf(1 / rayDir.x),
            (rayDir.y == 0) ? 1e30 : fabsf(1 / rayDir.y)
        };
        
        Vector2 stepDir;
        Vector2 sideDist;
        
        if (rayDir.x < 0) {
            stepDir.x = -1;
            sideDist.x = (player->position.x / TILE_SIZE - mapX) * deltaDist.x;
        } else {
            stepDir.x = 1;
            sideDist.x = (mapX + 1.0f - player->position.x / TILE_SIZE) * deltaDist.x;
        }
        
        if (rayDir.y < 0) {
            stepDir.y = -1;
            sideDist.y = (player->position.y / TILE_SIZE - mapY) * deltaDist.y;
        } else {
            stepDir.y = 1;
            sideDist.y = (mapY + 1.0f - player->position.y / TILE_SIZE) * deltaDist.y;
        }
        
        bool hit = false;
        int side = 0;
        
        while (!hit) {
            if (sideDist.x < sideDist.y) {
                sideDist.x += deltaDist.x;
                mapX += stepDir.x;
                side = 0;
            } else {
                sideDist.y += deltaDist.y;
                mapY += stepDir.y;
                side = 1;
            }
            
            if (worldMap[mapY][mapX] > 0) hit = true;
        }
        
        float perpWallDist;
        if (side == 0) perpWallDist = sideDist.x - deltaDist.x;
        else perpWallDist = sideDist.y - deltaDist.y;
        
        int lineHeight = (int)(screenHeight / perpWallDist);
        
        int drawStart = -lineHeight / 2 + screenHeight / 2;
        if (drawStart < 0) drawStart = 0;
        
        int drawEnd = lineHeight / 2 + screenHeight / 2;
        if (drawEnd >= screenHeight) drawEnd = screenHeight - 1;
        
        Color wallColor;
        if (worldMap[mapY][mapX] == 1) {
            wallColor = (side == 1) ? (Color){120,120,120,255} : (Color){160,160,160,255};
        } else {
            wallColor = (Color){100,100,200,255};
        }
        
        float shade = 1.0f / (1.0f + perpWallDist * 0.1f);
        Color shadedColor = {
            (unsigned char)(wallColor.r * shade),
            (unsigned char)(wallColor.g * shade),
            (unsigned char)(wallColor.b * shade),
            255
        };
        
        DrawLine(x, drawStart, x, drawEnd, shadedColor);
        
        DrawLine(x, drawEnd, x, screenHeight, (Color){60,60,60,255});
        DrawLine(x, 0, x, drawStart, (Color){40,40,80,255});
    }
}

void RenderMinimap(Player *player) {
    DrawRectangle(MINIMAP_X, MINIMAP_Y, MINIMAP_SIZE, MINIMAP_SIZE, Fade(BLACK, 0.7f));

    
    float minimapTileSize = MINIMAP_SIZE / 20.0f;
    
    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 20; x++) {
            Color tileColor;
            
            if (worldMap[y][x] == 1) {
                tileColor = GRAY;  
            } else {
                tileColor = DARKGRAY;  
            }
            
            DrawRectangle(
                MINIMAP_X + x * minimapTileSize,
                MINIMAP_Y + y * minimapTileSize,
                minimapTileSize,
                minimapTileSize,
                tileColor
            );
        }
    }
    
    float playerMinimapX = MINIMAP_X + (player->position.x / TILE_SIZE) * minimapTileSize;
    float playerMinimapY = MINIMAP_Y + (player->position.y / TILE_SIZE) * minimapTileSize;
    
    DrawCircle(playerMinimapX, playerMinimapY, minimapTileSize/2, RED);
    
    DrawLine(
        playerMinimapX,
        playerMinimapY,
        playerMinimapX + player->direction.x * minimapTileSize * 1.5f,
        playerMinimapY + player->direction.y * minimapTileSize * 1.5f,
        YELLOW
    );
    
    DrawRectangleLines(MINIMAP_X, MINIMAP_Y, MINIMAP_SIZE, MINIMAP_SIZE, WHITE);
}