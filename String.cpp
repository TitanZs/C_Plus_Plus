#include <iostream>
#include "string.h"
#include "iomanip"
#include <conio.h>
#include <ctime>
#include "time.h"
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
	string_c(const string_c& str) : string_c(str){}
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
	// 3 пункт проверка по содержимому
	bool compare_to(string_c str)
	{ 	
		int val = 0;
		for (int i = 0; i < strlen(str.get_string()); i++)
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
		int str_in = strlen(str);
		int str_ = strlen(string_);

		for (int i = str_in, p = str_; i > 0; i--, p--)
		{
			if (string_[p] == str[i])
			{
				if (str_in = 0) return 0;
				continue;
			}
			else
			{
				return -1;
			}
		}
	}
	void clear()
	{
		string_ = new char[1];
		strcpy_s(string_, 1, "");
		capacity = 0;
		length = 0;
	}
	bool startswith(char* str)
	{
		for (int i = 0; i > 0; i++)
		{
			if (string_[i] == str[i])
			{
				if (i = strlen(str)) return 0;
				continue;
			}
			else
			{
				return -1;
			}
		}
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
	void concat(char* str)
	{
		strcat_s(string_, strlen(string_) + strlen(str) + 1, str);
		capacity += sizeof(str);
		length += strlen(str);
	}
	void contact(char* str[], int size)
	{
		for (int i = 0; i < size; i++)
		{
			strcat_s(string_, strlen(string_) + strlen(str[i]) + 1, str[i]);
			capacity += sizeof(str[i]);
			length += strlen(str[i]);
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
	friend bool operator==(const string_c& lstr, const string_c& rstr)
	{
		return strcmp(lstr.string_,rstr.string_);
	}
	friend bool operator>(const string_c& lstr, const string_c& rstr)
	{
		return (strlen(lstr.string_) > strlen(rstr.string_)) ? true : false;
	}
	friend bool operator<(const string_c& lstr, const string_c& rstr)
	{
		return (strlen(lstr.string_) < strlen(rstr.string_)) ? true : false;
	}
	friend bool operator>=(const string_c& lstr, const string_c& rstr)
	{
		return (strlen(lstr.string_) >= strlen(rstr.string_)) ? true : false;
	}
	friend bool operator<=(const string_c& lstr, const string_c& rstr)
	{
		return (strlen(lstr.string_) <= strlen(rstr.string_)) ? true : false;
	}
	friend bool operator!=(const string_c& lstr, const string_c& rstr)
	{
		return (strlen(lstr.string_) != strlen(rstr.string_)) ? true : false;
	}
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
		int size = strlen(lstr.string_) + strlen(rstr.string_);
		char* temp = new char[size + 1];
		for (int i = 0; i < strlen(lstr.string_); i++)
			temp[i] = lstr.string_[i];
		for (int ii = strlen(lstr.string_), j = 0; ii <= size; ii++, j++)
			temp[ii] = rstr.string_[j];
		//strcat_s(temp1, strlen(temp1) + strlen(rstr.string_) + 1, rstr.string_);
		string_c temp1(temp);
		return temp1;
	}
	// 4 пункт делигирование оператора =+
	string_c& operator+=(const string_c& str) 	{		string_c::operator+=(str);	}
	string_c& operator+=(const char str)	{ string_c::operator+=(str); }
	string_c& operator+=(const char* str)
	{
		int size = strlen(this->string_) + strlen(str);
		char* temp = new char[size + 1];
		for (int i = 0; i < strlen(this->string_); i++)
			temp[i] = this->string_[i];
		for (int ii = strlen(this->string_), j = 0; ii <= size; ii++, j++)
			temp[ii] = str[j];

		this->capacity += sizeof(str);
		delete this->string_;
		this->string_ = temp;

		this->length += strlen(str);
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
	// 5 пункт переделал  методы инт и дабл
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
	int IndexOf(char chr)
	{
		for (int i = 0; i < strlen(string_); i++)
		{
			if (string_[i] == chr)
				return i;
		}
		return -1;
	}
	int LastIndexOf(char chr)
	{
		for (int i = strlen(string_); i > 0; i--)
		{
			if (string_[i] == chr)
				return i;
		}
		return -1;
	}
	int IndexOf(string_c str)
	{
		return  strpbrk(string_, str.string_) ? false : true;
	}
	int LastIndexOf(string_c str)
	{
		for (int i = strlen(string_); i > 0; i--)
		{
			if (string_[i] == str.string_[i])
				return i;
		}
		return -1;
	}
	int IndexOfAny(string_c str)
	{
		for(int i = 0; i < strlen(string_); i++)
		{
			if (string_[i] == str.string_[i])
				return i;
		}
		return -1;
	}
	void Normalize()
	{
		//_strset(string_, ' ');
	}
	void PadLeft(int val)
	{
		int size = strlen(string_) + val;
		char* temp = new char[size + 1];
		for (int i = 0; i < strlen(string_); i++)
		{
			temp[i] = string_[i];
		}
		for (int i = strlen(string_); i <= size; i++)
		{
			temp[i] = ' ';
		}
		delete[] string_;
		string_ = temp;
		temp = nullptr;
	}
	void PadRight(int val)
	{
		int size = strlen(string_) + val;
		char* temp = new char[size + 1];
		for (int i = 0; i < val; i++)
		{
			temp[i] = ' ';
		}
		for (int i = val, j = 0; i <= size; i++, j++)
		{
			temp[i] = string_[j];
		}
		delete[] string_;
		string_ = temp;
		temp = nullptr;
	}
	void PadLeft(char ch, int val )
	{
		int size = strlen(string_) + val;
		char* temp = new char[size + 1];
		for (int i = 0; i < strlen(string_); i++)
		{
			temp[i] = string_[i];
		}
		for (int i = strlen(string_); i <= size; i++)
		{
			temp[i] = ch;
		}
		delete[] string_;
		string_ = temp;
		temp = nullptr;
	}
	const string_c* getstring() const
	{
		return this;
	}
	const char* getstr() const
	{
		return string_;
	}
	void PadRight(char ch, int val )
	{
		int size = strlen(string_) + val;
		char* temp = new char[size + 1];
		for (int i = 0; i < val; i++)
		{
			temp[i] = ch;
		}
		for (int i = val, j = 0; i <= size; i++, j++)
		{
			temp[i] = string_[j];
		}
		delete[] string_;
		string_ = temp;
		temp = nullptr;
	}
	void Remove(int val)
	{
		if (val <= strlen(string_))
		{
			int size = strlen(string_)  - val;
			char* temp = new char[size+1];
			for (int i = 0; i < size; i++)
			{
				temp[i] = string_[i];
			}
			delete[] string_;
			string_ = temp;
			temp = nullptr;
		}
	}
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
		int val1;
		int chek = 0;
		for (int i = 0, j=0; i < strlen(string_); i++)
		{
			if (string_[i] == substr.string_[0])
			{
				for (int k = i, j = 0; j < strlen(substr.string_); j++, k++)
				{
					val1 = i;
					if (string_[k] == substr.string_[j])
					{
						chek = 1;
					}
					else
					{	
						chek = 0;
						break;
					}
				}
				if (chek == 1)
				{
					for (j = 0; j < strlen(substr.string_); j++, val1 ++)
					{
						string_[val1] = rep[j];
					}
				}
			}
		}
	}
	string_c* split(char separator, int& pieces)
	{
		int kol = 1;
		for (int i = 0; i < strlen(string_); i++)
		{
			if ((char)string_[i] == separator)
				 kol++;
		}
		if (kol > 1)
		{
			int kol2 = 2;
			string_c* temp = new string_c[kol];
			pieces = kol;
			for (int i = 0, p = 0, y = 0; i < strlen(string_); i++)
			{
				if (string_[i] == separator)
				{
					temp[p].string_[y] = '\0';
					p++;
					y=0;
					continue;
				}
				temp[p].string_[y] = string_[i];
				temp[p].length++;
				temp[p].capacity = sizeof(temp[p].string_);
				y++;
				if (i == strlen(string_)-1)
					temp[p].string_[y] = '\0';
			}
			return temp;
		}
		return nullptr;
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

		int first = 0, last = 0;
		for (int i = 0; i < strlen(string_); i++)
		{
			if (string_[i] != ' ')
			{
				first = i;
				break;
			}
		}
		for (int i = strlen(string_)-1; i > 0; i--)
		{
			if (string_[i] != ' ')
			{
				last = i;
				break;
			}
		}
		char* temp = new char[last - first+2];
		for (int i = 0, f = first; i < last - first+1; i++, f++)
		{
			temp[i] = string_[f];
		}
		temp[last - first + 1] = '\0';

		delete[] string_;
		string_ = temp;
		temp = nullptr;

		length =   last - first;
		capacity = sizeof(string_);
	}
	void TrimStart()
	{

		int first = 0;
		for (int i = 0; i < strlen(string_); i++)
		{
			if (string_[i] != ' ')
			{
				first = i;
				break;
			}
		}
		char* temp = new char[strlen(string_) - first + 2];
		for (int i = 0, f = first; i < strlen(string_) - first + 1; i++, f++)
		{
			temp[i] = string_[f];
		}
		temp[strlen(string_) - first + 1] = '\0';

		delete[] string_;
		string_ = temp;
		temp = nullptr;

		length = strlen(string_) - first;
		capacity = sizeof(string_);
	}
	void TrimEnd()
	{
		int  last = 0;
		for (int i = strlen(string_) - 1; i > 0; i--)
		{
			if (string_[i] != ' ')
			{
				last = i;
				break;
			}
		}
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
	void Reverse()
	{	
		char* temp = new char[strlen(string_)+1];
		for (int i = 0, f = strlen(string_)-1; i < strlen(string_); i++, f--)
		{
			temp[i] = string_[f];
		}
		temp[strlen(string_)] = '\0';

		delete[] string_;
		string_ = temp;
		temp = nullptr;

		length = strlen(string_);
		capacity = sizeof(string_);
	}
	void SortAZ()
	{
		int temp = 0; 
		bool exit = false; 
		while (!exit)
		{
			exit = true;
			for (int i = 0; i < (strlen(string_) - 1); i++) 
			if (string_[i] > string_[i + 1])
			{
				temp = string_[i];
				string_[i] = string_[i + 1];
				string_[i + 1] = temp;
				exit = false;
			}
		}
	}
	void SortZA()
	{
		int temp = 0;
		bool exit = false;
		while (!exit)
		{
			exit = true;
			for (int i = strlen(string_) - 1; i > 0; i--)
			if (string_[i] > string_[i - 1])
			{
				temp = string_[i];
				string_[i] = string_[i - 1];
				string_[i - 1] = temp;
				exit = false;
			}
		}
	}
	void Shuffle()
	{
		for (int i = 0; i < (strlen(string_) - 1); i++)
		{
			int temp = 0;
			int l = rand() % strlen(string_) ;
			int k = rand() % strlen(string_)  ;
			temp = string_[k];
			string_[k] = string_[l];
			string_[l] = temp;
		}
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
	int val = 0;
	for (int i = 0; i < strlen(fir.get_string()); i++)
	{
		if (fir[i] == sec[i])
		{
			val = 0;
			continue;
		}
		else
		{
			return 1;
		}
	}
	if (val == 0)
	{
		if (fir.getlength() == sec.getlength())
			val = 0;
		else
			val = 1;

		if (fir.getcapacity()  == sec.getcapacity() )
			val = 0;
		else
			val = 1;

		if (val = 0)
			return 0;
		else
			return 1;
	}
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
	/*
	char* str_test = "1) Hello world";
	string_c s(str_test);
	s.print();
	string_c d("2) Hello");
	d.print();
	cout << setw(3) << "==" << setw(3);
	if (d == s) cout << "-1"; else cout << "0"; cout << endl;
	cout << setw(3) << "<" << setw(3);
	if (d > s) cout << "-1"; else cout << "0"; cout << endl;
	cout << setw(3) << ">" << setw(3);
	if (d < s) cout << "-1"; else cout << "0"; cout << endl;
	cout << setw(3) << ">=" << setw(3);
	if (d >= s) cout << "-1"; else cout << "0"; cout << endl;
	cout << setw(3) << "<=" << setw(3);
	if (d <= s) cout << "-1"; else cout << "0"; cout << endl;
	d("Privet");
	d.print();
	cout << setw(3) << "6" << setw(3);
	cout << d[6]; cout << endl;
	cout << setw(3) << "4" << setw(3);
	cout << d[4]; cout << endl;
	d = d + s;
	d.print();
	d += s;
	d.print();
	d += "dddd";
	d.print(); cout << endl;
	//cout << "String - " << d;
	//cin >> d;
	d.print(); cout << endl;
	cout << "convert to char -  " << (char*)d << endl;
	cout << "convert to int -  " << (int)d << endl;
	cout << "convert to double -  " << (double)d << endl;
	d.print();
	//d.getLine();
	d.print();
	cout << endl << d.compare_to(s);
	cout << endl << d.compare_to("Test");
*/
	//string_c s;

	//char* st[10] = { "aaa", "ddd", "ggg", "qqq", "bbb", "nnn", "mmm", "jjj", "uuu", "ttt" };
	//strcat_s(st[0],2, "d");
	
	
	/*
	s.print();
	s.contact(st, 10);
	s.print();
	*/
	string_c a("1234563890");
	string_c b("   hjanrsgssgd     ");
	//a.print();
	//a.copyto(&b);
	//b.print();
	//cout << endl;
	//b.clear();
	//cout << b.IndexOf('d') << endl;
	//cout << b.IndexOf('g') << endl;
	//cout << endl << b.IndexOf(a);
	//b.Normalize();
	//b.print();
	//a.PadRight(10);
	//a.print();
	//a.print();
	//a.Remove(3);
	//a.Remove(3, 3);
	//a.Replace('4', '0');
	//string_c test1("456");
	//string_c test2("000");
	//a.Replace(test1, test2);
	
	//string_c n;
	//n.print_ln();

	/*
	int kol_split;
	string_c* gf;
	gf = a.split('3', kol_split);
	
	for (int i = 0; i < kol_split; i++)
		gf[i].print_ln();
	*/
	b.print(); cout  << "<" << endl;
	b.Insert("%%%%",5);
	b.print(); 	cout << "<" << endl;

	

	//int size;
	//char* g = a.split('2', size);
	
}
