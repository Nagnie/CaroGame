#include "View.h"
#include "Data.h"
#include "Model.h"
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

void DrawBoard(int r, int c, int x, int y, int color) {
	int tmp = GetCurrentColor();
	GotoXY(x, y);
	TextColor(color);

	// top row
	cout << TOP_LEFT << H_LINE << H_LINE << H_LINE;
	for (int i = 1; i < c; i++) {
		cout << TOP_CROSS << H_LINE << H_LINE << H_LINE;
	}
	cout << TOP_RIGHT;
	GotoXY(x, y + 1);
	for (int i = 0; i <= c; i++) {
		cout << V_LINE << SPACE << SPACE << SPACE;
	}

	// all the middle row
	for (int i = 1; i < r; i++) {
		GotoXY(x, y + i * 2);
		cout << LEFT_CROSS << H_LINE << H_LINE << H_LINE;
		for (int j = 1; j < c; j++)
			cout << CROSS << H_LINE << H_LINE << H_LINE;
		cout << RIGHT_CROSS;
		GotoXY(x, y + i * 2 + 1);
		for (int j = 0; j <= c; j++) {
			cout << V_LINE << SPACE << SPACE << SPACE;
		}
	}

	// bottom row
	GotoXY(x, y + 2 + 2 * (r - 1));
	cout << BOTTOM_LEFT << H_LINE << H_LINE << H_LINE;
	for (int i = 1; i < c; i++) {
		cout << BOTTOM_CROSS << H_LINE << H_LINE << H_LINE;
	}
	cout << BOTTOM_RIGHT;
	TextColor(tmp);
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

//update
void PrintCARO(int x, int y, int color)
{
	TextColor(color);
	unsigned char logo[] = { 32, 32, 179, 219, 219, 219, 219, 219, 219, 32, 32, 32, 32, 32, 179, 219, 219, 219, 219, 219, 32, 32, 32, 179, 219, 219, 219, 219, 219, 219, 219, 32, 32, 32, 32, 32, 179, 219, 219, 219, 219, 219, 219, 32, 32,
							179, 219, 219, 32, 32, 32, 32, 32, 179, 219, 219, 32, 179, 219, 219, 32, 32, 32, 32, 179, 219, 219, 32, 179, 219, 219, 32, 32, 32, 32, 179, 219, 219, 32, 179, 219, 219, 32, 32, 32, 32, 32, 179, 219, 219,
							179, 219, 219, 32, 32, 32, 32, 32, 32, 32, 32, 32, 179, 219, 219, 32, 32, 32, 32, 179, 219, 219, 32, 179, 219, 219, 32, 32, 32, 32, 179, 219, 219, 32, 179, 219, 219, 32, 32, 32, 32, 32, 179, 219, 219,
							179, 219, 219, 32, 32, 32, 32, 32, 32, 32, 32, 32, 179, 219, 219, 219, 219, 219, 219, 219, 219, 219, 32, 179, 219, 219, 219, 219, 219, 219, 219, 32, 32, 32, 179, 219, 219, 32, 32, 32, 32, 32, 179, 219, 219,
							179, 219, 219, 32, 32, 32, 32, 32, 179, 219, 219, 32, 179, 219, 219, 32, 32, 32, 32, 179, 219, 219, 32, 179, 219, 219, 32, 32, 32, 32, 179, 219, 219, 32, 179, 219, 219, 32, 32, 32, 32, 32, 179, 219, 219,
							179, 219, 219, 32, 32, 32, 32, 32, 179, 219, 219, 32, 179, 219, 219, 32, 32, 32, 32, 179, 219, 219, 32, 179, 219, 219, 32, 32, 32, 32, 179, 219, 219, 32, 179, 219, 219, 32, 32, 32, 32, 32, 179, 219, 219,
							32, 32, 179, 219, 219, 219, 219, 219, 219, 32, 32, 32, 179, 219, 219, 32, 32, 32, 32, 179, 219, 219, 32, 179, 219, 219, 32, 32, 32, 32, 179, 219, 219, 32, 32, 32, 179, 219, 219, 219, 219, 219, 219, 32, 32 };
	int num_lines = 7, num_chars = 45;
	for (int i = 0; i < num_lines; i++)
	{
		GotoXY(x, i + y);
		for (int j = 0; j < num_chars; j++)
			putchar(logo[i * num_chars + j]);
	}
}

void PrintNote(int x, int y, int color)
{
	TextColor(color);
	GotoXY(x, y);
	unsigned char Note[] = { 179, 32, 80, 114, 111, 106, 101, 99, 116, 32, 98, 121, 32, 71, 114, 111, 117, 112, 32, 49, 51, 32, 45, 32, 50, 50, 67, 84, 84, 52, 32, 72, 67, 77, 85, 83, 32, 179 };
	for (int i = 0; i < 38; i++)
	{
		cout << Note[i];
		Sleep(10);
	}

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

void BackGround()
{
	DrawPattern_Col(1, 6, LIGHT_RED, 3, 6);
	DrawPattern_Col(4, 24, MAGENTA, 4, 6);
	DrawPattern_Col(1, 42, LIGHT_RED, 3, 6);
	DrawPattern_Col(4, 60, MAGENTA, 4, 6);
	DrawPattern_Col(1, 78, LIGHT_RED, 3, 6);
	DrawPattern_Col(4, 96, MAGENTA, 4, 6);
	DrawPattern_Col(1, 114, LIGHT_RED, 3, 6);
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

void DrawButton()
{
	DrawBoxMini(14, 3, 89, 6, BLUE);
	GotoXY(94, 7);
	TextColor(BLUE);
	cout << "PLAY";
	Sleep(200);
	DrawBoxMini(14, 3, 89, 9, BLUE);
	GotoXY(94, 10);
	TextColor(BLUE);
	cout << "LOAD";
	Sleep(200);
	DrawBoxMini(14, 3, 89, 12, BLUE);
	GotoXY(94, 13);
	TextColor(BLUE);
	cout << "HELP";
	Sleep(200);
	DrawBoxMini(14, 3, 89, 15, BLUE);
	GotoXY(93, 16);
	TextColor(BLUE);
	cout << "OPTION";
	Sleep(200);
	DrawBoxMini(14, 3, 89, 18, BLUE);
	GotoXY(94, 19);
	TextColor(BLUE);
	cout << "EXIT";
	Sleep(200);
}

void CaroAnimation()
{
	PrintCARO(20, 9, MAGENTA);
	Sleep(150);
	PrintCARO(20, 9, YELLOW);
	Sleep(150);
	PrintCARO(20, 9, LIGHT_CYAN);
	Sleep(150);
	PrintCARO(20, 9, GREEN);
	Sleep(150);
	PrintCARO(20, 9, BLUE);
	Sleep(150);
	PrintCARO(20, 9, LIGHT_YELLOW);
	Sleep(150);
	PrintCARO(20, 9, RED);
}

int ProcessFinish(_POINT _A[B_SIZE][B_SIZE], int& _X, int& _Y, bool& _TURN, int pWhoWin, string& NamePlayer_O, string& NamePlayer_X, WinningPos WP[5])
{
	GotoXY(0, _A[B_SIZE - 1][B_SIZE - 1].y + 2);
	switch (pWhoWin) {
	case 1:
		SetOWin(NamePlayer_O, WP, _A);
		break;
	case -1:
		SetXWin(NamePlayer_X, WP, _A);
		break;
	case 0:
		SetConsoleBlank();
		ascii_art("                    DRAW !!", 1, 5, RED);
		break;
	case 2:
		_TURN = !_TURN;
		break;
	}
	GotoXY(_X, _Y);
	return pWhoWin;
}

char AskContinue(_POINT _A[B_SIZE][B_SIZE], bool sound[])
{
	GotoXY(50, 19);
	cout << "DO YOU WANT TO CONTINUE ??";
	TextColor(LIGHT_BLUE);
	//GotoXY(53, 22); cout << "YES -> PRESS Y ";
	//TextColor(LIGHT_RED);
	//GotoXY(53, 23); cout << "NO  -> PRESS N ";
	DrawBoxMini(10, 3, WIDTH / 2 - 10, 21, RED);
	GotoXY(WIDTH / 2 - 10 + 3, 22);
	TextColor(RED);
	cout << "YES";
	DrawBoxMini(10, 3, WIDTH / 2 + 5, 21, BLUE);
	GotoXY(WIDTH / 2 + 5 + 4, 22);
	TextColor(BLUE);
	cout << "NO";
	bool ok = 1;
	while (true) {
		char c = toupper(_getch());
		if (sound[CLICK_SFX]) PlayAudio(CLICK_SFX);
		if (c == ENTER)
			return (ok ? 'Y' : 'N');
		if (c == A || c == D)
			ok ^= 1;
		if (ok) {
			DrawBoxMini(10, 3, WIDTH / 2 - 10, 21, RED);
			GotoXY(WIDTH / 2 - 10 + 3, 22);
			TextColor(RED);
			cout << "YES";
			DrawBoxMini(10, 3, WIDTH / 2 + 5, 21, BLUE);
			GotoXY(WIDTH / 2 + 5 + 4, 22);
			TextColor(BLUE);
			cout << "NO";
		}
		else {
			DrawBoxMini(10, 3, WIDTH / 2 - 10, 21, BLUE);
			GotoXY(WIDTH / 2 - 10 + 3, 22);
			TextColor(BLUE);
			cout << "YES";
			DrawBoxMini(10, 3, WIDTH / 2 + 5, 21, RED);
			GotoXY(WIDTH / 2 + 5 + 4, 22);
			TextColor(RED);
			cout << "NO";
		}
	}
}

void DrawBanner(int x, int y, int color) {
	TextColor(color);
	SetConsoleOutputCP(65001);
	ifstream Read("assets/UI/Banner.txt");
	string line = "";
	for (int i = 0; Read.good(); i++) {
		getline(Read, line);
		GotoXY(x - (i == 0), y + i);
		cout << line;
	}
	Read.close();
	SetConsoleOutputCP(437);
}

void AskTurn(bool& _TURN, bool sound[], string& NamePlayer_O, string& NamePlayer_X, int& pvp) { // Hỏi lượt đánh trước
	SetConsoleBlank();
	DrawBoxMini(72, 20, 24, 8, BLACK);//vẽ khung to
	// Vẽ hai ô hiển thị O vs X
	int wide = 20;
	int high = 10;
	int x = 20;
	int y = 10;
	DrawAsciiFile(0, 2, "DrawTurn", MAGENTA);
	Draw(38, 15, "OTurn", GRAY);
	Draw(69, 15, "XTurn", GRAY);
	// Vẽ ô hiển thị tên
	int WideBoxName = 30;
	int HighBoxName = 3;
	int X_BoxName = 45;
	int Y_BoxName = 10;
	DrawBoxMini(WideBoxName, HighBoxName, X_BoxName, Y_BoxName, LIGHT_MAGENTA);
	GotoXY(X_BoxName + WideBoxName / 2 - NamePlayer_O.size() / 2, Y_BoxName + 1);
	TextColor(GREEN);
	cout << NamePlayer_O;
	GotoXY(X_BoxName + 1, Y_BoxName + 1);
	TextColor(BLUE);
	cout << (unsigned char)17;
	GotoXY(X_BoxName + WideBoxName - 2, Y_BoxName + 1);
	TextColor(BLUE);
	cout << (unsigned char)16;
	TextColor(RED);
	bool check = true;
	if (pvp) while (true) {
		char press = toupper(_getch());
		if (sound[CLICK_SFX]) PlayAudio(CLICK_SFX);
		if (press == 'D' || press == 'A') {
			if (press == 'D')
			{
				GotoXY(X_BoxName + WideBoxName - 2, Y_BoxName + 1);
				TextColor(YELLOW);
				cout << (unsigned char)16;
				Sleep(200);
				GotoXY(X_BoxName + WideBoxName - 2, Y_BoxName + 1);
				TextColor(BLUE);
				cout << (unsigned char)16;
			}
			else if (press == 'A') {
				GotoXY(X_BoxName + 1, Y_BoxName + 1);
				TextColor(YELLOW);
				cout << (unsigned char)17;
				Sleep(200);
				GotoXY(X_BoxName + 1, Y_BoxName + 1);
				TextColor(BLUE);
				cout << (unsigned char)17;
			}
			if (check == true)
			{
				GotoXY(X_BoxName + WideBoxName / 2 - NamePlayer_O.size() / 2, Y_BoxName + 1);
				for (int i = 0; i < NamePlayer_O.size(); i++)
					cout << ' ';
				GotoXY(X_BoxName + WideBoxName / 2 - NamePlayer_X.size() / 2, Y_BoxName + 1);
				TextColor(GREEN);
				cout << NamePlayer_X;
				check = false;
			}
			else if (check == false) {
				GotoXY(X_BoxName + WideBoxName / 2 - NamePlayer_X.size() / 2, Y_BoxName + 1);
				for (int i = 0; i < NamePlayer_X.size(); i++)
					cout << ' ';
				GotoXY(X_BoxName + WideBoxName / 2 - NamePlayer_O.size() / 2, Y_BoxName + 1);
				TextColor(GREEN);
				cout << NamePlayer_O;
				check = true;
			}
		}
		else if (press == ENTER) {
			break;
		}
	}
	GotoXY(x, y);
	Draw(38, 15, "OTurnC", O_COLOR);
	while (true) {
		unsigned char c = toupper(_getch());
		if (sound[CLICK_SFX]) PlayAudio(CLICK_SFX);
		if (c == 'A' || c == 'D') {
			if (c == 'A') {
				if (x == 50) {
					Draw(69, 15, "XTurn", GRAY);
					Draw(38, 15, "OTurnC", O_COLOR);
					x -= 30;
				}
			}
			else if (c == 'D') {
				if (x == 20) {
					Draw(69, 15, "XTurnC", X_COLOR);
					Draw(38, 15, "OTurn", GRAY);
					x += 30;
				}
			}
		}
		else if (c == ENTER) {
			if (x == 20) {
				_TURN = true; // true là lượt của O
				if (check == false)
					swap(NamePlayer_O, NamePlayer_X);
				return;
			}
			else if (x == 50) {
				_TURN = false; // false là lượt của X
				if (check == true)
					swap(NamePlayer_O, NamePlayer_X);
				return;
			}
		}
	}
}

void DrawEnterName(int x, int y, int color) {
	TextColor(color);
	SetConsoleOutputCP(65001);
	ifstream Read("assets/UI/DrawEnterName.txt");
	string line = "";
	for (int i = 0; Read.good(); i++) {
		getline(Read, line);
		GotoXY(x - (i == 0), y + i);
		cout << line;
	}
	Read.close();
	SetConsoleOutputCP(437);
}

bool EnterNamePlayer(string& NamePlayer_O, string& NamePlayer_X, int& pvp) {
	unsigned char x = 16;
	SetConsoleBlank();
	HideCursor(0);
	DrawBanner(9, 2, GREEN);
	DrawEnterName(19, 3, MAGENTA);
	TextColor(BLACK);
	GotoXY(50, 27);
	cout << "< 14 character max >";
	DrawBoxMini(49, 3, 35, 14, CYAN);
	TextColor(BLUE);
	GotoXY(51, 13); cout << " Player 1's Name ";
	TextColor(RED);
	GotoXY(48, 15); cout << x << ' ';
	NamePlayer_O = NamePlayer_X = "";
	if (!EnterName(NamePlayer_O, 14)) {
		HideCursor(1);
		return 0;
	}
	if (!pvp) {
		NamePlayer_X = "BOT";
		HideCursor(1);
		return 1;
	}
	DrawBoxMini(49, 3, 35, 19, CYAN);
	TextColor(BLUE);
	GotoXY(51, 18); cout << " Player 2's Name ";
	TextColor(RED);
	GotoXY(48, 20); cout << x << ' ';
	if (!EnterName(NamePlayer_X, 14)) {
		HideCursor(1);
		return 0;
	}
	HideCursor(1);
	return 1;
}

// Đếm số lượt chơi và in ra màn hình console
void CntTurn(bool& _TURN, int& cntX, int& cntO, bool validEnter) {
	if (_TURN == false && validEnter == true)
		++cntX;
	else if (_TURN == true && validEnter == true)
		++cntO;
}

// Hiển thị lượt chơi
void ShowTurn(int _X, int _Y, bool _TURN, bool validEnter)
{
	int tmp = GetCurrentColor();
	TextColor(CYAN);
	if (_TURN == true && validEnter == true)
	{
		TurnX();
	}
	else if (_TURN == false && validEnter == true)
	{
		TurnO();
	}
	GotoXY(_X, _Y);
	TextColor(tmp);
}

void UnHoverCell(_POINT _A[B_SIZE][B_SIZE], int x, int y) {
	int tmp = GetCurrentColor();
	TextColor(BLUE);
	GotoXY(_A[x][y].x - 1, _A[x][y].y);
	if (_A[x][y].c == 0)
		cout << "   ";
	else if (_A[x][y].c == 1) {
		TextColor(O_COLOR);
		cout << " O ";
	}
	else {
		TextColor(X_COLOR);
		cout << " X ";
	}
	TextColor(tmp);
}

void HoverCell(_POINT _A[B_SIZE][B_SIZE], int x, int y) {
	int tmp = GetCurrentColor();
	//TextColor(BLUE & 15 | BACKGROUND_YELLOW);
	TextColor(YELLOW);
	GotoXY(_A[x][y].x - 1, _A[x][y].y);
	if (_A[x][y].c == 0)
		cout << L_TRIANGLE << " " << R_TRIANGLE;
	else if (_A[x][y].c == 1) {
		cout << L_TRIANGLE;
		//TextColor(O_COLOR & 15 | BACKGROUND_YELLOW);
		TextColor(O_COLOR);
		cout << "O";
		TextColor(YELLOW);
		cout << R_TRIANGLE;
	}
	else {
		cout << L_TRIANGLE;
		//TextColor(X_COLOR & 15 | BACKGROUND_YELLOW);
		TextColor(X_COLOR);
		cout << "X";
		TextColor(YELLOW);
		cout << R_TRIANGLE;
	}
	TextColor(tmp);
}

void HideCursor(bool ok) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = !ok;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void DrawSaveFilesPage(const vector <_BUTTON>& v, int curPage, int filesPerPage) {
	TextColor(YELLOW);
	GotoXY(WIDTH / 2 - 25, HEIGHT / 2 + 8);
	cout << "< ";
	if (curPage <= filesPerPage)
		cout << "0";
	cout << curPage << " / ";
	int nPages = ceil(1.0 * v.size() / filesPerPage);
	if (nPages <= filesPerPage)
		cout << 0;
	cout << nPages << " >";

	TextColor(CYAN);
	for (int i = (curPage - 1) * filesPerPage, cnt = 1; i < curPage * filesPerPage; i++, cnt++) {
		GotoXY(BOX_X + 1, BOX_Y + 2 * cnt - 1);
		for (int j = 1; j < BOX_W - 1; j++)
			cout << " ";
		if (i < v.size()) {
			GotoXY(v[i].x, v[i].y);
			Sleep(50);
			cout << v[i].data;
		}
	}
}

void DrawInfoFile(_POINT _A[B_SIZE][B_SIZE], bool& _TURN, int& pvp, int& _COMMAND, bool sound[], int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO, int& cntWinO, int& cntLoseO, int& cntDraw, int& saveTurn, int& cntRound, string& NamePlayer_O, string& NamePlayer_X, float& remain, WinningPos WP[5], string fileName) {
	LoadData(_A, _TURN, pvp, _COMMAND, _X, _Y, cX, cY, cntX, cntO, cntWinO, cntLoseO, cntDraw, saveTurn, cntRound, NamePlayer_O, NamePlayer_X, fileName, remain);
	int x = WIDTH / 2 + 15, y = HEIGHT / 2 - 11, w = 32, h = 9;
	ClearBox(w - 2, h - 2, x + 1, y + 1);
	TextColor(BLACK);
	GotoXY(x + 2, y + 2);
	TextColor(BLUE);
	for (int i = 2; i < w - 1; i++)
		cout << H_LINE;
	GotoXY(x + w / 2 - 4, y + 1);
	TextColor(BLACK);
	cout << "MODE: ";
	TextColor(YELLOW);
	cout << (pvp ? "PvP" : "PvC");
	GotoXY(x + 2, y + 3);
	TextColor(BLACK);
	cout << "Player O: ";
	TextColor(BLUE);
	cout<< NamePlayer_O;
	GotoXY(x + 2, y + 5);
	TextColor(BLACK);
	cout << "Player X: ";
	TextColor(RED);
	cout << NamePlayer_X;
	GotoXY(x + 2, y + 7);
	TextColor(BLACK);
	cout << "Round   : ";
	TextColor(GREEN);
	cout << cntRound;
	GotoXY(x + w / 2 + 2, y + 7);
	TextColor(BLACK);
	cout << "Score: ";
	TextColor(BLUE);
	cout << cntWinO;
	TextColor(BLACK);
	cout << " / ";
	TextColor(RED);
	cout << cntRound - cntDraw - cntWinO - 1;
	GotoXY(x + 2, y + h - 2);
	TextColor(BLUE);
}

int ChooseOptionLM(bool sound[]) {
	int x1 = WIDTH / 2 + 18, x2 = x1 + 16, y = HEIGHT / 2, w = 10, h = 3;
	DrawBoxMini(w, h, x2, y, BLACK);
	GotoXY(x2 + 2, y + 1);
	TextColor(BLACK);
	cout << "DELETE";
	DrawBoxMini(w, h, x1, y, RED);
	GotoXY(x1 + 3, y + 1);
	TextColor(RED);
	cout << "LOAD";
	int cur = 0;
	while (true) {
		char c = toupper(_getch());
		if (sound[CLICK_SFX]) PlayAudio(CLICK_SFX);
		if (c == A || c == D)
			cur ^= 1;
		if (c == ESC)
			return -1;
		if (c == ENTER)
			return cur;
		if (cur) {
			DrawBoxMini(w, h, x2, y, RED);
			GotoXY(x2 + 2, y + 1);
			TextColor(RED);
			cout << "DELETE";
			DrawBoxMini(w, h, x1, y, BLACK);
			GotoXY(x1 + 3, y + 1);
			TextColor(BLACK);
			cout << "LOAD";
		}
		else {
			DrawBoxMini(w, h, x2, y, BLACK);
			GotoXY(x2 + 2, y + 1);
			TextColor(BLACK);
			cout << "DELETE";
			DrawBoxMini(w, h, x1, y, RED);
			GotoXY(x1 + 3, y + 1);
			TextColor(RED);
			cout << "LOAD";
		}
	}
}

void LoadGameMenu(_POINT _A[B_SIZE][B_SIZE], bool& _TURN, int& pvp, int& _COMMAND, bool sound[], int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO, int& cntWinO, int& cntLoseO, int& cntDraw, int& saveTurn, int& cntRound, string& NamePlayer_O, string& NamePlayer_X, float& remain, WinningPos WP[5]) {
	// Open the file that contains all the name of the saved games.
	fstream inp;
	inp.open("save/all_save.txt", ios::in);
	if (inp.fail()) {
		cout << "Can't open file\n";
		return;
	}

	SetConsoleBlank();
	BackGround();
	DrawBox(BOX_W, BOX_H - 1, BOX_X, BOX_Y, GREEN, 1);
	TextColor(CYAN);

	// Get the current save data
	string nameFile;
	int filesPerPage = 9;
	vector <_BUTTON> v;
	while (inp.good()) {
		getline(inp, nameFile);
		if (v.size() == 1 && v[0].data == "")
			v[0].data = nameFile;
		else
			v.push_back({ 0, 0, nameFile });
	}
	inp.close();
	GotoXY(47, 26);
	TextColor(MAGENTA);
	cout << " " << L_TRIANGLE << " PRESS ESC TO COMEBACK " << R_TRIANGLE << " ";
	DrawBoxMini(32, 9, WIDTH / 2 + 15, HEIGHT / 2 - 11, BLUE);
	if (v.size() == 1 && v[0].data == "") {
		GotoXY(34, 11);
		cout << "< EMPTY DATA >";
		while (true) {
			char c = toupper(_getch());
			if (sound[CLICK_SFX]) PlayAudio(CLICK_SFX);
			if (c == ESC)
				return;
		}
	}
	for (int i = 0, cnt = 1; i < v.size(); i++, cnt = cnt % filesPerPage + 1) {
		v[i].x = BOX_X + 1;
		v[i].y = BOX_Y + 2 * cnt - 1;
		int x = (BOX_W - 2 - v[i].data.size()) / 2;
		if (v[i].data.size() % 2 == 1)
			v[i].data += " ";
		while (x--)
			v[i].data = " " + v[i].data, v[i].data += " ";
	}
	int nFiles = v.size();
	int nPages = ceil(1.0 * nFiles / filesPerPage);
	DrawSaveFilesPage(v, 1, filesPerPage);
	int curFile = 0, prvFile = -1, curPage = 1, lastFile = 0;
	HoverButton(v[curFile]);
	GotoXY(0, 0);
	while (true) {
		if (v.empty()) {
			ClearBox(BOX_W - 2, BOX_H - 3, BOX_X + 1, BOX_Y + 1);
			GotoXY(34, 11);
			TextColor(MAGENTA);
			cout << "< EMPTY DATA >";
			int x1 = WIDTH / 2 + 18, x2 = x1 + 16, y = HEIGHT / 2, w = 10, h = 3;
			ClearBox(w, h, x2, y);
			ClearBox(w, h, x1, y);
			ClearBox(30, 7, WIDTH / 2 + 16, HEIGHT / 2 - 10);
			while (true) {
				char c = toupper(_getch());
				if (sound[CLICK_SFX]) PlayAudio(CLICK_SFX);
				if (c == ESC)
					return;
			}
		}
		DrawInfoFile(_A, _TURN, pvp, _COMMAND, sound, _X, _Y, cX, cY, cntX, cntO, cntWinO, cntLoseO, cntDraw, saveTurn, cntRound, NamePlayer_O, NamePlayer_X, remain, WP, CleanFileName(v[(curPage - 1) * filesPerPage + curFile].data));
		int _COMMAND = toupper(_getch());
		if (sound[CLICK_SFX]) PlayAudio(CLICK_SFX);
		lastFile = (curPage == nPages ? (nFiles - 1) % filesPerPage : filesPerPage - 1);
		if (_COMMAND == ESC) {
			return;
		}
		else if (_COMMAND == W) {
			prvFile = curFile--;
			if (curFile < 0)
				curFile = lastFile;
		}
		else if (_COMMAND == S) {
			prvFile = curFile++;
			if (curFile > lastFile)
				curFile = 0;
		}
		else if (_COMMAND == A) {
			if (--curPage < 1)
				curPage = nPages;
			prvFile = curFile;
			DrawSaveFilesPage(v, curPage, filesPerPage);
		}
		else if (_COMMAND == D) {
			curPage++;
			if (curPage > nPages)
				curPage = 1;
			prvFile = curFile;
			DrawSaveFilesPage(v, curPage, filesPerPage);
		}
		else if (_COMMAND == ENTER) {
			int option = ChooseOptionLM(sound);
			if (option < 0) {
				int x1 = WIDTH / 2 + 18, x2 = x1 + 16, y = HEIGHT / 2, w = 10, h = 3;
				ClearBox(w, h, x2, y);
				ClearBox(w, h, x1, y);
				continue;
			}
			else if (option) {
				string delCommand = "del save\\data\\";
				delCommand += '"' + CleanFileName(v[(curPage - 1) * filesPerPage + curFile].data) + ".txt" + '"';
				system(delCommand.c_str());
				for (int i = (curPage - 1) * filesPerPage + curFile; i < nFiles - 1; i++)
					v[i].data = v[i + 1].data;
				v.pop_back();
				fstream out;
				out.open("save/all_save.txt", ios::out);
				for (int i = 0; i < v.size(); i++) {
					if (i)
						out << endl;
					out << CleanFileName(v[i].data);
				}
				out.close();
				nFiles--;
				curFile = 0, prvFile = -1, lastFile = 0, curPage = 1, nPages = ceil(1.0 * nFiles / filesPerPage);
				int x1 = WIDTH / 2 + 18, x2 = x1 + 16, y = HEIGHT / 2, w = 10, h = 3;
				ClearBox(w, h, x2, y);
				ClearBox(w, h, x1, y);
				if (v.size()) {
					DrawSaveFilesPage(v, curPage, filesPerPage);
					HoverButton(v[curFile + filesPerPage * (curPage - 1)]);
				}
				continue;
			}
			//LoadData(_A, _TURN, pvp, _COMMAND, _X, _Y, cX, cY, cntX, cntO, cntWinO, cntLoseO, cntDraw, saveTurn, cntRound, NamePlayer_O, NamePlayer_X, CleanFileName(v[(curPage - 1) * filesPerPage + curFile].data), remain);
			//LoadingScreen(BLUE, GREEN, LIGHT_CYAN);
			StartGame(_A, 0, _TURN, pvp, _COMMAND, sound, _X, _Y, cX, cY, cntX, cntO, cntWinO, cntLoseO, cntDraw, saveTurn, cntRound, NamePlayer_O, NamePlayer_X, remain, WP);
			return;
		}
		
		lastFile = (curPage == nPages ? (nFiles - 1) % filesPerPage : filesPerPage - 1);
		
		if (curFile + filesPerPage * (curPage - 1) >= nFiles)
			prvFile = curFile = lastFile;
		UnhoverButton(v[prvFile + filesPerPage * (curPage - 1)], CYAN);
		HoverButton(v[curFile + filesPerPage * (curPage - 1)]);
	}
}

void DrawSaveFilesPageInPauseMenu(const vector <_BUTTON>& v, int curPage, int filesPerPage) {
	TextColor(MAGENTA);
	GotoXY(84, 15);
	for (int i = 0; i < 24; i++)
		cout << H_LINE;
	TextColor(BLACK);
	GotoXY(90, 16);
	cout << "< ";
	if (curPage <= filesPerPage)
		cout << "0";
	cout << curPage << " / ";
	int nPages = ceil(1.0 * v.size() / filesPerPage);
	if (nPages <= filesPerPage)
		cout << 0;
	cout << nPages << " >";

	TextColor(BLUE);
	for (int i = (curPage - 1) * filesPerPage, cnt = 0; i < curPage * filesPerPage; i++, cnt++) {
		GotoXY(79, 4 + 2 * cnt);
		for (int j = 0; j < 30; j++)
			cout << " ";
		if (i < v.size()) {
			GotoXY(v[i].x, v[i].y);
			Sleep(50);
			cout << v[i].data;
		}
	}
}

bool LoadGameInPauseMenu(_POINT _A[B_SIZE][B_SIZE], bool& _TURN, int& pvp, int& _COMMAND, bool sound[], int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO, int& cntWinO, int& cntLoseO, int& cntDraw, int& saveTurn, int& cntRound, string& NamePlayer_O, string& NamePlayer_X, float& remain, float& lastPressed, WinningPos WP[5]) {
	// Open the file that contains all the name of the saved games.
	fstream inp;
	inp.open("save/all_save.txt", ios::in);
	if (inp.fail()) {
		cout << "Can't open file\n";
		return 0;
	}
	// Get the current save data
	string nameFile;
	int filesPerPage = 6;
	vector <_BUTTON> v;
	while (inp.good()) {
		getline(inp, nameFile);
		if (v.size() == 1 && v[0].data == "")
			v[0].data = nameFile;
		else
			v.push_back({ 0, 0, nameFile });
	}
	inp.close();
	if (v.size() == 1 && v[0].data == "") {
		GotoXY(89, 9);
		TextColor(BLACK);
		cout << "< EMPTY DATA >";
		while (true) {
			char c = toupper(_getch());
			if (sound[CLICK_SFX]) PlayAudio(CLICK_SFX);
			if (c == ESC)
				return 0;
		}
	}
	for (int i = 0, cnt = 1; i < v.size(); i++, cnt = cnt % filesPerPage + 1) {
		v[i].x = 84;
		v[i].y = 3 + 2 * cnt - 1;
		int x = (24 - v[i].data.size()) / 2;
		if (v[i].data.size() % 2 == 1)
			v[i].data += " ";
		while (x--)
			v[i].data = " " + v[i].data, v[i].data += " ";
	}
	int nFiles = v.size();
	int nPages = ceil(1.0 * nFiles / filesPerPage);
	DrawSaveFilesPageInPauseMenu(v, 1, filesPerPage);
	int curFile = 0, prvFile = -1, curPage = 1, lastFile = 0;
	HoverButton(v[curFile]);
	while (true) {
		int _COMMAND = toupper(_getch());
		if (sound[CLICK_SFX]) PlayAudio(CLICK_SFX);
		lastFile = (curPage == nPages ? (nFiles - 1) % filesPerPage : filesPerPage - 1);
		if (_COMMAND == ESC) {
			return 0;
		}
		else if (_COMMAND == W) {
			prvFile = curFile--;
			if (curFile < 0)
				curFile = lastFile;
		}
		else if (_COMMAND == S) {
			prvFile = curFile++;
			if (curFile > lastFile)
				curFile = 0;
		}
		else if (_COMMAND == A) {
			if (--curPage < 1)
				curPage = nPages;
			prvFile = curFile;
			DrawSaveFilesPageInPauseMenu(v, curPage, filesPerPage);
		}
		else if (_COMMAND == D) {
			curPage++;
			if (curPage > nPages)
				curPage = 1;
			prvFile = curFile;
			DrawSaveFilesPageInPauseMenu(v, curPage, filesPerPage);
		}
		else if (_COMMAND == ENTER) {
			LoadData(_A, _TURN, pvp, _COMMAND, _X, _Y, cX, cY, cntX, cntO, cntWinO, cntLoseO, cntDraw, saveTurn, cntRound, NamePlayer_O, NamePlayer_X, CleanFileName(v[(curPage - 1) * filesPerPage + curFile].data), remain);
			//LoadingScreen(BLUE, GREEN, LIGHT_CYAN);
			StartGame(_A, 0, _TURN, pvp, _COMMAND, sound, _X, _Y, cX, cY, cntX, cntO, cntWinO, cntLoseO, cntDraw, saveTurn, cntRound, NamePlayer_O, NamePlayer_X, remain, WP);
			return 1;
		}

		lastFile = (curPage == nPages ? (nFiles - 1) % filesPerPage : filesPerPage - 1);

		if (curFile + filesPerPage * (curPage - 1) >= nFiles)
			prvFile = curFile = lastFile;
		UnhoverButton(v[prvFile + filesPerPage * (curPage - 1)], BLUE);
		HoverButton(v[curFile + filesPerPage * (curPage - 1)]);
	}
}

void DrawCaroBox(int w, int h, int x, int y, int Time)
{
	TextColor(GREEN);
	GotoXY(x + w / 2, y);
	for (int i = 0; i < w / 2; i++)
	{
		GotoXY(x + w / 2 + i, y);
		cout << BOX_H_LINE;
		GotoXY(x + w / 2 - i, y);
		cout << BOX_H_LINE;
		Sleep(Time);
	}
	GotoXY(x, y);
	cout << BOX_TOP_LEFT;
	GotoXY(x + w, y);
	cout << BOX_TOP_RIGHT;

	for (int i = 1; i < h - 1; i++) {
		GotoXY(x, i + y);
		cout << BOX_V_LINE;
		for (int j = 1; j < w; j++)
			cout << SPACE;
		cout << BOX_V_LINE;
		Sleep(Time);
	}

	GotoXY(x, h + y - 1);
	cout << BOX_BOTTOM_LEFT;
	GotoXY(x + w, h + y - 1);
	cout << BOX_BOTTOM_RIGHT;
	GotoXY(x, y + h - 5);
	cout << BOX_LEFT;
	GotoXY(x + w, y + h - 5);
	cout << BOX_RIGHT;
	for (int i = 1; i <= w / 2; i++)
	{
		GotoXY(x + i, y + h - 1);
		cout << BOX_H_LINE;
		GotoXY(x + w - i, y + h - 1);
		cout << BOX_H_LINE;
		GotoXY(x + i, y + h - 5);
		cout << BOX_H_LINE;
		GotoXY(x + w - i, y + h - 5);
		cout << BOX_H_LINE;
		Sleep(Time);
	}
	DrawBoxMini(59, 13, 14, 6, LIGHT_YELLOW);
	CaroAnimation();
	Sleep(500);
	PrintNote(24, 21, BLACK);

}

void MainScreen() {
	BackGround();
	DrawCaroBox(62, 19, 12, 5, 5);
	Sleep(500);
	DrawButton();
}

void MainMenu(_POINT _A[B_SIZE][B_SIZE], bool& _TURN, int& pvp, int& _COMMAND, bool sound[], int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO, int& cntWinO, int& cntLoseO, int& cntDraw, int& saveTurn, int& cntRound, string& NamePlayer_O, string& NamePlayer_X, float& remain, WinningPos WP[5])
{
	Sleep(50);
	SetConsoleBlank();
	BackGround();
	MainScreen();

	int x = 94;
	int y = 7;
	DrawBoxMini(14, 3, 89, y - 1, RED);
	GotoXY(x, y); // Đưa cursor tới phím chức năng đầu tiên.
	TextColor(RED);
	cout << "PLAY";
	while (true)
	{
		unsigned char c = toupper(_getch());
		if (sound[CLICK_SFX]) PlayAudio(CLICK_SFX);
		if (c == 'W' || c == 'S')
		{
			//c = _getch();
			if (c == 'W')
			{
				// Đưa lại nút cũ về màu xanh
				DrawBoxMini(14, 3, 89, y - 1, BLUE);
				TextColor(BLUE);
				if (y == 7)
				{
					GotoXY(x, y);
					cout << "PLAY";
				}
				if (y == 10)
				{
					GotoXY(x, y);
					cout << "LOAD";
				}
				if (y == 13)
				{
					GotoXY(x, y);
					cout << "HELP";
				}
				if (y == 16)
				{
					GotoXY(x - 1, y);
					cout << "OPTION";
				}
				if (y == 19)
				{
					GotoXY(x, y);
					cout << "EXIT";
				}
				y = y - 3;
				if (y < 7)
					y = 19;
				//Biến nút đang trỏ vào thành màu đỏ 
				DrawBoxMini(14, 3, 89, y - 1, RED);
				TextColor(RED);
				if (y == 7)
				{
					GotoXY(x, y);
					cout << "PLAY";
				}
				if (y == 10)
				{
					GotoXY(x, y);
					cout << "LOAD";
				}
				if (y == 13)
				{
					GotoXY(x, y);
					cout << "HELP";
				}
				if (y == 16)
				{
					GotoXY(x - 1, y);
					cout << "OPTION";
				}
				if (y == 19)
				{
					GotoXY(x, y);
					cout << "EXIT";
				}
			}
			else if (c == 'S')
			{
				DrawBoxMini(14, 3, 89, y - 1, BLUE);
				TextColor(BLUE);
				if (y == 7)
				{
					GotoXY(x, y);
					cout << "PLAY";
				}
				if (y == 10)
				{
					GotoXY(x, y);
					cout << "LOAD";
				}
				if (y == 13)
				{
					GotoXY(x, y);
					cout << "HELP";
				}
				if (y == 16)
				{
					GotoXY(x - 1, y);
					cout << "OPTION";
				}
				if (y == 19)
				{
					GotoXY(x, y);
					cout << "EXIT";
				}
				y = y + 3;
				if (y > 19)
					y = 7;
				DrawBoxMini(14, 3, 89, y - 1, RED);
				TextColor(RED);

				if (y == 7)
				{
					GotoXY(x, y);
					cout << "PLAY";
				}
				if (y == 10)
				{
					GotoXY(x, y);
					cout << "LOAD";
				}
				if (y == 13)
				{
					GotoXY(x, y);
					cout << "HELP";
				}
				if (y == 16)
				{
					GotoXY(x - 1, y);
					cout << "OPTION";
				}
				if (y == 19)
				{
					GotoXY(x, y);
					cout << "EXIT";
				}
			}
		}
		else if ((c == 32) || (c == 13)) // Tương tác với phím bằng cách bấm Enter hoặc Space
		{
			if (y == 7)
			{
				pvp = ChooseMode(sound);
				if (pvp == -1) {
					pvp = 0;
					return;
				}
				if (!EnterNamePlayer(NamePlayer_O, NamePlayer_X, pvp))
					return;
				AskTurn(_TURN, sound, NamePlayer_O, NamePlayer_X, pvp);
				cntWinO = cntLoseO = cntDraw = 0;
				cntRound = 1;
				StartGame(_A, 1, _TURN, pvp, _COMMAND, sound, _X, _Y, cX, cY, cntX, cntO, cntWinO, cntLoseO, cntDraw, saveTurn, cntRound, NamePlayer_O, NamePlayer_X, remain, WP);
				return;
			}
			if (y == 10)
			{
				LoadGameMenu(_A, _TURN, pvp, _COMMAND, sound, _X, _Y, cX, cY, cntX, cntO, cntWinO, cntLoseO, cntDraw, saveTurn, cntRound, NamePlayer_O, NamePlayer_X, remain, WP);
				return;
			}
			if (y == 13)
			{
				HelpScreen(sound);
				return;
			}
			if (y == 16)
			{
				SettingMenu(sound);
				return;
			}
			if (y == 19)
			{
				ExitGame();
			}
		}
	}
}

void HelpScreen(bool sound[])
{
	SetConsoleBlank();
	DrawBox(98, 25, 11, 2, CYAN, 0);
	DrawBoxMini(94, 23, 13, 3, LIGHT_CYAN);
	for (int i = 0; i < 21; i++)
	{
		TextColor(LIGHT_CYAN);
		GotoXY(34, 4 + i);
		cout << V_LINE;
	}

	TextColor(RED);
	GotoXY(20, 8);
	cout << L_TRIANGLE << " RULE " << R_TRIANGLE;
	GotoXY(40, 5);
	cout << "The game is played on a board with 12 rows and 12 columns." << endl;
	GotoXY(40, 7);
	cout << "To win the round, player needs to make a line consisting of 5" << endl;
	GotoXY(40, 8);
	cout << "consecutive pieces of the same type horizontally, vertically or" << endl;
	GotoXY(40, 9);
	cout << "diagonally. Time for each turn is 15 seconds." << endl;
	GotoXY(40, 11);
	cout << "If more than 90% of the board has been marked, the result will ";
	GotoXY(40, 12);
	cout << "be a draw.";

	TextColor(GREEN);
	GotoXY(20, 15);
	cout << L_TRIANGLE << " MOVE " << R_TRIANGLE;
	GotoXY(40, 15);
	cout << "Up: W";
	GotoXY(40, 16);
	cout << "Down: S";
	GotoXY(55, 15);
	cout << "Left: A";
	GotoXY(55, 16);
	cout << "Right: D";
	GotoXY(70, 15);
	cout << "Choose: Enter";
	GotoXY(70, 16);
	cout << "Pause game: Esc";

	TextColor(MAGENTA);
	GotoXY(18, 21);
	cout << L_TRIANGLE << " ABOUT US " << R_TRIANGLE;
	GotoXY(76, 20);
	cout << "Teacher: Truong Toan Thinh";
	GotoXY(76, 21);
	cout << "Group: 13";
	GotoXY(76, 22);
	cout << "22CTT4 - HCMUS";
	GotoXY(40, 19);
	cout << "Dang Duy Lan      -  22120182";
	GotoXY(40, 20);
	cout << "Nguyen Nhat Long  -  22120194";
	GotoXY(40, 21);
	cout << "Hoang Thanh Man   -  22120200";
	GotoXY(40, 22);
	cout << "Ly Truong Nam     -  22120218";
	GotoXY(40, 23);
	cout << "Tran Thao Ngan    -  22120225";
	TextColor(LIGHT_RED);
	GotoXY(47, 26);
	cout << " " << L_TRIANGLE << " PRESS ESC TO COMEBACK " << R_TRIANGLE << " ";
	while (true) {
		char c = _getch();
		if (sound[CLICK_SFX]) PlayAudio(CLICK_SFX);
		if (c == ESC)
			return;
	}
}

void LoadingScreen(int color1, int color2, int color3) //color 1 la mau khung, 2 la mau chu, 3 la mau cai thanh o giua
{
	SetConsoleBlank();
	unsigned char s = { 219 };
	DrawBoxMini(51, 3, 34, 13, color1);
	GotoXY(55, 17);
	TextColor(color2);
	cout << "LOADING...";
	GotoXY(36, 14);
	for (int i = 0; i < 34; i++)
	{
		TextColor(color3);
		cout << s;
		Sleep(10);
	}
	Sleep(200);
	GotoXY(70, 14);
	for (int i = 0; i < 13; i++)
	{
		TextColor(color3);
		cout << s;
		Sleep(10);
	}
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

void SettingMenu(bool sound[]) {
	SetConsoleBlank();
	DrawPattern_Col(1, 6, MAGENTA, 4, 6);
	DrawPattern_Col(4, 24, LIGHT_MAGENTA, 4, 6);
	DrawPattern_Col(1, 42, MAGENTA, 4, 6);
	DrawPattern_Col(4, 60, LIGHT_MAGENTA, 4, 6);
	DrawPattern_Col(1, 78, MAGENTA, 4, 6);
	DrawPattern_Col(4, 96, LIGHT_MAGENTA, 4, 6);
	DrawPattern_Col(1, 114, MAGENTA, 4, 6);
	DrawBox(34, 15, 19, 6, BLACK, 0);
	DrawBox(34, 15, 67, 6, BLACK, 0);
	TextColor(RED);
	GotoXY(32, 8); cout << "< MUSIC >";
	GotoXY(78, 8); cout << "< CLICK SFX >";

	DrawBoxMini(15, 3, 29, 11, RED);
	TextColor(BLUE);
	DrawBoxMini(15, 3, 29, 14, GRAY);
	TextColor(RED);
	GotoXY(30, 12); cout << L_TRIANGLE << "  TURN ON  " << R_TRIANGLE;
	TextColor(BLUE);
	GotoXY(33, 15); cout << "TURN OFF";

	DrawBoxMini(15, 3, 77, 11, GRAY);
	DrawBoxMini(15, 3, 77, 14, GRAY);
	GotoXY(81, 12); cout << "TURN ON";
	GotoXY(81, 15); cout << "TURN OFF";

	int m = 2, n = 2, i = 0, j = 0;
	_POINT a[2][2];
	a[0][0] = { 29, 11, 0 };
	a[1][0] = { 29, 14, 0 };
	a[0][1] = { 77, 11, 0 };
	a[1][1] = { 77, 14, 0 };
	TextColor(BLACK);
	GotoXY(48, 25); cout << "- PRESS ESC TO COMEBACK -";
	TextColor(BLUE);
	string unhoverOn = "   TURN ON   ", unhoverOff = "   TURN OFF  ";
	string hoverOn = "   TURN ON   ", hoverOff = "   TURN OFF  ";
	hoverOn[0] = L_TRIANGLE; hoverOn.back() = R_TRIANGLE;
	hoverOff[0] = L_TRIANGLE; hoverOff.back() = R_TRIANGLE;
	while (true) {
		char c = toupper(_getch());
		int newI = i, newJ = j;
		if (c == ESC)
			return;
		else if (c == ENTER) {
			if (i * m + j == 0)
				SetSound(sound, BGM, 1);
			else if (i * m + j == 2)
				SetSound(sound, BGM, 0);
			else if (i * m + j == 1)
				SetSound(sound, CLICK_SFX, 1);
			else
				SetSound(sound, CLICK_SFX, 0);
			if (sound[CLICK_SFX]) PlayAudio(CLICK_SFX);
			continue;
		}
		else if (c == W)
			newI = (--newI + m) % m;
		else if (c == S)
			newI = ++newI % m;
		else if (c == A)
			newJ = (--newJ + n) % n;
		else if (c == D)
			newJ = ++newJ % n;
		DrawBoxMini(15, 3, a[i][j].x, a[i][j].y, GRAY);
		TextColor(BLUE);
		GotoXY(a[i][j].x + 1, a[i][j].y + 1); cout << (i * m + j < 2 ? unhoverOn : unhoverOff);
		i = newI, j = newJ;
		DrawBoxMini(15, 3, a[i][j].x, a[i][j].y, RED);
		TextColor(RED);
		GotoXY(a[i][j].x + 1, a[i][j].y + 1); cout << (i * m + j < 2 ? hoverOn : hoverOff);
		if (sound[CLICK_SFX]) PlayAudio(CLICK_SFX);
	}
}

void VeX1(int x, int y, int color) {
	TextColor(color);
	SetConsoleOutputCP(65001);
	ifstream Read("assets/UI/VeX1.txt");
	string line = "";
	for (int i = 0; Read.good(); i++) {
		getline(Read, line);
		GotoXY(x, y + i);
		cout << line;
	}
	Read.close();
	SetConsoleOutputCP(437);
}

void VeX2(int x, int y, int color) {
	TextColor(color);
	SetConsoleOutputCP(65001);
	ifstream Read("assets/UI/VeX2.txt");
	string line = "";
	for (int i = 0; Read.good(); i++) {
		getline(Read, line);
		GotoXY(x, y + i);
		cout << line;
	}
	Read.close();
	SetConsoleOutputCP(437);
}

void VeO1(int x, int y, int color) {
	TextColor(color);
	SetConsoleOutputCP(65001);
	ifstream Read("assets/UI/VeO1.txt");
	string line = "";
	for (int i = 0; Read.good(); i++) {
		getline(Read, line);
		GotoXY(x - (i == 0), y + i);
		cout << line;
	}
	Read.close();
	SetConsoleOutputCP(437);
}

void VeO2(int x, int y, int color) {
	TextColor(color);
	SetConsoleOutputCP(65001);
	ifstream Read("assets/UI/VeO2.txt");
	string line = "";
	for (int i = 0; Read.good(); i++) {
		getline(Read, line);
		GotoXY(x - (i == 0), y + i);
		cout << line;
	}
	Read.close();
	SetConsoleOutputCP(437);
}

void TurnX() {
	VeO1(95, 4, GRAY);
	VeX2(74, 4, RED);
}

void TurnO() {
	VeO2(95, 4, BLUE);
	VeX1(74, 4, GRAY);
}

string getFileContents(ifstream& File)
{
	string Lines = "";        //All lines

	if (File)                      //Check if everything is good
	{
		while (File.good())
		{
			string TempLine;                  //Temp line
			getline(File, TempLine);        //Get temp line
			TempLine += "\n";                      //Add newline character

			Lines += TempLine;                     //Add newline
		}
		Lines.pop_back();
		return Lines;
	}
	else                           //Return error
	{
		return "ERROR File does not exist.";
	}
}

void DrawAsciiFile(int x, int y, string nameFile, int color) {
	TextColor(color);
	SetConsoleOutputCP(65001);
	GotoXY(x, y);
	ifstream Read("assets/UI/" + nameFile + ".txt");
	string Art = getFileContents(Read);
	cout << Art << endl;
	Read.close();
	SetConsoleOutputCP(437);
}

void DrawTimer(float time, bool _TURN) {
	time = float(int(time * 100)) / 100;
	int num[2] = { 0 };
	num[0] = (int)ceil(time) / 10;
	num[1] = (int)ceil(time) % 10;
	for (int i = 0; i < 2; i++)
		DrawNumber(80 + i * 10 - (i == 1 && (num[0] == 1 || num[1] == 9)), 20, num[i], (num[0] == 0 && num[1] <= 5 ? RED : YELLOW));
}

bool PauseGame(_POINT _A[B_SIZE][B_SIZE], bool& _TURN, int& pvp, int& _COMMAND, bool sound[], int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO, int& cntWinO, int& cntLoseO, int& cntDraw, int& saveTurn, int& cntRound, string& NamePlayer_O, string& NamePlayer_X, float& remain, float& lastPressed, WinningPos WP[5]) {
	remain += lastPressed - clock();
	ClearBox(49, 15, 64, 3);
	TextColor(BLACK);
	GotoXY(87, 1);
	cout << "PAUSED";
	TextColor(LIGHT_MAGENTA);
	GotoXY(63, 10);
	cout << BOX_V_LINE;
	GotoXY(113, 10);
	cout << BOX_V_LINE;
	for (int i = 0; i < 15; i++) {
		GotoXY(78, 3 + i);
		cout << V_LINE;
	}
	int x = 65, y = 4;
	vector <_BUTTON> button;
	button.resize(5);
	button[0].data = "    SAVE    ";
	button[1].data = "    LOAD    ";
	button[2].data = "   OPTION   ";
	button[3].data = "   RESUME   ";
	button[4].data = "    EXIT    ";
	for (int i = 0; i < button.size(); i++) {
		button[i].x = x;
		button[i].y = y + 3 * i;
	}
	TextColor(BLACK);
	int n = button.size();
	for (int i = 0; i < n; i++) {
		GotoXY(button[i].x, button[i].y);
		cout << button[i].data;
	}
	char c;
	int cur = 0, prv = -1;
	bool ok = 0;
	HoverButton(button[cur]);
	while (true) {
		c = toupper(_getch());
		if (sound[CLICK_SFX]) PlayAudio(CLICK_SFX);
		if (c == ESC)
			break;
		else if (c == W || c == S) {
			if (c == W)
				prv = cur--;
			else
				prv = cur++;
			if (cur < 0)
				cur = n - 1;
			if (cur >= n)
				cur = 0;
			UnhoverButton(button[prv], BLACK);
			HoverButton(button[cur]);
		}
		else if (c == ENTER) {
			if (cur == 4) {
				ok = 1;
				break;
			}
			if (cur == 3)
				break;
			if (cur == 1) {
				UnhoverButton(button[cur], BLACK);
				bool ok = LoadGameInPauseMenu(_A, _TURN, pvp, _COMMAND, sound, _X, _Y, cX, cY, cntX, cntO, cntWinO, cntLoseO, cntDraw, saveTurn, cntRound, NamePlayer_O, NamePlayer_X, remain, lastPressed, WP);
				if (ok)
					return 1;
				ClearBox(34, 15, 79, 3);
				HoverButton(button[cur]);
			}
			else if (cur == 0) {
				UnhoverButton(button[cur], BLACK);
				string fileName = "";
				GotoXY(88, 6);
				TextColor(GREEN);
				cout << "ENTER FILE NAME: ";
				DrawBoxMini(25, 3, 84, 8, BLACK);
				GotoXY(85, 9);
				cout << L_TRIANGLE << ' ';
				HideCursor(0);
				bool ok = EnterName(fileName, 20);
				if (ok) {
					SaveData(_A, _TURN, pvp, _COMMAND, _X, _Y, cX, cY, cntX, cntO, cntWinO, cntLoseO, cntDraw, saveTurn, cntRound, NamePlayer_O, NamePlayer_X, fileName, remain);
					GotoXY(87, 13);
					cout << "SAVED SUCCESSFULLY!";
				}
				HideCursor(1);
				while (ok) {
					char c = toupper(_getch());
					if (sound[CLICK_SFX]) PlayAudio(CLICK_SFX);
					break;
				}
				ClearBox(34, 15, 79, 3);
				HoverButton(button[cur]);
			}
			else {
				UnhoverButton(button[cur], BLACK);
				GotoXY(83, 4); cout << "MUSIC";
				GotoXY(83, 11); cout << "CLICK_SFX";
				TextColor(BLACK);
				GotoXY(86, 6); cout << "TURN ON";
				DrawBoard(1, 1, 98, 5, BLACK);
				GotoXY(86, 9); cout << "TURN OFF";
				DrawBoard(1, 1, 98, 8, BLACK);
				
				GotoXY(86, 13); cout << "TURN ON";
				DrawBoard(1, 1, 98, 12, BLACK);
				GotoXY(86, 16); cout << "TURN OFF";
				DrawBoard(1, 1, 98, 15, BLACK);
				int n = 4, i = 0;
				_POINT a[4];
				a[0] = { 99, 6, 0 };
				a[1] = { 99, 9, 0 };
				a[2] = { 99, 13, 0 };
				a[3] = { 99, 16, 0 };
				GotoXY(a[i].x, a[i].y); cout << L_TRIANGLE;
				GotoXY(a[i].x + 2, a[i].y); cout << R_TRIANGLE;
				if (sound[BGM])
					GotoXY(a[0].x + 1, a[0].y), cout << "X";
				else
					GotoXY(a[1].x, a[1].y), cout << " X ";
				if (sound[CLICK_SFX])
					GotoXY(a[2].x, a[2].y), cout << " X ";
				else
					GotoXY(a[3].x, a[3].y), cout << " X ";
				while (true) {
					char c = toupper(_getch());
					if (c == ESC) {
						if (sound[CLICK_SFX]) PlayAudio(CLICK_SFX);
						break;
					}
					int newI = i;
					if (c == ENTER) {
						if (i == 0) {
							GotoXY(a[0].x + 1, a[0].y);
							cout << "X";
							GotoXY(a[1].x + 1, a[1].y);
							cout << " ";
							SetSound(sound, BGM, 1);
						}
						else if (i == 1) {
							GotoXY(a[1].x + 1, a[1].y);
							cout << "X";
							GotoXY(a[0].x + 1, a[0].y);
							cout << " ";
							SetSound(sound, BGM, 0);
						}
						else if (i == 2) {
							GotoXY(a[2].x + 1, a[2].y);
							cout << "X";
							GotoXY(a[3].x + 1, a[3].y);
							cout << " ";
							SetSound(sound, CLICK_SFX, 1);
						}
						else {
							GotoXY(a[3].x + 1, a[3].y);
							cout << "X";
							GotoXY(a[2].x + 1, a[2].y);
							cout << " ";
							SetSound(sound, CLICK_SFX, 0);
						}
						if (sound[CLICK_SFX]) PlayAudio(CLICK_SFX);
						continue;
					}
					else if (c == W)
						newI = (--newI + n) % n;
					else if (c == S)
						newI = ++newI % n;
					GotoXY(a[i].x, a[i].y); cout << ' ';
					GotoXY(a[i].x + 2, a[i].y); cout << ' ';
					i = newI;
					GotoXY(a[i].x, a[i].y); cout << L_TRIANGLE;
					GotoXY(a[i].x + 2, a[i].y); cout << R_TRIANGLE;
					if (sound[CLICK_SFX]) PlayAudio(CLICK_SFX);
				}
				ClearBox(34, 15, 79, 3);
				HoverButton(button[cur]);
			}
		}
	}
	TextColor(BLACK);
	GotoXY(87, 1);
	cout << "      ";
	lastPressed = clock();
	return ok;
}

void DrawTimerBox(bool _TURN) {
	DrawBox(23, 9, 77, 19, (_TURN ? O_COLOR : X_COLOR), 0);
	//DrawAsciiFile(68 + 2 * 10, 26, "Dot", YELLOW);
}

void DrawScoreBoard(bool _TURN, int _X, int _Y, int cntWinO, int cntLoseO, int cntRound) {
	unsigned char p = 219;
	DrawBox(51, 17, 63, 2, LIGHT_MAGENTA, 0);
	for (int i = 0; i < 47; i++)
	{
		TextColor(MAGENTA);
		GotoXY(6 + i, 1); cout << H_LINE;
	}
	TextColor(BLACK);
	GotoXY(23, 1);
	cout << " - ROUND " << cntRound << " - ";
	ShowTurn(_X, _Y, !_TURN, true);
	TextColor(LIGHT_MAGENTA);
	DrawNumber(74, 11, cntLoseO, LIGHT_CYAN);
	DrawNumber(96, 11, cntWinO, LIGHT_CYAN);
	GotoXY(88, 13); cout << p << p;
	GotoXY(88, 15); cout << p << p;

	TextColor(LIGHT_MAGENTA);
	GotoXY(63, 10); cout << BOX_LEFT;
	for (int i = 0; i < 49; i++)
	{
		GotoXY(64 + i, 10);
		cout << BOX_H_LINE;
	}
	cout << BOX_RIGHT;
	TextColor(BLUE);
	GotoXY(83, 10); cout << " - SCORE - ";
}

void DrawGameInfo(_POINT _A[B_SIZE][B_SIZE], bool _TURN, int _X, int _Y, int cX, int cY, int cntWinO, int cntLoseO, int cntRound) {
	DrawBoard(B_SIZE, B_SIZE, BOARD_X, BOARD_Y, BLACK);
	TextColor(MAGENTA);
	for (int i = 2; i < 27; i++) {
		GotoXY(WIDTH / 2 - 2, i);
		cout << V_LINE;
	}
	DrawScoreBoard(_TURN, _X, _Y, cntWinO, cntLoseO, cntRound);
	DrawTimerBox(_TURN);
	for (int i = 0; i < B_SIZE; i++)
		for (int j = 0; j < B_SIZE; j++)
			if (_A[i][j].c == -1) {
				GotoXY(_A[i][j].x, _A[i][j].y);
				TextColor(X_COLOR);
				cout << 'X';
			}
			else if (_A[i][j].c == 1) {
				GotoXY(_A[i][j].x, _A[i][j].y);
				TextColor(O_COLOR);
				cout << 'O';
			}
	HoverCell(_A, cY, cX);
}

void DrawNumber(int x, int y, int number, int color) {
	TextColor(color);
	SetConsoleOutputCP(65001);
	string f = "assets/UI/Number/";
	f += char('0' + number);
	f += ".txt";
	ifstream Read(f);
	string line = "";
	for (int i = 0; Read.good(); i++) {
		getline(Read, line);
		GotoXY(x - (i == 0), y + i);
		cout << line;
	}
	Read.close();
	SetConsoleOutputCP(437);
}

void ClearBox(int w, int h, int x, int y) {
	int tmp = GetCurrentColor();
	TextColor(CYAN);
	for (int i = 0; i < h; i++) {
		GotoXY(x, y + i);
		for (int j = 0; j < w; j++)
			cout << ' ';
	}
	TextColor(tmp);
}

void UnhoverButton(_BUTTON a, int color) {
	TextColor(color);
	GotoXY(a.x, a.y);
	cout << a.data;
}

void HoverButton(_BUTTON a) {
	TextColor(RED & 15 | BACKGROUND_YELLOW);
	GotoXY(a.x, a.y);
	cout << a.data;
}

void ascii_art(string input, int x, int y, int t_color) {
	//	set_console_size();
	TextColor(t_color);
	//first layer
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == '.') break;
		if (i == 0) GotoXY(x, ++y);
		if (input[i] == 'A' || input[i] == 'a')
			cout << "  ___   ";
		if (input[i] == 'B' || input[i] == 'b')
			cout << " _____  ";
		if (input[i] == 'C' || input[i] == 'c')
			cout << " _____  ";
		if (input[i] == 'D' || input[i] == 'd')
			cout << " _____  ";
		if (input[i] == 'E' || input[i] == 'e')
			cout << " _____  ";
		if (input[i] == 'F' || input[i] == 'f')
			cout << " _____  ";
		if (input[i] == 'G' || input[i] == 'g')
			cout << " _____  ";
		if (input[i] == 'H' || input[i] == 'h')
			cout << " _   _  ";
		if (input[i] == 'I' || input[i] == 'i')
			cout << " _____  ";
		if (input[i] == 'J' || input[i] == 'j')
			cout << "   ___  ";
		if (input[i] == 'K' || input[i] == 'k')
			cout << " _   __ ";
		if (input[i] == 'L' || input[i] == 'l')
			cout << " _      ";
		if (input[i] == 'M' || input[i] == 'm')
			cout << " __  __  ";
		if (input[i] == 'N' || input[i] == 'n')
			cout << " _   _  ";
		if (input[i] == 'O' || input[i] == 'o')
			cout << " _____  ";
		if (input[i] == 'P' || input[i] == 'p')
			cout << " _____  ";
		if (input[i] == 'Q' || input[i] == 'q')
			cout << " _____  ";
		if (input[i] == 'R' || input[i] == 'r')
			cout << " _____  ";
		if (input[i] == 'S' || input[i] == 's')
			cout << " _____  ";
		if (input[i] == 'T' || input[i] == 't')
			cout << " _____  ";
		if (input[i] == 'U' || input[i] == 'u')
			cout << " _   _  ";
		if (input[i] == 'V' || input[i] == 'v')
			cout << " _   _  ";
		if (input[i] == 'W' || input[i] == 'w')
			cout << " _    _  ";
		if (input[i] == 'X' || input[i] == 'x')
			cout << "__   __ ";
		if (input[i] == 'Y' || input[i] == 'y')
			cout << "__   __ ";
		if (input[i] == 'Z' || input[i] == 'z')
			cout << " ______ ";
		if (input[i] == ' ')
			cout << "  ";
		if (input[i] == '`')
			cout << " _  ";
		if (input[i] == '~')
			cout << "      ";
		if (input[i] == '1')
			cout << " __   ";
		if (input[i] == '2')
			cout << " _____  ";
		if (input[i] == '3')
			cout << " _____  ";
		if (input[i] == '4')
			cout << "   ___  ";
		if (input[i] == '5')
			cout << " _____  ";
		if (input[i] == '6')
			cout << "  ____  ";
		if (input[i] == '7')
			cout << " ______ ";
		if (input[i] == '8')
			cout << " _____  ";
		if (input[i] == '9')
			cout << " _____  ";
		if (input[i] == '0')
			cout << " _____  ";
		if (input[i] == '!')
			cout << " _  ";
		if (input[i] == '@')
			cout << "   ____   ";
		if (input[i] == '#')
			cout << "   _  _    ";
		if (input[i] == '$')
			cout << "  _   ";
		if (input[i] == '%')
			cout << " _   __ ";
		if (input[i] == '^')
			cout << " /\\  ";
		if (input[i] == '&')
			cout << "         ";
		if (input[i] == '*')
			cout << "    _     ";
		if (input[i] == '(')
			cout << "  __ ";
		if (input[i] == ')')
			cout << "__   ";
		if (input[i] == '-')
			cout << "         ";
		if (input[i] == '_')
			cout << "         ";
		if (input[i] == '=')
			cout << "         ";
		if (input[i] == '+')
			cout << "        ";
		if (input[i] == '[')
			cout << " ___  ";
		if (input[i] == '{')
			cout << "   __ ";
		if (input[i] == ']')
			cout << " ___  ";
		if (input[i] == '}')
			cout << "__    ";
		if (input[i] == '|')
			cout << " _  ";
		if (input[i] == '\\')
			cout << "__      ";
		if (input[i] == ';')
			cout << " _  ";
		if (input[i] == ':')
			cout << "    ";
		if (input[i] == '\'')
			cout << " _  ";
		if (input[i] == '"')
			cout << " _ _  ";
		if (input[i] == '<')
			cout << "   __ ";
		if (input[i] == ',')
			cout << "    ";
		if (input[i] == '>')
			cout << "__    ";
		if (input[i] == '/')
			cout << "     __ ";
		if (input[i] == '?')
			cout << " ___   ";
	}
	cout << endl;
	//second layer
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == '.') break;
		if (i == 0) GotoXY(x, ++y);
		if (input[i] == 'A' || input[i] == 'a')
			cout << " / _ \\  ";
		if (input[i] == 'B' || input[i] == 'b')
			cout << "| ___ \\ ";
		if (input[i] == 'C' || input[i] == 'c')
			cout << "/  __ \\ ";
		if (input[i] == 'D' || input[i] == 'd')
			cout << "|  _  \\ ";
		if (input[i] == 'E' || input[i] == 'e')
			cout << "|  ___| ";
		if (input[i] == 'F' || input[i] == 'f')
			cout << "|  ___| ";
		if (input[i] == 'G' || input[i] == 'g')
			cout << "|  __ \\ ";
		if (input[i] == 'H' || input[i] == 'h')
			cout << "| | | | ";
		if (input[i] == 'I' || input[i] == 'i')
			cout << "|_   _| ";
		if (input[i] == 'J' || input[i] == 'j')
			cout << "  |_  | ";
		if (input[i] == 'K' || input[i] == 'k')
			cout << "| | / / ";
		if (input[i] == 'L' || input[i] == 'l')
			cout << "| |     ";
		if (input[i] == 'M' || input[i] == 'm')
			cout << "|  \\/  | ";
		if (input[i] == 'N' || input[i] == 'n')
			cout << "| \\ | | ";
		if (input[i] == 'O' || input[i] == 'o')
			cout << "|  _  | ";
		if (input[i] == 'P' || input[i] == 'p')
			cout << "| ___ \\ ";
		if (input[i] == 'Q' || input[i] == 'q')
			cout << "|  _  | ";
		if (input[i] == 'R' || input[i] == 'r')
			cout << "| ___ \\ ";
		if (input[i] == 'S' || input[i] == 's')
			cout << "/  ___| ";
		if (input[i] == 'T' || input[i] == 't')
			cout << "|_   _| ";
		if (input[i] == 'U' || input[i] == 'u')
			cout << "| | | | ";
		if (input[i] == 'V' || input[i] == 'v')
			cout << "| | | | ";
		if (input[i] == 'W' || input[i] == 'w')
			cout << "| |  | | ";
		if (input[i] == 'X' || input[i] == 'x')
			cout << "\\ \\ / / ";
		if (input[i] == 'Y' || input[i] == 'y')
			cout << "\\ \\ / / ";
		if (input[i] == 'Z' || input[i] == 'z')
			cout << "|___  / ";
		if (input[i] == ' ')
			cout << "  ";
		if (input[i] == '`')
			cout << "( ) ";
		if (input[i] == '~')
			cout << "      ";
		if (input[i] == '1')
			cout << "/  |  ";
		if (input[i] == '2')
			cout << "/ __  \\ ";
		if (input[i] == '3')
			cout << "|____ | ";
		if (input[i] == '4')
			cout << "  /   | ";
		if (input[i] == '5')
			cout << "|  ___| ";
		if (input[i] == '6')
			cout << " / ___| ";
		if (input[i] == '7')
			cout << "|___  / ";
		if (input[i] == '8')
			cout << "|  _  | ";
		if (input[i] == '9')
			cout << "|  _  | ";
		if (input[i] == '0')
			cout << "|  _  | ";
		if (input[i] == '!')
			cout << "| | ";
		if (input[i] == '@')
			cout << "  / __ \\  ";
		if (input[i] == '#')
			cout << " _| || |_  ";
		if (input[i] == '$')
			cout << " | |  ";
		if (input[i] == '%')
			cout << "(_) / / ";
		if (input[i] == '^')
			cout << "|/\\| ";
		if (input[i] == '&')
			cout << "  ___    ";
		if (input[i] == '*')
			cout << " /\\| |/\\  ";
		if (input[i] == '(')
			cout << " / / ";
		if (input[i] == ')')
			cout << "\\ \\  ";
		if (input[i] == '-')
			cout << "         ";
		if (input[i] == '_')
			cout << "         ";
		if (input[i] == '=')
			cout << " ______  ";
		if (input[i] == '+')
			cout << "   _    ";
		if (input[i] == '[')
			cout << "|  _| ";
		if (input[i] == '{')
			cout << "  / / ";
		if (input[i] == ']')
			cout << "|_  | ";
		if (input[i] == '}')
			cout << "\\ \\   ";
		if (input[i] == '|')
			cout << "| | ";
		if (input[i] == '\\')
			cout << "\\ \\     ";
		if (input[i] == ';')
			cout << "(_) ";
		if (input[i] == ':')
			cout << " _  ";
		if (input[i] == '\'')
			cout << "( ) ";
		if (input[i] == '"')
			cout << "( | ) ";
		if (input[i] == '<')
			cout << "  / / ";
		if (input[i] == ',')
			cout << "    ";
		if (input[i] == '>')
			cout << "\\ \\   ";
		if (input[i] == '/')
			cout << "    / / ";
		if (input[i] == '?')
			cout << "|__ \\  ";
	}
	cout << endl;
	//third layer
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == '.') break;
		if (i == 0) GotoXY(x, ++y);
		if (input[i] == 'A' || input[i] == 'a')
			cout << "/ /_\\ \\ ";
		if (input[i] == 'B' || input[i] == 'b')
			cout << "| |_/ / ";
		if (input[i] == 'C' || input[i] == 'c')
			cout << "| /  \\/ ";
		if (input[i] == 'D' || input[i] == 'd')
			cout << "| | | | ";
		if (input[i] == 'E' || input[i] == 'e')
			cout << "| |__   ";
		if (input[i] == 'F' || input[i] == 'f')
			cout << "| |_    ";
		if (input[i] == 'G' || input[i] == 'g')
			cout << "| |  \\/ ";
		if (input[i] == 'H' || input[i] == 'h')
			cout << "| |_| | ";
		if (input[i] == 'I' || input[i] == 'i')
			cout << "  | |   ";
		if (input[i] == 'J' || input[i] == 'j')
			cout << "    | | ";
		if (input[i] == 'K' || input[i] == 'k')
			cout << "| |/ /  ";
		if (input[i] == 'L' || input[i] == 'l')
			cout << "| |     ";
		if (input[i] == 'M' || input[i] == 'm')
			cout << "| .  . | ";
		if (input[i] == 'N' || input[i] == 'n')
			cout << "|  \\| | ";
		if (input[i] == 'O' || input[i] == 'o')
			cout << "| | | | ";
		if (input[i] == 'P' || input[i] == 'p')
			cout << "| |_/ / ";
		if (input[i] == 'Q' || input[i] == 'q')
			cout << "| | | | ";
		if (input[i] == 'R' || input[i] == 'r')
			cout << "| |_/ / ";
		if (input[i] == 'S' || input[i] == 's')
			cout << "\\ `--.  ";
		if (input[i] == 'T' || input[i] == 't')
			cout << "  | |   ";
		if (input[i] == 'U' || input[i] == 'u')
			cout << "| | | | ";
		if (input[i] == 'V' || input[i] == 'v')
			cout << "| | | | ";
		if (input[i] == 'W' || input[i] == 'w')
			cout << "| |  | | ";
		if (input[i] == 'X' || input[i] == 'x')
			cout << " \\ V /  ";
		if (input[i] == 'Y' || input[i] == 'y')
			cout << " \\ V /  ";
		if (input[i] == 'Z' || input[i] == 'z')
			cout << "   / /  ";
		if (input[i] == ' ')
			cout << "  ";
		if (input[i] == '`')
			cout << " \\| ";
		if (input[i] == '~')
			cout << " /\\/| ";
		if (input[i] == '1')
			cout << "`| |  ";
		if (input[i] == '2')
			cout << "`' / /' ";
		if (input[i] == '3')
			cout << "    / / ";
		if (input[i] == '4')
			cout << " / /| | ";
		if (input[i] == '5')
			cout << "|___ \\  ";
		if (input[i] == '6')
			cout << "/ /___  ";
		if (input[i] == '7')
			cout << "   / /  ";
		if (input[i] == '8')
			cout << " \\ V /  ";
		if (input[i] == '9')
			cout << "| |_| | ";
		if (input[i] == '0')
			cout << "| |/' | ";
		if (input[i] == '!')
			cout << "| | ";
		if (input[i] == '@')
			cout << " / / _` | ";
		if (input[i] == '#')
			cout << "|_  __  _| ";
		if (input[i] == '$')
			cout << "/ __) ";
		if (input[i] == '%')
			cout << "   / /  ";
		if (input[i] == '^')
			cout << "     ";
		if (input[i] == '&')
			cout << " ( _ )   ";
		if (input[i] == '*')
			cout << " \\ ` ' /  ";
		if (input[i] == '(')
			cout << "| |  ";
		if (input[i] == ')')
			cout << " | | ";
		if (input[i] == '-')
			cout << " ______  ";
		if (input[i] == '_')
			cout << "         ";
		if (input[i] == '=')
			cout << "|______| ";
		if (input[i] == '+')
			cout << " _| |_  ";
		if (input[i] == '[')
			cout << "| |   ";
		if (input[i] == '{')
			cout << " | |  ";
		if (input[i] == ']')
			cout << "  | | ";
		if (input[i] == '}')
			cout << " | |  ";
		if (input[i] == '|')
			cout << "| | ";
		if (input[i] == '\\')
			cout << " \\ \\    ";
		if (input[i] == ';')
			cout << "    ";
		if (input[i] == ':')
			cout << "(_) ";
		if (input[i] == '\'')
			cout << "|/  ";
		if (input[i] == '"')
			cout << " V V  ";
		if (input[i] == '<')
			cout << " / /  ";
		if (input[i] == ',')
			cout << "    ";
		if (input[i] == '>')
			cout << " \\ \\  ";
		if (input[i] == '/')
			cout << "   / /  ";
		if (input[i] == '?')
			cout << "   ) | ";
	}
	cout << endl;
	//fourth layer
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == '.') break;
		if (i == 0) GotoXY(x, ++y);
		if (input[i] == 'A' || input[i] == 'a')
			cout << "|  _  | ";
		if (input[i] == 'B' || input[i] == 'b')
			cout << "| ___ \\ ";
		if (input[i] == 'C' || input[i] == 'c')
			cout << "| |     ";
		if (input[i] == 'D' || input[i] == 'd')
			cout << "| | | | ";
		if (input[i] == 'E' || input[i] == 'e')
			cout << "|  __|  ";
		if (input[i] == 'F' || input[i] == 'f')
			cout << "|  _|   ";
		if (input[i] == 'G' || input[i] == 'g')
			cout << "| | __  ";
		if (input[i] == 'H' || input[i] == 'h')
			cout << "|  _  | ";
		if (input[i] == 'I' || input[i] == 'i')
			cout << "  | |   ";
		if (input[i] == 'J' || input[i] == 'j')
			cout << "    | | ";
		if (input[i] == 'K' || input[i] == 'k')
			cout << "|    \\  ";
		if (input[i] == 'L' || input[i] == 'l')
			cout << "| |     ";
		if (input[i] == 'M' || input[i] == 'm')
			cout << "| |\\/| | ";
		if (input[i] == 'N' || input[i] == 'n')
			cout << "| . ` | ";
		if (input[i] == 'O' || input[i] == 'o')
			cout << "| | | | ";
		if (input[i] == 'P' || input[i] == 'p')
			cout << "|  __/  ";
		if (input[i] == 'Q' || input[i] == 'q')
			cout << "| | | | ";
		if (input[i] == 'R' || input[i] == 'r')
			cout << "|    /  ";
		if (input[i] == 'S' || input[i] == 's')
			cout << " `--. \\ ";
		if (input[i] == 'T' || input[i] == 't')
			cout << "  | |   ";
		if (input[i] == 'U' || input[i] == 'u')
			cout << "| | | | ";
		if (input[i] == 'V' || input[i] == 'v')
			cout << "| | | | ";
		if (input[i] == 'W' || input[i] == 'w')
			cout << "| |/\\| | ";
		if (input[i] == 'X' || input[i] == 'x')
			cout << " / ^ \\  ";
		if (input[i] == 'Y' || input[i] == 'y')
			cout << "  \\ /   ";
		if (input[i] == 'Z' || input[i] == 'z')
			cout << "  / /   ";
		if (input[i] == ' ')
			cout << "  ";
		if (input[i] == '`')
			cout << "    ";
		if (input[i] == '~')
			cout << "|/\\/  ";
		if (input[i] == '1')
			cout << " | |  ";
		if (input[i] == '2')
			cout << "  / /   ";
		if (input[i] == '3')
			cout << "    \\ \\ ";
		if (input[i] == '4')
			cout << "/ /_| | ";
		if (input[i] == '5')
			cout << "    \\ \\ ";
		if (input[i] == '6')
			cout << "| ___ \\ ";
		if (input[i] == '7')
			cout << "  / /   ";
		if (input[i] == '8')
			cout << " / _ \\  ";
		if (input[i] == '9')
			cout << "\\____ | ";
		if (input[i] == '0')
			cout << "|  /| | ";
		if (input[i] == '!')
			cout << "| | ";
		if (input[i] == '@')
			cout << "| | (_| | ";
		if (input[i] == '#')
			cout << " _| || |_  ";
		if (input[i] == '$')
			cout << "\\__ \\ ";
		if (input[i] == '%')
			cout << "  / /   ";
		if (input[i] == '^')
			cout << "     ";
		if (input[i] == '&')
			cout << " / _ \\/\\ ";
		if (input[i] == '*')
			cout << "|_     _| ";
		if (input[i] == '(')
			cout << "| |  ";
		if (input[i] == ')')
			cout << " | | ";
		if (input[i] == '-')
			cout << "|______| ";
		if (input[i] == '_')
			cout << "         ";
		if (input[i] == '=')
			cout << " ______  ";
		if (input[i] == '+')
			cout << "|_   _| ";
		if (input[i] == '[')
			cout << "| |   ";
		if (input[i] == '{')
			cout << "< <   ";
		if (input[i] == ']')
			cout << "  | | ";
		if (input[i] == '}')
			cout << "  > > ";
		if (input[i] == '|')
			cout << "| | ";
		if (input[i] == '\\')
			cout << "  \\ \\   ";
		if (input[i] == ';')
			cout << " _  ";
		if (input[i] == ':')
			cout << "    ";
		if (input[i] == '\'')
			cout << "    ";
		if (input[i] == '"')
			cout << "      ";
		if (input[i] == '<')
			cout << "< <   ";
		if (input[i] == ',')
			cout << " _  ";
		if (input[i] == '>')
			cout << "  > > ";
		if (input[i] == '/')
			cout << "  / /   ";
		if (input[i] == '?')
			cout << "  / /  ";
	}
	cout << endl;
	//fifth layer
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == '.') break;
		if (i == 0) GotoXY(x, ++y);
		if (input[i] == 'A' || input[i] == 'a')
			cout << "| | | | ";
		if (input[i] == 'B' || input[i] == 'b')
			cout << "| |_/ / ";
		if (input[i] == 'C' || input[i] == 'c')
			cout << "| \\__/\\ ";
		if (input[i] == 'D' || input[i] == 'd')
			cout << "| |/ /  ";
		if (input[i] == 'E' || input[i] == 'e')
			cout << "| |___  ";
		if (input[i] == 'F' || input[i] == 'f')
			cout << "| |     ";
		if (input[i] == 'G' || input[i] == 'g')
			cout << "| |_\\ \\ ";
		if (input[i] == 'H' || input[i] == 'h')
			cout << "| | | | ";
		if (input[i] == 'I' || input[i] == 'i')
			cout << " _| |_  ";
		if (input[i] == 'J' || input[i] == 'j')
			cout << "/\\__/ / ";
		if (input[i] == 'K' || input[i] == 'k')
			cout << "| |\\  \\ ";
		if (input[i] == 'L' || input[i] == 'l')
			cout << "| |____ ";
		if (input[i] == 'M' || input[i] == 'm')
			cout << "| |  | | ";
		if (input[i] == 'N' || input[i] == 'n')
			cout << "| |\\  | ";
		if (input[i] == 'O' || input[i] == 'o')
			cout << "\\ \\_/ / ";
		if (input[i] == 'P' || input[i] == 'p')
			cout << "| |     ";
		if (input[i] == 'Q' || input[i] == 'q')
			cout << "\\ \\/' / ";
		if (input[i] == 'R' || input[i] == 'r')
			cout << "| |\\ \\  ";
		if (input[i] == 'S' || input[i] == 's')
			cout << "/\\__/ / ";
		if (input[i] == 'T' || input[i] == 't')
			cout << "  | |   ";
		if (input[i] == 'U' || input[i] == 'u')
			cout << "| |_| | ";
		if (input[i] == 'V' || input[i] == 'v')
			cout << "\\ \\_/ / ";
		if (input[i] == 'W' || input[i] == 'w')
			cout << "\\  /\\  / ";
		if (input[i] == 'X' || input[i] == 'x')
			cout << "/ / \\ \\ ";
		if (input[i] == 'Y' || input[i] == 'y')
			cout << "  | |   ";
		if (input[i] == 'Z' || input[i] == 'z')
			cout << "./ /___ ";
		if (input[i] == ' ')
			cout << "  ";
		if (input[i] == '`')
			cout << "    ";
		if (input[i] == '~')
			cout << "      ";
		if (input[i] == '1')
			cout << "_| |_ ";
		if (input[i] == '2')
			cout << "./ /___ ";
		if (input[i] == '3')
			cout << ".___/ / ";
		if (input[i] == '4')
			cout << "\\___  | ";
		if (input[i] == '5')
			cout << "/\\__/ / ";
		if (input[i] == '6')
			cout << "| \\_/ | ";
		if (input[i] == '7')
			cout << "./ /    ";
		if (input[i] == '8')
			cout << "| |_| | ";
		if (input[i] == '9')
			cout << ".___/ / ";
		if (input[i] == '0')
			cout << "\\ |_/ / ";
		if (input[i] == '!')
			cout << "|_| ";
		if (input[i] == '@')
			cout << " \\ \\__,_| ";
		if (input[i] == '#')
			cout << "|_  __  _| ";
		if (input[i] == '$')
			cout << "(   / ";
		if (input[i] == '%')
			cout << " / / _  ";
		if (input[i] == '^')
			cout << "     ";
		if (input[i] == '&')
			cout << "| (_>  < ";
		if (input[i] == '*')
			cout << " / , . \\  ";
		if (input[i] == '(')
			cout << "| |  ";
		if (input[i] == ')')
			cout << " | | ";
		if (input[i] == '-')
			cout << "         ";
		if (input[i] == '_')
			cout << " ______  ";
		if (input[i] == '=')
			cout << "|______| ";
		if (input[i] == '+')
			cout << "  |_|   ";
		if (input[i] == '[')
			cout << "| |_  ";
		if (input[i] == '{')
			cout << " | |  ";
		if (input[i] == ']')
			cout << " _| | ";
		if (input[i] == '}')
			cout << " | |  ";
		if (input[i] == '|')
			cout << "| | ";
		if (input[i] == '\\')
			cout << "   \\ \\  ";
		if (input[i] == ';')
			cout << "( ) ";
		if (input[i] == ':')
			cout << " _  ";
		if (input[i] == '\'')
			cout << "    ";
		if (input[i] == '"')
			cout << "      ";
		if (input[i] == '<')
			cout << " \\ \\  ";
		if (input[i] == ',')
			cout << "( ) ";
		if (input[i] == '>')
			cout << " / /  ";
		if (input[i] == '/')
			cout << " / /    ";
		if (input[i] == '?')
			cout << " |_|   ";
	}
	cout << endl;
	//sixth layer
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == '.') break;
		if (i == 0) GotoXY(x, ++y);
		if (input[i] == 'A' || input[i] == 'a')
			cout << "\\_| |_/ ";
		if (input[i] == 'B' || input[i] == 'b')
			cout << "\\____/  ";
		if (input[i] == 'C' || input[i] == 'c')
			cout << " \\____/ ";
		if (input[i] == 'D' || input[i] == 'd')
			cout << "|___/   ";
		if (input[i] == 'E' || input[i] == 'e')
			cout << "\\____/  ";
		if (input[i] == 'F' || input[i] == 'f')
			cout << "\\_|     ";
		if (input[i] == 'G' || input[i] == 'g')
			cout << " \\____/ ";
		if (input[i] == 'H' || input[i] == 'h')
			cout << "\\_| |_/ ";
		if (input[i] == 'I' || input[i] == 'i')
			cout << " \\___/  ";
		if (input[i] == 'J' || input[i] == 'j')
			cout << "\\____/  ";
		if (input[i] == 'K' || input[i] == 'k')
			cout << "\\_| \\_/ ";
		if (input[i] == 'L' || input[i] == 'l')
			cout << "\\_____/ ";
		if (input[i] == 'M' || input[i] == 'm')
			cout << "\\_|  |_/ ";
		if (input[i] == 'N' || input[i] == 'n')
			cout << "\\_| \\_/ ";
		if (input[i] == 'O' || input[i] == 'o')
			cout << " \\___/  ";
		if (input[i] == 'P' || input[i] == 'p')
			cout << "\\_|     ";
		if (input[i] == 'Q' || input[i] == 'q')
			cout << " \\_/\\_\\ ";
		if (input[i] == 'R' || input[i] == 'r')
			cout << "\\_| \\_| ";
		if (input[i] == 'S' || input[i] == 's')
			cout << "\\____/  ";
		if (input[i] == 'T' || input[i] == 't')
			cout << "  \\_/   ";
		if (input[i] == 'U' || input[i] == 'u')
			cout << " \\___/  ";
		if (input[i] == 'V' || input[i] == 'v')
			cout << " \\___/  ";
		if (input[i] == 'W' || input[i] == 'w')
			cout << " \\/  \\/  ";
		if (input[i] == 'X' || input[i] == 'x')
			cout << "\\/   \\/ ";
		if (input[i] == 'Y' || input[i] == 'y')
			cout << "  \\_/   ";
		if (input[i] == 'Z' || input[i] == 'z')
			cout << "\\_____/ ";
		if (input[i] == ' ')
			cout << "  ";
		if (input[i] == '`')
			cout << "    ";
		if (input[i] == '~')
			cout << "      ";
		if (input[i] == '1')
			cout << "\\___/ ";
		if (input[i] == '2')
			cout << "\\_____/ ";
		if (input[i] == '3')
			cout << "\\____/  ";
		if (input[i] == '4')
			cout << "    |_/ ";
		if (input[i] == '5')
			cout << "\\____/  ";
		if (input[i] == '6')
			cout << "\\_____/ ";
		if (input[i] == '7')
			cout << "\\_/     ";
		if (input[i] == '8')
			cout << "\\_____/ ";
		if (input[i] == '9')
			cout << "\\____/  ";
		if (input[i] == '0')
			cout << " \\___/  ";
		if (input[i] == '!')
			cout << "(_) ";
		if (input[i] == '@')
			cout << "  \\____/  ";
		if (input[i] == '#')
			cout << "  |_||_|   ";
		if (input[i] == '$')
			cout << " |_|  ";
		if (input[i] == '%')
			cout << "/_/ (_) ";
		if (input[i] == '^')
			cout << "     ";
		if (input[i] == '&')
			cout << " \\___/\\/ ";
		if (input[i] == '*')
			cout << " \\/|_|\\/  ";
		if (input[i] == '(')
			cout << " \\_\\ ";
		if (input[i] == ')')
			cout << "/_/  ";
		if (input[i] == '-')
			cout << "         ";
		if (input[i] == '_')
			cout << "|______| ";
		if (input[i] == '=')
			cout << "         ";
		if (input[i] == '+')
			cout << "        ";
		if (input[i] == '[')
			cout << "|___| ";
		if (input[i] == '{')
			cout << "  \\_\\ ";
		if (input[i] == ']')
			cout << "|___| ";
		if (input[i] == '}')
			cout << "/_/   ";
		if (input[i] == '|')
			cout << "|_| ";
		if (input[i] == '\\')
			cout << "    \\_\\ ";
		if (input[i] == ';')
			cout << "|/  ";
		if (input[i] == ':')
			cout << "(_) ";
		if (input[i] == '\'')
			cout << "    ";
		if (input[i] == '"')
			cout << "      ";
		if (input[i] == '<')
			cout << "  \\_\\ ";
		if (input[i] == ',')
			cout << "|/  ";
		if (input[i] == '>')
			cout << "/_/   ";
		if (input[i] == '/')
			cout << "/_/     ";
		if (input[i] == '?')
			cout << " (_)   ";
	}
	cout << endl;
}

