//////////////////////////////////////////////////////////////////////////////////////////////////
/*
*		���� "����������" - ��� ����������� ���������� ����. ������� ���� �������� ������.
*		� ��� ����� ��������� ������� �������������� ���������� �������.
*
*		��������� ����� �� 52 ��������, �� ������� �������� ����� �� 1 �� 13,
*	������ �������� � ������ �� ���� ����� ����������� ���������.
*
*		� ������� ������ ������� ���������� ���� � 25 ��������.
*
*		������� ����� ������ �������������� �������� � �������, ������������� ��
*	(��� ������������ �� �� �����, ������� ����), ����� ��������� ������ �������� � ���������
*	���������� �� ��� �����.
*		������ �� �������� ���������� ��� ����� � ���� �� ������ �� ����� ����.
*		����� ������� ��������� �����, ���������� �� ��������� ��������,
*	�������� ����� ��������� ��� � ����� �� ��������� ������ ������ ����� � �. �.
*		��� ������������ �� ��� ���, ���� �� ����� ��������� ��� ������ ��������.
*
*		��������� ������ ����������� ������ ��������� �� �����, ��������� ��
*	������� ���������� ����� � ������� ��������.
*		����������� ��������� ���, ��� �������� ���������� ���������� �����.
*
*+--------------------------------------------------------------------------+-----------------------+-------------+
*|							���������� �����								|	� ���� ��� �������	| �� ���������|
*+--------------------------------------------------------------------------+-----------------------+-------------|
*|	�� 2 ���������� �����													|		10 �����		|  20 �����	  |
*|	�� 2 ���� ���������� �����												|		20 �����		|  30 �����	  |
*|	�� 3 ���������� �����													|		40 �����		|  50 �����	  |
*|	�� 3 ���������� ����� � ��� ������ ���������� �����						|		80 �����		|  90 �����	  |
*|	�� 4 ���������� �����													|		160 �����		|  170 �����  |
*|	�� 5 ���������������� �����, �� �� ����������� �� ������� �������������	|		50 �����		|  60 �����	  |
*|	�� ��� ���� �� 1 � ��� ���� �� 13										|		100 �����		|  110 �����  |
*|	�� ����� 1, 13, 12, 11 � 10, �� �� ����������� �� ������� �������������	|		150 �����		|  160 �����  |
*|	�� 4 �������															|		200 �����		|  210 �����  |
*+--------------------------------------------------------------------------+-----------------------+-------------+
*/
//////////////////////////////////////////////////////////////////////////////////////////////////
#include <algorithm>
#include <vector>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
//////////////////////////////////////////////////////////////////////////////////////////////////
//	#pragma hdrstop //������������ ���� ��� ����� ���������
/*	#pragma hdrstop
*	������ PCH - ��� ������������� ������� ��
*	#pragma hdrstop ����� ���������������� � ��������, ���� ��� ��� �
*	CPP ������ ���������� �������� �� �� ������������������ �������� �� #pragma hdrstop -
*	�� ��������� ��� ����������� ���.
*	��� ����� ���� � ���������� ����, �� ��� ���� ������� ���-����-������-���.
*/
//////////////////////////////////////////////////////////////////////////////////////////////////
using namespace std;
//////////////////////////////////////////////////////////////////////////////////////////////////
/*���� ���� ���*/
bool isGame;

/*���� ���� � �����������*/
bool isComputer;

/*��� ������*/
int arrPoleUser[5][5];

/*��� �����*/
int arrPoleComp[5][5];
vector<int> vCards;
int currentCard;
//////////////////////////////////////////////////////////////////////////////////////////////////

/*��� �����*/
int  AICountFreeCells(int xCol, int yRow);
void AI(int *nCol, int *nRow);
void stepAI();

/*��� ����*/
void recreateStackCards();
int  score(int numbers[5], bool bDiagonal);
int  totalScore(int pole[5][5]);
int  nextCard();
bool writeCardIntoCompCell(int nCol, int nRow);
bool writeCardIntoUserCell(int nCol, int nRow); //������������ ���������� ����� � ������ (���� nCol � nRow ������ � �������)

												/*�������� �� 4 �������*/
bool checkForOnce(const int *numbers);

/*�������� ��  1, 13, 12, 11 � 10*/
bool check113121110(const int *numbers);

/*�������� �� ����� 1 � 13*/
bool check113(const int *numbers);

/*�������� �� ���������������� �����*/
bool checkSerialNum(const int *numbers);

