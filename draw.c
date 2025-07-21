
#include "raylib.h"

int main(void)
{
    const int screenWidth = 1024;
    const int screenHeight = 760;

    InitWindow(screenWidth, screenHeight, "simple art");

    Vector2 ball_pos  = {(float)screenWidth/2, (float)screenHeight/2};

    SetTargetFPS(60);               

    while (!WindowShouldClose())   
    {
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("A simple circle", 10, 10, 20, LIGHTGRAY);

            DrawCircleV(ball_pos, 50, MAROON);

        EndDrawing();
    }
    CloseWindow();       
    return 0;
}


