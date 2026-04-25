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
#include <stdarg.h> //Infinit arguments, Infinit Power
#include <sys/stat.h>
#include <string.h>
#include "raylib.h"
#include "raymath.h"


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
bool debug = false;

Rectangle Death = {-1000, 900, 3000, 10};
Rectangle PlayerPosition = { 150, 500, 25, 25};

//Helper stuff
Rectangle GetClosestRect(Rectangle Player, enum Direction direction, int amount, ...);

//Level Loops
int MenuLoop(void);

int Level0Loop(void);

int Level1Loop(void);
int Level1_2Loop();
int Level2Loop(void);
int Level2_2Loop(void);
int Level3Loop(void);
int Level4Loop(void);
int Level5Loop(void);
int Level6Loop(void);

int LevelSelectorLoop(void);
int CreditsLoop(void);



Texture2D texture;
Texture2D star;



float timer = 0.0f;
int timer_0 = 0;
bool done_0 = true;
bool firstrungame = true;
int nextlvl = -1;
char filepath[512];

FILE *file;

int main(void)
{
	// TODO 1: Hier musst du die Window-Size definieren
	const int screenWidth = 1000;
	const int screenHeight = 1000;

	InitWindow(screenWidth, screenHeight, "GetToSpace");

	SetTargetFPS(60);



	texture = LoadTexture("images/Vol1.png");
	star = LoadTexture("images/Star.png");


	//Saves Logik:
	char *home = getenv("HOME");
	if (home != NULL) {
		char path[512];
		char helperpath[512];
		int res =0;
		snprintf(helperpath, sizeof(helperpath),"%s/.GetToSpace", home);
		snprintf(path, sizeof(path), "%s/.GetToSpace/saves", home);
		snprintf(filepath, sizeof(filepath), "%s/.GetToSpace/saves/save.dat", home);

		res = mkdir(helperpath, 0755);
		if(res == -1){
			firstrungame = false;
		}
		res = mkdir(path, 0775);
		if(res == -1){
			firstrungame = false;
		}

		file = fopen(filepath, "a+");
		if (file == NULL) {
			perror("Error: Couldn't open saves file");
		}
	}

	if(file !=0 && firstrungame){
		fseek(file, 0, SEEK_SET);
		fprintf(file, "WARNING: EDITING THIS FILE MAY CURROPT YOUR GAME!\n0");
		fflush(file);
	}

	if(file != NULL){
		fseek(file, 0, SEEK_SET);
		fscanf(file, "WARNING: EDITING THIS FILE MAY CURROPT YOUR GAME!\n%i", &nextlvl);
		nextlvl = nextlvl/298;
	}


	int levelcnt = 98;
	// Game loop
	while (!WindowShouldClose())
	{
		BeginDrawing();

		if(levelcnt != 0){
			DrawTexture(texture, 0, 0, WHITE);
		}

		char levelText[32];
		snprintf(levelText, sizeof(levelText), "%d", nextlvl);
		DrawText(levelText, 100, 30, 10, RED);

		switch (levelcnt) {
		case 98:
			levelcnt = MenuLoop();
			break;
		case 0:
			if(Level0Loop() == 1){
				levelcnt++;
				ClearBackground(RAYWHITE);
				PlayerPosition.x = 150;
				PlayerPosition.y = 500;
				freopen(filepath, "w", file);
				freopen(filepath, "a+", file);
				if(file != NULL){
					fseek(file, 0, SEEK_SET);
					fprintf(file, "WARNING: EDITING THIS FILE MAY CURROPT YOUR GAME!\n%i", levelcnt * 298);
					fflush(file);
				}else{
					perror("ERROR: Resetting file");
				}
			}
			break;
		case 1:
			if(Level1Loop() == 1){
				levelcnt++;
				ClearBackground(RAYWHITE);
				PlayerPosition.x = 750;
				PlayerPosition.y = 500;
				freopen(filepath, "w", file);
				freopen(filepath, "a+", file);
				if(file != NULL){
					fseek(file, 0, SEEK_SET);
					fprintf(file, "WARNING: EDITING THIS FILE MAY CURROPT YOUR GAME!\n%i", levelcnt * 298);
					fflush(file);
				}else{
					perror("ERROR: Resetting file");
				}
			}
			break;
		case 2:
			if(Level1_2Loop() == 1){
				levelcnt++;
				ClearBackground(RAYWHITE);
				freopen(filepath, "w", file);
				freopen(filepath, "a+", file);
				if(file != NULL){
					fseek(file, 0, SEEK_SET);
					fprintf(file, "WARNING: EDITING THIS FILE MAY CURROPT YOUR GAME!\n%i", levelcnt * 298);
					fflush(file);
				}else{
					perror("ERROR: Resetting file");
				}
			}
			break;
		case 3:
			if(Level2Loop() == 1){
				levelcnt++;
				ClearBackground(RAYWHITE);
				freopen(filepath, "w", file);
				freopen(filepath, "a+", file);
				if(file != NULL){
					fseek(file, 0, SEEK_SET);
					fprintf(file, "WARNING: EDITING THIS FILE MAY CURROPT YOUR GAME!\n%i", levelcnt * 298);
					fflush(file);
				}else{
					perror("ERROR: Resetting file");
				}
			}
			break;
		case 4:
			if(Level2_2Loop() == 1){
				levelcnt++;
				ClearBackground(RAYWHITE);
				freopen(filepath, "w", file);
				freopen(filepath, "a+", file);
				if(file != NULL){
					fseek(file, 0, SEEK_SET);
					fprintf(file, "WARNING: EDITING THIS FILE MAY CURROPT YOUR GAME!\n%i", levelcnt * 298);
					fflush(file);
				}else{
					perror("ERROR: Resetting file");
				}
			}
			break;
		case 5:
			if(Level3Loop() == 1){
				levelcnt++;
				ClearBackground(RAYWHITE);
				freopen(filepath, "w", file);
				freopen(filepath, "a+", file);
				if(file != NULL){
					fseek(file, 0, SEEK_SET);
					fprintf(file, "WARNING: EDITING THIS FILE MAY CURROPT YOUR GAME!\n%i", levelcnt * 298);
					fflush(file);
				}else{
					perror("ERROR: Resetting file");
				}
			}
			break;
		case 6:
			if(Level4Loop() == 1){
				levelcnt++;
				ClearBackground(RAYWHITE);
				freopen(filepath, "w", file);
				freopen(filepath, "a+", file);
				if(file != NULL){
					fseek(file, 0, SEEK_SET);
					fprintf(file, "WARNING: EDITING THIS FILE MAY CURROPT YOUR GAME!\n%i", levelcnt * 298);
					fflush(file);
				}else{
					perror("ERROR: Resetting file");
				}
			}
			break;
		case 7:
			if(Level5Loop() == 1){
				levelcnt++;
				ClearBackground(RAYWHITE);
				freopen(filepath, "w", file);
				freopen(filepath, "a+", file);
				if(file != NULL){
					fseek(file, 0, SEEK_SET);
					fprintf(file, "WARNING: EDITING THIS FILE MAY CURROPT YOUR GAME!\n%i", levelcnt * 298);
					fflush(file);
				}else{
					perror("ERROR: Resetting file");
				}
			}
			break;
		case 8:
			if(Level6Loop() == 1){
				levelcnt++;
				ClearBackground(RAYWHITE);
				freopen(filepath, "w", file);
				freopen(filepath, "a+", file);
				if(file != NULL){
					fseek(file, 0, SEEK_SET);
					fprintf(file, "WARNING: EDITING THIS FILE MAY CURROPT YOUR GAME!\n%i", levelcnt * 298);
					fflush(file);
				}else{
					perror("ERROR: Resetting file");
				}
			}
			break;
		case 97:
			levelcnt = LevelSelectorLoop();
			break;
		case 99:
			levelcnt = CreditsLoop();
			break;
		default:
			levelcnt = 98;
			break;
		}




		EndDrawing();
	}


	UnloadTexture(texture);
	UnloadTexture(star);
	fclose(file);

	CloseWindow();

	return 0;
}
int MenuLoop(void){
    Rectangle PlayButton   = { 300, 450, 350, 150 };
    Rectangle LevelSelect  = { 300, 625, 350, 150 };
    Rectangle CreditsBtn   = { 300, 800, 350, 150 };

    Vector2 MousePos = GetMousePosition();
    bool clicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    ClearBackground(LIGHTGRAY);

    DrawText("GetToSpace!", 320, 150, 60, BLUE);
    DrawText("A game by TheSkriptKid", 335, 225, 25, BLUE);


    bool hPlay   = CheckCollisionPointRec(MousePos, PlayButton);
    bool hSelect = CheckCollisionPointRec(MousePos, LevelSelect);
    bool hCred   = CheckCollisionPointRec(MousePos, CreditsBtn);

    DrawRectangleRounded(PlayButton,  0.3f, 8, hPlay   ? GREEN  : GRAY);
    DrawRectangleRounded(LevelSelect, 0.3f, 8, hSelect ? YELLOW : GRAY);
    DrawRectangleRounded(CreditsBtn,  0.3f, 8, hCred   ? GREEN  : GRAY);

    DrawText(hPlay   ? "Let's Go!"  : "Play!",    390, 510, 40, BLUE);
    DrawText(hSelect ? "Pick one!"  : "Levels",   390, 685, 40, BLUE);
    DrawText(hCred   ? "Thanks! :)" : "Credits",  385, 860, 40, BLUE);


    if(nextlvl <= 0){
        DrawRectangleRounded(LevelSelect, 0.3f, 8, Fade(GRAY, 0.4f));
        DrawText("Levels", 390, 685, 40, Fade(BLUE, 0.3f));
    }

    if(clicked){
        if(hPlay)                        return nextlvl;
        if(hSelect && nextlvl > 0)       return 97;
        if(hCred)                        return 99;
    }

    return 98;
}

