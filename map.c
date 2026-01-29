#include "raylib.h"
#include "map.h"
#include <stdio.h>

#define TILE_SIZE 30
#define MAP_WIDTH 20
#define MAP_HEIGHT 20

static GameMode currentMode = MODE_PLAY;
static int showMinimap = 1;
static int showGrid = 1;

int worldMap[MAP_HEIGHT][MAP_WIDTH] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,0,1},
    {1,0,0,1,1,0,0,1,0,0,0,0,1,0,0,1,1,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,1,1,0,0,1,0,0,0,0,1,0,0,1,1,0,0,1},
    {1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,0,1},
    {1,0,0,1,1,0,0,1,0,0,0,0,1,0,0,1,1,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,1,1,0,0,1,0,0,0,0,1,0,0,1,1,0,0,1},
    {1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void DrawSimpleMap(void) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (worldMap[y][x] == 1) {
                DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, 
                            TILE_SIZE, TILE_SIZE, LIGHTGRAY);
            } else {
                DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, 
                            TILE_SIZE, TILE_SIZE, DARKGRAY);
            }
            
            DrawRectangleLines(x * TILE_SIZE, y * TILE_SIZE, 
                             TILE_SIZE, TILE_SIZE, WHITE);
        }
    }
}

void DrawMapGrid(void) {  
    for (int y = 0; y <= MAP_HEIGHT; y++) {
        DrawLine(0, y * TILE_SIZE, MAP_WIDTH * TILE_SIZE, y * TILE_SIZE, 
                Fade(WHITE, 0.3f));
    }
    for (int x = 0; x <= MAP_WIDTH; x++) {
        DrawLine(x * TILE_SIZE, 0, x * TILE_SIZE, MAP_HEIGHT * TILE_SIZE, 
                Fade(WHITE, 0.3f));
    }
}

void HandleMapEditor(Player *player) {
    Vector2 mousePos = GetMousePosition();
    
    int mapX = (int)(mousePos.x / TILE_SIZE);
    int mapY = (int)(mousePos.y / TILE_SIZE);
    
    if (mapX >= 0 && mapX < MAP_WIDTH && mapY >= 0 && mapY < MAP_HEIGHT) {
        DrawRectangleLines(mapX * TILE_SIZE, mapY * TILE_SIZE, 
                          TILE_SIZE, TILE_SIZE, GREEN);
        
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            worldMap[mapY][mapX] = 1;  
        }
        
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            worldMap[mapY][mapX] = 0; 
        }
        
        if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) {
            player->position.x = (mapX + 0.5f) * TILE_SIZE;
            player->position.y = (mapY + 0.5f) * TILE_SIZE;
        }
    }
}

void DrawMousePositionInfo() {
    Vector2 mousePos = GetMousePosition();
    int mapX = (int)(mousePos.x / TILE_SIZE);
    int mapY = (int)(mousePos.y / TILE_SIZE);
    
    char infoText[64];
    sprintf(infoText, "Mouse: (%d, %d) | Map: [%d, %d]", 
            (int)mousePos.x, (int)mousePos.y, mapX, mapY);
    
    DrawText(infoText, 10, 40, 20, YELLOW);
}

void DrawGameStateInfo(void) {
    const char *modeText = (currentMode == MODE_PLAY) ? 
                          "PLAY MODE (M to toggle)" : 
                          "EDIT MODE (M to toggle)";
    
    DrawText(modeText, 10, 70, 20, 
             (currentMode == MODE_PLAY) ? GREEN : ORANGE);
    

}

GameMode GetCurrentMode(void) { return currentMode; }
void SetCurrentMode(GameMode mode) { currentMode = mode; }
int GetShowMinimap(void) { return showMinimap; }
void ToggleShowMinimap(void) { showMinimap = !showMinimap; }