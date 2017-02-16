//////////////////////////////////////////////////////////////////////////////////////////////////
/*
*		Игра "Математико" - это итальянская логическая игра. Правила игры довольно просты.
*		В ней могут принимать участие неограниченное количество человек.
*
*		Готовится набор из 52 карточек, на которых записаны числа от 1 до 13,
*	причем карточки с каждым из этих чисел встречаются четырежды.
*
*		У каждого игрока имеется квадратное поле с 25 клетками.
*
*		Ведущий берет колоду приготовленных карточек с числами, растасовывает ее
*	(или раскладывает их на столе, числами вниз), затем открывает первую карточку и объявляет
*	написанное на ней число.
*		Каждый из играющих записывает это число в одну из клеток на своем поле.
*		Затем ведущий объявляет число, написанное на следующей карточке,
*	играющие опять вписывают его в любую из свободных клеток своего листа и т. д.
*		Так продолжается до тех пор, пока не будут заполнены все клетки квадрата.
*
*		Результат игрока оценивается числом набранных им очков, зависящим от
*	способа размещения чисел в клетках квадрата.
*		Победителем считается тот, кто набирает наибольшее количество очков.
*
*+--------------------------------------------------------------------------+-----------------------+-------------+
*|							Комбинации чисел								|	В ряду или столбце	| По диагонали|
*+--------------------------------------------------------------------------+-----------------------+-------------|
*|	За 2 одинаковых числа													|		10 очков		|  20 очков	  |
*|	За 2 пары одинаковых чисел												|		20 очков		|  30 очков	  |
*|	За 3 одинаковых числа													|		40 очков		|  50 очков	  |
*|	За 3 одинаковых числа и два других одинаковых числа						|		80 очков		|  90 очков	  |
*|	За 4 одинаковых числа													|		160 очков		|  170 очков  |
*|	За 5 последовательных чисел, но не обязательно по порядку расположенных	|		50 очков		|  60 очков	  |
*|	За три раза по 1 и два раза по 13										|		100 очков		|  110 очков  |
*|	За числа 1, 13, 12, 11 и 10, но не обязательно по порядку расположенных	|		150 очков		|  160 очков  |
*|	За 4 единицы															|		200 очков		|  210 очков  |
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
//	#pragma hdrstop //раскомпилить если жрёт много оперативы
/*	#pragma hdrstop
*	аналог PCH - все заинклуденные хаэдеры до
*	#pragma hdrstop будут прекомпилированы и закешены, если где еще в
*	CPP файлах компилятор встретит ту же последовательность хэадеров до #pragma hdrstop -
*	то заюзается уже скомпиленый кеш.
*	Для этого есть и нормальные вещи, но мне лень гуглить что-либо-нибудь-кое.
*/
//////////////////////////////////////////////////////////////////////////////////////////////////
using namespace std;
//////////////////////////////////////////////////////////////////////////////////////////////////
/*Если игра идёт*/
bool isGame;

/*Если игра с компьютером*/
bool isComputer;

/*Для юзверя*/
int arrPoleUser[5][5];

/*Для компа*/
int arrPoleComp[5][5];
vector<int> vCards;
int currentCard;
//////////////////////////////////////////////////////////////////////////////////////////////////
/*Пользователь записывает номер в ячейку (счёт nCol и nRow ведётся с единицы)*/
//bool WriteCardIntoUserCell(int nCol, int nRow);

/*Для карт*/
//void ReCreateCards();
int score(int numbers[5], bool bDiagonal);
int totalScore(int pole[5][5]);

/*Проверка на 4 единицы*/
bool checkForOnce(const int *numbers);

/*Проверка на  1, 13, 12, 11 и 10*/
bool check113121110(const int *numbers);

/*Проверка на числа 1 и 13*/
bool check113(const int *numbers);

/*Проверка на последовательные числа*/
bool checkSerialNum(const int *numbers);

/*Проверка на одинаковые числа*/
bool checkIdenticalNum(const int *numbers, int n1 = 4, int n2 = 0);

//////////////////////////////////////////////////////////////////////////////////////////////////
////НА РАСПРЕДЕЛЕНИЕ//////////////////////НА РАСПРЕДЕЛЕНИЕ////////////////////НА РАСПРЕДЕЛЕНИЕ////
void newGame();
void recreateStackCards();
int  nextCard();
void stepAI();
void endGame();
////НА РАСПРЕДЕЛЕНИЕ//////////////////////НА РАСПРЕДЕЛЕНИЕ////////////////////НА РАСПРЕДЕЛЕНИЕ////
//////////////////////////////////////////////////////////////////////////////////////////////////