int Level0Loop(void){

	timer ++;
	timer_0 = (int)(timer / 60);

	switch (timer_0) {
	case 1:
		DrawText("Space.", 480, 500, 20 , GREEN);
		break;
	case 4:
		ClearBackground(BLACK);
		DrawText("What is Space?", 460, 500, 20 , GREEN);
		break;
	case 7:
		ClearBackground(BLACK);
		DrawText("Or better, why are we so Fascinated of it?", 350, 500, 20 , GREEN);
		break;
	case 10:
		ClearBackground(BLACK);
		DrawText("Why do we want to get to it? Explore it? Look at it?", 250, 500, 20 , GREEN);
		break;
	case 13:
		ClearBackground(BLACK);
		DrawText("I dont know. ", 440, 500, 20 , GREEN);
		break;
	case 15:
		ClearBackground(BLACK);
		DrawText("This is Cube.", 440, 500, 20 , GREEN);
		PlayerPosition.x = 490;
		PlayerPosition.y = 700;
		DrawRectangleGradientEx(PlayerPosition, GREEN, BLUE, PURPLE, GRAY);
		break;
	case 16:
		ClearBackground(BLACK);
		DrawText("Say Hi Cube!", 440, 500, 20 , GREEN);
		if(done_0){
			velocityY = -25;
			done_0 = false;
		}

		break;
	case 18:
		ClearBackground(BLACK);
		DrawText("He also loves Space!", 440, 500, 20 , GREEN);
		DrawRectangleGradientEx(PlayerPosition, GREEN, BLUE, PURPLE, GRAY);
		break;
	case 20:
		ClearBackground(BLACK);
		DrawText("Can you help him get to space? I think a good Vehicle is a few Levels to the right!", 80, 500, 20 , GREEN);
		DrawRectangleGradientEx(PlayerPosition, GREEN, BLUE, PURPLE, GRAY);
		break;



	case 22:
		PlayerPosition.x = 150;
		PlayerPosition.y = 500;
		return 1;
		break;
	default:
		break;
	}


	if(timer_0 >= 16 && timer_0 <= 18){
		jump = jump - (jump * 0.1f);
		velocityY = velocityY - velocityY *0.1f + gravity;
		if(PlayerPosition.y > 700){
			velocityY=0;
		}
		PlayerPosition.y += velocityY;
		DrawRectangleGradientEx(PlayerPosition, GREEN, BLUE, PURPLE, GRAY);
	}

	return -1;
}