void DrawXWin() {
	ClearBox(44, 7, 68, 20);
	DrawAsciiFile(0, 18, "DrawXWin02", RED);
	Sleep(150);
	DrawAsciiFile(0, 18, "DrawXWin02", BLUE);
	Sleep(150);
	DrawAsciiFile(0, 18, "DrawXWin02", YELLOW);
	Sleep(150);
	DrawAsciiFile(0, 18, "DrawXWin02", RED);
	Sleep(150);
	DrawAsciiFile(0, 18, "DrawXWin02", BLUE);
	Sleep(150);
	DrawAsciiFile(0, 18, "DrawXWin02", YELLOW);
	Sleep(150);
	DrawAsciiFile(0, 18, "DrawXWin02", X_COLOR);
}

void DrawOWin() {
	ClearBox(44, 7, 68, 20);
	DrawAsciiFile(0, 18, "DrawOWin02", RED);
	Sleep(100);
	DrawAsciiFile(0, 18, "DrawOWin02", BLUE);
	Sleep(100);
	DrawAsciiFile(0, 18, "DrawOWin02", YELLOW);
	Sleep(100);
	DrawAsciiFile(0, 18, "DrawOWin02", RED);
	Sleep(100);
	DrawAsciiFile(0, 18, "DrawOWin02", BLUE);
	Sleep(100);
	DrawAsciiFile(0, 18, "DrawOWin02", YELLOW);
	Sleep(100);
	DrawAsciiFile(0, 18, "DrawOWin02", O_COLOR);
}

