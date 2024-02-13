#include "View.h"
#include "Data.h"
#include "Control.h"

void FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void TextColor(int x) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}

void SetConsoleBlank() {
	int h = HEIGHT, w = WIDTH;
	TextColor(WHITE);
	for (int i = 0; i < h; i++) {
		GotoXY(0, i);
		for (int j = 0; j < w; j++)
			cout << SPACE;
	}
	GotoXY(0, 0);
}

int GetCurrentColor() {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(console, &consoleInfo);
	WORD textAttributes = consoleInfo.wAttributes;
	return textAttributes;
}

void DrawBox(int w, int h, int x, int y, int color, int Time) {
	int tmp = GetCurrentColor();
	TextColor(color);
	for (int i = 0; i < w / 2; i++) {
		GotoXY(x + w / 2 - i, y);
		cout << BOX_H_LINE;
		GotoXY(x + w / 2 + i, y);
		cout << BOX_H_LINE;
		Sleep(Time);
	}
	GotoXY(x, y);
	cout << BOX_TOP_LEFT;
	GotoXY(x + w - 1, y);
	cout << BOX_TOP_RIGHT;
	for (int i = 1; i < h - 1; i++) {
		GotoXY(x, y + i);
		cout << BOX_V_LINE;
		for (int j = 1; j < w - 1; j++)
			cout << SPACE;
		cout << BOX_V_LINE;
		Sleep(Time);
	}
	GotoXY(x, y + h - 1);
	cout << BOX_BOTTOM_LEFT;
	GotoXY(x + w - 1, y + h - 1);
	cout << BOX_BOTTOM_RIGHT;
	for (int i = w / 2 - 1 ; i >= 0; i--) {
		GotoXY(x + w / 2 - i, y + h - 1);
		cout << BOX_H_LINE;
		GotoXY(x + w / 2 + i - (w % 2 == 0), y + h - 1);
		cout << BOX_H_LINE;
		Sleep(Time);
	}
	TextColor(tmp);
}

void DrawPattern_Col(int x, int y, int color, int pt, int kc)
{
	TextColor(color);
	unsigned char pattern = pt;
	for (int i = 0; i < 30; i = i + kc)
	{
		GotoXY(y, x + i);
		putchar(pattern);
	}
}

void BackGround1()
{
	DrawPattern_Col(2, 6, LIGHT_RED, 3, 5);
	DrawPattern_Col(2, 24, RED, 3, 5);
	DrawPattern_Col(2, 42, LIGHT_RED, 3, 5);
	DrawPattern_Col(2, 60, RED, 3, 5);
	DrawPattern_Col(2, 78, LIGHT_RED, 3, 5);
	DrawPattern_Col(2, 96, RED, 3, 5);
	DrawPattern_Col(2, 114, LIGHT_RED, 3, 5);
}

void BackGround2()
{
	DrawPattern_Col(2, 6, LIGHT_MAGENTA, 4, 5);
	DrawPattern_Col(2, 24, MAGENTA, 4, 5);
	DrawPattern_Col(2, 42, LIGHT_MAGENTA, 4, 5);
	DrawPattern_Col(2, 60, MAGENTA, 4, 5);
	DrawPattern_Col(2, 78, LIGHT_MAGENTA, 4, 5);
	DrawPattern_Col(2, 96, MAGENTA, 4, 5);
	DrawPattern_Col(2, 114, LIGHT_MAGENTA, 4, 5);
}

void BackGround3()
{
	DrawPattern_Col(2, 6, BLACK, 4, 5);
	DrawPattern_Col(2, 24, GRAY, 4, 5);
	DrawPattern_Col(2, 42, BLACK, 4, 5);
	DrawPattern_Col(2, 60, GRAY, 4, 5);
	DrawPattern_Col(2, 78, BLACK, 4, 5);
	DrawPattern_Col(2, 96, GRAY, 4, 5);
	DrawPattern_Col(2, 114, BLACK, 4, 5);
}

void BackGround4()
{
	DrawPattern_Col(2, 6, LIGHT_BLUE, 4, 5);
	DrawPattern_Col(2, 24, CYAN, 4, 5);
	DrawPattern_Col(2, 42, LIGHT_BLUE, 4, 5);
	DrawPattern_Col(2, 60, CYAN, 4, 5);
	DrawPattern_Col(2, 78, LIGHT_BLUE, 4, 5);
	DrawPattern_Col(2, 96, CYAN, 4, 5);
	DrawPattern_Col(2, 114, LIGHT_BLUE, 4, 5);
}

