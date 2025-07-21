
#include "raylib.h"

int main(void)
{
    const int screenWidth = 1024;
    const int screenHeight = 760;

    InitWindow(screenWidth, screenHeight, "simple art");

    // Vector2 ball_pos  = {(float)screenWidth/2, (float)screenHeight/2}; 

    RenderTexture2D canvas = LoadRenderTexture(screenWidth, screenHeight);

    //clear texture before the loop
    BeginTextureMode(canvas);
    ClearBackground(RAYWHITE);
    EndTextureMode();

    SetTargetFPS(60);               

    while (!WindowShouldClose())   
    {
        Vector2 mouse_pos = GetMousePosition();

        BeginDrawing();
        

            // ClearBackground(RAYWHITE);
            DrawTextureRec(canvas.texture, (Rectangle){0, 0, (float)canvas.texture.width,(float)canvas.texture.height }, (Vector2) {0, 0}, WHITE);


            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                BeginTextureMode(canvas);
                DrawCircle((int)GetMouseX(), (int)GetMouseY(), 30, MAGENTA);
                EndTextureMode();
            } else {
                // a circle for reference
                DrawCircle(GetMouseX(), GetMouseY(), 3, MAGENTA );
            }


            // DrawText("A simple circle", 10, 10, 20, LIGHTGRAY);

            // DrawCircleV(mouse_pos, 20, MAROON);
        EndDrawing();
    }
    CloseWindow();       
    return 0;
}


