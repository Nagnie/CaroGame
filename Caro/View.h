#pragma once
#include "Data.h"

void FixConsoleWindow();
void SetConsoleBlank();
void DrawBoard(int row, int col, int x, int y, int color);
void TextColor(int x);
int GetCurrentColor();
void DrawBox(int w, int h, int x, int y, int color, int Time);
void DrawPattern_Col(int x, int y, int color, int pt, int kc);
void BackGround();
void DrawBoxMini(int w, int h, int x, int y, int color);
void MainScreen();
void MainMenu();
void HideCursor(bool ok);
string getFileContents(ifstream& File);
void DrawAsciiFile(int x, int y, string nameFile, int color);
void changeFont(int x);