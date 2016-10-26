// ����, ���, ���� "������ ����������������-2", �++, ���
//
// tbitfield.cpp - Copyright (c) ������� �.�. 07.05.2001
//   ������������ ��� Microsoft Visual Studio 2008 �������� �.�. (19.04.2015)
//
// ������� ����




#include "tbitfield.h"


TBitField::TBitField(int len) //:BitLen(len) ����������� 
{
	BitLen = len;
	MemLen = (len - 1) / (8 * sizeof(TELEM)) + 1;
	pMem = new TELEM[len];
	if (pMem != NULL)
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = 0;
		}
}

TBitField::TBitField(const TBitField &bf) // ����������� ����������� (�������������???)
{
	BitLen = bf.BitLen;  //���������� ���������� ����������� �������� �������� ���� �����������������
	MemLen = bf.MemLen;  //���-�� ��������� ��� �������������� �������� ����
	pMem = new TELEM[MemLen];  //��������� ������ ��� ������� ����
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i]; //�������� �������� �� ��������� ����� � ������ ��� �������� ����
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // ������ ������ ������� � ������� ���� n
{
	return n / (sizeof(TELEM) * 8); //�������� ������ ����, � ������� �������� ���� �����. ��� 35--1. 8 ��� ����� ��� � ���� � �������� �� 4
}

TELEM TBitField::GetMemMask(const int n) const // ������� ����� ��� ���� n
{
	return 1 << (n % (sizeof(TELEM) * 8));	//�������� 1 �� ������� �� ������� �� 32. ��� 35-3 
}

// ������ � ����� �������� ����

int TBitField::GetLength(void) const // �������� ����� (�-�� �����)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // ���������� ����� ���
{
	if (n < 0)
	{
		throw 'n<0'; //throw invalid_argument("Number<0")
	}
	if (n > BitLen)
	{
		throw 'n>BL';
	}
	pMem[GetMemIndex(n)] |= GetMemMask(n); //�������� ������� pMem � �������� ���� � ������� �������� ���� ����� ����������� ������ �������� � ���������� � ������
}


void TBitField::ClrBit(const int n) // �������� ���
{
	if (n < 0)
	{
		throw 'n<0';
	}
	if (n > BitLen)
	{
		throw 'n>BL';
	}
	pMem[GetMemIndex(n)] &= ~GetMemMask(n); //�������� ������� pMem � �������� ���� � ������� �������� ���� ����� ����������� ������ �������� � ���������� � ��������� ����� ������ ��������
}

int TBitField::GetBit(const int n) const // �������� �������� ����
{
	if (n < 0)
	{
		throw 'n<0';
	}
	if (n > BitLen)
	{
		throw 'n>BL';
	}
	return ((pMem[GetMemIndex(n)] & GetMemMask(n)) != 0); //�� ������� �� ������� ����� ����������� ����� ��������. �� ��� ������� ����� 1. ������� � �������� �������

}

// ������� ��������

TBitField& TBitField::operator=(const TBitField &bf) //���������� ������������
{
	if (pMem != bf.pMem) //���� ������� ���� �� ���������, ��
	{
		BitLen = bf.BitLen; //����������� ������� ����� ����
		MemLen = bf.MemLen; //����������� �������� ���-�� �����
		delete[]pMem; //������� ������ �������� ����
		pMem = new TELEM[MemLen]; //�������� ������. ������������ ������ ������ ����� MemLen
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i]; //������ ������������� ������������
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // ���������� ��������� ���������
{
	int result = 1; //���������� ����� ��������� 1
	if (BitLen != bf.BitLen) result = 0; //���� ����� �� ���������, �� ������������� ��������� ��� ���������
	else
		for (int i = 0; i < BitLen; i++) //���� �� ��������� ��� ��������� ����
		{
			if (pMem[i] != bf.pMem[i]) result = 0; break; //���� ���� ��� �� ���������, �� ������� �� �����
		}
	return result;
}

int TBitField::operator!=(const TBitField &bf) const // ��������� ���������
{

	int result = 0; //���������� ����� ��������� 0, �� ���������
	if (BitLen != bf.BitLen) result = 1; //���� ����� �� ���������, �� ������������� ��� ������� ����� �� �����
	else
		for (int i = 0; i < BitLen; i++) //���� �� ��������� ��� ��������� ����
		{
			if (pMem[i] != bf.pMem[i]) result = 1; break; //���� ���� ��� �� ���������, �� ������� �� ����� � ������� �� �����
		}
	return result;
}

TBitField TBitField::operator|(const TBitField &bf) // ���������� �������� "���"
{
	int len = BitLen; //����� ���������. ����������� ����� ������� �����
	if (len < bf.BitLen)  //���� ����� ������ ����� ������� �������, �� ����������� ����� ������� ��������
		len = bf.BitLen;
	TBitField temp(len); //������� ����� ������ ������ ������� � ����� ���� ���������
	for (int i = 0; i < MemLen; i++) //���� �� ���� �������� �������
		temp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++) //���� �� ����� ������� �������
		temp.pMem[i] |= bf.pMem[i]; //������ ��������� ���.
	return temp; //���������� ������, ������� � ����� ������ ����� ��������
}

TBitField TBitField::operator&(const TBitField &bf) // ���������� �������� "�"
{
	int len = BitLen;
	if (len > bf.BitLen)
		len = bf.BitLen;
	TBitField temp(len);
	for (int i = 0; i < MemLen; i++)
		temp.pMem[i] = pMem[i];
	for (int i = 0; i < len; i++)
		temp.pMem[i] &= bf.pMem[i];
	return temp;
}

TBitField TBitField::operator~(void) // ���������� ���������
{
	TBitField temp(*this);
	for (int i = 0; i < MemLen - 1; i++) //���� �� ����� ��������� �������
	{
		temp.pMem[i] = ~temp.pMem[i]; //������ �������� ���� ��������
	}
	for (int i = sizeof(TELEM) * 8 * (MemLen - 1); i < BitLen; i++)
	{
		if ((temp).GetBit(i) == 1) //���� �������� ����=1
			temp.ClrBit(i); //��������� ������ ���� 0
		else
			temp.SetBit(i); //��������� ��� ����� ����� �� ����
	}
	return temp;
}

// ����/�����

istream &operator >> (istream &istr, TBitField &bf) // ����
{
	char c; //�������� ������
	int i = 0;
	istr >> c; //������ ��� ���� 0 ��� 1, ���� �� ��� ����� �� �
	while ((c == '1') || (c == '0'))
	{
		if (c == '1')
		{
			bf.SetBit(i); //���� C �� ������� i=1 �� ������ ���� �������
		}
		if (c == '0')
		{
			bf.ClrBit(i); //���� C �� ������� i=0 �� ������� ���/��������� 0
		}
		i++;
		istr >> c; //������ �
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // �����
{
	ostr << " Length of BitField=" << bf.BitLen << endl; //������� ������� �� 0 � 1 ����� �����
	for (int i = 0; i < bf.BitLen; i++) //���� �� ���� ���������
	{
		ostr << bf.GetBit(i);
	}
	return ostr;
}