void DrawBoxMini(int w, int h, int x, int y, int color)
{
	int tmp = GetCurrentColor();
	TextColor(color);
	GotoXY(x, y);
	cout << TOP_LEFT;
	for (int i = 1; i < w - 1; i++)
		cout << H_LINE;
	cout << TOP_RIGHT;

	for (int i = 1; i < h - 1; i++) {
		GotoXY(x, i + y);
		cout << V_LINE;
		for (int j = 1; j < w - 1; j++)
			cout << SPACE;
		cout << V_LINE;
	}

	GotoXY(x, h + y - 1);
	cout << BOTTOM_LEFT;
	for (int i = 1; i < w - 1; i++)
		cout << H_LINE;
	cout << BOTTOM_RIGHT;
	TextColor(tmp);
}


void HideCursor(bool ok) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = !ok;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void MainScreen() {
	BackGround1();
	DrawBox(92, 10, 15, 9, RED, 10);
	DrawAsciiFile(21, 10, "VLNY Gift", RED);
	Sleep(200);
	DrawAsciiFile(21, 10, "VLNY Gift", YELLOW);
	Sleep(200);
	DrawAsciiFile(21, 10, "VLNY Gift", MAGENTA);
	Sleep(200);
	DrawAsciiFile(21, 10, "VLNY Gift", BLUE);
	Sleep(200);
	DrawAsciiFile(21, 10, "VLNY Gift", CYAN);
	Sleep(200);
	DrawAsciiFile(21, 10, "VLNY Gift", RED);
}

void secondScreen() {
	SetConsoleBlank();
	BackGround2();
	DrawAsciiFile(46, 21, "Flowers", RED);
	Sleep(500);
	DrawBox(92, 16, 15, 4, RED, 0);
	Sleep(1500);
	TextColor(LIGHT_MAGENTA);
	GotoXY(20, 5);
	cout << "14/12/2024 - Happy Valentine Day";
	Sleep(2000);
	TextColor(MAGENTA);
	Sleep(500);
	GotoXY(20, 8);
	cout << "We have been in love for 59 days, answered 46 questions in SumOne.";
	Sleep(2000);
	GotoXY(20, 10);
	cout << "Even though it's been less than 2 months, we've already celebrated Christmas, New";
	GotoXY(20, 11);
	cout << "Year, my birthday, Lunar New Year and Valentine's Day together.";
	Sleep(5000);
	GotoXY(20, 13);
	cout << "There are 214 days left until your birthday, maybe we will have the opportunity ";
	GotoXY(20, 14);
	cout << "to travel together.";
	Sleep(5000);
	GotoXY(20, 16);
	cout << "I hope by then you know how to take pictures :)";
}

void thirdScreen() {
	SetConsoleBlank();
	BackGround3();
	GotoXY(51, 4);
	TextColor(BLACK);
	cout << (unsigned char)3 << " My Confession " << (unsigned char)3;
	Sleep(500);
	DrawBox(92, 18, 14, 6, BLACK, 0);
	Sleep(500);
	TextColor(RED);
	GotoXY(18, 8);
	cout << "My year 2023 has passed in a way that I find quite wasteful and without much meaning.";
	Sleep(3000);
	TextColor(MAGENTA);
	GotoXY(18, 9);
	cout << "The only consolation is that I met you and we are together, after many near misses.";
	Sleep(4500);
	GotoXY(18, 10);
	TextColor(RED);
	cout << "Sometimes, I will say inconsiderate things even though I don't mean it, so if you ";
	GotoXY(18, 11);
	cout << "feel hurt, please let me know.";
	Sleep(5000);
	GotoXY(18, 12);
	TextColor(MAGENTA);
	cout << "This Tet, when I came home and heard that my cousin was about to marry her 7-year ";
	GotoXY(18, 13);
	cout << "relationship, I was in awe. And I thought, 'could we be like that?'";
	Sleep(9000);
	GotoXY(18, 14);
	TextColor(RED);
	cout << "Maybe it's a bit difficult, to be honest with you, deep down I think 'no', but that";
	GotoXY(18, 15);
	cout << "doesn't mean I don't want it to come true, nor does it mean I don't believe you.";
	Sleep(9000);
	GotoXY(18, 16);
	TextColor(MAGENTA);
	cout << "I just don't believe in myself.";
	Sleep(2000);
	GotoXY(18, 17);
	cout << "...";
	Sleep(2000);
	GotoXY(18, 18);
	TextColor(RED);
	cout << "But, I will try my best, to be able to be with you for a long time, so long that the ";
	GotoXY(18, 19);
	cout << "people around us have to say 'omg you guys still love each other?'.";
	Sleep(8000);
	GotoXY(18, 20);
	TextColor(MAGENTA);
	cout << "That's my dream love. Do you want that? I guess your answer is yes too =))";
}