int Level1Loop(void){
	//Objekts
	Rectangle startplatt = {50, 850,900, 25};
	Rectangle Goal = {770, 750, 25,25};



	DrawRectangleLines(startplatt.x,startplatt.y,startplatt.width,startplatt.height, BLACK);
	DrawRectangle(Death.x, Death.y, Death.width, Death.height, RED);
	DrawRectangleRec(Goal, GOLD);


	DrawTexture(star, Goal.x - Goal.width, Goal.y-Goal.height, WHITE);


	if(CheckCollisionRecs(PlayerPosition, Goal)){
		PlayerPosition.x = 150;
		PlayerPosition.y = 500;
		return 1;
	} else{
		DrawFPS(50, 50);


		DrawText("Look at the Stars. Aren't they Beatiful? I wanna try to get to them!", 300, 700, 15 , GREEN);

		if(PlayerPosition.x ==150){
			timer ++;
			if(timer > 300){
				DrawText("Move with  W A D", 300, 600, 20 , GRAY);
			}
		}else{
			timer = 0;
		}

		if(IsKeyDown(KEY_D)){
			velocityX = Clamp(velocityX + 1, -5, 5);
		}else if(IsKeyDown(KEY_A)){
			velocityX = Clamp(velocityX - 1, -5, 5);
		}


		if(IsKeyPressed(KEY_W) && Nogravity){
			velocityY = -25;
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
	}
	return -1;
}

int Level1_2Loop(void){
	//Objekts
	Rectangle startplatt = {50, 850,900, 25};
	Rectangle Goal = {150, 750, 25,25};

	DrawRectangleLines(startplatt.x,startplatt.y,startplatt.width,startplatt.height, BLACK);
	DrawRectangle(Death.x, Death.y, Death.width, Death.height, RED);
	DrawRectangleRec(Goal, GOLD);


	DrawTexture(star, Goal.x - Goal.width, Goal.y-Goal.height, WHITE);


	if(CheckCollisionRecs(PlayerPosition, Goal)){
		PlayerPosition.x = 150;
		PlayerPosition.y = 500;
		return 1;
	} else{
		DrawFPS(50, 50);


		DrawText("They are left, right, above, below... EVERYWHERE!!", 300, 700, 15 , GREEN);

		if(PlayerPosition.x ==150){
			timer ++;
			if(timer > 300){
				DrawText("Move with  W A D", 300, 600, 20 , GRAY);
			}
		}else{
			timer = 0;
		}

		if(IsKeyDown(KEY_D)){
			velocityX = Clamp(velocityX + 1, -5, 5);
		}else if(IsKeyDown(KEY_A)){
			velocityX = Clamp(velocityX - 1, -5, 5);
		}


		if(IsKeyPressed(KEY_W) && Nogravity){
			velocityY = -25;
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
	}
	return -1;
}

int Level2Loop(void){
	//Objekts
	Rectangle startplatt = {50, 850,300, 25};
	Rectangle startplatt2 = {500, 850,400, 25};
	Rectangle Goal = {770, 750, 25,25};



	DrawRectangleLines(startplatt.x,startplatt.y,startplatt.width,startplatt.height, BLACK);
	DrawRectangleLines(startplatt2.x,startplatt2.y,startplatt2.width,startplatt2.height, BLACK);
	DrawRectangle(Death.x, Death.y, Death.width, Death.height, RED);
	DrawRectangleRec(Goal, GOLD);

	DrawTexture(star, Goal.x - Goal.width, Goal.y-Goal.height, WHITE);


	if(PlayerPosition.y >= 825){
		timer ++;
		if(timer > 300){
			DrawText("Jump with Space", 300, 600, 20 , GRAY);
		}
	}else {
		timer = 0;
	}

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
			velocityY = -25;
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

int Level2_2Loop(void){
	//Objekts
	Rectangle startplatt = {50, 850,200, 25};
	Rectangle startplatt2 = {350, 850,200, 25};
	Rectangle startplatt3 = {650, 850,200, 25};
	Rectangle Goal = {770, 750, 25,25};



	DrawRectangleLines(startplatt.x,startplatt.y,startplatt.width,startplatt.height, BLACK);
	DrawRectangleLines(startplatt2.x,startplatt2.y,startplatt2.width,startplatt2.height, BLACK);
	DrawRectangleLines(startplatt3.x,startplatt3.y,startplatt3.width,startplatt3.height, BLACK);
	DrawRectangle(Death.x, Death.y, Death.width, Death.height, RED);
	DrawRectangleRec(Goal, GOLD);


	DrawTexture(star, Goal.x - Goal.width, Goal.y-Goal.height, WHITE);


	if(CheckCollisionRecs(PlayerPosition, Goal)){
		PlayerPosition.x = 150;
		PlayerPosition.y = 500;
		return 1;
	} else{
		DrawFPS(50, 50);


		DrawText("No Obstacles stand strong in the way", 300, 700, 15 , GREEN);



		if(IsKeyDown(KEY_D)){
			velocityX = Clamp(velocityX + 1, -5, 5);
		}else if(IsKeyDown(KEY_A)){
			velocityX = Clamp(velocityX - 1, -5, 5);
		}


		if(IsKeyPressed(KEY_W) && Nogravity){
			velocityY = -25;
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
		} else if(CheckCollisionRecs(startplatt3, PlayerPosition)){
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
	}
	return -1;
}

int Level3Loop(void){



	//Objekts
	Rectangle startplatt = {50, 850,900, 25};
	Rectangle obstacle1 = {700,750,100,100};
	Rectangle obstacle2 = {300,750,100,100};
	Rectangle Goal = {770, 650, 25,25};

	DrawRectangleLines(startplatt.x,startplatt.y,startplatt.width,startplatt.height, BLACK);
	DrawRectangle(obstacle1.x, obstacle1.y, obstacle1.width, obstacle1.height, BLUE);
	DrawRectangle(obstacle2.x, obstacle2.y, obstacle2.width, obstacle2.height, BLUE);
	DrawRectangle(Death.x, Death.y, Death.width, Death.height, RED);
	DrawRectangleRec(Goal, GOLD);

	DrawTexture(star, Goal.x - Goal.width, Goal.y-Goal.height, WHITE);

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
			velocityY = -20;
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
	Rectangle startplatt = {75, 850,100, 25};
	Rectangle jump1 = {200, 750, 100 ,25};
	Rectangle jump2 = {350, 650, 60 ,25};
	Rectangle jump3= {450, 550, 40 ,25};
	Rectangle jump5 = {750, 750, 100 ,25};
	Rectangle Goal = {770, 700, 25,25};


	DrawRectangleLines(startplatt.x,startplatt.y,startplatt.width,startplatt.height, BLACK);
	DrawRectangle(Death.x, Death.y, Death.width, Death.height, RED);

	DrawRectangleLines(jump1.x,jump1.y,jump1.width,jump1.height, GRAY);
	DrawRectangleLines(jump2.x,jump2.y,jump2.width,jump2.height, GRAY);
	DrawRectangleLines(jump3.x,jump3.y,jump3.width,jump3.height, GRAY);
	DrawRectangleLines(jump5.x,jump5.y,jump5.width,jump5.height, GRAY);

	DrawRectangleRec(Goal, GOLD);


	DrawTexture(star, Goal.x - Goal.width, Goal.y-Goal.height, WHITE);


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
			velocityY = -25;
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
	Rectangle startplatt = {50, 850,900, 25};
	Rectangle Death2 = {450, 775, 35,75};
	Rectangle Goal = {770, 750, 25,25};



	DrawRectangleLines(startplatt.x,startplatt.y,startplatt.width,startplatt.height, BLACK);
	DrawRectangleRec(Death2, RED);
	DrawRectangleRec(Goal, GOLD);

	DrawTexture(star, Goal.x - Goal.width, Goal.y-Goal.height, WHITE);

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
			velocityY = -25;
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
			PlayerPosition.x = 150;
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

int Level6Loop(void){

	//Objekts
	Rectangle startplatt = {50, 850,300, 25};
	Rectangle boost = {350, 550, 25, 300};
	Rectangle boost2 = {550, 550, 25, 300};
	Rectangle Goal = {770, 750, 25,25};



	DrawRectangleLines(startplatt.x,startplatt.y,startplatt.width,startplatt.height, BLACK);
	DrawRectangleRec(boost, BLUE);
	DrawRectangleRec(boost2, BLUE);
	DrawRectangleRec(Goal, GOLD);

	DrawTexture(star, Goal.x - Goal.width, Goal.y-Goal.height, WHITE);

	if(PlayerPosition.y > 550){
		timer ++;
		if(timer > 300){
			DrawText("Try standing still in the blue Boost Pad and Press Jump!", 300, 500, 15 , GRAY);
		}
	}else{
		timer =0;
	}

	if(CheckCollisionRecs(PlayerPosition, Goal)){
		PlayerPosition.x = 150;
		PlayerPosition.y = 500;
		return 1;
	} else{
		DrawFPS(50, 50);


		DrawText("Are you prepared?", 400, 700, 15 , GREEN);


		if(IsKeyDown(KEY_D)){
			velocityX = Clamp(velocityX + 1, -5, 5);
		}else if(IsKeyDown(KEY_A)){
			velocityX = Clamp(velocityX - 1, -5, 5);
		}


		if(IsKeyPressed(KEY_W) && Nogravity){
			velocityY = -25;
		}


		Nogravity = false;

		if(CheckCollisionRecs(startplatt, PlayerPosition)){
			Nogravity = true;
			if(velocityY > 0){
				velocityY = 0;
			}
		} else if(CheckCollisionRecs(GetClosestRect(PlayerPosition, down, 4, startplatt, boost, Goal, boost2),PlayerPosition)){
			Nogravity = true;
		}else if(CheckCollisionRecs(GetClosestRect(PlayerPosition, down, 4, startplatt, boost, Goal, boost2),PlayerPosition)){
			Nogravity = true;
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



int CreditsLoop(void){
	Rectangle Back = {370, 750, 200, 100};

	Vector2 MousePos;
	bool clicked = false;

	MousePos = GetMousePosition();
	clicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

	DrawText("Thanks to:", 320, 100, 50, GREEN);

	DrawText("RayLib for the Amazing work!", 300, 250, 25, BLUE);
	DrawText("HackClub for giving Motivation!", 300, 300, 25, BLUE);
	DrawText("Claude and Github Copilot!", 300, 350, 25, BLUE);
	DrawText("and ...", 400, 390, 40, RED);
	DrawText("Thank YOU for Playing!!!", 300, 450, 25, PURPLE);

	DrawRectangleRounded(Back, 0.3, 10, YELLOW);
	DrawText("Back", 440, 790, 25, BLUE);


	if(CheckCollisionPointRec(MousePos, Back)){
		DrawRectangleRounded(Back, 0.3, 10, YELLOW);
		DrawText("Back", 440, 790, 25, BLUE);
		if(clicked){
			return 98;
		}
	}else{
		DrawRectangleRounded(Back, 0.3, 10, PURPLE);
		DrawText("Back", 440, 790, 25, BLUE);
	}

	ClearBackground(GRAY);
	return 99;
}

int LevelSelectorLoop(void){

    const char *levelNames[] = {
        "Intro",     // 0
        "Level 1",   // 1
        "Level 1-2", // 2
        "Level 2",   // 3
        "Level 2-2", // 4
        "Level 3",   // 5
        "Level 4",   // 6
        "Level 5",   // 7
        "Level 6",   // 8
    };
    int totalLevels = 9;

    Rectangle backBtn = { 20, 20, 120, 45 };
    Vector2 mousePos = GetMousePosition();
    bool clicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    ClearBackground(DARKGRAY);
    DrawText("Select Level", 350, 40, 40, WHITE);


    Color backColor = CheckCollisionPointRec(mousePos, backBtn) ? YELLOW : GRAY;
    DrawRectangleRounded(backBtn, 0.3f, 8, backColor);
    DrawText("< Menu", 30, 32, 20, BLACK);
    if (CheckCollisionPointRec(mousePos, backBtn) && clicked) {
        return 98;
    }


    int cols = 3;
    int btnW = 240, btnH = 80;
    int padX = 60, padY = 30;
    int startX = 100, startY = 150;

    for (int i = 0; i < totalLevels; i++) {
        int col = i % cols;
        int row = i / cols;

        Rectangle btn = {
            startX + col * (btnW + padX),
            startY + row * (btnH + padY),
            btnW,
            btnH
        };

        bool unlocked = (i <= nextlvl);
        bool hover    = CheckCollisionPointRec(mousePos, btn);

        Color bgColor;
        if (!unlocked)        bgColor = Fade(GRAY, 0.4f);
        else if (hover)       bgColor = GREEN;
        else                  bgColor = DARKGREEN;

        DrawRectangleRounded(btn, 0.25f, 8, bgColor);
        DrawRectangleRoundedLines(btn, 0.25f, 8, BLACK);


        if (i < nextlvl) {
            DrawText("*", btn.x + btnW - 22, btn.y + 6, 25, GOLD);
        }

        if (unlocked) {
            DrawText(levelNames[i],
                     btn.x + 20,
                     btn.y + btnH/2 - 12,
                     22, WHITE);

            if (hover && clicked) {

                PlayerPosition.x = 150;
                PlayerPosition.y = 500;
                velocityX = 0;
                velocityY = 0;
                return i;
            }
        } else {

            DrawText("LOCKED",
                     btn.x + 60,
                     btn.y + btnH/2 - 12,
                     22, Fade(WHITE, 0.4f));
        }
    }

    return 97;
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



