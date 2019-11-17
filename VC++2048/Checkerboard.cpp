#include "Checkerboard.h"
#include <time.h>
#define PIECE_LENGTH 4
Checkerboard::Checkerboard()
{
	this->pieceArray = new int* [PIECE_LENGTH];
	this->tempArray = new int* [PIECE_LENGTH];
	for (size_t i = 0; i < PIECE_LENGTH; i++)
	{
		this->pieceArray[i] = new int[PIECE_LENGTH]();
		this->tempArray[i] = new int[PIECE_LENGTH]();
		
	}
	srand((unsigned)time(0)); //初始化时间种子
	this->hanleNum(true);
	this->changeTemp();
	this->hanleNum(true);
}
Checkerboard::~Checkerboard()
{
	for (size_t i = 0; i < 4; i++)
	{
		delete[] pieceArray[i];
		delete[] tempArray[i];

	}
	delete[] pieceArray;
	delete[] tempArray;
	
}
bool Checkerboard::thanNewAndOld()
{

	for (size_t i = 0; i < PIECE_LENGTH; i++)
	{
		for (size_t j = 0; j < PIECE_LENGTH; j++)
		{
			if (pieceArray[i][j] != tempArray[i][j])
			{
				return false;
			}
		}
	}
	return true;

}
void Checkerboard:: hanleNum(bool init)
{
	bool flag = false;
	//比较在按完方向键后数组是否发生变化
	if (!init) {

		if (thanNewAndOld())
		{

			return;
		}
	}
	//在剩余为0的坐标中产生随机数
	int xy = rand() % (temp.size() == 0 ? 16 : temp.size());


	int data = rand() % 5;
	if (data != 4) {
		data = 2;
	}
	if (init)
	{
		this->pieceArray[xy / PIECE_LENGTH][xy % PIECE_LENGTH] = 2;
	}
	else {
		this->pieceArray[temp[xy] / PIECE_LENGTH][temp[xy] % PIECE_LENGTH] = data;
	}
	
	for (size_t i = 0; i < PIECE_LENGTH; i++)
	{
		for (size_t j = 0; j < PIECE_LENGTH; j++)
		{
			this->tempArray[i][j] = pieceArray[i][j];

		}
	}
	changeTemp();


}
void Checkerboard::changeTemp()