struct stuctMax {
	int maxX;
	int maxY;
};

//////////////////////////////////////////////////////////////////////////////////////////////////
int main() {
	setlocale(0, "");
	/*Тестовый массив на 570*/
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

	/*Проходим столбцы*/
	for (int xCount = 0; xCount < 5; xCount++) {
		int numbers[5];
		for (int yCount = 0; yCount < 5; yCount++) {
			numbers[yCount] = Pole[xCount][yCount];
		}
		totalScore += score(numbers, false);
	}

	/*Проходим строки*/
	for (int yCount = 0; yCount < 5; yCount++) {
		int numbers[5];
		for (int xCount = 0; xCount < 5; xCount++) {
			numbers[xCount] = Pole[xCount][yCount];
		}
		totalScore += score(numbers, false);
	}

	/*Проходим диагонали*/
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

	/*Проверка на 4 единицы*/
	if (checkForOnce(numbers)) { if (bDiagonal) return 210; else return 200; }

	/*Проверка на числа 1, 13, 12, 11 и 10*/
	else if (check113121110(numbers)) { if (bDiagonal) return 160; else return 150; }

	/*Проверка на числа 1, 13*/
	else if (check113(numbers)) { if (bDiagonal) return 110; else return 100; }

	/*Проверка на последовательные числа*/
	else if (checkSerialNum(numbers)) { if (bDiagonal) return 60; else return 50; }
	else if (checkIdenticalNum(numbers, 4, 0)) { if (bDiagonal) return 170; else return 160; }
	else if (checkIdenticalNum(numbers, 3, 2)) { if (bDiagonal) return 90; else return 80; }
	else if (checkIdenticalNum(numbers, 3, 0)) { if (bDiagonal) return 50; else return 40; }
	else if (checkIdenticalNum(numbers, 2, 2)) { if (bDiagonal) return 30; else return 20; }
	else if (checkIdenticalNum(numbers, 2, 0)) { if (bDiagonal) return 20; else return 10; }

	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
/*Проверка на 4 единицы*/
bool checkForOnce(const int *numbers) {
	int arr[] = { 1,1,1,1 };
	if (memcmp(numbers, arr, sizeof(arr)) == 0 ||

		/*Ниже строка для ИИ*/
		memcmp(&numbers[1], arr, sizeof(arr)) == 0) return true;

	return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
/*Проверка на  1, 13, 12, 11 и 10*/
bool check113121110(const int *numbers) {
	int arr[] = { 1,10,11,12,13 };

	if (memcmp(numbers, arr, sizeof(arr)) == 0) return true;

	return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
/*Проверка на числа 1 и 13*/
bool check113(const int *numbers) {
	int arr[] = { 1,1,1,13,13 };

	if (memcmp(numbers, arr, sizeof(arr)) == 0) return true;

	return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
/*Проверка на последовательные числа*/
bool checkSerialNum(const int *numbers) {

	for (int iCount = 1; iCount < 5; iCount++) {
		if (numbers[iCount] - numbers[iCount - 1] != 1) return false;
	}

	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
/*Проверка на одинаковые числа*/
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

void newGame() {
	memset(arrPoleUser, 0, sizeof(arrPoleUser));
	memset(arrPoleComp, 0, sizeof(arrPoleComp));
	recreateStackCards();
	isGame = true;
}

void recreateStackCards() {

	vCards.clear();

	for (int iCount = 0; iCount < 4; iCount++)
		for (int nCount = 1; nCount <= 13; nCount++)
			vCards.push_back(nCount);

	random_shuffle(vCards.begin(), vCards.end());

	vCards.resize(25);
}

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

void stepAI() {
	if (!isGame) return; //return NULL не срабатывает, я удивлён
	int row, col;
}

void endGame() {

	int userScores = totalScore(arrPoleUser);
	int compScores = totalScore(arrPoleComp);

	isGame = false;
}

/*
*	В процессе здесь появится простой ИИ
*	который на каждом шагу будет ставить число в ячейку, при которой будет наибольшее суммарное кол-во очков на данном шаге.
*	Ячейка должна лежать не на диагонали и вокруг ячейки должно быть больше свободных клеток, чем на других просмотренных ячейках.
*	Диагонали имеют самый низкий приоритет при рассмотрении ситуации ИИ.
*/