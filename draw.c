
#include <stdio.h>
#include "raylib.h"
#include <time.h>
#define MAX_COLOR_COUNT  8
#define BACKGROUND_COLOR (Color) {152, 161, 188, 255}
#define TEXT_COLOR (Color) {41, 44, 78, 255} 

int main(void)
{
    const int screenWidth = 1024;
    const int screenHeight = 760;
    float brush_size = 20.0f;
    float max_brush_size = 60.0f;
    float min_brush_size = 10.0;
    Color colors[MAX_COLOR_COUNT] = {
        BLACK, RED, GREEN, YELLOW, BLUE, PINK, BROWN, ORANGE
    };
    int color_selected = 0;

    //Save and clear
    Rectangle btn_save = {778, 150, 84, 40};
    bool btn_save_mouse_hover = false; 
    Rectangle btn_clear = {884, 150, 84, 40};
    bool btn_clear_mouse_hover = false;

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
    
    //define color recs data
    Rectangle colors_recs[MAX_COLOR_COUNT] = { 0 };

    int colors_per_raw = 4;
    int rect_width = 40;
    int rect_height = 40;
    int spacing = 4;
    int start_x = 788; //left margin
    int start_y = 50;

    for (int i = 0; i  < MAX_COLOR_COUNT; i++)
    {
        int row = i / colors_per_raw;
        int col = i % colors_per_raw;
        colors_recs[i].x = start_x + (rect_width + spacing) * col;
        colors_recs[i].y = start_y + (rect_height + spacing) * row;
        colors_recs[i].width = rect_width;
        colors_recs[i].height = rect_height;
    }

    InitWindow(screenWidth, screenHeight, "simple art");

    // Vector2 ball_pos  = {(float)screenWidth/2, (float)screenHeight/2}; 

    RenderTexture2D canvas = LoadRenderTexture(screenWidth - 300, screenHeight);

    //clear texture before the loop
    BeginTextureMode(canvas);
    ClearBackground(RAYWHITE);
    EndTextureMode();

    SetTargetFPS(60);               

    while (!WindowShouldClose())   
    {
        Vector2 mouse_pos = GetMousePosition();

        BeginDrawing();
        

            ClearBackground(BACKGROUND_COLOR);
            DrawTextureRec(canvas.texture, (Rectangle){0, 0, (float)canvas.texture.width,(float)-canvas.texture.height }, (Vector2) {0, 0}, WHITE);


            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                BeginTextureMode(canvas);
                DrawCircle((int)GetMouseX(), (int)GetMouseY(), brush_size, colors[color_selected]);
                EndTextureMode();
            } else {
                // a circle for reference
                DrawCircle(GetMouseX(), GetMouseY(), brush_size, colors[color_selected] );
            }

            //check for hover
            if(CheckCollisionPointRec(mouse_pos, btn_save)) 
            {
                btn_save_mouse_hover = true;
            } else 
            {
                btn_save_mouse_hover = false;
            }
            if(CheckCollisionPointRec(mouse_pos, btn_clear))
            {
                btn_clear_mouse_hover = true;
            } else 
            {
                btn_clear_mouse_hover = false;
            }

            //keys controls
            if (IsKeyDown(KEY_C) || (btn_clear_mouse_hover && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))){
                BeginTextureMode(canvas);
                ClearBackground(WHITE);
                EndTextureMode();
            } else if (IsKeyDown(KEY_S) || (btn_save_mouse_hover && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))) {
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

            //Tools Panel- Ignore the hard coded numbers :)
            DrawRectangle(start_x - 10, start_y - 30, 192, 120, WHITE);
            DrawRectangleRec(btn_save, WHITE);
            DrawRectangleLinesEx(btn_save, 3, btn_save_mouse_hover ? RED : TEXT_COLOR);
            DrawText("SAVE!", 788, 160, 16, btn_save_mouse_hover ? RED : TEXT_COLOR);
                    
            DrawRectangleRec(btn_clear, WHITE);
            DrawRectangleLinesEx(btn_clear, 3, btn_clear_mouse_hover ? RED : TEXT_COLOR);
            DrawText("CLEAR", 894, 160, 16, btn_clear_mouse_hover ? RED : TEXT_COLOR);

            DrawText("COLORS:", start_x, start_y - 20, 16, TEXT_COLOR);
            for (int i = 0; i < MAX_COLOR_COUNT; i++){
                DrawRectangleRec(colors_recs[i], colors[i]);
            }



        EndDrawing();
    }
    CloseWindow();       
    return 0;
}


