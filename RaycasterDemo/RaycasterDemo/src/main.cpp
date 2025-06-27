#include "raylib.h"
#include <iostream>
#define DR 0.0174533 // one degree in radians

const int SCREEN_WIDTH = 1000, SCREEN_HEIGHT = 500;
float playerX, playerY, playerAngle, playerSize, playerDX, playerDY, playerSpeed;
Color playerColour;
Vector2 playerVelocity;

int map[6][7] = { {1, 1, 1, 1, 1, 1, 1},
				  {1, 0, 0, 0, 0, 0, 1},
				  {1, 0, 0, 0, 0, 0, 1},
				  {1, 0, 1, 0, 0, 0, 1},
				  {1, 0, 1, 0, 0, 0, 1},
				  {1, 1, 1, 1, 1, 1, 1} };
int squareSize = 64;
const int ROW_SIZE = 6;
const int COL_SIZE = 7;
float rx, ry, ra, xo, yo, vx, vy, hx, hy;

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

float distance(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void rayCalc()
{
	float distH = 100000, distV = 100000, distF;
	int r, dof, mx, my;

	ra = -playerAngle + (DR * 180) - (DR * 30);
	if (ra < 0)
	{
		ra += 2 * PI;
	}
	else if (ra > 2 * PI)
	{
		ra = 0;
	}
	for (r = 0; r < 60; r++)
	{
		 //---- Horizontal Lines ----
		dof = 0;
		float aTan = -1/tan(ra);
		if (ra > PI) // Looking Up
		{
			ry = (((int)playerY >> 6) << 6); // Rounding ry to nearest 64
			rx = (ry - playerY) * aTan + playerX;
			yo = -squareSize;
			xo = yo * aTan;
			if (xo > SCREEN_WIDTH)
			{
				xo = SCREEN_WIDTH;
			}
			if (xo < 0)
			{
				xo = 0;
			}
		}

		if (ra < PI) // Looking Down
		{
			ry = (((int)playerY >> 6) << 6) + squareSize; // Rounding ry to nearest 64
			rx = (ry - playerY) * aTan + playerX;
			yo = squareSize;
			xo = yo * aTan;
			if (xo > SCREEN_WIDTH)
			{
				xo = SCREEN_WIDTH;
			}
			if (xo < -SCREEN_WIDTH)
			{
				xo = -SCREEN_WIDTH;
			}

		}

		if (ra == 3.14 || ra == 0)
		{
			rx = playerX;
			ry = playerY;
			dof = 8;
		}

		if (rx > squareSize * 7)
		{
			rx = squareSize * 6;
		}

		if (rx < 0)
		{
			rx = 0;
		}

		mx = rx / squareSize;
		my = ry / squareSize;


		while (dof < 8)
		{
			mx = rx / squareSize;
			my = ry / squareSize;


			if (map[my][mx] == 1 || map[my - 1][mx] == 1)
			{
				dof = 8;
				hx = rx;
				hy = ry;
				distH = distance(playerX, playerY, hx, hy);
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}


		// ---- Vertical Lines ----
		dof = 0;
		float nTan = -tan(ra);
		if (ra < PI / 2 || ra > (3 * PI) / 2) // Looking Left
		{
			rx = (((int)playerX >> 6) << 6); // Rounding ry to nearest 64
			ry = (rx - playerX) * nTan + playerY;
			xo = -squareSize;
			yo = xo * nTan;
		}

		if (ra > PI / 2 && ra < (3 * PI) / 2) // Looking Right
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

			if (my > 6)
			{
				my = 6;
			}

			if (map[my][mx] == 1 || map[my][mx - 1] == 1) // be careful of mx - 1
			{
				dof = 8;
				vx = rx;
				vy = ry;
				distV = distance(playerX, playerY, vx, vy);
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}

		if (distV > distH)
		{
			rx = hx;
			ry = hy;
			distF = distH;
		}
		else if (distH > distV)
		{
			rx = vx;
			ry = vy;
			distF = distV;
		}
		else
		{
			distF = 552;
		}

		DrawLine(playerX, playerY, rx, ry, RED);

		// ---- Drawing 3D Walls ----
		float lineH = (squareSize * 320) / distF;
		float lineO = 250 - lineH / 2;
		if (lineH > 320)
		{
			lineH = 320;
		}
		DrawLineEx(Vector2{(float)r * 8 + 552, lineO }, Vector2{(float)r * 8 + 552, lineH + lineO },8 , RED);

		ra += DR;
		if (ra < 0)
		{
			ra += 2 * PI;
		}
		else if (ra > 2 * PI)
		{
			ra = 0;
		}
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

		rayCalc();

		DrawRectangle(playerX, playerY, playerSize, playerSize, playerColour);	
		DrawRectangle(rx, ry, playerSize, playerSize, RED);
		DrawLine(playerX , playerY, playerX + playerDX, playerY + playerDY, YELLOW);
		//DrawLine(playerX + +(playerSize / 2.0f), playerY + +(playerSize / 2.0f), playerX + playerDX * 10, playerY + playerDY * 10, RED);*

	EndDrawing();
}

int main() {

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raycaster Demo");

	init();

	while (!WindowShouldClose())
	{
		draw();
		update();
	}

	CloseWindow();

	return 0;
}