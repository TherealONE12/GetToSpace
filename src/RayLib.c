/*
 ============================================================================
 Name        : RayLib.c
 Author      : Jakcom
 Version     : V0.0.1
 Copyright   : MIT
 Description : A game, In Pure C
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "raymath.h"
#include <stdarg.h> //Infinit arguments, Infinit Power

enum Direction{
	up,
	down,
	left,
	right
};

//movement V2
float velocityX = 0;
float velocityY = 0;
float jump = 0;
float gravity = 0.5f;
bool Nogravity = false;
bool debug = true;

Rectangle Death = {-1000, 900, 3000, 10};
Rectangle PlayerPosition = { 150, 500, 25, 25};

//Helper stuff
Rectangle GetClosestRect(Rectangle Player, enum Direction direction, int amount, ...);

//Level Loops
int Level1Loop(void);
int Level2Loop(void);
int Level3Loop(void);
int Level4Loop(void);
int Level5Loop(void);

int main(void)
{
	// TODO 1: Hier musst du die Window-Size definieren
	const int screenWidth = 1000;
	const int screenHeight = 1000;

	InitWindow(screenWidth, screenHeight, "GetToSpace");

	SetTargetFPS(60);




	int levelcnt = 5;
	// Game loop
	while (!WindowShouldClose())
	{
		BeginDrawing();
		switch (levelcnt) {
		case 1:
			if(Level1Loop() == 1){
				levelcnt++;
				ClearBackground(RAYWHITE);
			}
			break;
		case 2:
			if(Level2Loop() == 1){
				levelcnt++;
				ClearBackground(RAYWHITE);
			}
			break;
		case 3:
			if(Level3Loop() == 1){
				levelcnt++;
				ClearBackground(RAYWHITE);
			}
			break;
		case 4:
			if(Level4Loop() == 1){
				levelcnt++;
				ClearBackground(RAYWHITE);
			}
			break;
		case 5:
			if(Level5Loop() == 1){
				levelcnt++;
				ClearBackground(RAYWHITE);
			}
			break;
		default:
			break;
		}




		EndDrawing();
	}

	CloseWindow();

	return 0;
}


int Level1Loop(void){
	//Objekts
	Rectangle startplatt = {50, 800,900, 25};
	Rectangle Goal = {770, 750, 25,25};



	DrawRectangle(startplatt.x,startplatt.y,startplatt.width,startplatt.height, BLACK);
	DrawRectangle(Death.x, Death.y, Death.width, Death.height, RED);
	DrawRectangleRec(Goal, GOLD);



	if(CheckCollisionRecs(PlayerPosition, Goal)){
		PlayerPosition.x = 150;
		PlayerPosition.y = 500;
		return 1;
	} else{
		DrawFPS(50, 50);


		DrawText("Look at the Stars. Aren't they Beatiful? I wanna try to get to them!", 300, 700, 15 , GREEN);


		if(IsKeyDown(KEY_D)){
			velocityX = Clamp(velocityX + 1, -5, 5);
		}else if(IsKeyDown(KEY_A)){
			velocityX = Clamp(velocityX - 1, -5, 5);
		}


		if(IsKeyPressed(KEY_W) && Nogravity){
			velocityY = -15;
		}

		Nogravity = false;
		if(CheckCollisionRecs(startplatt, PlayerPosition)){
			Nogravity = true;
			if(velocityY > 0){
				velocityY = 0;
			}
		}



		velocityX = velocityX - velocityX *0.1f;
		if(!IsKeyDown(KEY_W)){
			jump = jump - (jump * 0.1f);
		}


		if(Nogravity){
			velocityY = velocityY - velocityY *0.1f;
			PlayerPosition.y += velocityY + jump;
		}else{
			velocityY = velocityY - velocityY *0.1f + gravity;
			PlayerPosition.y += velocityY;
		}

		PlayerPosition.x += velocityX;


		// Movement
		velocityX *= 0.9f;
		if(!Nogravity){
			velocityY += gravity;
		}
		velocityY *= 0.98f;


		if ((PlayerPosition.y + PlayerPosition.height) > Death.y){ //Death
			PlayerPosition.x = 450;
			PlayerPosition.y = 500;
		}

		DrawRectangleGradientEx(PlayerPosition, GREEN, BLUE, PURPLE, GRAY);

		ClearBackground(RAYWHITE);
	}
	return -1;
}

int Level2Loop(void){
	//Objekts
	Rectangle startplatt = {50, 800,300, 25};
	Rectangle startplatt2 = {450, 800,400, 25};
	Rectangle Goal = {770, 750, 25,25};



	DrawRectangle(startplatt.x,startplatt.y,startplatt.width,startplatt.height, BLACK);
	DrawRectangle(startplatt2.x,startplatt2.y,startplatt2.width,startplatt2.height, BLACK);
	DrawRectangle(Death.x, Death.y, Death.width, Death.height, RED);
	DrawRectangleRec(Goal, GOLD);



	if(CheckCollisionRecs(PlayerPosition, Goal)){
		PlayerPosition.x = 150;
		PlayerPosition.y = 500;
		return 1;
	} else{
		DrawFPS(50, 50);


		DrawText("The Higher  you go, the Higher you Jump!", 300, 700, 15 , GREEN);


		if(IsKeyDown(KEY_D)){
			velocityX = Clamp(velocityX + 1, -5, 5);
		}else if(IsKeyDown(KEY_A)){
			velocityX = Clamp(velocityX - 1, -5, 5);
		}


		if(IsKeyPressed(KEY_W) && Nogravity){
			velocityY = -20;
		}

		Nogravity = false;
		if(CheckCollisionRecs(startplatt, PlayerPosition)){
			Nogravity = true;
			if(velocityY > 0){
				velocityY = 0;
			}
		} else if(CheckCollisionRecs(startplatt2, PlayerPosition)){
			Nogravity = true;
			if(velocityY > 0){
				velocityY = 0;
			}
		}



		velocityX = velocityX - velocityX *0.1f;
		if(!IsKeyDown(KEY_W)){
			jump = jump - (jump * 0.1f);
		}


		if(Nogravity){
			velocityY = velocityY - velocityY *0.1f;
			PlayerPosition.y += velocityY + jump;
		}else{
			velocityY = velocityY - velocityY *0.1f + gravity;
			PlayerPosition.y += velocityY;
		}

		PlayerPosition.x += velocityX;


		// Movement
		velocityX *= 0.9f;
		if(!Nogravity){
			velocityY += gravity;
		}
		velocityY *= 0.98f;


		if ((PlayerPosition.y + PlayerPosition.height) > Death.y){ //Death
			PlayerPosition.x = 150;
			PlayerPosition.y = 500;
		}

		DrawRectangleGradientEx(PlayerPosition, GREEN, BLUE, PURPLE, GRAY);

		ClearBackground(RAYWHITE);
	}
	return -1;
}

int Level3Loop(void){



	//Objekts
	Rectangle startplatt = {50, 800,900, 25};
	Rectangle obstacle1 = {700,700,100,100};
	Rectangle obstacle2 = {300,700,100,100};
	Rectangle Goal = {770, 650, 25,25};

	DrawRectangle(startplatt.x,startplatt.y,startplatt.width,startplatt.height, BLACK);
	DrawRectangle(obstacle1.x, obstacle1.y, obstacle1.width, obstacle1.height, BLUE);
	DrawRectangle(obstacle2.x, obstacle2.y, obstacle2.width, obstacle2.height, BLUE);
	DrawRectangle(Death.x, Death.y, Death.width, Death.height, RED);
	DrawRectangleRec(Goal, GOLD);

	if(CheckCollisionRecs(PlayerPosition, Goal)){
		PlayerPosition.x = 50;
		PlayerPosition.y = 500;
		return 1;
	} else{
		DrawFPS(50, 50);

		DrawText("Cosmic is Weird. Once you think you understand it, it suprises you even more!", 300, 600, 15 , GREEN);



		if(IsKeyDown(KEY_D)){
			velocityX = Clamp(velocityX + 1, -5, 5);
		}else if(IsKeyDown(KEY_A)){
			velocityX = Clamp(velocityX - 1, -5, 5);
		}


		if(IsKeyPressed(KEY_W) && Nogravity){
			velocityY = -15;
		}


		Nogravity = false;

		if(CheckCollisionRecs(GetClosestRect(PlayerPosition, right, 3, startplatt, obstacle1, obstacle2), PlayerPosition)){
			if(velocityX >0){
				velocityX = 0;
			}
		}

		if(CheckCollisionRecs(GetClosestRect(PlayerPosition, left, 3, startplatt, obstacle1, obstacle2), PlayerPosition)){
			if(velocityX < 0){
				velocityX = 0;
			}
		}
		Nogravity = false;
		if(CheckCollisionRecs(GetClosestRect(PlayerPosition, down, 3, startplatt, obstacle1, obstacle2), PlayerPosition)){
			Nogravity = true;
			if(velocityY > 0){
				velocityY = 0;
			}
		}
		if(debug){
			DrawRectangleLinesEx(GetClosestRect(PlayerPosition, left, 3, startplatt, obstacle1, obstacle2), 5, GRAY);
			DrawRectangleLinesEx(GetClosestRect(PlayerPosition, down, 3, startplatt, obstacle1, obstacle2), 5, GRAY);
			DrawRectangleLinesEx(GetClosestRect(PlayerPosition, right, 3, startplatt, obstacle1, obstacle2), 5, GRAY);



		}


		velocityX = velocityX - velocityX *0.1f;
		if(!IsKeyDown(KEY_W)){
			jump = jump - (jump * 0.1f);
		}


		if(Nogravity){
			velocityY = velocityY - velocityY *0.1f;
			PlayerPosition.y += velocityY + jump;
		}else{
			velocityY = velocityY - velocityY *0.1f + gravity;
			PlayerPosition.y += velocityY;
		}

		PlayerPosition.x += velocityX;


		// Movement
		velocityX *= 0.9f;
		if(!Nogravity){
			velocityY += gravity;
		}
		velocityY *= 0.98f;


		if ((PlayerPosition.y + PlayerPosition.height) > Death.y){ //Death
			PlayerPosition.x = 150;
			PlayerPosition.y = 500;
		}

		DrawRectangleGradientEx(PlayerPosition, GREEN, BLUE, PURPLE, GRAY);

		ClearBackground(RAYWHITE);
	}
	return -1;
}

int Level4Loop(void){
	//Objekts
	Rectangle startplatt = {50, 800,100, 25};
	Rectangle jump1 = {200, 750, 100 ,25};
	Rectangle jump2 = {350, 700, 60 ,25};
	Rectangle jump3= {450, 650, 40 ,25};
	Rectangle jump4 = {550, 700, 100 ,25};
	Rectangle jump5 = {750, 800, 100 ,25};
	Rectangle Goal = {770, 750, 25,25};


	DrawRectangle(startplatt.x,startplatt.y,startplatt.width,startplatt.height, BLACK);
	DrawRectangle(Death.x, Death.y, Death.width, Death.height, RED);

	DrawRectangleRec(jump1, BLACK);
	DrawRectangleRec(jump2, BLACK);
	DrawRectangleRec(jump3, BLACK);
	DrawRectangleRec(jump4, BLACK);
	DrawRectangleRec(jump5, BLACK);


	DrawRectangleRec(Goal, GOLD);




	if(CheckCollisionRecs(PlayerPosition, Goal)){
		PlayerPosition.x = 150;
		PlayerPosition.y = 500;
		return 1;
	} else{
		DrawFPS(50, 50);


		DrawText("If you Go Up or Down, the Beauty of Space never leaves!", 300, 500, 15 , GREEN);


		if(IsKeyDown(KEY_D)){
			velocityX = Clamp(velocityX + 1, -5, 5);
		}else if(IsKeyDown(KEY_A)){
			velocityX = Clamp(velocityX - 1, -5, 5);
		}


		if(IsKeyPressed(KEY_W) && Nogravity){
			velocityY = -15;
		}


		Nogravity = false;


		if(CheckCollisionRecs(startplatt, PlayerPosition)){
			Nogravity = true;
			if(velocityY > 0){
				velocityY = 0;
			}
		} else if(CheckCollisionRecs(jump1, PlayerPosition)){
			Nogravity = true;
			if(velocityY > 0){
				velocityY = 0;
			}
		} else if(CheckCollisionRecs(jump2, PlayerPosition)){
			Nogravity = true;
			if(velocityY > 0){
				velocityY = 0;
			}
		} else if(CheckCollisionRecs(jump3, PlayerPosition)){
			Nogravity = true;
			if(velocityY > 0){
				velocityY = 0;
			}
		} else if(CheckCollisionRecs(jump4, PlayerPosition)){
			Nogravity = true;
			if(velocityY > 0){
				velocityY = 0;
			}
		} else if(CheckCollisionRecs(jump5, PlayerPosition)){
			Nogravity = true;
			if(velocityY > 0){
				velocityY = 0;
			}
		}



		velocityX = velocityX - velocityX *0.1f;
		if(!IsKeyDown(KEY_W)){
			jump = jump - (jump * 0.1f);
		}


		if(Nogravity){
			velocityY = velocityY - velocityY *0.1f;
			PlayerPosition.y += velocityY + jump;
		}else{
			velocityY = velocityY - velocityY *0.1f + gravity;
			PlayerPosition.y += velocityY;
		}

		PlayerPosition.x += velocityX;


		// Movement
		velocityX *= 0.9f;
		if(!Nogravity){
			velocityY += gravity;
		}
		velocityY *= 0.98f;


		if ((PlayerPosition.y + PlayerPosition.height) > Death.y){ //Death
			PlayerPosition.x = 150;
			PlayerPosition.y = 500;
		}

		DrawRectangleGradientEx(PlayerPosition, GREEN, BLUE, PURPLE, GRAY);

		ClearBackground(RAYWHITE);
	}
	return -1;
}

int Level5Loop(void){

	//Objekts
	Rectangle startplatt = {50, 800,900, 25};
	Rectangle Death2 = {450, 775, 25,20};
	Rectangle Goal = {770, 750, 25,25};



	DrawRectangle(startplatt.x,startplatt.y,startplatt.width,startplatt.height, BLACK);
	DrawRectangle(Death.x, Death.y, Death.width, Death.height, RED);
	DrawRectangleRec(Death2, RED);
	DrawRectangleRec(Goal, GOLD);



	if(CheckCollisionRecs(PlayerPosition, Goal)){
		PlayerPosition.x = 150;
		PlayerPosition.y = 500;
		return 1;
	} else{
		DrawFPS(50, 50);


		DrawText("Space May Be dangerous", 300, 700, 15 , GREEN);


		if(IsKeyDown(KEY_D)){
			velocityX = Clamp(velocityX + 1, -5, 5);
		}else if(IsKeyDown(KEY_A)){
			velocityX = Clamp(velocityX - 1, -5, 5);
		}


		if(IsKeyPressed(KEY_W) && Nogravity){
			velocityY = -15;
		}


		Nogravity = false;

		if(CheckCollisionRecs(startplatt, PlayerPosition)){
			Nogravity = true;
			if(velocityY > 0){
				velocityY = 0;
			}
		}



		velocityX = velocityX - velocityX *0.1f;
		if(!IsKeyDown(KEY_W)){
			jump = jump - (jump * 0.1f);
		}


		if(Nogravity){
			velocityY = velocityY - velocityY *0.1f;
			PlayerPosition.y += velocityY + jump;
		}else{
			velocityY = velocityY - velocityY *0.1f + gravity;
			PlayerPosition.y += velocityY;
		}

		PlayerPosition.x += velocityX;


		// Movement
		velocityX *= 0.9f;
		if(!Nogravity){
			velocityY += gravity;
		}
		velocityY *= 0.98f;


		if ((PlayerPosition.y + PlayerPosition.height) > Death.y){ //Death
			PlayerPosition.x = 450;
			PlayerPosition.y = 500;
		}else if(CheckCollisionRecs(Death2, PlayerPosition)){
			PlayerPosition.x = 150;
			PlayerPosition.y = 500;
		}

		DrawRectangleGradientEx(PlayerPosition, GREEN, BLUE, PURPLE, GRAY);

		ClearBackground(RAYWHITE);
	}
	return -1;
}


Rectangle GetClosestRect(Rectangle Player, enum Direction direction, int amount, ...){
	va_list arguments;
	va_start(arguments, amount);

	Rectangle closest;
	Rectangle parameter;

	bool firstargument = true;
	bool under = false;
	float mindis = 0;
	bool firstrun = true;

	for(int i = 0; i < amount; ++i ){
		parameter = va_arg(arguments, Rectangle);
		if(firstargument){
			closest = parameter;
			firstargument = false;
		}else{
			if(direction == up){
				if((Player.y - (parameter.y + parameter.height)) >= 0){  // Rechteck ist über dem Spieler
					for(int i = 0; i < Player.width; i++){
						if((parameter.x < Player.x + i) && (Player.x + i < (parameter.x + parameter.width))){
							under = true;
							break;
						}
					}
					if(under){
						if(firstrun){
							mindis = Player.y - (parameter.y + parameter.height);
							closest = parameter;
							firstrun = false;
						} else if((Player.y - (parameter.y + parameter.height)) < mindis){
							mindis = Player.y - (parameter.y + parameter.height);
							closest = parameter;
						}
						under = false;
					}
				}
			} else if (direction == right){
				if((parameter.x - (Player.x + Player.width)) >= 0){
					if(firstrun){
						mindis = parameter.x - (Player.x + Player.width);
						closest = parameter;
						firstrun = false;
					}else{
						if((parameter.x - (Player.x + Player.width)) < mindis){
							mindis = parameter.x - (Player.x + Player.width);
							closest=parameter;
						}
					}
				}
			} else if (direction == down){
				if(((parameter.y - (Player.y+ Player.height)) < (closest.y - (Player.y + Player.height))) >0){
					for(int i = 0; i < Player.width; i++){
						if((parameter.x < Player.x + i) && ( Player.x + i < (parameter.x + parameter.width))){
							under = true;
							break;
						}
					}
					if(under){
						closest = parameter;
						under = false;
					}
				}
			} else if (direction == left){
				if((Player.x - (parameter.x + parameter.width)) >= 0){
					if(firstrun){
						mindis = Player.x - (parameter.x + parameter.width);
						closest = parameter;
						firstrun = false;
					}else{
						if((Player.x - (parameter.x + parameter.width)) < mindis){
							mindis = Player.x - (parameter.x + parameter.width);
							closest = parameter;
						}
					}
				}
			}
		}
	}
	va_end(arguments);
	return closest;
}



