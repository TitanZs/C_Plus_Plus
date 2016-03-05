#include <iostream>
#include "string.h"
#include <string>
#include "iomanip"
#include <conio.h>
#include <ctime>
#include "time.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>

using namespace std;

class string_c
{
	char* string_;
	unsigned int capacity;
	unsigned int length;
public:
	// 1) пункт  прменил дилегирование. 
	string_c(): string_c(nullptr){}
	explicit string_c(int i): string_c(nullptr)
	{
		if (i < 10)
			capacity = 10;
		else
			capacity = i;
	}
	explicit string_c(char* _str)
	{
		if (_str == NULL)
		{
			string_ = new char[80];
			strcpy_s(string_, 80, " ");
		}
		else
		{
			string_ = new char[strlen(_str) + 1];
			strcpy_s(string_, strlen(_str) + 1, _str);
		}
		capacity = sizeof(string_);
		length = strlen(string_) + 1;
	}
	string_c(string_c& str) : string_c(str.string_)	{}
	~string_c()	{		delete[] string_;	}

	char* get_string()	{		return string_;	}
	// 2 пункт дилегирование принта
	void print()	{		cout << string_;	}
	void print_ln(){ string_c::print(); cout << endl; }
	void getLine()
	{
		char name[128];
		cout << endl << "Input string: ";
		cin.getline(name, 100);
		string_ = new char[strlen(name) + 1];
		strcpy_s(string_, strlen(name) + 1, name);
		capacity = sizeof(string_);
		length = strlen(string_);
	}
	int getlength()	{		return capacity ;	}
	int getcapacity()	{		return length;	}
	bool compare_to(string_c str)	{ compare_to(str); }
	bool compare_to(char* str)	
	{
		int val = 0;
		for (int i = 0; i < strlen(str); i++)
		{
			if (str[i] == string_[i])
			{
				continue;
			}
			else
			{
				return 1;
			}
		}
		return 0;
	}
	bool contains(string_c str){ return strpbrk(string_, str.string_) ? false : true; }
	bool endswith(char* str)
	{
		int val = 0;
		for (int i = 0; i < strlen("sgd"); i++)
		if (*strstr(string_, str) == string_[strlen(string_)-strlen(str)+i-1]){ val = 0; }	else{ val = 1; }
			return val;
	}
	bool startswith(char* str)
	{
		int val=0;
		for (int i = 0; i < strlen(str); i++)
			if (*strstr(string_, str) == string_[0]){ val = 0; }else{ val = 1; }
			return val; 
	}
	void clear()
	{
		string_ = new char[1];
		strcpy_s(string_, 1, "");
		capacity = 0;
		length = 0;
	}	
	void copyto(string_c* str)
	{
			delete[] str->string_;
			str->string_ = new char[strlen(string_) + 1];
			strcpy_s(str->string_, strlen(string_) + 1, string_);
	}
	bool equals(char* str)	{ return (strcmp(str, string_)) ? true : false; }
	void connetc(string_c str)	
	{
		strcpy_s(string_, strlen(str.string_) + 1, str.string_);
		capacity += str.capacity;
		length += str.length;
	}
	void concat(char* str)	{ concat(str, strlen(string_)); }
	void concat(char* str, int size)
	{
		for (int i = 0; i < size; i++)
		{
			strcat_s(string_, strlen(string_) + strlen(str) + 1, str);
			capacity += sizeof(str);
			length += strlen(str);
		}
	}
	string_c& operator=(const string_c& str)
	{
		if (this != &str)
		{
			delete[] this->string_;
			this->string_ = new char[strlen(str.string_) + 1];
			strcpy_s(this->string_, strlen(str.string_) + 1, str.string_);
		}
		return *this;
	}

	friend bool operator==(const string_c& lstr, const string_c& rstr)	{ return strcmp(lstr.string_, rstr.string_);}
	friend bool operator>(const string_c& lstr, const string_c& rstr)	{ return strcmp(lstr.string_, rstr.string_);}
	friend bool operator<(const string_c& lstr, const string_c& rstr)	{ return strcmp(lstr.string_, rstr.string_);}
	friend bool operator>=(const string_c& lstr, const string_c& rstr)	{ return strcmp(lstr.string_, rstr.string_);}
	friend bool operator<=(const string_c& lstr, const string_c& rstr)	{ return strcmp(lstr.string_, rstr.string_);}
	friend bool operator!=(const string_c& lstr, const string_c& rstr)	{ return strcmp(lstr.string_, rstr.string_);}

