#ifndef MAP_H
#define MAP_H

#include "raylib.h"
#include "player.h" 

void DrawSimpleMap(void);
void DrawMapGrid(void);  
void HandleMapEditor(Player *player);
void DrawMousePositionInfo(void);
void DrawGameStateInfo(void);

typedef enum {
    MODE_PLAY,
    MODE_EDIT
} GameMode;

GameMode GetCurrentMode(void);
void SetCurrentMode(GameMode mode);
int GetShowMinimap(void);
void ToggleShowMinimap(void);

#endif