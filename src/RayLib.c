/*
 ============================================================================
 Name        : RayLib.c
 Author      : Jakcom
 Version     : V0.0.1
 Copyright   : Your copyright notice
 Description : A game, In Pure C
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "raymath.h"
#include <stdarg.h> //Infinit arguments, Infinit Power

enum {
	up,
	down,
	left,
	right
} direction;


Rectangle GetClosestRect(int amount, ..., Rectangle Player, direction direction);

int main(void)
{
	// TODO 1: Hier musst du die Window-Size definieren
	const int screenWidth = 1000;
	const int screenHeight = 1000;

	InitWindow(screenWidth, screenHeight, "Mein erstes Game - lets gooo Hitboxes!!! in nur 2 tries");

	SetTargetFPS(60);

	Rectangle PlayerPosition = { 450, 500, 25, 25};

	Rectangle startplatt = {50, 800,900, 25};


	Rectangle obstacle1 = {700,700,100,100};
	Rectangle obstacle2 = {300,700,100,100};


	//movement V2
	float velocityX = 0;
	float velocityY = 0;
	float jump = 0;
	float gravity = 0.5f;
	bool Nogravity = false;

	// Game loop
	while (!WindowShouldClose())
	{
		BeginDrawing();
		DrawFPS(50, 50);

		DrawRectangle(startplatt.x,startplatt.y,startplatt.width,startplatt.height, BLACK);
		DrawRectangle(obstacle1.x, obstacle1.y, obstacle1.width, obstacle1.height, RED);
		DrawRectangle(obstacle2.x, obstacle2.y, obstacle2.width, obstacle2.height, RED);

		if(IsKeyDown(KEY_D)){
			if(velocityX < 5){
				velocityX += 1;
			}else{
				velocityX = 5;
			}
		}else if(IsKeyDown(KEY_A)){
			if(velocityX > -5){
				velocityX -= 1;
			}else{
				velocityX = -5;
			}
		}else if(IsKeyDown(KEY_W)){
			if(jump > -15){
				jump -= 3;
			}else{
				jump = -15;
			}
		}





		if(CheckCollisionRecs(GetClosestRect(3, startplatt, obstacle1, obstacle2, PlayerPosition, up), PlayerPosition)){
			jump = 0;
		}
		if(CheckCollisionRecs(GetClosestRect(3, startplatt, obstacle1, obstacle2, PlayerPosition, right), PlayerPosition)){
			if(velocityX >0){
				velocityX = 0;
			}
		}
		if(CheckCollisionRecs(GetClosestRect(3, startplatt, obstacle1, obstacle2, PlayerPosition, down), PlayerPosition)){
			Nogravity=True;
		}
		if(CheckCollisionRecs(GetClosestRect(3, startplatt, obstacle1, obstacle2, PlayerPosition, left), PlayerPosition)){
			if(velocityX < 0){
				velocityX = 0;
			}
		}

		velocityX = velocityX - velocityX *0.1f;
		jump = jump - jump * 0.1f;

		if(Nogravity){
			velocityY = velocityY - velocityY *0.1f;
			PlayerPosition.y += velocityY + jump;
		}else{
			velocityY = velocityY - velocityY *0.1f + gravity;
			PlayerPosition.y += velocityY;
		}

		PlayerPosition.x += velocityX;



		DrawRectangleGradientEx(PlayerPosition, GREEN, BLUE, PURPLE, GRAY);

		ClearBackground(RAYWHITE);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}


Rectangle GetClosestRect(int amount, ..., Rectangle Player, direction direction){
	va_list arguments;
	va_start(arguments, amount);

	Rectangle closest;
	Rectangle parameter;

	bool firstargument = true;
	bool under = false;
	int mindis = 0;
	bool firstrun = true;


	for(int i = 0; i < amount; ++i ){
		parameter = va_arg(arguments, Rectangle);
		if(firstargument){
			closest = parameter;
			firstargument = false;
		}else{
			if(direction == up){
				if((Player.y - parameter.y + parameter.height) < (Player.y - closest.y + closest.height)){
					for(int i = 0; i < Player.width; i++){
						if(parameter.x < Player.x + i < (parameter.x + parameter.width)){
							under = True;
							break;
						}
					}
					if(under){
						closest = parameter;
						under = false;
					}
				}
			} else if (direction == right){
				if(!(parameter.x - Player.x + Player.width) >= 0){
					if(firstrun){
						mindis = parameter.x - Player.x + Player.width;
					}else{
						if((parameter.x - Player.x + Player.width) < mindis){
							mindis = parameter.x - Player.x + Player.width;
						}
					}
				}
			} else if (direction == down){
				if((parameter.y - Player.y+ Player.height) < (closest.y - Player.y + Player.height)){
					for(int i = 0; i < Player.width; i++){
						if(parameter.x < Player.x + i < (parameter.x + parameter.width)){
							under = True;
							break;
						}
					}
					if(under){
						closest = parameter;
						under = false;
					}
				}
			} else if (direction == left){
				if(!(Player.x - parameter.x + parameter.width) >= 0){
					if(firstrun){
						mindis = Player.x - parameter.x + parameter.width;
					}else{
						if((Player.x - parameter.x + parameter.width) < mindis){
							mindis = Player.x - parameter.x + parameter.width;
						}
					}
				}
			}
		}
	}

	va_end(arguments);
	return closest;
}