void fourthScreen() {
	SetConsoleBlank();
	BackGround4();
	Sleep(500);
	GotoXY(53, 4);
	TextColor(BLACK);
	cout << (unsigned char)4 << " Some Secret " << (unsigned char)4;
	Sleep(500);
	DrawBox(92, 18, 14, 6, BLACK, 0);
	Sleep(500);
	GotoXY(19, 8);
	cout << "I used google translate so if there are any grammar mistakes or anything, please";
	GotoXY(19, 9);
	cout << "ignore them hehe.";
	Sleep(5000);
	GotoXY(19, 11);
	cout << "Initially, I wanted to code a fancy program, I already had an idea, but when";
	GotoXY(19, 12);
	cout << "I started coding, my nails were too dkasjncndjwkdw, so I did this simple one.";
	Sleep(5000);
	GotoXY(19, 14);
	cout << "Every time I sleep with you, I just want to play with your dick all night, but ";
	GotoXY(19, 15);
	cout << "I'm also sleepy so I can't play with it all night huhu.";
	Sleep(5000);
	GotoXY(19, 17);
	cout << "I love you so much, so I will make you love me so much, so that even if you love  ";
	GotoXY(19, 18);
	cout << "another girl in the future, you won't love her as much as me hehe.";
	Sleep(6000);
	GotoXY(19, 20);
	cout << "Always be by my side, this is an order, not a suggestion!";
}

void endScreen() {
	SetConsoleBlank();
	DrawAsciiFile(1, 22, "FlowersEnd", MAGENTA);
	DrawAsciiFile(76, 22, "FlowersEnd", MAGENTA);
	TextColor(LIGHT_RED);
	GotoXY(23, 3);
	cout << (unsigned char)3;
	GotoXY(17, 10);
	cout << (unsigned char)3;
	GotoXY(8, 6);
	cout << (unsigned char)3;
	GotoXY(20, 18);
	cout << (unsigned char)3;
	GotoXY(10, 16);
	cout << (unsigned char)3;
	GotoXY(105, 17);
	cout << (unsigned char)3;
	GotoXY(98, 13);
	cout << (unsigned char)3;
	GotoXY(100, 3);
	cout << (unsigned char)3;
	GotoXY(110, 6);
	cout << (unsigned char)3;
	GotoXY(90, 19);
	cout << (unsigned char)3;
	Sleep(100);
	DrawAsciiFile(28, 5, "Bye", RED);
	DrawAsciiFile(40, 12, "Byee", RED);
	Sleep(200);
	DrawAsciiFile(28, 5, "Bye", YELLOW);
	DrawAsciiFile(40, 12, "Byee", YELLOW);
	Sleep(200);
	DrawAsciiFile(28, 5, "Bye", GREEN);
	DrawAsciiFile(40, 12, "Byee", GREEN);
	Sleep(200);
	DrawAsciiFile(28, 5, "Bye", CYAN);
	DrawAsciiFile(40, 12, "Byee", CYAN);
	Sleep(200);
	DrawAsciiFile(28, 5, "Bye", BLUE);
	DrawAsciiFile(40, 12, "Byee", BLUE);
	Sleep(200);
	DrawAsciiFile(28, 5, "Bye", MAGENTA);
	DrawAsciiFile(40, 12, "Byee", MAGENTA);
	Sleep(200);
	DrawAsciiFile(28, 5, "Bye", RED);
	DrawAsciiFile(40, 12, "Byee", RED);
}

void MainMenu()
{
	SetConsoleBlank();
	MainScreen();
	Sleep(2000);
	secondScreen();
	Sleep(4000);
	thirdScreen();
	Sleep(4000);
	fourthScreen();
	Sleep(4000);
	endScreen();
	Sleep(5000000);
}


void changeFont(int x)
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = x;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_BOLD;
	wcscpy_s(cfi.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void DrawAsciiFile(int x, int y, string nameFile, int color) {
	TextColor(color);
	SetConsoleOutputCP(65001);
	ifstream Read("assets/UI/" + nameFile + ".txt");
	string line = "";
	for (int i = 0; Read.good(); i++) {
		getline(Read, line);
		GotoXY(x - (i == 0), y + i);
		cout << line;
	}
	Read.close();
	SetConsoleOutputCP(437);
}

