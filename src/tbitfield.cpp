// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле




#include "tbitfield.h"


TBitField::TBitField(int len) //:BitLen(len) конструктор 
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

TBitField::TBitField(const TBitField &bf) // конструктор копирования (инициализатор???)
{
	BitLen = bf.BitLen;  //внутренней переменной присваиваем значение битового поля максимальнойдлины
	MemLen = bf.MemLen;  //кол-во элементов для предоставления битового поля
	pMem = new TELEM[MemLen];  //выделение памяти под битовое поле
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i]; //копируем элементы из вводимого числа в память для битового поля
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс памяти дляинта в котором есть n
{
	return n / (sizeof(TELEM) * 8); //получаем индекс инта, к котором хранится наше число. для 35--1. 8 это число бит в бите и умножаем на 4
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << (n % (sizeof(TELEM) * 8));	//сдвигаем 1 на остаток от деления на 32. для 35-3 
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить сдвиг бит
{
	if (n < 0)
	{
		throw 'n<0'; //throw invalid_argument("Number<0")
	}
	if (n > BitLen)
	{
		throw 'n>BL';
	}
	pMem[GetMemIndex(n)] |= GetMemMask(n); //элементу массива pMem с индексом инта в котором хранится наше число присваиваем старое значение и объединяем с маской
}


void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0)
	{
		throw 'n<0';
	}
	if (n > BitLen)
	{
		throw 'n>BL';
	}
	pMem[GetMemIndex(n)] &= ~GetMemMask(n); //элементу массива pMem с индексом инта в котором хранится наше число присваиваем старое значение и пересекаем с инверсией маски нашего элемента
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0)
	{
		throw 'n<0';
	}
	if (n > BitLen)
	{
		throw 'n>BL';
	}
	return ((pMem[GetMemIndex(n)] & GetMemMask(n)) != 0); //на элемент из массива интов накладываем маску элемента. на его позиции стоит 1. битовое и получаем элемент

}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) //перегрузка присваивания
{
	if (pMem != bf.pMem) //если биторые поля не совпадают, то
	{
		BitLen = bf.BitLen; //присваиваем значине длины поля
		MemLen = bf.MemLen; //присваиваем значение кол-ва интов
		delete[]pMem; //удаляем память битового поля
		pMem = new TELEM[MemLen]; //выделяем память. динамический массив пустой длины MemLen
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i]; //делаем поэлементноге присваивание
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // перегрузка сравнение равенство
{
	int result = 1; //изначально безем результат 1
	if (BitLen != bf.BitLen) result = 0; //если длтны не совпадают, то автоматически отсеиваем это сравнение
	else
		for (int i = 0; i < BitLen; i++) //цикл по элементам при равенстве длин
		{
			if (pMem[i] != bf.pMem[i]) result = 0; break; //если хоть раз не совпадают, то выходим их цикла
		}
	return result;
}

int TBitField::operator!=(const TBitField &bf) const // прегрузка сравнение
{

	int result = 0; //изначально безем результат 0, те совпадают
	if (BitLen != bf.BitLen) result = 1; //если длтны не совпадают, то автоматически эти массивы интов не равны
	else
		for (int i = 0; i < BitLen; i++) //цикл по элементам при равенстве длин
		{
			if (pMem[i] != bf.pMem[i]) result = 1; break; //если хоть раз не совпадают, то выходим их цикла и массивы не равны
		}
	return result;
}

TBitField TBitField::operator|(const TBitField &bf) // перегрузка операция "или"
{
	int len = BitLen; //новая переменна. присваиваем длину массива интов
	if (len < bf.BitLen)  //если длина меньше длины второго объекта, то присваиваем длине большее значение
		len = bf.BitLen;
	TBitField temp(len); //создаем новый объект класса который и бдует наши смлиянием
	for (int i = 0; i < MemLen; i++) //цикл по длин перрвого массива
		temp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++) //цикл по длине второго массива
		temp.pMem[i] |= bf.pMem[i]; //делаем побитовое или.
	return temp; //возвращаем массив, который и будет итогом нашей операции
}

TBitField TBitField::operator&(const TBitField &bf) // перегрузка операция "и"
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

TBitField TBitField::operator~(void) // перегрузка отрицание
{
	TBitField temp(*this);
	for (int i = 0; i < MemLen - 1; i++) //цикл по длине исходного массива
	{
		temp.pMem[i] = ~temp.pMem[i]; //делаем инверсию всех значений
	}
	for (int i = sizeof(TELEM) * 8 * (MemLen - 1); i < BitLen; i++)
	{
		if ((temp).GetBit(i) == 1) //если значение бита=1
			temp.ClrBit(i); //вставляем вместо него 0
		else
			temp.SetBit(i); //оставляем его таким какой он есть
	}
	return temp;
}

// ввод/вывод

istream &operator >> (istream &istr, TBitField &bf) // ввод
{
	char c; //вводимый символ
	int i = 0;
	istr >> c; //делаем его ввод 0 или 1, если не эти числа то в
	while ((c == '1') || (c == '0'))
	{
		if (c == '1')
		{
			bf.SetBit(i); //если C на позиции i=1 то вводим этот элемент
		}
		if (c == '0')
		{
			bf.ClrBit(i); //если C на позиции i=0 то удаляем его/заполняем 0
		}
		i++;
		istr >> c; //вводим С
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	ostr << " Length of BitField=" << bf.BitLen << endl; //выводим строчку из 0 и 1 длины такой
	for (int i = 0; i < bf.BitLen; i++) //цикл по длин элементаж
	{
		ostr << bf.GetBit(i);
	}
	return ostr;
}