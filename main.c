#include "raylib.h"
#include "player.h"
#include "raycaster.h"
#include "map.h"
#include <stdio.h>

int main() {
    const int screenWidth = 600;
    const int screenHeight = 600;
    
    InitWindow(screenWidth, screenHeight, "Raycasting Engine - 3D + Minimap + Editor");
    SetTargetFPS(60);
    
    Player player;
    InitPlayer(&player);
    
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        
        if (IsKeyPressed(KEY_M)) {
            GameMode current = GetCurrentMode();
            SetCurrentMode((current == MODE_PLAY) ? MODE_EDIT : MODE_PLAY);
        }
        
        if (IsKeyPressed(KEY_H)) {
            ToggleShowMinimap();
        }
        
        if (IsKeyPressed(KEY_F5)) {
            FILE *file = fopen("map.bin", "wb");
            if (file) {
                extern int worldMap[20][20];
                fwrite(worldMap, sizeof(int), 20*20, file);
                fclose(file);
                TraceLog(LOG_INFO, "Map saved to map.bin");
            }
        }
        
        if (IsKeyPressed(KEY_L)) {
            FILE *file = fopen("map.bin", "rb");
            if (file) {
                extern int worldMap[20][20];
                size_t read = fread(worldMap, sizeof(int), 20*20, file);
                fclose(file);
                if (read == 20*20) {
                    TraceLog(LOG_INFO, "Map loaded from map.bin");
                }
            }
        }
        
        if (GetCurrentMode() == MODE_PLAY) {
            UpdatePlayer(&player, deltaTime);
        } else {
            HandleMapEditor(&player);
        }
        
        BeginDrawing();
        ClearBackground(BLACK);
        
        if (GetCurrentMode() == MODE_PLAY) {
            Render3DView(&player);
            
            if (GetShowMinimap()) {
                RenderMinimap(&player);
            }
        } else {
            DrawSimpleMap();
            DrawPlayer2D(&player);
            
            DrawMapGrid(); 
            
            DrawMousePositionInfo();
        }
        
        DrawGameStateInfo();
        DrawFPS(10, 10);
        
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}