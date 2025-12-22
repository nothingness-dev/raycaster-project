#include "raylib.h"
#include "player.h"
#include "raycaster.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    
    InitWindow(screenWidth, screenHeight, "Raycasting Engine - 3D + Minimap");
    SetTargetFPS(60);
    
    Player player;
    InitPlayer(&player);
    
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        

        UpdatePlayer(&player, deltaTime);
        
        BeginDrawing();
        ClearBackground(BLACK);
        

        Render3DView(&player);
        

        RenderMinimap(&player);
        

        DrawFPS(10, 10);
        DrawText("3D View + Minimap", 10, 40, 20, YELLOW);
        DrawText("WASD: Move | Arrows: Rotate", 10, 70, 18, WHITE);
        
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}