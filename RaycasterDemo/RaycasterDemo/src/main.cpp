#include "raylib.h"

const int SCREEN_WIDTH = 1000, SCREEN_HEIGHT = 500;
float playerX, playerY, playerAngle, playerSize;
Color playerColour;

int map[6][7] = { {1, 1, 1, 1, 1, 1, 1},
				  {1, 0, 0, 0, 0, 0, 1},
				  {1, 0, 1, 0, 0, 0, 1},
				  {1, 0, 1, 0, 0, 0, 1},
				  {1, 0, 1, 0, 0, 0, 1},
				  {1, 1, 1, 1, 1, 1, 1} };
int squareSize = 64;
const int ROW_SIZE = 6;
const int COL_SIZE = 7;

void initPlayer()
{
	playerX = 500.0f;
	playerY = 250.0f;
	playerSize = 10.0f;
	playerColour = YELLOW;
}

void init()
{
	initPlayer();

}

void update()
{
	if (IsKeyDown(KEY_W)) {playerY -= 0.05;}
	if (IsKeyDown(KEY_S)) {playerY += 0.05;}
	if (IsKeyDown(KEY_A)) {playerX -= 0.05;}
	if (IsKeyDown(KEY_D)) {playerX += 0.05;}
}

void draw()
{
	BeginDrawing();
	
		ClearBackground(GRAY);

		DrawRectangle(playerX, playerY, playerSize, playerSize, playerColour);

		for (int row = 0; row < ROW_SIZE; row++)
		{
			for (int col = 0; col < COL_SIZE; col++)
			{
				if (map[row][col] == 1)
				{
					DrawRectangle(col * squareSize, row * squareSize, squareSize, squareSize, WHITE);
				}
			}
		}

	EndDrawing();
}

int main() {

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raycaster Demo");

	init();

	while (!WindowShouldClose())
	{
		update();
		draw();
	}

	CloseWindow();

	return 0;
}