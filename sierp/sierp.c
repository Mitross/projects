#include <stdio.h>
#include <raylib.h>
#include <math.h>

#define WIDTH 900
#define HEIGHT 600

#define START_SIDE_LEN 560.0
#define MAX_DEPTH 7
#define kostast 20

void draw_triangle(Vector2 top, float side_len){
	float y = top.y + side_len * sinf(60 * DEG2RAD);
        Vector2 bottom_left = (Vector2){top.x - side_len/2, y};
        Vector2 bottom_right = (Vector2){top.x + side_len/2 , y};

	DrawTriangle(top, bottom_left, bottom_right, WHITE);	
}



void sierptriangle(Vector2 top, float side_len,int max_depth, int current_depth){
	
	if(current_depth >= max_depth){
		draw_triangle(top,side_len);
		return;
	}
	
	current_depth++;

	float y = top.y + side_len/2 * sinf(60 * DEG2RAD);
	Vector2 bottom_left = (Vector2){top.x - side_len/4, y};
	Vector2 bottom_right = (Vector2){top.x + side_len/4, y};

	sierptriangle(top, side_len/2, max_depth, current_depth);
	sierptriangle(bottom_left, side_len/2, max_depth, current_depth);
	sierptriangle(bottom_right, side_len/2, max_depth, current_depth);
}


int main(){
	InitWindow(WIDTH,HEIGHT,"SIERPINSKI TRIANGLE");
	
	SetTargetFPS(60);

	int depth =0;
	float animation_interval = 0;
	while(!WindowShouldClose()){
		
		if (IsKeyPressed(KEY_SPACE))
			depth = 0;

		animation_interval += GetFrameTime();
		if(animation_interval > 1.0){
			animation_interval = 0;
			if(depth <= MAX_DEPTH)
				depth++;
		}

		//do something
		BeginDrawing();

		ClearBackground(BLACK);

		Vector2 top = (Vector2){WIDTH/2, 50};
		sierptriangle(top, START_SIDE_LEN, depth, 1);


		EndDrawing();
	}

	CloseWindow();
	return 0;
}
