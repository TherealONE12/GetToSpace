/*
 ============================================================================
 Name        : RayLib.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "raymath.h"


int main(void)
{
	// TODO 1: Hier musst du die Window-Size definieren
	const int screenWidth = 1000;
	const int screenHeight = 1000;

	InitWindow(screenWidth, screenHeight, "Mein erstes Game - lets gooo Hitboxes!!! in nur 2 tries");

	SetTargetFPS(60);

	Rectangle ballPosition; //{ 450, 500, 25, 25};
	ballPosition.x=450;
	ballPosition.y=500;
	ballPosition.width=25;
	ballPosition.height=25;


	Rectangle startplatt; //{50, 800,900, 25};
	startplatt.x=50;
	startplatt.y=800;
	startplatt.width=900;
	startplatt.height=25;

	Rectangle obstacle1 = {700,700,100,100};
	Rectangle obstacle2 = {300,700,100,100};
	int PressedKey = 0;
	int PressedKeymin1 =0;



	// Game loop
	while (!WindowShouldClose())
	{
		BeginDrawing();
		DrawFPS(50, 50);

		DrawRectangle(startplatt.x,startplatt.y,startplatt.width,startplatt.height, BLACK);
		DrawRectangle(obstacle1.x, obstacle1.y, obstacle1.width, obstacle1.height, RED);
		DrawRectangle(obstacle2.x, obstacle2.y, obstacle2.width, obstacle2.height, RED);

		//TODO: Update logic to support stopping...
		PressedKeymin1 = PressedKey;
		PressedKey = GetKeyPressed();
		if(PressedKey==0){
			PressedKey = PressedKeymin1;
		}

		if(PressedKey==KEY_RIGHT){
			ballPosition.x++;
		}else if(PressedKey==KEY_LEFT){
			ballPosition.x--;
		}


		//Todo: Update Collision logic, it sucks
		if(GetCollisionRec(startplatt, ballPosition)){
			ballPosition.y --;
			DrawRectangleGradientEx(ballPosition, GREEN, BLUE, PURPLE, GRAY);
		}else{
			ballPosition.y ++;
			DrawRectangleGradientEx(ballPosition, GREEN, BLUE, PURPLE, GRAY);
		}














		ClearBackground(RAYWHITE);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}

