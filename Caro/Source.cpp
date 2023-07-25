#include "Data.h"
#include "Control.h"
#include "View.h"
#include "Model.h"


_POINT _A[B_SIZE][B_SIZE]; //Ma trận bàn cờ
bool _TURN; //true là lượt người thứ nhất và false là lượt người thứ hai
int _COMMAND; // Biến nhận giá trị phím người dùng nhập
int _X, _Y, cX, cY; //Tọa độ hiện hành trên màn hình bàn cờ
int cntX, cntO, saveTurn = 0, cntWinO = 0, cntLoseO = 0, cntDraw = 0, cntRound = 1;
float remain;
bool sound[] = { 1, 1 };
int pvp = 1;
string NamePlayer_O = "", NamePlayer_X = "";
WinningPos WP[5];

int main() {
	HideCursor(1);
	FixConsoleWindow();
	changeFont(23);
	LoadSound(sound);
//	LoadingScreen(BLUE, GREEN, LIGHT_CYAN);
	while (true) {
		MainMenu(_A, _TURN, pvp, _COMMAND, sound, _X, _Y, cX, cY, cntX, cntO, cntWinO, cntLoseO, cntDraw, saveTurn, cntRound, NamePlayer_O, NamePlayer_X, remain, WP);
	}
	return 0;
}