/*�������� �� ���������� �����*/
bool checkIdenticalNum(const int *numbers, int n1 = 4, int n2 = 0);

/*������� ������ � ����� ����*/
void newGame();
void endGame();

//////////////////////////////////////////////////////////////////////////////////////////////////

struct structMax {
	int maxX;
	int maxY;
};

//////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
	setlocale(0, "");
	/*�������� ������ �� 570*/
	int arr[5][5] = {
		{ 1, 1, 7, 1, 7 },
		{ 2, 10, 2, 13, 2 },
		{ 5, 12, 13, 5, 7 },
		{ 3, 3, 3, 11, 3 },
		{ 4, 12, 4, 13, 12 } };
	cout << totalScore(arr) << endl;
	system("pause");
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////

int totalScore(int Pole[5][5]) {
	int totalScore = 0;

	/*�������� �������*/
	for (int xCount = 0; xCount < 5; xCount++) {
		int numbers[5];
		for (int yCount = 0; yCount < 5; yCount++) {
			numbers[yCount] = Pole[xCount][yCount];
		}
		totalScore += score(numbers, false);
	}

	/*�������� ������*/
	for (int yCount = 0; yCount < 5; yCount++) {
		int numbers[5];
		for (int xCount = 0; xCount < 5; xCount++) {
			numbers[xCount] = Pole[xCount][yCount];
		}
		totalScore += score(numbers, false);
	}

	/*�������� ���������*/
	int numbers[5];
	for (int iCount = 0; iCount < 5; iCount++) {
		numbers[iCount] = Pole[iCount][iCount];
	}
	totalScore += score(numbers, true);
	for (int iCount = 0; iCount < 5; iCount++) {
		numbers[iCount] = Pole[4 - iCount][iCount];
	}
	totalScore += score(numbers, true);

	return totalScore;
}
//////////////////////////////////////////////////////////////////////////////////////////////////

