#include "Booth_.h"
#include <stdio.h>
#include <iostream>

#define uint unsigned int
using namespace std;


Booth::Booth(int a, int b, int bit)
{
	x = a;
	y = b;
	bits = bit;
}

Booth::~Booth()
{

}
void Booth::Output()
{
	bool dot = true;
	for (int i = bits; i >= 0; i--)
	{
		putchar(((res >> i) & 0x01) + 0x30);

		if ((i == bits - 1) && dot)
		{
			putchar('.');
		}
	}
}
void Booth::count()
{
	uint result = 0;
	int z = 0;

	bits++;	//ѭ�����Σ����һ��Ч��
	y <<= 1;//β���0
	for (int i = 0; i < bits; i++)
	{
		//y&0x01 �����һλ��1  ��+-y�Ĳ���  ((int)((y >> 1) & 0x01)))-y�Ĳ���
		uint t = (((int)(y & 0x01)) - ((int)((y >> 1) & 0x01))) * x;
		z += (int)t;
		if ((z & (1 << bits)) == 0)
		{
			z &= ((1 << (bits + 1)) - 1);
		}
		y >>= 1;
		result >>= 1;
		result |= ((((uint)z) & 0x01) << 31);

		if (i < (bits - 1))
		{
			z >>= 1;
		}
	}

	if ((z & (1 << bits)) != 0)
	{
		z |= ~((1 << (bits + 1)) - 1);
	}

	result = ((((uint)z)) << (bits - 1)) | ((result >> (32 - bits)) & ((1 << bits) - 1));
	bits = bits + bits - 1;
	res = result;
}