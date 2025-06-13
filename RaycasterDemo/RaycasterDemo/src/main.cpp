#include "raylib.h"
#include <iostream>

const int SCREEN_WIDTH = 1000, SCREEN_HEIGHT = 500;
float playerX, playerY, playerAngle, playerSize, playerDX, playerDY, playerSpeed;
Color playerColour;
Vector2 playerVelocity;

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
	playerX = 200.0f;
	playerY = 250.0f;
	playerSize = 10.0f;
	playerColour = YELLOW;
	playerSpeed = 100.0f;
	playerDX = cos(playerAngle) * 5; playerDY = sin(playerAngle) * 5;
}

void init()
{
	initPlayer();

}

void input()
{
	playerVelocity = { 0,0 };
	if (IsKeyDown(KEY_W)) { playerVelocity.x += playerDX / playerSpeed; playerVelocity.y += playerDY/ playerSpeed;}
	if (IsKeyDown(KEY_S)) { playerVelocity.x -= playerDX / playerSpeed; playerVelocity.y -= playerDY / playerSpeed; }
	if (IsKeyDown(KEY_D)) { playerAngle += 0.001; if (playerAngle >= 2 * PI) { playerAngle = 0; } playerDX = cos(playerAngle) * 5; playerDY = sin(playerAngle) * 5; }
	if (IsKeyDown(KEY_A)) { playerAngle -= 0.001; if (playerAngle <= 0) { playerAngle = 2 * PI; } playerDX = cos(playerAngle) * 5; playerDY = sin(playerAngle) * 5; }
}

void collision() 
{
	float tempX = playerX + playerVelocity.x;
	float tempY = playerY + playerVelocity.y;
	bool collide = false;

	for (int row = 0; row < ROW_SIZE; row++)
	{
		if (collide)
		{
			std::cout << "collide\n";
			break;
		}

		for (int col = 0; col < COL_SIZE; col++)
		{
			if ((tempX + playerSize >= col * squareSize && tempX <= (col * squareSize) + squareSize) &&
				(tempY + playerSize >= row * squareSize && tempY <= (row * squareSize) + squareSize) &&
				map[row][col] == 1)
			{
				collide = true;
				break;
			}
			else
			{
				collide = false;
			}
		}
	}

	if (!collide)
	{
		playerX += playerVelocity.x;
		playerY += playerVelocity.y;
	}
	else
	{
		playerX -= playerVelocity.x;
		playerY -= playerVelocity.y;
	}
}

void update()
{
	input();
	collision();
	
	playerX += playerVelocity.x;
	playerY += playerVelocity.y;
}

void draw()
{
	BeginDrawing();
	
		ClearBackground(GRAY);

		DrawRectangle(playerX, playerY, playerSize, playerSize, playerColour);
		DrawLine(playerX + +(playerSize / 2.0f), playerY + +(playerSize / 2.0f), playerX + playerDX * 10, playerY + playerDY * 10, RED);

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