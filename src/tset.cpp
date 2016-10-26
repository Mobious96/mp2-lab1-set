






#include "tset.h"

TSet::TSet(int mp) :BitField(mp)
{
	MaxPower = mp;
}


TSet::TSet(const TSet &s) :BitField(s.BitField)
{
	MaxPower = s.MaxPower;
}


TSet::TSet(const TBitField &bf) :BitField(bf)
{
	MaxPower = bf.GetLength();
}

TSet::operator TBitField() 

{
	TBitField temp(this->BitField);
	return temp;
}

int TSet::GetMaxPower(void) const 
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const 
{
	return BitField.GetBit(Elem); 
}

void TSet::InsElem(const int Elem) 
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) 
{
	BitField.ClrBit(Elem);
}



TSet& TSet::operator=(const TSet &s) 
{
	BitField = s.BitField;
	MaxPower = s.MaxPower;
	return *this;
}

int TSet::operator==(const TSet &s) const 
{
	return BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const 
{
	return BitField != s.BitField;
}

TSet TSet::operator+(const TSet &s) 
{

	TSet temp(BitField | s.BitField);
	return temp;
}

TSet TSet::operator+(const int Elem) 
{
	if (Elem > BitField.GetLength())
	{
		throw 'E>L';
	}
	TSet temp(BitField);
	temp.InsElem(Elem);
	return temp;
}

TSet TSet::operator-(const int Elem) 
{
	TSet temp(MaxPower);
	temp.DelElem(Elem);
	return temp;
}

TSet TSet::operator*(const TSet &s) 
{
	TSet temp(BitField & s.BitField);
	return temp;
}

TSet TSet::operator~(void) 
{
	TSet temp(~BitField);
	return temp;
}



istream &operator >> (istream &istr, TSet &s) 
{
	int i = 0;
	char c;
	do
	{
		istr >> c;
	} while (c != '{');
	do
	{
		istr >> i;
		s.InsElem(i);
		do
		{
			istr >> c;
		} while ((c = ',') && (c = '}'));
	} while (c != '}');
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) 
{
	ostr << '{';
	for (int i = 0; i < s.GetMaxPower(); i++)
	{
		if (s.IsMember(i))
		{
			ostr << ' ' << i << ',';
		}
	}
	ostr << '}';
	return ostr;
}