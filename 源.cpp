#include<iostream>
#include <ctype.h>
#include <stdio.h>
#include<string.h>
#include<bitset>
#include"stdlib.h"
using namespace std;

const int IP[64] = {58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,
                      62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,
                      57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,
                      61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7};//CHECK

const int IP_[64] = { 40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,
                        38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,
                        36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27,
                        34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25 };//CHECK

const int E[48] = { 32,1,2,3,4,5,4,5,6,7,8,9,
				 8,9,10,11,12,13,12,13,14,15,16,17,
				 16,17,18,19,20,21,20,21,22,23,24,25,
				 24,25,26,27,28,29,28,29,30,31,32,1 };//CHECK

const int P[32] = { 16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,
				 2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25 };//CHECK

const int PC1[56] = { 57,49,41,33,25,17,9,1,58,50,42,34,26,18,
                      10,2,59,51,43,35,27,19,11,3,60,52,44,36,
					  63,55,47,39,31,23,15,7,62,54,46,38,12,22,
					  14,6,61,53,45,37,29,21,13,5,28,20,30,4 };//CHECK

const int PC2[48] = { 14,17,11,24,1,5,3,28,15,6,21,10,
                      23,19,12,4,26,8,16,7,27,20,13,2,
                      41,52,31,37,47,55,30,40,51,45,33,48,
                      44,49,39,56,34,53,46,42,50,36,29,32 };//CHECK

const int S[32][16] = { 14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
					    0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
					    4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
					    15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13, 
						15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
                        3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
                        0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
                        13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9, 
						10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
                        13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
                        13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
                        1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12, 
						7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
                        13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
                        10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
                        3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14, 
						2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
                        14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
                        4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
                        11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3, 
						12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
                        10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
                        9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
                        4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13, 
					    4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
                        13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
                        1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
                        6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12,
	                    13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
                        1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
                        7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
                        2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11 };//CHECK

int c[64] = {};

int k[56] = {};

int K[48] = {};//仅在局部使用

void initswap(int* );//初始置换

void endswap(int*);//最后的逆初始置换

void LRswap(int*);//左右换

void keyswap(int*);

void moveswap(bool,int*,int);//对于轮子密钥的操作,flag若为1则加密，为0解密

void round(int*);//轮结构

void tobin(int , int ,int* );

void process(bool, unsigned int, unsigned int, unsigned int, unsigned int);

int main()
{
	bool flag=false;
	/*unsigned int C1 = 0x85E81354;
	unsigned int C2 = 0x0F0AB405;
	unsigned int KEY1 = 0x13345779;
	unsigned int KEY2 = 0x9BBCDFF1;*/

	unsigned int C1 = 0x01234567;
	unsigned int C2 = 0x89ABCDEF;
	unsigned int KEY1 = 0x13345779;
	unsigned int KEY2 = 0x9BBCDFF1;
	unsigned int D1 = 0x2d16f19a;
	unsigned int D2 = 0x2ac2582a;
	process(flag, C1, C2, KEY1, KEY2);
	cout << endl;
	process(true, D1, D2, KEY1, KEY2);
	system("pause");
	return 0;
}

void initswap(int* p)
{
	int *temp;
	temp = (int*)malloc(sizeof(int) * 64);
	for (int i = 0; i < 64; i++)
	{
		temp[i] = p[IP[i] - 1];
	}
	for (int i = 0; i < 64; i++)
	{
		p[i] = temp[i];
	}
	free(temp);
}//CHECK

void LRswap(int* p)
{
	int temp;
	for (int i = 0; i < 32; i++)
	{
		temp = p[i];
		p[i] = p[i + 32];
		p[i + 32] = temp;
	}
}

void endswap(int* p)
{
	int *temp;
	temp = (int*)malloc(sizeof(int) * 64);
	for (int i = 0; i < 64; i++)
	{
		temp[i] = p[IP_[i] - 1];
	}
	for (int i = 0; i < 64; i++)
	{
		p[i] = temp[i];
	}
	free(temp);
}

void keyswap(int*p)
{
	int *temp;
	temp = (int*)malloc(sizeof(int) * 56);
	for (int i = 0; i < 56; i++)
	{
		temp[i] = p[PC1[i] - 1];
	}
	for (int i = 0; i < 56; i++)
	{
		p[i] = temp[i];
	}
	free(temp);//CHECK
}

