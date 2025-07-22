
#include "raylib.h"
#include <stdio.h>
#include <time.h>
#define MAX_COLOR_COUNT  6


int main(void)
{
    const int screenWidth = 1024;
    const int screenHeight = 760;
    float brush_size = 20.0f;
    float max_brush_size = 60.0f;
    float min_brush_size = 10.0;
    Color colors[MAX_COLOR_COUNT] = {
        BLACK, RED, GREEN, YELLOW, BLUE, PINK
    };
    int color_selected = 0;
    //Date and time (for image name)
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char image_name[100];
    snprintf(
        image_name,
        sizeof(image_name),
        "image_%02d_%02d_%02d_%02d_%02d_%02d.png",
        t->tm_mday,
        t->tm_mon + 1,
        t->tm_year % 100,
        t->tm_hour,
        t->tm_min,
         t->tm_sec
    );
    


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
        

            ClearBackground(RAYWHITE);
            DrawTextureRec(canvas.texture, (Rectangle){0, 0, (float)canvas.texture.width,(float)-canvas.texture.height }, (Vector2) {0, 0}, WHITE);


            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                BeginTextureMode(canvas);
                DrawCircle((int)GetMouseX(), (int)GetMouseY(), brush_size, colors[color_selected]);
                EndTextureMode();
            } else {
                // a circle for reference
                DrawCircle(GetMouseX(), GetMouseY(), brush_size, colors[color_selected] );
            }

            //keys controls
            if (IsKeyDown(KEY_C)){
                BeginTextureMode(canvas);
                ClearBackground(WHITE);
                EndTextureMode();
            } else if (IsKeyDown(KEY_S)) {
                Image image = LoadImageFromTexture(canvas.texture);
                ImageFlipVertical(&image);
                ExportImage(image, image_name);
                UnloadImage(image);
            } else if (IsKeyPressed(KEY_UP)){
                if (brush_size >= max_brush_size){
                    brush_size = max_brush_size;
                } else {
                    brush_size += 2.0;
                }
            } else if (IsKeyPressed(KEY_DOWN)){
                if(brush_size <= min_brush_size){
                    brush_size = min_brush_size;
                } else {
                    brush_size -= 2.0;
                }
            }

            //color handling
            if (IsKeyPressed(KEY_LEFT)) color_selected++;
            else if(IsKeyPressed(KEY_RIGHT)) color_selected--;

            if (color_selected >= MAX_COLOR_COUNT) color_selected = MAX_COLOR_COUNT -1 ;
            else if (color_selected < 0 ) color_selected = 0;





            // DrawText("A simple circle", 10, 10, 20, LIGHTGRAY);

            // DrawCircleV(mouse_pos, 20, MAROON);
        EndDrawing();
    }
    CloseWindow();       
    return 0;
}