void SetOWin(string NamePlayer_O, WinningPos WP[5], _POINT _A[B_SIZE][B_SIZE]) {
	for (int i = 0; i < 5; i++) {
		GotoXY(_A[WP[i].x][WP[i].y].x, _A[WP[i].x][WP[i].y].y);
		TextColor(BLUE);
		Sleep(80);
		cout << "O";
		GotoXY(_A[WP[i].x][WP[i].y].x, _A[WP[i].x][WP[i].y].y);
		TextColor(RED);
		Sleep(80);
		cout << "O";
		GotoXY(_A[WP[i].x][WP[i].y].x, _A[WP[i].x][WP[i].y].y);
		TextColor(GREEN);
		Sleep(80);
		cout << "O";
		GotoXY(_A[WP[i].x][WP[i].y].x - 1, _A[WP[i].x][WP[i].y].y);
		TextColor(O_COLOR & 15 | BACKGROUND_YELLOW);
		Sleep(80);
		cout << " O ";
	}
	GotoXY(48, 28);
	cout << "<< PRESS ENTER TO CONTINUE >>";
	int x = 3;
	int y = 2;
	long long a[] = { RED,BLUE,GREEN,YELLOW,GRAY,BLUE };
	int n = sizeof(a) / sizeof(a[0]);
	ClearBox(25, 9, 76, 19);
	while (true) {
		unsigned char c;
		if (_kbhit()) {
			unsigned char c = _getch();
			if (c == ENTER) {
				SetConsoleBlank();
				Sleep(100);
				ascii_art("congratulation", x, y, RED);
				ascii_art(NamePlayer_O, x + 15 * 7 / 2 - NamePlayer_O.size() * 7 / 2, y + 6, BLUE);
				Sleep(100);
				ascii_art("congratulation", x, y, GREEN);
				ascii_art(NamePlayer_O, x + 15 * 7 / 2 - NamePlayer_O.size() * 7 / 2, y + 6, BLUE);
				Sleep(100);
				ascii_art("congratulation", x, y, YELLOW);
				ascii_art(NamePlayer_O, x + 15 * 7 / 2 - NamePlayer_O.size() * 7 / 2, y + 6, BLUE);
				Sleep(100);
				ascii_art("congratulation", x, y, BLUE);
				ascii_art(NamePlayer_O, x + 15 * 7 / 2 - NamePlayer_O.size() * 7 / 2, y + 6, BLUE);
				Sleep(100);
				ascii_art("congratulation", x, y, RED);
				ascii_art(NamePlayer_O, x + 15 * 7 / 2 - NamePlayer_O.size() * 7 / 2, y + 6, BLUE);
				break;
			}
		}
		for (int i = 0; i < n; i++) {
			if (_kbhit())
				c = _getch();
			TextColor((a[i] & 15) | BACKGROUND_YELLOW);
			Sleep(100);
			GotoXY(_A[WP[0].x][WP[0].y].x, _A[WP[0].x][WP[0].y].y);
			cout << "O";
			GotoXY(_A[WP[1].x][WP[1].y].x, _A[WP[1].x][WP[1].y].y);
			cout << "O";
			GotoXY(_A[WP[2].x][WP[2].y].x, _A[WP[2].x][WP[2].y].y);
			cout << "O";
			GotoXY(_A[WP[3].x][WP[3].y].x, _A[WP[3].x][WP[3].y].y);
			cout << "O";
			GotoXY(_A[WP[4].x][WP[4].y].x, _A[WP[4].x][WP[4].y].y);
			cout << "O";
		}
		DrawOWin();
	}
}