//********************************************************************************
//轮结构内部有问题，一直到free前面都可以运行，但是在第二次循环的时候就会出问题
void round(int* p)//轮结构
{
	int *R;
	int *L;
	int *XOR;
	int *T;
	int row;
	int col;
	R = (int *)malloc(sizeof(int) * 32);
	L = (int *)malloc(sizeof(int) * 32);
	XOR = (int *)malloc(sizeof(int) * 48);
	T = (int *)malloc(sizeof(int) * 32);
	for (int i = 0; i < 32; i++)//分成左右两部分
	{
		L[i] = p[i];
		R[i] = p[i + 32];
		p[i] = R[i];//上一次的右侧是下一次的左侧
	}
	for (int i = 0; i < 48; i++)
	{
		XOR[i] = R[E[i]-1];//扩展置换，E表，因为从一开始所以要减一
		XOR[i] = XOR[i] ^ K[i];
	}
	char str[5] = {};//转二进制
	for (int i = 0; i < 8; i++)//S盒代换
	{
		int temp;
		row = 4 * i + 2*XOR[6 * i]+XOR[6 * i + 5];
		col = 8*XOR[6 * i + 1]+4* XOR[6 * i + 2]+2*XOR[6 * i + 3]+ XOR[6 * i + 4];
		temp = S[row][col];
		temp += 16;
		itoa(temp, str, 2);
		for (int j = 0; j < 4; j++)
		{
			R[j + 4 * i] = str[j + 1]-48;//char型，ascii码，所以要-48
			str[j + 1] = NULL;
		}
	}
	for (int i = 0; i < 32; i++)//P置换
	{
		T[i] = R[P[i] - 1];
	}
	for (int i = 0; i < 32; i++)//和左侧的异或
	{
		p[i + 32] = T[i] ^ L[i];
		//因为之前已经将p左侧更改过而且这里没必要对R操作，直接给p赋值
	}
	free(R);
	free(L);
	free(XOR);
	free(T);
}

void moveswap(bool flag,int* c,int turn)//移动＋置换选择
{
	int num;
	int *temp;
	temp = (int *)malloc(sizeof(int)*56);
	if (flag == true)
	{
		if ((turn > 2 && turn < 9) || (turn > 9 && turn < 16))
			num = 2;
		else
			num = 1;
	}
	else
	{
		if (turn == 1)
			num = 0;
		else if (turn == 2 || turn == 9 || turn == 16)
			num = 27;
		else
			num = 26;
	}
	for (int i = 0; i < 28; i++)
	{
		temp[i] = c[(i + num) % 28];
		temp[i+28] = c[(i + num) % 28 + 28];
	}	
	for (int i = 0; i < 56; i++)
	{
		c[i] = temp[i];
	}
	for (int i = 0; i < 48; i++)
	{
		K[i] = temp[PC2[i] - 1];
	}
	free(temp);
}//CHECK

void tobin(int a, int b,int* p)
{
	bitset<32> bitveca(a);
	bitset<32> bitvecb(b);
	for (int i = 0; i < 32; i++)
	{
		p[63 - i] = bitvecb[i];
		p[31 - i] = bitveca[i];
	}
	for (int i = 0; i < 64; i++)
	cout << p[i];
	cout << endl;
}//CHECK

void process(bool flag,unsigned int C1, unsigned int C2, unsigned int KEY1, unsigned int KEY2)
{
	int *temp;
	temp = (int*)malloc(sizeof(int) * 64);
	tobin(C1, C2, c);
	tobin(KEY1, KEY2, temp);
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			k[j + 7 * i] = temp[j + 8 * i];
		}
	}
	free(temp);
	initswap(c);
	keyswap(k);
	for (int i = 1; i < 16; i++)
	{
		moveswap(flag, k, i);
		round(c);
	}

	LRswap(c);
	endswap(c);

	for (int i = 0; i < 16; i++)
	{
		cout << hex << 8*c[i * 4]+4*c[i * 4 + 1]+2*c[i * 4 + 2]+ c[i * 4 + 3];
	}
}