{
	temp.clear();
	for (size_t i = 0; i < PIECE_LENGTH; i++)
	{
		for (size_t j = 0; j < PIECE_LENGTH; j++)
		{
			if (pieceArray[i][j] == 0)
			{
				temp.push_back(i * PIECE_LENGTH + j);

			}

		}
	}
}
void Checkerboard::left(int* fraction)
{
	for (int i = 0; i < PIECE_LENGTH; i++)
	{
		int tempLeft[] = { 0,0,0,0 };
		int k = 0;
		for (int j = 0; j < PIECE_LENGTH; j++)
		{
			if (j < PIECE_LENGTH - 1 && pieceArray[i][j] != 0)
			{
				for (int l = j + 1; l < PIECE_LENGTH; l++) {
					if (pieceArray[i][l] != 0 && pieceArray[i][j] != pieceArray[i][l]) {
						break;
					}
					if (pieceArray[i][l] != 0 && pieceArray[i][j] == pieceArray[i][l]) {
						pieceArray[i][j] = pieceArray[i][j] * 2;
						*fraction += pieceArray[i][j];
						pieceArray[i][l] = 0;
						break;
					}
				}


			}
			if (pieceArray[i][j] != 0)
			{
				tempLeft[k] = pieceArray[i][j];
				k++;
			}

		}
		for (int j = 0; j < PIECE_LENGTH; j++)
		{
			pieceArray[i][j] = tempLeft[j];
		}

	}

}
void Checkerboard::right(int* fraction) {

	for (int i = 0; i < PIECE_LENGTH; i++)
	{
		int tempRight[] = { 0,0,0,0 };
		int k = PIECE_LENGTH - 1;
		for (int j = PIECE_LENGTH - 1; j >= 0; j--)
		{
			if (j > 0 && pieceArray[i][j] != 0)
			{
				for (int l = j - 1; l >= 0; l--) {
					if (pieceArray[i][l] != 0 && pieceArray[i][j] != pieceArray[i][l]) {
						break;
					}
					if (pieceArray[i][l] != 0 && pieceArray[i][j] == pieceArray[i][l]) {
						pieceArray[i][j] = pieceArray[i][j] * 2;
						*fraction += pieceArray[i][j];
						pieceArray[i][l] = 0;
						break;
					}
				}


			}
			if (pieceArray[i][j] != 0)
			{
				tempRight[k] = pieceArray[i][j];
				k--;
			}

		}
		for (int j = 0; j < 4; j++)
		{
			pieceArray[i][j] = tempRight[j];
		}

	}

}
void Checkerboard::down(int *fraction) {

	for (int i = 0; i < PIECE_LENGTH; i++)
	{
		int tempBottom[] = { 0,0,0,0 };
		int k = PIECE_LENGTH - 1;
		for (int j = PIECE_LENGTH - 1; j >= 0; j--)
		{
			if (j > 0 && pieceArray[j][i] != 0)
			{
				for (int l = j - 1; l >= 0; l--) {
					if (pieceArray[l][i] != 0 && pieceArray[j][i] != pieceArray[l][i]) {
						break;
					}
					if (pieceArray[l][i] != 0 && pieceArray[j][i] == pieceArray[l][i]) {
						pieceArray[j][i] = pieceArray[j][i] * 2;
						*fraction += pieceArray[j][i];
						pieceArray[l][i] = 0;
						break;;
					}
				}


			}
			if (pieceArray[j][i] != 0) {
				tempBottom[k] = pieceArray[j][i];
				k--;
			}

		}
		for (int j = 0; j < 4; j++)
		{
			pieceArray[j][i] = tempBottom[j];
		}

	}

}
void Checkerboard::up(int* fraction) {

	for (int i = 0; i < PIECE_LENGTH; i++)
	{
		int tempTop[] = { 0,0,0,0 };
		int k = 0;
		for (int j = 0; j < PIECE_LENGTH; j++)
		{
			if (j < PIECE_LENGTH - 1 && pieceArray[j][i] != 0)
			{
				for (int l = j + 1; l < 4; l++) {
					if (pieceArray[l][i] != 0 && pieceArray[j][i] != pieceArray[l][i]) {
						break;
					}
					if (pieceArray[l][i] != 0 && pieceArray[j][i] == pieceArray[l][i]) {
						pieceArray[j][i] = pieceArray[j][i] * 2;
						*fraction += pieceArray[j][i];
						pieceArray[l][i] = 0;
						break;;
					}
				}
			}
			if (pieceArray[j][i] != 0)
			{
				tempTop[k] = pieceArray[j][i];
				k++;
			}
		}
		for (int j = 0; j < 4; j++)
		{
			pieceArray[j][i] = tempTop[j];
		}
	}

}
bool Checkerboard::IsGameOver()
{
	if(temp.size()!=0)
	{
		return false;
	}
	for (size_t i = 0; i < PIECE_LENGTH; i++)
	{
		for (size_t j = 0; j < PIECE_LENGTH; j++)
		{


			if ((i < PIECE_LENGTH - 1 && pieceArray[i][j] == pieceArray[i + 1][j]) || (j < PIECE_LENGTH - 1 && pieceArray[i][j] == pieceArray[i][j + 1]))
			{
				return false;
			}


		}

	}


	return true;

}
void Checkerboard::restart()
{
	for (size_t i = 0; i < PIECE_LENGTH; i++)
	{
		for (size_t j = 0; j < PIECE_LENGTH; j++)
		{
			pieceArray[i][j] = 0;
		}
	}
	hanleNum(true);
	changeTemp();
	hanleNum(true);

}
void Checkerboard::drawArray(std::function<void(int**)> drawCallBabck)
{
	drawCallBabck(this->pieceArray);
}