void SetXWin(string NamePlayer_X, WinningPos WP[5], _POINT _A[B_SIZE][B_SIZE]) {
	for (int i = 0; i < 5; i++) {
		GotoXY(_A[WP[i].x][WP[i].y].x, _A[WP[i].x][WP[i].y].y);
		TextColor(BLUE);
		Sleep(80);
		cout << "X";
		GotoXY(_A[WP[i].x][WP[i].y].x, _A[WP[i].x][WP[i].y].y);
		TextColor(RED);
		Sleep(80);
		cout << "X";
		GotoXY(_A[WP[i].x][WP[i].y].x, _A[WP[i].x][WP[i].y].y);
		TextColor(GREEN);
		Sleep(80);
		cout << "X";
		GotoXY(_A[WP[i].x][WP[i].y].x - 1, _A[WP[i].x][WP[i].y].y);
		TextColor(X_COLOR & 15 | BACKGROUND_YELLOW);
		Sleep(80);
		cout << " X ";
	}
	//
	GotoXY(48, 28);
	cout << "<< PRESS ENTER TO CONTINUE >>";
	int x = 3;
	int y = 2;
	long long a[] = { RED,BLUE,GREEN,YELLOW,GRAY,RED };
	int n = sizeof(a) / sizeof(a[0]);
	ClearBox(25, 9, 76, 19);
	while (true) {
		unsigned char c;
		if (_kbhit()) {
			c = _getch();
			if (c == ENTER) {
				SetConsoleBlank();
				Sleep(100);
				ascii_art("congratulation", x, y, RED);
				ascii_art(NamePlayer_X, x + 15 * 7 / 2 - NamePlayer_X.size() * 7 / 2, y + 6, BLUE);
				Sleep(100);
				ascii_art("congratulation", x, y, GREEN);
				ascii_art(NamePlayer_X, x + 15 * 7 / 2 - NamePlayer_X.size() * 7 / 2, y + 6, BLUE);
				Sleep(100);
				ascii_art("congratulation", x, y, YELLOW);
				ascii_art(NamePlayer_X, x + 15 * 7 / 2 - NamePlayer_X.size() * 7 / 2, y + 6, BLUE);
				Sleep(100);
				ascii_art("congratulation", x, y, BLUE);
				ascii_art(NamePlayer_X, x + 15 * 7 / 2 - NamePlayer_X.size() * 7 / 2, y + 6, BLUE);
				Sleep(100);
				ascii_art("congratulation", x, y, RED);
				ascii_art(NamePlayer_X, x + 15 * 7 / 2 - NamePlayer_X.size() * 7 / 2, y + 6, BLUE);
				break;
			}
		}
		else {
			for (int i = 0; i < n; i++) {
				if (_kbhit())
					c = _getch();
				TextColor((a[i] & 15) | BACKGROUND_YELLOW);
				Sleep(100);
				GotoXY(_A[WP[0].x][WP[0].y].x, _A[WP[0].x][WP[0].y].y);
				cout << "X";
				GotoXY(_A[WP[1].x][WP[1].y].x, _A[WP[1].x][WP[1].y].y);
				cout << "X";
				GotoXY(_A[WP[2].x][WP[2].y].x, _A[WP[2].x][WP[2].y].y);
				cout << "X";
				GotoXY(_A[WP[3].x][WP[3].y].x, _A[WP[3].x][WP[3].y].y);
				cout << "X";
				GotoXY(_A[WP[4].x][WP[4].y].x, _A[WP[4].x][WP[4].y].y);
				cout << "X";
			}
			DrawXWin();
		}
	}
}

