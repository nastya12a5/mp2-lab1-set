// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	
	if (len < 0)
		throw ("wrong length");
	else {
		BitLen = len;
		if (len % (sizeof(TELEM) * 8) == 0)
			MemLen = len / (sizeof(TELEM) * 8);
		else
			MemLen = (len / (sizeof(TELEM) * 8)) + 1;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;
	}

}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	pMem = new TELEM[MemLen];
	if (pMem != NULL)
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	
	delete []pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return(n / 32);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	TELEM t = 1;
	char shift = n % 32;
	TELEM result= t << shift;
	return result;
	
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
 return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n >= BitLen)) { throw "wrong length"; }
	TELEM m= GetMemMask(n);
	int idx = GetMemIndex(n);
	pMem[idx]= pMem[idx] | m;
	
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n >= BitLen)) { throw "wrong length"; }
	TELEM m= ~(GetMemMask(n));

	int idx= GetMemIndex(n);
	pMem[idx]= pMem[idx] & m;
	
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n >= BitLen)) { throw "wrong length"; }
	TELEM m= GetMemMask(n);
	int idx= GetMemIndex(n);
	TELEM res= m & pMem[idx];
	(res != 0) ? (res = 1) : (res);
  return res;
	
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	
	if (MemLen != bf.MemLen)
	{
		delete []pMem;
	}
	pMem = new TELEM[bf.MemLen];
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	for(int i = 0; i < MemLen; i++)
	{
		pMem[i]= bf.pMem[i];
	}
	return *this;
	
	
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
	{
		return 0;
	}
		for (int i = 0; i <MemLen; i++)
		{
			if ((*this).pMem[i] != bf.pMem[i])
			{
				return 0;
			}
		} 
	
	
		for (int i = (MemLen - 1) * 32; i < BitLen; i++)
		{
			if (GetBit(i) != bf.GetBit(i))
			{
				return 0;
			}

		}
		return 1;
	
	
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	
	if (*this == bf)
		return 0;
	else
		return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	
	
	int max_L = BitLen;
	if (max_L < bf.BitLen)
		max_L = bf.BitLen;
	TBitField res(max_L);
	for (int i = 0; i < MemLen; i++)
		res.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		res.pMem[i] |= bf.pMem[i];
	return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	
	
	int Mlen = BitLen;
	if (Mlen < bf.BitLen) Mlen = bf.BitLen;
	TBitField res(Mlen);
	for (int i = 0; i < MemLen; i++) res.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++) res.pMem[i] &= bf.pMem[i];
	return res;
}

TBitField TBitField::operator~(void) // отрицание
{
	
	TBitField res(BitLen);
	for (int i = 0; i < BitLen; i++) {
		if (!GetBit(i))
			res.SetBit(i);
		else
			res.ClrBit(i);
	}
	return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	char a;
	for (int i = 0; i < bf.MemLen; i++)
	{
		bf.pMem[i]= 0;
	}


	for (int i = 0; i < bf.BitLen; i++) {
		istr >> a;
		if (a == '1') {
			bf.SetBit(i);
		}
		else if (a == '0') {
			bf.ClrBit(i);
		}
		else {
			break;
		}
	}
	return istr;
	

}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{

	for (int i = 0; i < bf.BitLen; i++) {
		if (bf.GetBit(i) != 0)
		{
			ostr << '1';

		}
		else { ostr << '0'; }
		

		
	}
	return ostr;
	
}