	string_c& operator()(const char* str)
	{
		strcpy_s(this->string_, strlen(str) + 1, str);
		return *this;
	}
	char& operator[](int i)
	{
		char pull = '-';
		return (i >= 0 && i < strlen(this->string_)) ? this->string_[i] : pull;
	}
	friend string_c operator+(const string_c& lstr, const string_c& rstr)	
	{
		int size = strlen(lstr.string_) + strlen(rstr);
		char* temp = new char[size + 1];

		for (int i = 0; i < strlen(lstr.string_); i++)
			temp[i] = lstr.string_[i];
		for (int ii = strlen(lstr.string_), j = 0; ii <= size; ii++, j++)
			temp[ii] = rstr[j];

		string_c temp1(temp);
		return temp1;
	}
	string_c& operator+=(const string_c& str) 	{		operator+=(str.string_); return *this;		return *this;	}
	string_c& operator+=(const char str)		{		operator+=(str); return *this; 		return *this;	}
	string_c& operator+=(const char* str)
	{
		// я  не могу определить чего но при выподнении данного кода программа вылетает в деструкторе.  хотя адресс остется тотже. а по логике должно работать!
		// можно узнать ответ в чем проблема?
		// реализовал по другому. Но код больше !
		//strcat_s(string_, strlen(string_) + strlen(str) + 1, str);

		char* temp = new char[strlen(string_) + strlen(str) + 1];
		for (int i = 0, k = 0; i < strlen(string_) + strlen(str) + 1; i++)
		{
			if (i <= strlen(string_)-1)
				temp[i] = string_[i];
			else
			{
				temp[i] = str[k];
				k++;
			}
		}
		delete[] string_;
		string_ = temp;
		temp = nullptr;

		capacity += sizeof(str);
		length += strlen(str);
		return *this;
	}
	friend ostream & operator<<(ostream & cout, const string_c & str)
	{
		cout << str.string_;
		return cout;
	}
	friend istream & operator>>(istream & cin, string_c & str)
	{
		char name[128];
		cout << "Input string: ";
		cin.getline(name, 100);
		str.string_ = new char[strlen(name) + 1];
		strcpy_s(str.string_, strlen(name) + 1, name);
		str.capacity = sizeof(str.string_);
		str.length = strlen(str.string_ );
		return cin;
	}
	operator char*() const
	{
		return string_;
	}
	operator int() const
	{
		int val = 0;
		val = atoi(string_);
		return val;
	}
	operator double() const
	{
		double val = 0;
		val = atof(string_);
		return val;
	}
	// лучше придумать не могу , как оптимизировать!
	int IndexOf(char chr)
	{
		for (int i = 0; i < strlen(string_); i++)
			if (string_[i] == chr)		return i;
		return -1;
	}
	int LastIndexOf(char chr)
	{
		_strrev(string_);
		return IndexOf(chr);
		_strrev(string_);
	}
	int IndexOf(string_c str)	{		return IndexOf(str.string_[0]);	}
	int LastIndexOf(string_c str)	{		return LastIndexOf(str.string_[0]);	}
	bool IndexOfAny(string_c str){		return strstr(string_, str.string_);	}
	void Normalize()
	{
		//_strset(string_, ' ');
	}
	void PadLeft(int val)
	{
		for (val; val > 0; val--)			Insert(" ", 0);
	}
	void PadRight(int val)
	{
		for (val; val > 0; val--)			Insert(" ", strlen(string_));
	}
	void PadLeft(char ch, int val )
	{
		for (val; val > 0; val--)			Insert(&ch, 0);
	}
	void PadRight(char ch, int val)
	{
		for (val; val > 0; val--)			Insert(&ch, strlen(string_));
	}
	const string_c* getstring() const
	{
		return this;
	}
	const char* getstr() const
	{
		return string_;
	}