void Draw(int x, int y, string nameFile, int color) {
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

int ChooseMode(bool sound[]) {
	SetConsoleBlank();
	BackGround();
	DrawAsciiFile(0, 3, "ChooseMode", BLACK);

	DrawBoxMini(34, 9, 68, 14, GRAY);
	DrawAsciiFile(0, 15, "pvc", GRAY);

	DrawBoxMini(34, 9, 19, 14, RED);
	DrawAsciiFile(0, 15, "pvp", RED);
	bool cur = 0;
	while (true) {
		char c = toupper(_getch());
		if (sound[CLICK_SFX]) PlayAudio(CLICK_SFX);
		if (c == ESC)
			return -1;
		if (c == ENTER) {
			return !cur;
		}
		if (c == A || c == D)
			cur ^= 1;
		if (cur == 0) {
			DrawBoxMini(34, 9, 68, 14, GRAY);
			DrawAsciiFile(0, 15, "pvc", GRAY);

			DrawBoxMini(34, 9, 19, 14, RED);
			DrawAsciiFile(0, 15, "pvp", RED);
		}
		else {
			DrawBoxMini(34, 9, 68, 14, RED);
			DrawAsciiFile(0, 15, "pvc", RED);

			DrawBoxMini(34, 9, 19, 14, GRAY);
			DrawAsciiFile(0, 15, "pvp", GRAY);
		}
	}
	GotoXY(27, 27);
}

void ExitScreen()
{
	SetConsoleBlank();
	DrawAsciiFile(0, 0, "PatternBG", LIGHT_CYAN);
	do {
		DrawBoxMini(88, 12, 15, 8, LIGHT_CYAN);
		DrawAsciiFile(24, 10, "DrawGoodbye", RED);
		Sleep(300);
		DrawAsciiFile(24, 10, "DrawGoodbye", GREEN);
		Sleep(300);
		DrawAsciiFile(24, 10, "DrawGoodbye", LIGHT_BLUE);
		Sleep(300);
		DrawAsciiFile(24, 10, "DrawGoodbye", MAGENTA);
		Sleep(300);
	} while (!_kbhit());
	GotoXY(0, 25);
}
