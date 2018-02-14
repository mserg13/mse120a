// IntegerNumb.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstring>


class ClArray
{
private:
	int *Data;
	int arrSize;

public:
	ClArray();
	ClArray(int);
	~ClArray();
	ClArray(const ClArray& t);  // copy
	ClArray(ClArray&& t);       // move

public:
	int getSize() const;  //  размер 
	void Add(const int  val);// добавление в конец 

	void Insert(const  int pos, const int  val);  // добавление в указ. позицию 

	int IndexOf(const int val);   //  возвращает индекс 
	int LastIndexOf(const int val); //  возвращает последний  индекс 
	int resize(int newsize);   // 


public:
	int &operator[](int ind);
	ClArray &operator= (const ClArray &t);
	ClArray &operator= (ClArray &&t);
	int &operator==(ClArray& t);  //  2 массива равны ==
	int &operator!=(ClArray& t);  //  сравнение двух массивов !=
	int & ClArray::operator<(ClArray& t); // сравнение <
	ClArray &operator+(ClArray& m2);
	friend std::istream & operator >> (std::istream & is, ClArray & a);
	friend std::ostream & operator << (std::ostream & to, const ClArray & a);

};


ClArray::~ClArray()
{
	delete[] Data;
	Data = 0;
}

ClArray::ClArray() :
arrSize(10)
{
	Data = new int[arrSize];
	if (Data == 0)
	{
		std::cerr << "Can't allocate memory!!";
		exit(-1);
	}
	memset(Data, 0, arrSize * sizeof(int));
}

ClArray::ClArray(int arr_size) :
arrSize(arr_size)
{
	Data = new int[arrSize];
	if (Data == 0)
	{
		std::cerr << "Can't allocate memory!!";
		exit(-1);
	}
	memset(Data, 0, arrSize * sizeof(int));
}

//ClArray::ClArray(const ClArray& t)   // конструктор копирования
//{
//	if (this == &t)
//		return;
//
//	Data = new int[t.arrSize];
//
//	if (Data == 0)
//	{
//		std::cerr << "Can't allocate memory!!";
//		exit(-1);
//	}
//
//	memcpy(Data, t.Data, t.arrSize * sizeof(int));
//	arrSize = t.arrSize;
//}

ClArray::ClArray(const ClArray& t)  // конструктор копирования
{


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
	//Data = t.Data;

	Data = new int[t.arrSize];
	for (int i = 0; i< arrSize; i++)
		Data[i] = t.Data[i];

	//t.Data = nullptr;
	delete[] t.Data;
	t.Data = 0;

	t.arrSize = 0;
}


int ClArray::getSize() const
{
	return (arrSize);
}

void ClArray::Add(const int val)
{
	// создаем промежуточный массив 
	int *tmp = new int[arrSize];
	if (tmp == 0)
	{
		std::cerr << "Can't allocate memory!!";
		exit(-1);
	}
	memcpy(tmp, Data, arrSize * sizeof(int));// копируем в него данные 
	delete[] Data;  // удалим данные 

	Data = new int[arrSize + 1]; // создаем новые данные + новый елемент который добавили 
	if (Data == 0)
	{
		std::cerr << "Can't allocate memory!!";
		exit(-1);
	}

	for (int i = 0; i < arrSize; ++i)  //  копируем  данные в нов. массив  
		*(Data + i) = *(tmp + i);

	*(Data + arrSize) = val;    // допишем значение в последний эл-мент 

	delete[]tmp;// удалим промежуточный массив 
	tmp = 0;

	arrSize++;  // увеличим размер  массива на 1 

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
	
//	Data = new int[newSize];
//	for (int i = 0; i < newSize; i++)
//		Data[i] = temp[i];

//	delete[] temp;
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
	delete[] Data;
	Data = 0;

	Data = new int[newSize];
	arrSize = newSize;

	for (int i = 0; i < newSize; i++)
		Data[i] = temp[i];
	delete[] temp;
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
		if (Data == 0)
		{
			std::cerr << "Can't allocate memory!!";
			exit(-1);
		}
		memcpy(Data, t.Data, t.arrSize * sizeof(int));
		arrSize = t.arrSize;
	}
	return *this;
}

ClArray &ClArray::operator= (ClArray &&t)
{
	if (this != &t)
	{
		delete[] Data;
		Data = new int[t.arrSize];
		if (Data == 0)
		{
			std::cerr << "Can't allocate memory!!";
			exit(-1);
		}
		memcpy(Data, t.Data, t.arrSize * sizeof(int));
		arrSize = t.arrSize;

		delete[] t.Data;
		//t.Data = nullptr;

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
	ma.Add(2);  // добавление в конец 
	std::cout << "ma = " << ma << std::endl;
	ClArray mb(ma);// копируем 

	std::cout << "mb = " << mb << std::endl;

	//ClArray md(std::move(ma));
	ClArray md;

	//md = std::move(ma);

	md = ma;
	std::cout << "md = " << md << std::endl;
	std::cout << "ma = " << ma << std::endl;

	mb.Insert(mb.IndexOf(3), 99);  // вставим число 99 перед первым элементом со значением 3
	std::cout << std::endl << mb;

	std::cout << std::endl;

	mb[10] = mb[1] + ma[1];

	std::cout << mb[10];
	std::cout << std::endl;
	std::cout << "ma = " << ma << std::endl;

	ma + ma;
	std::cout << std::endl;
	std::cout << "ma = " << ma << std::endl;

	std::cout << (ma == ma) << std::endl;
	std::cout << (ma != ma) << std::endl;
	std::cout << (ma < ma) << std::endl;
	
	ma.resize(5);
	std::cout << "ma.size = " << ma.getSize() << std::endl;
	std::cout << "ma = " << ma << std::endl;
	
	mb.resize(15);
	std::cout << "mb.size = " << mb.getSize() << std::endl;
	std::cout << "mb = " << mb << std::endl;

	getchar();
	getchar();
	return 0;
}

