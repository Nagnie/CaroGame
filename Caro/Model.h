#pragma once
#include "Data.h"

void ResetData(_POINT _A[B_SIZE][B_SIZE], bool& _TURN, int& _COMMAND, int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO, float& remain);
bool CheckFullBoard(_POINT _A[B_SIZE][B_SIZE]);
void SetupGame(_POINT _A[B_SIZE][B_SIZE], bool reset, bool& _TURN, int& _COMMAND, int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO, int cntWinO, int cntLoseO, int cntDraw, int& cntRound, string& NamePlayer_O, string& NamePlayer_X, float& remain);
int TestBoard(_POINT _A[B_SIZE][B_SIZE], int& saveTurn, int& cntWinO, int& cntLoseO, int& cntDraw, int& cntRound, bool check);
bool CheckWin(_POINT _A[B_SIZE][B_SIZE], int x, int y, WinningPos WP[5]);
bool CheckWinLose(_POINT _A[B_SIZE][B_SIZE], int& saveTurn, int cX, int cY, WinningPos WP[5]);
int CheckBoard(_POINT _A[B_SIZE][B_SIZE], bool _TURN, int pX, int pY);
void StartGame(_POINT _A[B_SIZE][B_SIZE], bool reset, bool& _TURN, int& pvp, int& _COMMAND, bool sound[], int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO, int& cntWinO, int& cntLoseO, int& cntDraw, int& saveTurn, int& cntRound, string& NamePlayer_O, string& NamePlayer_X, float& remain, WinningPos WP[5]);
bool LoadData(_POINT _A[B_SIZE][B_SIZE], bool& _TURN, int& pvp, int& _COMMAND, int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO, int& cntWinO, int& cntLoseO, int& cntDraw, int& saveTurn, int& cntRound, string& NamePlayer_O, string& NamePlayer_X, string FileName, float& remain);
bool SaveData(_POINT _A[B_SIZE][B_SIZE], bool& _TURN, int& pvp, int& _COMMAND, int& _X, int& _Y, int& cX, int& cY, int& cntX, int& cntO, int& cntWinO, int& cntLoseO, int& cntDraw, int& saveTurn, int& cntRound, string& NamePlayer_O, string& NamePlayer_X, string FileName, float& remain);
void LoadSound(bool sound[]);
void SetSound(bool sound[], int type, bool value);
void PlayAudio(int type);
void StopSound(int type);
string CleanFileName(string s);
bool EnterName(string& s, int len);
void ExitGame();