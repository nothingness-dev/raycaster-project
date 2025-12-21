#include "raylib.h"
#include "player.h"
#include "map.h"

int main() {
    const int screenWidth = 600;
    const int screenHeight = 600;
    
    InitWindow(screenWidth, screenHeight, "Raycasting Engine");
    SetTargetFPS(60);
    
    Player player;
    InitPlayer(&player);
    
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        UpdatePlayer(&player, deltaTime);
        
        BeginDrawing();
        ClearBackground(BLACK);
        
        DrawSimpleMap();
        DrawPlayer2D(&player);
        DrawFPS(10, 10);
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}