	void Remove(int val){ string_c::Remove(val, strlen(string_)); }
	void Remove(int ind, int val)
	{
		if (ind <= strlen(string_))
		{
			int size = 256;
			char* temp = new char[size + 1];
			for (int i = 0; i < size; i++)
			{
				if (i >= ind && val >0)
				{
					temp[i] = ' ';
					val--;
				}
				else
					temp[i] = string_[i];
			}
			delete[] string_;
			string_ = temp;
			temp = nullptr;
		}
	}
	void Replace(char R, char Z)
	{
		int size = 256;
		char* temp = new char[size + 1];
		for (int i = 0; i < size; i++)
		{
				temp[i] = string_[i];
				if (temp[i] == R)
					temp[i] = Z;
		}
		delete[] string_;
		string_ = temp;
		temp = nullptr;
	}
	void Replace(string_c substr, string_c rep)
	{	
		// да Наталья действительно интересно придумала.
			int id = IndexOf(substr);
			this->Remove(id, strlen(substr));
			this->Insert(rep, id);
	}
	string_c* split(char separator, int& pieces)
	{
		int kol = 0, i;
		char* g;
		for (i = 0; i < strlen(string_); i++)
			if (string_[i] == separator)kol++;
		pieces = kol+1;
		string_c* temp = new string_c[pieces];
		char* h = string_;
		char* pch = strtok_s(h, &separator, &g);
		i = 0;
		while (pch != NULL)
		{
			temp[i].string_ = pch; i++;
			h = g;
			pch = strtok_s(h, &separator, &g);
		}
		return temp;
	}
	void ToLower()
	{
		_strlwr_s(string_ = _strdup(string_), strlen(string_) + 1);
	}
	void ToUpper()
	{
		_strupr_s(string_ = _strdup(string_), strlen(string_) + 1);
	}
	void Trim()
	{
		TrimStart();
		TrimEnd();
	}
	void TrimStart()
	{		// короче не придумал
		char* temp;
		int i, k;
		for (i = 0; i < strlen(string_); i++)
		{
			if (string_[i] != ' ')
			{
				int val = strlen(string_) - i;
				temp = new char[val+1];
				for (k = 0; k < val; k++, i++)
					temp[k] = string_[i];
				temp[k] = '\0';
				delete[] string_;
				string_ = temp;
				temp = nullptr;
				break;
			}
		}	
		length = strlen(string_);
		capacity = sizeof(string_);
	}
	void TrimEnd()
	{
		char* temp;
		int i, k;
		for (i = strlen(string_)-1; i > 0; i--)
		{
			if (string_[i] != ' ')
			{
				int val = strlen(string_) - (strlen(string_) - i);
				temp = new char[val + 2];
				temp[val+1] = '\0';
				for (k = val; k >= 0; k--, i--)
					temp[k] = string_[i];
				
				delete[] string_;
				string_ = temp;
				temp = nullptr;
				break;
			}
		}
		length = strlen(string_);
		capacity = sizeof(string_);
	}
	void Reverse()	{		_strrev(string_);	}
	void SortAZ()
	{
		for (int i = 0; i<strlen(string_); i++)
		{
			for (int k = 0; k<strlen(string_) - 1 - i; k++)
			{
				if (string_[k + 1]<string_[k])
					swap(string_[k + 1], string_[k]);
			}
		}
	}
	void SortZA()
	{
		this->SortAZ();
		_strrev(string_);
	}
	char* begin()
	{
		return  string_;
	}
	char* end()
	{
		return string_ + strlen(string_);
	}
	void Shuffle()
	{
		random_shuffle(begin(), end());
	}
	void RandomFill()
	{
		int l;
		for (int i = 0; i < strlen(string_)-1; i++)
		{
			 l = rand() % 121;
			string_[i] = l;	
		}
	}
	void Resize(int  val)
	{
		if (val < strlen(string_))
		{
			int  last = val - 1;

			char* temp = new char[strlen(string_) - (strlen(string_) - last) + 2];
			for (int i = 0, f = 0; i < strlen(string_) - (strlen(string_) - last) + 1; i++, f++)
			{
				temp[i] = string_[f];
			}
			temp[strlen(string_) - (strlen(string_) - last) + 1] = '\0';

			delete[] string_;
			string_ = temp;
			temp = nullptr;

			length = strlen(string_) - (strlen(string_) - last);
			capacity = sizeof(string_);
		}
	}
	void Insert(char* str, int val)
	{
		if (val < strlen(string_))
		{
			int  last = val - 1;

			char* temp = new char[strlen(string_) + (strlen(str)) + 1];
			for (int i = 0, f = 0, k = 0; i < strlen(string_) + (strlen(str) + 1); i++)
			{
				
				if (i < val || i > val + strlen(str)-1)
				{
					temp[i] = string_[k];
					k++;
				}
				else
				{
					temp[i] = str[f];
					f++;
				}
			}
		
			delete[] string_;
			string_ = temp;
			temp = nullptr;

			length = strlen(string_) - (strlen(string_) - last);
			capacity = sizeof(string_);
		}
	}
};
static int Compare(string_c fir, string_c sec)
{
	Compare(fir, sec);
}
static int Compare(string_c fir, char* sec)
{
	for (int i = 0; i < strlen(fir.get_string()); i++)
	{
		if (fir[i] == sec[i])
		{
			continue;
		}
		else
		{
			return 0;
		}
	}
	return 1;
}
void main()
{
	srand(time(NULL));

	string_c c("1");
	string_c b("123456");

	// реализация индекс
	cout << b.LastIndexOf(c) << endl;

	// а как еще проверить операторы?, все рабоатет! 
	cout << "Operator == -\t";
	if (c == b)
		cout << true;
	else
		cout << false;
	cout << endl;

	cout << "Operator < -\t";
	if (c < b)
		cout << true;
	else
		cout << false;
	cout << endl;

	cout << "Operator > -\t";
	if (c > b)
		cout << true;
	else
		cout << false;
	cout << endl;

	cout << "Operator <= -\t";
	if (c <= b)
		cout << true;
	else
		cout << false;
	cout << endl;

	cout << "Operator >= -\t";
	if (c >= b)
		cout << true;
	else
		cout << false;
	cout << endl;

	cout << "Operator != -\t";
	if (c != b)
		cout << true;
	else
		cout << false;
	cout << endl;

	c += b;

	c.print_ln();

	/*b.TrimEnd();

	char a = '3';
	int kol;
	string_c* gf;
	gf = b.split(a, kol );
	for (int i = 0; i < kol; i++)
		gf[i].print_ln();

	//b.print_ln();

	*/


}
