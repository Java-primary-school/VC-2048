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
	void hanleNum(bool); //产生随机2或4
	bool thanNewAndOld(); //判断数组是否改变
	void changeTemp(); //改变temp
	bool IsGameOver();
	void restart(); //重新开始
	void drawArray(std::function<void(int**)> drawCallBabck); //画数组回调
private:
	int** pieceArray;
	int** tempArray;
	std::vector<int> temp; //存在数组为0的下标
};
