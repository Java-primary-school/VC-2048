#pragma once
#include <iostream>
#include <vector>
#define PIECE_LENGTH 4
#include <functional>
class Checkerboard
{
public:
	Checkerboard();
	~Checkerboard();
	void left(int*);
	void right(int*);
	void up(int*);
	void down(int*);
	void hanleNum(bool); //�������2��4
	bool thanNewAndOld(); //�ж������Ƿ�ı�
	void changeTemp(); //�ı�temp
	bool IsGameOver();
	void restart(); //���¿�ʼ
	void drawArray(std::function<void(int**)> drawCallBabck); //������ص�
private:
	int** pieceArray;
	int** tempArray;
	std::vector<int> temp; //��������Ϊ0���±�
};
