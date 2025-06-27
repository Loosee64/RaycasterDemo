#include "raylib.h"
#include <iostream>

const int SCREEN_WIDTH = 1000, SCREEN_HEIGHT = 500;
float playerX, playerY, playerAngle, playerSize, playerDX, playerDY, playerSpeed;
Color playerColour;
Vector2 playerVelocity;

int map[6][7] = { {1, 1, 1, 0, 1, 1, 1},
				  {1, 0, 0, 0, 0, 0, 1},
				  {1, 0, 0, 0, 0, 0, 1},
				  {1, 0, 1, 0, 0, 0, 1},
				  {1, 0, 1, 0, 0, 0, 1},
				  {1, 1, 1, 1, 1, 1, 1} };
int squareSize = 64;
const int ROW_SIZE = 6;
const int COL_SIZE = 7;
float rx, ry, ra, xo, yo;

void initPlayer()
{
	playerX = 200.0f;
	playerY = 250.0f;
	playerSize = 10.0f;
	playerColour = YELLOW;
	playerSpeed = 100.0f;
	playerAngle = 3.14;
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

void rayCalc()
{
	
	int r, dof, mx, my;

	ra = playerAngle;
	for (r = 0; r < 1; r++)
	{
		 //---- Horizontal Lines ----
		//dof = 0;
		//float aTan = -1/tan(ra);
		//if (ra < PI) // Looking Up
		//{
		//	ry = (((int)playerY >> 6) << 6); // Rounding ry to nearest 64
		//	rx = (ry - playerY) * aTan + playerX;
		//	yo = -squareSize;
		//	xo = yo * aTan;
		//	if (xo > SCREEN_WIDTH)
		//	{
		//		xo = SCREEN_WIDTH;
		//	}
		//	if (xo < 0)
		//	{
		//		xo = 0;
		//	}
		//}

		//if (ra > PI) // Looking Down
		//{
		//	ry = (((int)playerY >> 6) << 6) + squareSize; // Rounding ry to nearest 64
		//	rx = (ry - playerY) * aTan + playerX;
		//	yo = squareSize;
		//	xo = yo * aTan;
		//	if (xo > SCREEN_WIDTH)
		//	{
		//		xo = SCREEN_WIDTH;
		//	}
		//	if (xo < -SCREEN_WIDTH)
		//	{
		//		xo = -SCREEN_WIDTH;
		//	}

		//}

		//if (ra == 3.14 || ra == 0)
		//{
		//	rx = playerX;
		//	ry = playerY;
		//	dof = 8;
		//}

		//if (rx > squareSize * 7)
		//{
		//	rx = squareSize * 6;
		//}

		//if (rx < 0)
		//{
		//	rx = 0;
		//}

		//mx = rx / squareSize;
		//my = ry / squareSize;


		//while (dof < 8)
		//{
		//	mx = rx / squareSize;
		//	my = ry / squareSize;


		//	if (map[my][mx] == 1 || map[my - 1][mx] == 1)
		//	{
		//		dof = 8;
		//		std::cout << rx << " " << ry << " " << map[my][mx] << "\n";
		//	}
		//	else
		//	{
		//		rx += xo;
		//		ry += yo;
		//		dof += 1;
		//	}
		//}


		// ---- Vertical Lines ----
		dof = 0;
		float nTan = -tan(ra);
		if (ra > PI / 2 && ra < (3 * PI) / 2) // Looking Left
		{
			rx = (((int)playerX >> 6) << 6); // Rounding ry to nearest 64
			ry = (rx - playerX) * nTan + playerY;
			xo = -squareSize;
			yo = xo * nTan;
		}

		if (ra < PI / 2 || ra > (3 * PI) / 2) // Looking Right
		{
			rx = (((int)playerX >> 6) << 6) + squareSize; // Rounding ry to nearest 64
			ry = (rx - playerX) * nTan + playerY;
			xo = squareSize;
			yo = xo * nTan;

		}

		if (ra == PI / 2 || ra == (3 * PI) / 2)
		{
			rx = playerX;
			ry = playerY;
			dof = 8;
		}

		if (yo > squareSize * 7)
		{
			yo = squareSize * 6;
		}

		if (ry < 0)
		{
			ry = 0;
		}

		mx = rx / squareSize;
		my = ry / squareSize;


		while (dof < 8)
		{
			mx = rx / squareSize;
			my = ry / squareSize;


			if (map[my][mx] == 1 || map[my][mx - 1] == 1)
			{
				dof = 8;
				std::cout << rx << " " << ry << " " << map[my][mx] << "\n";
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}

	}
}

void update()
{
	input();
	collision();
	rayCalc();
	
	playerX += playerVelocity.x;
	playerY += playerVelocity.y;
}

void draw()
{
	BeginDrawing();
	
		ClearBackground(GRAY);

		for (int row = 0; row < ROW_SIZE; row++)
		{
			for (int col = 0; col < COL_SIZE; col++)
			{
				if (map[row][col] == 1)
				{
					DrawRectangle(col * squareSize, row * squareSize, squareSize - 1, squareSize - 1, WHITE);
				}
				if (map[row][col] == 0)
				{
					DrawRectangle(col * squareSize, row * squareSize, squareSize - 1, squareSize - 1, BLACK);
				}
			}
		}

		DrawRectangle(playerX, playerY, playerSize, playerSize, playerColour);
		DrawLine(playerX, playerY, rx, ry, RED);
		DrawRectangle(rx, ry, playerSize, playerSize, RED);
		//DrawLine(playerX + +(playerSize / 2.0f), playerY + +(playerSize / 2.0f), playerX + playerDX * 10, playerY + playerDY * 10, RED);*

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