int score(int numbers[5], bool bDiagonal) {
	sort(numbers, numbers + 5);

	/*�������� �� 4 �������*/
	if (checkForOnce(numbers)) { if (bDiagonal) return 210; else return 200; }

	/*�������� �� ����� 1, 13, 12, 11 � 10*/
	else if (check113121110(numbers)) { if (bDiagonal) return 160; else return 150; }

	/*�������� �� ����� 1, 13*/
	else if (check113(numbers)) { if (bDiagonal) return 110; else return 100; }

	/*�������� �� ���������������� �����*/
	else if (checkSerialNum(numbers)) { if (bDiagonal) return 60; else return 50; }
	else if (checkIdenticalNum(numbers, 4, 0)) { if (bDiagonal) return 170; else return 160; }
	else if (checkIdenticalNum(numbers, 3, 2)) { if (bDiagonal) return 90; else return 80; }
	else if (checkIdenticalNum(numbers, 3, 0)) { if (bDiagonal) return 50; else return 40; }
	else if (checkIdenticalNum(numbers, 2, 2)) { if (bDiagonal) return 30; else return 20; }
	else if (checkIdenticalNum(numbers, 2, 0)) { if (bDiagonal) return 20; else return 10; }

	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
/*�������� �� 4 �������*/

bool checkForOnce(const int *numbers) {
	int arr[] = { 1,1,1,1 };
	if (memcmp(numbers, arr, sizeof(arr)) == 0 ||

		/*���� ������ ��� ��*/
		memcmp(&numbers[1], arr, sizeof(arr)) == 0) return true;

	return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
/*�������� ��  1, 13, 12, 11 � 10*/
bool check113121110(const int *numbers) {
	int arr[] = { 1,10,11,12,13 };

	if (memcmp(numbers, arr, sizeof(arr)) == 0) return true;

	return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
/*�������� �� ����� 1 � 13*/
bool check113(const int *numbers) {
	int arr[] = { 1,1,1,13,13 };

	if (memcmp(numbers, arr, sizeof(arr)) == 0) return true;

	return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
/*�������� �� ���������������� �����*/
bool checkSerialNum(const int *numbers) {

	for (int iCount = 1; iCount < 5; iCount++) {
		if (numbers[iCount] - numbers[iCount - 1] != 1) return false;
	}

	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
/*�������� �� ���������� �����*/
bool checkIdenticalNum(const int *numbers, int n1, int n2) {
	int next = 0;
	int count[2] = { 0 };

	for (int iCount = 1; iCount < 5; iCount++) {
		if (numbers[iCount] == 0 || numbers[iCount - 1] == 0) continue;

		if (numbers[iCount] == numbers[iCount - 1]) count[next]++;
		else if (count[next] != 0) next++;
	}

	if (count[0]) count[0]++;
	if (count[1]) count[1]++;
	if ((count[0] >= n1 && count[1] >= n2) ||
		(count[1] >= n1 && count[0] >= n2)) return true;

	return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
void newGame() {
	memset(arrPoleUser, 0, sizeof(arrPoleUser));
	memset(arrPoleComp, 0, sizeof(arrPoleComp));
	recreateStackCards();
	isGame = true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
void recreateStackCards() {

	vCards.clear();

	for (int iCount = 0; iCount < 4; iCount++)
		for (int nCount = 1; nCount <= 13; nCount++)
			vCards.push_back(nCount);

	random_shuffle(vCards.begin(), vCards.end());

	vCards.resize(25);
}
//////////////////////////////////////////////////////////////////////////////////////////////////
int nextCard() {
	if (!isGame) return 0;

	if (vCards.empty()) {
		endGame();
		return 0;
	}
	else {
		currentCard = vCards.back();
		vCards.pop_back();
		stepAI();
	}

	return currentCard;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
void stepAI() {
	if (!isGame) return; //return NULL �� �����������, � ������
	int row, col;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
void endGame() {
	int userScores = totalScore(arrPoleUser);
	int compScores = totalScore(arrPoleComp);
	isGame = false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
/*
*	� �������� ����� �������� ������� ��
*	������� �� ������ ���� ����� ������� ����� � ������, ��� ������� ����� ���������� ��������� ���-�� ����� �� ������ ����.
*	������ ������ ������ �� �� ��������� � ������ ������ ������ ���� ������ ��������� ������, ��� �� ������ ������������� �������.
*	��������� ����� ����� ������ ��������� ��� ������������ �������� ��.
*/
//////////////////////////////////////////////////////////////////////////////////////////////////
void AI(int *nCol, int *nRow) {
	int numbers[5];

	int iMaxTotalScores = 0;
	vector<structMax> vMax;

	for (int x = 0; x < 5; x++) {
		for (int y = 0; y < 5; y++) {
			if (arrPoleComp[x][y] == 0) {
				arrPoleComp[x][y] = currentCard;
				int iScores = totalScore(arrPoleComp);
				if (iMaxTotalScores <= iScores) {
					if (iMaxTotalScores < iScores) {
						vMax.clear();
						iMaxTotalScores = iScores;
					}

					structMax max;
					max.maxX = x;
					max.maxY = y;

					vMax.push_back(max);

				}
				arrPoleComp[x][y] = 0;
			}
		}
	}

	int iMaxFreeCells = 0;
	int iMaxX = 0;
	int iMaxY = 0;

	for (int i = 0; i < vMax.size(); i++) {
		structMax max = vMax[i];

		int count = AICountFreeCells(max.maxX, max.maxY);
		if (iMaxFreeCells <= count) {
			iMaxFreeCells = count;
			iMaxX = max.maxX;
			iMaxY = max.maxY;
		}
	}

	*nCol = iMaxX + 1;
	*nRow = iMaxY + 1;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
int AICountFreeCells(int xCol, int yRow) {

	int Count = 0;

	if (xCol == 2 && yRow == 2) return 999;
	/*��������� ���������� ����������*/
	if (xCol - yRow == 0 || xCol + yRow == 4) return 0;

	for (int x = 0; x < 5; x++) {
		for (int y = 0; y < 5; y++) {
			if (arrPoleComp[x][yRow] == 0) Count++;
			if (arrPoleComp[xCol][y] == 0) Count++;
			if (arrPoleComp[x][y] == 0) Count++;
			if (arrPoleComp[4 - x][y] == 0) Count++;
		}
	}
	return Count;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
bool writeCardIntoCompCell(int nCol, int nRow) {
	/*��-�� ����, ��� ���� � �������� ���������� � ����*/
	nCol--;
	nRow--;

	/*���� ������ ������*/
	if (arrPoleComp[nCol][nRow]) return false;
	/*���� ������ ��������*/
	else {
		arrPoleComp[nCol][nRow] = currentCard;
	}

	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
bool writeCardIntoUserCell(int nCol, int nRow) {
	if (!isGame) return false;

	/*��-�� ����, ��� ���� � �������� ���������� � ����*/
	nCol--;
	nRow--;

	/*���� ������ ������*/
	if (arrPoleUser[nCol][nRow]) return false;
	/*���� ������ ��������*/
	else {
		arrPoleUser[nCol][nRow] = currentCard;
	}

	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////