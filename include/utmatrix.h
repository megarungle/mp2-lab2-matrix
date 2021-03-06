﻿// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
  ValType *pVector;
  int Size;       // размер вектора
  int StartIndex; // индекс первого элемента вектора
public:
  TVector(int s = 10, int si = 0);
  TVector(const TVector &v);                // конструктор копирования
  ~TVector();
  int GetSize()      { return Size;       } // размер вектора
  int GetStartIndex(){ return StartIndex; } // индекс первого элемента
  ValType& operator[](int pos);             // доступ
  bool operator==(const TVector &v) const;  // сравнение
  bool operator!=(const TVector &v) const;  // сравнение
  TVector& operator=(const TVector &v);     // присваивание

  // скалярные операции
  TVector  operator+(const ValType &val);   // прибавить скаляр
  TVector  operator-(const ValType &val);   // вычесть скаляр
  TVector  operator*(const ValType &val);   // умножить на скаляр

  // векторные операции
  TVector  operator+(const TVector &v);     // сложение
  TVector  operator-(const TVector &v);     // вычитание
  ValType  operator*(const TVector &v);     // скалярное произведение

  // ввод-вывод
  friend istream& operator>>(istream &in, TVector &v)
  {
    for (int i = 0; i < v.Size; i++)
      in >> v.pVector[i];
    return in;
  }
  friend ostream& operator<<(ostream &out, const TVector &v)
  {
    for (int i = 0; i < v.Size; i++)
      out << v.pVector[i] << ' ';
    return out;
  }
};

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
    if (s < 0)
    {
        throw "negative size";
    }
    
    if (si < 0)
    {
        throw "negative SI";
    }
    
    if (s > MAX_VECTOR_SIZE || si > MAX_VECTOR_SIZE)
    {
        throw "too large size";
    }
    
    Size = s;
    StartIndex = si;
    
    pVector = new ValType[Size];
    
    for (int i = 0; i < Size; ++i)
    {
        pVector[i] = 0;
    }
} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v)
{
    Size = v.Size;
    StartIndex = v.StartIndex;
    
    pVector = new ValType[Size];
    
    for (int i = 0; i < Size; ++i)
    {
        pVector[i] = v.pVector[i];
    }
} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector()
{
    delete[] pVector;
} /*-------------------------------------------------------------------------*/

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)
{
    if (pos >= StartIndex + Size)
    {
        throw "out of range";
    }
    
    if (pos < StartIndex)
    {
        throw "pos can not be less than SI";
    }
    
    return pVector[pos - StartIndex];
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const
{
    if ( (Size == v.Size) && (StartIndex == v.StartIndex) )
    {
        for (int i = 0; i < Size; ++i)
        {
            if (pVector[i] != v.pVector[i])
            {
                return 0;
            }
        }
        
        return 1;
    }
    
    return 0;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const
{
    return !((*this) == v);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
    if (this != &v)
    {
        if (Size != v.Size)
        {
            Size = v.Size;
            delete[] pVector;
            pVector = new ValType[Size];
        }
        
		StartIndex = v.StartIndex;

        for (int i = 0; i < Size; ++i)
        {
            pVector[i] = v.pVector[i];
        }
    }
    
    return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
	TVector<ValType> Tmp(*this);

    for (int i = 0; i < Tmp.Size; ++i)
    {
        Tmp.pVector[i] += val;
    }

	return Tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
	TVector<ValType> Tmp(*this);

	for (int i = 0; i < Tmp.Size; ++i)
	{
		Tmp.pVector[i] -= val;
	}

	return Tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
	TVector<ValType> Tmp(*this);

	for (int i = 0; i < Tmp.Size; ++i)
	{
		Tmp.pVector[i] *= val;
	}

	return Tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
    /*
    if ( (StartIndex + Size) != (v.StartIndex + v.Size) )
    {
        throw "non equal";
    }
    
    TVector<ValType> TmpB = (Size >= v.Size) ? *this : v;
    TVector<ValType> TmpS = (v.Size <= Size) ? v : *this;
    
    for (int i = 0; i < TmpS.Size; ++i)
    {
        TmpB.pVector[TmpB.Size - TmpS.Size + i] += TmpS.pVector[i]; 
    }
    
    return TmpB;
    */
    
    // простая реализация
    if ( (Size != v.Size) || (StartIndex != v.StartIndex) )
    {
        throw "non equal";
    }
    
    TVector<ValType> Tmp(*this);
    
    for (int i = 0; i < Size; ++i)
    {
        Tmp.pVector[i] = Tmp.pVector[i] + v.pVector[i];
    }
    
    return Tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
    /*
    if ( (StartIndex + Size) != (v.StartIndex + v.Size) )
    {
        throw "non equal";
    }
    
    TVector<ValType> TmpB = (Size >= v.Size) ? *this : v;
    TVector<ValType> TmpS = (v.Size <= Size) ? v : *this;
    
    for (int i = 0; i < TmpS.Size; ++i)
    {
        TmpB.pVector[TmpB.Size - TmpS.Size + i] -= TmpS.pVector[i]; 
    }
    
    return TmpB;
    */
    
    // простая реализация
    if ( (Size != v.Size) || (StartIndex != v.StartIndex) )
    {
        throw "non equal";
    }
    
    TVector<ValType> Tmp(*this);
    
    for (int i = 0; i < Size; ++i)
    {
        Tmp.pVector[i] = Tmp.pVector[i] - v.pVector[i];
    }
    
    return Tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
    /*
    if ( (StartIndex + Size) != (v.StartIndex + v.Size) )
    {
        throw "non equal";
    }
    
    ValType Tmp = 0;
    
    TVector<ValType> TmpB = (Size >= v.Size) ? *this : v;
    TVector<ValType> TmpS = (v.Size <= Size) ? v : *this;
    
    for (int i = 0; i < TmpS.Size; ++i)
    {
        Tmp += TmpB.pVector[TmpB.Size - TmpS.Size + i] * TmpS.pVector[i]; 
    }
    
    return Tmp;
    */
    
    // простая реализация
    if ( (Size != v.Size) || (StartIndex != v.StartIndex) )
    {
        throw "not equal";
    }
    
    ValType Tmp = 0;
    
    for (int i = 0; i < Size; ++i)
    {
        Tmp += pVector[i] * v.pVector[i];
    }
    
    return Tmp;
} /*-------------------------------------------------------------------------*/


// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
  TMatrix(int s = 10);                           
  TMatrix(const TMatrix &mt);                    // копирование
  TMatrix(const TVector<TVector<ValType> > &mt); // преобразование типа
  bool operator==(const TMatrix &mt) const;      // сравнение
  bool operator!=(const TMatrix &mt) const;      // сравнение
  TMatrix& operator= (const TMatrix &mt);        // присваивание
  TMatrix  operator+ (const TMatrix &mt);        // сложение
  TMatrix  operator- (const TMatrix &mt);        // вычитание

  // ввод / вывод
  friend istream& operator>>(istream &in, TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      in >> mt.pVector[i];
    return in;
  }
  friend ostream& operator<<(ostream &out, const TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      out << mt.pVector[i] << endl;
    return out;
  }
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s): TVector<TVector<ValType> >(s)
{
    if (s < 0)
    {
        throw "negative size";
    }
    
    if (s > MAX_MATRIX_SIZE)
    {
        throw "too large size";
    }
    
    for (int i = 0; i < s; ++i)
    {
        this->pVector[i] = TVector<ValType>(s-i, i);
    }
} /*-------------------------------------------------------------------------*/

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt):
    TVector<TVector<ValType> >(mt)
    {
        // можно убрать этот цикл, т.к. TVector<TVector<ValType> >(mt)
        // уже выполнил всю работу
        
        /*
        for (int i = 0; i < this->Size; ++i)
        {
            this->pVector[i] = mt.pVector[i];
        }
        */
    }

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt):
    TVector<TVector<ValType> >(mt) {}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
    /*
    if (size != mt.Size) return 0;
    
    for (int i = 0; i < this->Size; ++i)
    {
        if (this->pVector[i] != mt.pVector[i]) return 0;
    }
    
    return 1;
    */
    
    // или
    
    return TVector<TVector<ValType> >::operator==(mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
    return !((*this) == mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
    if (this != &mt)
    {
        if (this->Size != mt.Size)
        {
			this->Size = mt.Size;
            delete[] this->pVector;
			this->pVector = new TVector<ValType>[this->Size];
        }

        for (int i = 0; i < this->Size; ++i)
        {
			this->pVector[i] = mt.pVector[i];
        }
    }
    
    return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
    /*
    if (this->Size != mt.Size)
    {
        throw "not equal";
    }
    
    TMatrix<ValType> Tmp(*this);
    
    for (int i = 0; i < this->Size; ++i)
    {
        Tmp.pVector[i] = Tmp.pVector[i] + mt.pVector[i];
    }
    
    return Tmp;
    */
    
    return TVector<TVector<ValType> >::operator+(mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
    /*
    if (this->Size != mt.Size)
    {
        throw "not equal";
    }
    
    TMatrix<ValType> Tmp(*this);
    
    for (int i = 0; i < this->Size; ++i)
    {
        Tmp.pVector[i] = Tmp.pVector[i] - mt.pVector[i];
    }
    
    return Tmp;
    */
    
    return TVector<TVector<ValType> >::operator-(mt);
} /*-------------------------------------------------------------------------*/

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif