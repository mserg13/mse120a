/// IntegerNumb.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstring>


class ClArray
{
private:
	int *Data;
	int arrSize;
	int maxSize;

public:
	ClArray();
	ClArray(int);
	ClArray(int arr_size, const int& n);
	~ClArray();
	ClArray(const ClArray& t);  // copy
	ClArray(ClArray&& t);       // move

public:
	int getSize() const;  //  размер 
	int pushback(const int  val);// добавление в конец 
	int popback();// взять элемент в конце массива 
	int reserve(const int n); // резерв n + n, arrSize = n
	void Insert(const  int pos, const int  val);  // добавление в указ. позицию 

	int IndexOf(const int val);   //  возвращает индекс 
	int LastIndexOf(const int val); //  возвращает последний  индекс 
	int resize(int newsize);   // 
	int resizeOne(int newsize);

public:
	int &operator[](int ind);
	ClArray &operator= (const ClArray &t);
	ClArray &operator= (ClArray &&t);
	int &operator==(ClArray& t);  //  2 массива равны ==
	int &operator!=(ClArray& t);  //  сравнение двух массивов !=
	int & operator<(ClArray& t); // сравнение <
	ClArray &operator+(ClArray& m2);
	friend std::istream & operator >> (std::istream & is, ClArray & a);
	friend std::ostream & operator << (std::ostream & to, const ClArray & a);

};


ClArray::~ClArray()
{
	//	delete[] Data;
}

ClArray::ClArray() :
arrSize(10)
{
	Data = new int[arrSize];
	for (int i = 0; i< arrSize; i++)
		Data[i] = 0;
}

ClArray::ClArray(int arr_size) :
arrSize(arr_size)
{
	Data = new int[arrSize];
	for (int i = 0; i< arrSize; i++)
		Data[i] = 0;
}

ClArray::ClArray(int arr_size, const int& n) :
arrSize(arr_size)
{
	Data = new int[arrSize];
	for (int i = 0; i< arrSize; i++)
		Data[i] = n;
}

ClArray::ClArray(const ClArray& t)  // конструктор копирования
{

	if (this == &t)
		return;

	arrSize = t.arrSize;
	Data = new int[t.arrSize];
	for (int i = 0; i< arrSize; i++)
		Data[i] = t.Data[i];
}

ClArray::ClArray(ClArray&& t)  // конструктор перемещения
: Data(nullptr),
arrSize(0)
{
	arrSize = t.arrSize;
	Data = t.Data;

	t.Data = nullptr;
	t.arrSize = 0;

}


int ClArray::getSize() const
{
	return (arrSize);
}

int ClArray::pushback(const int val)
{
	// создаем промежуточный массив 

	int newSize = arrSize + 1;
	int *tmp = new int[newSize];
	for (int i = 0; i< arrSize; i++)
		tmp[i] = this->Data[i];
	tmp[arrSize] = val;

	delete[] Data;
	Data = tmp;
	arrSize = newSize;
	tmp = 0;

	return arrSize;
}

int ClArray::popback()
{
	// создаем промежуточный массив 

	int newSize = arrSize - 1;
	int *tmp = new int[newSize];
	for (int i = 0; i< newSize; i++)
		tmp[i] = Data[i];
	
	delete[] Data;
	Data = tmp;
	arrSize = newSize;
	tmp = 0;

	return arrSize;
}

int ClArray::reserve(const int n)
{
	// создаем промежуточный массив 

	arrSize = n;
	maxSize = 2*n;
	int *tmp = new int[maxSize];
	for (int i = 0; i< arrSize; i++)
		tmp[i] = Data[i];
	for (int i = arrSize; i< maxSize; i++)
		tmp[i] = 0;

	delete[] Data;
	Data = tmp;
	
	tmp = 0;

	return arrSize;
}



int ClArray::IndexOf(const int val)
{
	for (int pos = 0; pos < arrSize; ++pos)
	{
		if (val == *(Data + pos))
			return (pos);
	}
	return -1;
}

void ClArray::Insert(const  int pos, const int  val)
{
	if (pos < 0 || pos >(arrSize - 1))
	{
		std::cerr << "Index out of range";
		exit(-1);
	}
	arrSize++;

	int *tmp = new int[arrSize];
	if (tmp == 0)
	{
		std::cerr << "Can't allocate memory!!";
		exit(-1);
	}
	int i = 0, j = 0;
	while (i < pos)
	{
		*(tmp + i) = *(Data + i);
		i++;
	}

	*(tmp + pos) = val;
	j = i;
	i++;

	while (i < (arrSize))
	{
		tmp[i++] = Data[j++];
	}
	delete[] Data;

	Data = new int[arrSize];
	if (Data == 0)
	{
		std::cerr << "Can't allocate memory!!";
		exit(-1);
	}
	memcpy(Data, tmp, arrSize * sizeof(int));
	delete[]tmp;
	tmp = 0;

}


int ClArray::LastIndexOf(const int val)
{
	for (int pos = arrSize - 1; pos != -1; --pos)
	{
		if (val == *(Data + pos))
			return (pos);
	}
	return -1;
}



int ClArray::resizeOne(int newSize)  // изменение размера массива
{

	arrSize = newSize;

	return newSize;

}


int ClArray::resize(int newSize)  // изменение размера массива
{

	int  *temp = new int[newSize];
	if (arrSize >= newSize)
	{
		for (int i = 0; i < newSize; i++)
			temp[i] = Data[i];
	}
	else
	{
		for (int i = 0; i < arrSize; i++)
			temp[i] = Data[i];
		for (int i = arrSize; i < newSize; i++)
			temp[i] = 0;
	}

	delete[] Data;
	Data = 0;

	Data = &temp[0];
	temp = 0;

	arrSize = newSize;

	return newSize;

}

int & ClArray::operator ==(ClArray& t)// const
{
	int ok = 1;
	if (arrSize == t.arrSize)
	{
		int i = 0;
		while (i < arrSize && ok)
		if (Data[i] != t.Data[i])
		{
			ok = 0;
			return ok;
		}
		else i++;
	}
	return ok;
}

ClArray & ClArray::operator+(ClArray& m2)// const
{
	int newSize = arrSize + m2.arrSize;
	int  *temp = new int[newSize];
	for (int i = 0; i < arrSize; i++)
		temp[i] = Data[i];
	for (int i = arrSize; i < newSize; i++)
		temp[i] = m2.Data[i - arrSize];

	//delete[] Data;
	Data = 0;

	Data = &temp[0];
	arrSize = newSize;
	temp = 0;

	return *this;
}


int & ClArray::operator !=(ClArray& t)// const
{
	int ok = 0;
	if (arrSize == t.arrSize)
	{
		int i = 0;
		while (i < arrSize && !ok)
		if (Data[i] != t.Data[i])
		{
			ok = 1;
			return ok;
		}
		else
			i++;
	}
	return ok;
}

int & ClArray::operator<(ClArray& t)// const
{
	int ok = 0;
	int min;
	if (arrSize <= t.arrSize)
		min = arrSize;
	else
		min = t.arrSize;
	int i = 0;
	while (i < min && !ok)
	{
		if (Data[i] == t.Data[i])
		{
			i++;
		}
		else
		{
			if (Data[i] < t.Data[i])
			{
				ok = 1;
				return ok;
			}
			else
			{
				ok = 0;
				return ok;
			}

		}
	}

	return ok;
}



int & ClArray::operator[](int ind)// const
{
	if (ind > (arrSize - 1) || ind < 0)
	{
		std::cerr << "Index out of range";
		exit(-1);
	}
	return (Data[ind]);
}


ClArray &ClArray::operator= (const ClArray &t)
{
	if (this != &t)
	{
		delete[] Data;
		Data = new int[t.arrSize];
		Data = &t.Data[0];
		arrSize = t.arrSize;

		// Delete comments
	}
	return *this;
}

ClArray &ClArray::operator= (ClArray &&t)
{
	if (this != &t)
	{
		delete[] Data;

		Data = t.Data;
		arrSize = t.arrSize;

		t.Data = nullptr;
		t.arrSize = 0;
	}
	return *this;
}



std::ostream & operator << (std::ostream & to, const ClArray & a)
{
	for (int i = 0; i < a.arrSize; ++i)

		to << a.Data[i] << ' ';
	return to;
}

std::istream & operator >> (std::istream & is, ClArray & a)
{
	for (int i = 0; i < a.arrSize; ++i)
		is >> a.Data[i];
	return is;
}


int main()
{
	ClArray ma;
	ClArray mc(3);//  создаем массив на три э-та, по умолчанию заполнен нулями
	std::cout << "Enter a elements:\n";
	std::cin >> ma;  // Ввводим значения 
	std::cout << ma[9] << std::endl;  // Вывод 10-го э-та 
	ma.pushback(2);  // добавление в конец 
	std::cout << "ma = " << ma << std::endl;

	ClArray mb(ma);//  конструктор копирования
	std::cout << "mb(ma) " << std::endl;
	std::cout << "mb = " << mb << std::endl;
	std::cout << "ma = " << ma << std::endl;

	ClArray md(std::move(ma)); // move constructor
	std::cout << "md(std::move(ma)) " << std::endl;
	std::cout << "md = " << md << std::endl;
	std::cout << "ma = " << ma << std::endl;


	ma = md;       // оператор присваивания
	std::cout << "ma = md " << std::endl;
	std::cout << "md = " << md << std::endl;
	std::cout << "ma = " << ma << std::endl;

	ClArray mf;
	mf = std::move(ma);  // оператор перемешения
	std::cout << "mf = std::move(ma) " << std::endl;
	std::cout << "mf = " << md << std::endl;
	std::cout << "ma = " << ma << std::endl;
	ma = mf;


	std::cout << "Some manipulations:  " << std::endl;
	mb.Insert(mb.IndexOf(3), 99);  // вставим число 99 перед первым элементом со значением 3
	std::cout << std::endl << mb;
	std::cout << std::endl;
	mb[10] = mb[1] + ma[1];

	std::cout << mb[10];
	std::cout << std::endl;
	std::cout << "ma = " << ma << std::endl;
	ma = ma + ma;
	std::cout << "ma = ma + ma " << std::endl;
	std::cout << "ma = " << ma << std::endl;

	std::cout << "Some compares:  " << std::endl;
	std::cout << (ma == ma) << std::endl;
	std::cout << (ma != ma) << std::endl;
	std::cout << (ma < ma) << std::endl;

	ma.resize(5);
	std::cout << "ma.size = " << ma.getSize() << std::endl;
	std::cout << "ma = " << ma << std::endl;

	mb.resize(15);
	std::cout << "mb.size = " << mb.getSize() << std::endl;
	std::cout << "mb = " << mb << std::endl;

	
	std::cout << "mf = " << mf << std::endl;
	mf.pushback(1000);  // add element
	std::cout << "mf.pushback(1000) " << std::endl;
	std::cout << "mf = " << mf << std::endl;

	mf.popback();  // add element
	std::cout << "mf.popback() " << std::endl;
	std::cout << "mf = " << mf << std::endl;


	mf.reserve(4);  // add element
	std::cout << "mf.reserve(4) " << std::endl;
	std::cout << "mf = " << mf << std::endl;

	std::cout << "mf[3] = " << mf[3] << std::endl;

	mf.resizeOne(6);
	std::cout << "mf[5] = " << mf[5] << std::endl;



	getchar();
	getchar();
	return 0;
}

