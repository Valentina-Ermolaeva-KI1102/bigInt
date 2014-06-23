#include "bigInt.h"

void BinaryWrite(bigInt *integer, char *FName)
{
	if(integer == NULL)
		return;
	std::ofstream out(FName, std::ios::out | std::ios::binary);
	if(!out.good())
	{
		std::cout<<"Error create file.\n";
		return;
	}
	if(!integer->size)
		out.write("0", 1);
	else
	{
		if(integer->Sign)
			out<<'-';
		if(integer->size)
			out.write(integer->Integer, integer->size);
	}
	out.close();
}

void TextWrite(bigInt *integer, char *FName)
{
	if(integer == NULL)
		return;
	std::ofstream out(FName, std::ios::out);
	if(!out.good())
	{
		std::cout<<"Error create file.\n";
		return;
	}
	if(!integer->size)
		out<<0;
	else
	{
		if(integer->Sign)
			out<<'-';
		int i = 0;
		while(i < integer->size)
		{
			out<<integer->Integer[i];
			i++;
		}
	}
	out.close();
}

int atoi(char ch)//Из символа в число
{
	if(ch == '0') return 0;
	if(ch == '1') return 1;
	if(ch == '2') return 2;
	if(ch == '3') return 3;
	if(ch == '4') return 4;
	if(ch == '5') return 5;
	if(ch == '6') return 6;
	if(ch == '7') return 7;
	if(ch == '8') return 8;
	if(ch == '9') return 9;
	return -1;
} 

char itoa(int i)//из цифры в символ
{
	if(i<0) i = -i;
	switch(i)
	{
	case 0: return '0';
	case 1: return '1';
	case 2: return '2';
	case 3: return '3';
	case 4: return '4';
	case 5: return '5';
	case 6: return '6';
	case 7: return '7';
	case 8: return '8';
	case 9: return '9';
	default: return 0;
	}
}

char* shiftRight(char *integer, int p)//сдвиг строки на 1 разряд в право
{
	int i = 0, j = 0;
	while(integer[i] != '\0')
		i++;
	while(integer[j] == -51 )
		j++;
	memcpy(integer, integer+p, i - p);
	memset(integer+(i-p), '0', p);
	return integer;
}

char* divisionInTwo(char* integer)//Деление числа в строке на 2
{
	int size = 0, beg, it, cf = 0;
	while(integer[size] != '\0')
		size++;
	char *rez = (char*)malloc(size+1);
	beg = it = 0;
	if(beg < 0)
		return NULL;
	while(beg < size)
	{
		rez[it] = itoa((atoi(integer[beg]) + 10 * cf)/2);
		cf = atoi(integer[beg])%2;
		it++;
		beg++;
	}
	rez[it] = 0;
	return rez;
}

bigInt::bigInt()
{
	Integer = NULL;
	Sign = false;
	size = 0;
}

bigInt::bigInt(char *integer)
{
	
	Integer = NULL;
	Sign = false;
	size = 0;
	if(!integer || !strcmp(integer, ""))
		return;
	int anti_size = 0, i = 0;
	if(integer[0] == '-')
	{
		Sign = true;
		i++;
	}
	else if(integer[0] == '+')
		i++;
	else if(!isdigit(integer[0]))
	{
		std::cout<<"error in input string!\n";
		return;
	}
	int j = i;
	while(integer[j] == '0')
		j++;
	anti_size += (j - i);
	while(integer[i] != '\0')
	{
		if(!isdigit(integer[i]))
		{
			std::cout<<"error in input string!\n";
			return;
		}
		size++;
		i++;
	}
	size = size - anti_size;
	if(!size)
		return;
	Integer = (char*)malloc(size+1);
	memcpy(Integer, integer+j, size);
	Integer[size] = 0;
}

bigInt::bigInt(int integer)
{
	Integer = NULL;
	Sign = false;
	size = 0;
	if(!integer)
		return;
	if(integer < 0)
		Sign = true;
	int int_buf = integer;
	do 
		size++;
	while(int_buf /= 10);
	Integer = (char*)malloc(size+1);
	int i = size - 1;
	while(integer)
	{
		Integer[i] = itoa(integer%10);
		integer /= 10;
		i--;
	}
	Integer[size] = 0;
}

bigInt::bigInt(char *FName, bool Binary)
{
	Integer = NULL;
	Sign = false;
	size = 0;
	char buf;
	if(!Binary)
	{
		std::ifstream in(FName, std::ios::in);
		if(!in.good())
		{
			std::cout<<"Error open file.\n";
			return;
		}
		in.seekg(0, std::ios::end);
		size = in.tellg();
		in.seekg(0, std::ios::beg);
		in>>buf;
		if(buf == -52)
		{
			std::cout<<"Error: Empty file.\n";
			return;
		}
		else if(buf == '-')
		{
			Sign = true;
			size--;
			in>>buf;
		}
		else if(buf == '+')
		{
			size--;
			in>>buf;
		}
		else if(!isdigit(buf))
		{
			std::cout<<"error in input file!\n";
			return;
		}
		int i = 0;
		while(buf == '0' && !in.eof())
		{
			in>>buf;
			size--;
		}
		if(size)
		{
			Integer = (char*)malloc(size+1);
			while(!in.eof())
			{
				if(!isdigit(buf))
				{
					std::cout<<"error in input string!\n";
					free(Integer);
					size = 0;
					Sign = false;
					Integer = NULL;
					return;
				}
				Integer[i] = buf;
				i++;
				in>>buf;
			}
			Integer[i] = 0;
		}
		in.close();
	}
	else
	{
		std::ifstream in(FName, std::ios::in | std::ios::binary);	
		if(!in.good())
		{
			std::cout<<"Error open file.\n";
			return;
		}
		in.seekg(0, std::ios::end);
		size = in.tellg();
		in.seekg(0, std::ios::beg);
		in>>buf;
		if(buf == '-')
		{
			Sign = true;
			size--;
			in>>buf;
		}
		else if(buf == '+')
		{
			size--;
			in>>buf;
		}
		else if(!isdigit(buf))
		{
			std::cout<<"error in input file!\n";
			return;
		}
		int i = 0;
		while(buf == '0' && !in.eof())
		{
			in>>buf;
			size--;
		}
		if(size)
		{
			Integer = (char*)malloc(size+1);
			while(!in.eof())
			{
				if(!isdigit(buf))
				{
					std::cout<<"error in input string!\n";
					return;
				}
				Integer[i] = buf;
				i++;
				in>>buf;
			}
			Integer[i] = 0;
		}
		in.close();
	}
}

bigInt::bigInt(bigInt *integer)
{
	size = integer->size;
	Sign = integer->Sign;
	Integer = (char*)malloc(size+1);
	memcpy(Integer, integer->Integer, size);
	Integer[size] = 0;
}

void bigInt::Update(char* integer)
{
	free(Integer);
	Integer = NULL;
	Sign = false;
	size = 0;
	int anti_size = 0, i = 0;
	if(!integer || integer[0] == '\0')
		return;
	if(integer[0] == '-')
	{
		Sign = true;
		i++;
	}
	else if(integer[0] == '+')
		i++;
	else if(!isdigit(integer[0]))
	{
		std::cout<<"error in input string!\n";
		return;
	}
	int j = i;
	while(integer[j] == '0')
		j++;
	anti_size += (j - i);
	while(integer[i] != '\0')
	{
		if(!isdigit(integer[i]))
		{
			std::cout<<"error in input string!\n";
			return;
		}
		size++;
		i++;
	}
	size = size - anti_size;
	if(!size)
		return;
	Integer = (char*)malloc(size+1);
	memcpy(Integer, integer+j, size);
	Integer[size] = 0;
}

bigInt* bigInt::BinaryRead(char *FName)
{
	char buf;
	std::ifstream in(FName, std::ios::in | std::ios::binary);
	if(!in.good())
	{
		std::cout<<"Error open file.\n";
		return NULL;
	}
	in.seekg(0, std::ios::end);
	size = in.tellg();
	in.seekg(0, std::ios::beg);
	in>>buf;
	if(buf == '-')
	{
		Sign = true;
		size--;
		in>>buf;
	}
	else if(buf == '+')
	{
		Sign = false;
		size--;
		in>>buf;
	}
	else if(isdigit(buf))
		Sign = false;
	else
	{
		std::cout<<"error in input file!\n";
		return NULL;
	}
	int i = 0;
	while(buf == '0' && !in.eof())
	{
		in>>buf;
		size--;
	}
	free(Integer);
	Integer = (char*)malloc(size+1);
	while(!in.eof())
	{
		if(!isdigit(buf))
		{
			std::cout<<"error in input string!\n";
			free(Integer);
			Integer = NULL;
			return NULL;
		}
		Integer[i] = buf;
		i++;
		in>>buf;
	}
	Integer[i] = 0;
	in.close();
	return this;
}

bigInt* bigInt::TextRead(char *FName)
{
	char buf;
	std::ifstream in(FName, std::ios::in);
	if(!in.good())
	{
		std::cout<<"Error open file.\n";
		return NULL;
	}
	in.seekg(0, std::ios::end);
	size = in.tellg();
	in.seekg(0, std::ios::beg);
	in>>buf;
	if(buf == '-')
	{
		Sign = true;
		size--;
		in>>buf;
	}
	else if(buf == '+')
	{
		Sign = false;
		size--;
		in>>buf;
	}
	else if(isdigit(buf))
		Sign = false;
	else
	{
		std::cout<<"error in input file!\n";
		return NULL;
	}
	int i = 0;
	while(buf == '0' && !in.eof())
	{
		in>>buf;
		size--;
	}
	free(Integer);
	Integer = (char*)malloc(size+1);
	while(!in.eof())
	{
		if(!isdigit(buf))
		{
			std::cout<<"error in input string!\n";
			return NULL;
		}
		Integer[i] = buf;
		i++;
		in>>buf;
	}
	Integer[i] = 0;
	in.close();
	return this;
}

void bigInt::BinaryWrite(char *FName)
{
	std::ofstream out(FName, std::ios::out | std::ios::binary);
	if(!out.good())
	{
		std::cout<<"Error create file.\n";
		return;
	}
	if(Sign)
		if(size)
			out<<'-';
	if(size)
		out.write(Integer, size);
	else
		out.write("0", 1);
	out.close();
}

void bigInt::TextWrite(char *FName)
{
	std::ofstream out(FName, std::ios::out);
	if(!out.good())
	{
		std::cout<<"Error create file.\n";
		return;
	}
	if(Sign)
		if(size)
			out<<'-';
	if(size)
	{
		int i = 0;
		while(i < size)
		{
			out<<Integer[i];
			i++;
		}
	}
	else
		out<<0;
	out.close();
}

bigInt* bigInt::Summary(bigInt* integer)
{
	if(!integer)
		return this;
	if(!integer->size)
		return this;
	if(!size)
		return integer;
	bool new_Sign;
	int great = 0;
	bigInt *new_int;
	char *new_Integer;
	int new_size;
	bool First_Sign = Sign, Second_Sign = integer->Sign;
	Sign = false; integer->Sign = false;
	if(*this > *integer)
	{
		great = 1;
		new_size = size + 2;
		new_Sign = First_Sign;
	}
	else 
	{
		great = 2;
		new_size = integer->size + 2;
		new_Sign = Second_Sign;
	}
	Sign = First_Sign;
	integer->Sign = Second_Sign;
	if(new_Sign)
		new_size++;
	new_Integer = (char*)malloc(new_size+1);
	memset(new_Integer, -51, new_size - 1);
	new_Integer[new_size] = 0;
	if(Sign == integer->Sign)
	{
		if(great == 1)
		{
			int rez, i, j, k, CF=0;
			for(i = integer->size - 1, j = size - 1, k = new_size - 1; i >= 0; i--, j--, k--)
			{
				int A = atoi(Integer[j]);
				int B = atoi(integer->Integer[i]);
				rez = A + B + CF;
				CF = rez / 10;
				new_Integer[k] = itoa(rez%10);
			}
			for(; j >= 0; j--, k--)
			{
				int A = atoi(Integer[j]);
				rez = A + CF;
				CF = rez / 10;
				new_Integer[k] = itoa(rez%10);
			}
			if(CF)
				new_Integer[k--] = '1';
			if(Sign)
				new_Integer[k--] = '-';
			i = 0;
			while(new_Integer[i] == -51)
				i++;
			new_int = new bigInt(new_Integer + i);
			free(new_Integer);
			return new_int;
		}
		else
		{
			int rez, i, j, k, CF = 0;
			for(i = size - 1, j = integer->size - 1, k = new_size - 1; i >= 0; i--, j--, k--)
			{
				int A = atoi(integer->Integer[j]);
				int B = atoi(Integer[i]);
				rez = A + B + CF;
				CF = rez / 10;
				new_Integer[k] = itoa(rez%10);
			}
			for(; j >= 0; j--, k--)
			{
				int A = atoi(integer->Integer[j]);
				rez = A + CF;
				CF = rez / 10;
				new_Integer[k] = itoa(rez%10);
			}
			if(CF)
				new_Integer[k--] = '1';
			if(new_Sign)
				new_Integer[k--] = '-';
			i = 0;
			while(new_Integer[i] == -51)
				i++;
			new_int = new bigInt(new_Integer + i);
			free(new_Integer);
			return new_int;
		}
	}
	if(!Sign)//+(1)-(2) 1 - this
	{
		if(great == 1)
		{
			int rez, i, j, k, CF = 0, CFbuf;
			for(i = integer->size - 1, j = size - 1, k = new_size - 1; i >= 0; i--, j--, k--)
			{
				int A = atoi(Integer[j]);
				int B = atoi(integer->Integer[i]);
				CFbuf = 0;
				if (A < B)
				{
					A += 10;
					CFbuf++;
				}
				rez = A - B;
				if(CF)
				{
					if(!rez)
					{
						rez += 10;
						CFbuf++;
					}
					rez -= CF;
				}
				CF = CFbuf;
				new_Integer[k] = itoa(rez%10);
			}
			for(; j >= 0; j--, k--)
			{
				int A = atoi(Integer[j]);
				CFbuf = 0;
				rez = A;
				if(rez < CF)
				{
					rez += 10;
					CFbuf++;
				}
				rez -= CF;
				CF = CFbuf;
				new_Integer[k] = itoa(rez%10);
			}
			if(CF)
				new_Integer[k--] = '1';
			if(new_Sign)
				new_Integer[k--] = '-';

			i = 0;
			while(new_Integer[i] == -51)
				i++;
			new_int = new bigInt(new_Integer + i);
			free(new_Integer);
			return new_int;
		}
		else
		{
			int rez, CFbuf, i, j, k, CF = 0;
			for(i = size - 1, j = integer->size - 1, k = new_size - 1; i >= 0; i--, j--, k--)
			{
				int A = atoi(integer->Integer[j]);
				int B = atoi(Integer[i]);
				CFbuf = 0;
				if(A < B)
				{
					A += 10;
					CFbuf++;
				}
				rez = A - B;
				if(CF)
				{
					if(!rez)
					{
						rez += 10;
						CFbuf++;
					}
					rez -= CF;
				}
				CF = CFbuf;
				new_Integer[k] = itoa(rez%10);
			}
			for(; j >= 0; j--, k--)
			{
				int A = atoi(integer->Integer[j]);
				CFbuf = 0;
				rez = A;
				if(rez < CF)
				{
					rez +=10;
					CFbuf++;
				}
				rez -= CF;
				CF = CFbuf;
				new_Integer[k] = itoa(rez%10);
			}
			if(CF)
				new_Integer[k--] = '1';
			if(new_Sign)
				new_Integer[k--] = '-';
			i = 0;
			while(new_Integer[i] == -51)
				i++;
			new_int = new bigInt(new_Integer + i);
			free(new_Integer);
			return new_int;
		}
	}
	else//+(2)-(1) 1 - this
	{
		if(great == 2)
		{
			int rez, CFbuf, i, j, k, CF = 0;
			for(i = integer->size - 1, j = size - 1, k = new_size - 1; j >= 0; i--, j--, k--)
			{
				int A = atoi(integer->Integer[i]);
				int B = atoi(Integer[j]);
				CFbuf = 0;
				if(A < B)
				{
					A += 10;
					CFbuf++;
				}
				rez = A - B;
				if(CF)
				{
					if(!rez)
					{
						rez += 10;
						CFbuf++;
					}
					rez -= CF;
				}
				CF = CFbuf;
				new_Integer[k] = itoa(rez%10);
			}
			for(; i >= 0; i--, k--)
			{
				int A = atoi(integer->Integer[i]);
				CFbuf = 0;
				rez = A;
				if(rez < CF)
				{
					rez += 10;
					CFbuf++;
				}
				rez -= CF;
				CF = CFbuf;
				new_Integer[k] = itoa(rez%10);
			}
			if(CF)
				new_Integer[k--] = '1';
			if(new_Sign)
				new_Integer[k--] = '-';

			i = 0;
			while(new_Integer[i] == -51)
				i++;
			new_int = new bigInt(new_Integer + i);
			free(new_Integer);
			return new_int;
		}
		else
		{
			int rez, CFbuf, i, j, k, CF = 0;
			for(i = size - 1, j = integer->size - 1, k = new_size - 1; j >= 0; i--, j--, k--)
			{
				int A = atoi(Integer[i]);
				int B = atoi(integer->Integer[j]);
				CFbuf = 0;
				if(A < B)
				{
					A += 10;
					CFbuf++;
				}
				rez = A - B;
				if(CF)
				{
					if(!rez)
					{
						rez += 10;
						CFbuf++;
					}
					rez -= CF;
				}
				CF = CFbuf;
				new_Integer[k] = itoa(rez%10);
			}
			for(; i >= 0; i--, k--)
			{
				int A = atoi(Integer[i]);
				CFbuf = 0;
				if(A < CF)
				{
					A += 10;
					CFbuf++;
				}
				rez = A - CF;
				CF = CFbuf;
				new_Integer[k] = itoa(rez%10);
			}
			if(CF)
				new_Integer[k--] = '1';
			if(new_Sign)
				new_Integer[k--] = '-';
			i = 0;
			while(new_Integer[i] == -51)
				i++;
			new_int = new bigInt(new_Integer + i);
			free(new_Integer);
			return new_int;
		}
	}
	return NULL;
}

void bigInt::SummaryS(bigInt* integer)
{
	if(!integer)
		return;
	if(!integer->size)
		return;
	if(!size)
	{
		Sign = integer->Sign;
		size = integer->size;
		Update(integer->Integer);
		return;
	}
	bool new_Sign;
	int great = 0;
	char *new_Integer;
	int new_size;
	bool First_Sign = Sign, Second_Sign = integer->Sign;
	Sign = false; integer->Sign = false;
	if(*this > *integer)
	{
		great = 1;
		new_size = size + 2;
		new_Sign = First_Sign;
	}
	else 
	{
		great = 2;
		new_size = integer->size + 2;
		new_Sign = Second_Sign;
	}
	Sign = First_Sign;
	integer->Sign = Second_Sign;
	if(new_Sign)
		new_size++;
	new_Integer = (char*)malloc(new_size+1);
	memset(new_Integer, -51, new_size - 1);
	new_Integer[new_size] = 0;
	if(Sign == integer->Sign)
	{
		if(great == 1)
		{
			int rez, i, j, k, CF = 0;
			for(i = integer->size - 1, j = size - 1, k = new_size - 1; i >= 0; i--, j--, k--)
			{
				int A = atoi(Integer[j]);
				int B = atoi(integer->Integer[i]);
				rez = A + B + CF;
				CF = rez / 10;
				new_Integer[k] = itoa(rez%10);
			}
			for(; j >= 0; j--, k--)
			{
				int A = atoi(Integer[j]);
				rez = A + CF;
				CF = rez / 10;
				new_Integer[k] = itoa(rez%10);
			}
			if(CF)
				new_Integer[k--] = '1';
			if(Sign)
				new_Integer[k--] = '-';
			i = 0;
			while(new_Integer[i] == -51)
				i++;
			Update(new_Integer+i);
			free(new_Integer);
			return;
		}
		else
		{
			int rez, i, j, k, CF = 0;
			for(i = size - 1, j = integer->size - 1, k = new_size - 1; i >= 0; i--, j--, k--)
			{
				int A = atoi(integer->Integer[j]);
				int B = atoi(Integer[i]);
				rez = A + B + CF;
				CF = rez / 10;
				new_Integer[k] = itoa(rez%10);
			}
			for(; j >= 0; j--, k--)
			{
				int A = atoi(integer->Integer[j]);
				rez = A + CF;
				CF = rez / 10;
				new_Integer[k] = itoa(rez%10);
			}
			if(CF)
				new_Integer[k--] = '1';
			if(new_Sign)
				new_Integer[k--] = '-';
			i = 0;
			while(new_Integer[i] == -51)
				i++;
			Update(new_Integer + i);
			free(new_Integer);
			return;
		}
	}
	if(!Sign)//+(1)-(2) 1 - this
	{
		if(great == 1)
		{
			int rez, CFbuf, i, j, k, CF = 0;
			for(i = integer->size - 1, j = size - 1, k = new_size - 1; i >= 0; i--, j--, k--)
			{
				int A = atoi(Integer[j]);
				int B = atoi(integer->Integer[i]);
				CFbuf = 0;
				if (A < B)
				{
					A += 10;
					CFbuf++;
				}
				rez = A - B;
				if(CF)
				{
					if(!rez)
					{
						rez += 10;
						CFbuf++;
					}
					rez -= CF;
				}
				CF = CFbuf;
				new_Integer[k] = itoa(rez%10);
			}
			for(; j >= 0; j--, k--)
			{
				int A = atoi(Integer[j]);
				CFbuf = 0;
				rez = A;
				if(rez < CF)
				{
					rez += 10;
					CFbuf++;
				}
				rez -= CF;
				CF = CFbuf;
				new_Integer[k] = itoa(rez%10);
			}
			if(CF)
				new_Integer[k--] = '1';
			if(new_Sign)
				new_Integer[k--] = '-';

			i = 0;
			while(new_Integer[i] == -51)
				i++;
			Update(new_Integer + i);
			free(new_Integer);
			return;
		}
		else
		{
			int rez, CFbuf, i, j, k, CF = 0;
			for(i = size - 1, j = integer->size - 1, k = new_size - 1; i >= 0; i--, j--, k--)
			{
				int A = atoi(integer->Integer[j]);
				int B = atoi(Integer[i]);
				CFbuf = 0;
				if(A < B)
				{
					A += 10;
					CFbuf++;
				}
				rez = A - B;
				if(CF)
				{
					if(!rez)
					{
						rez += 10;
						CFbuf++;
					}
					rez -= CF;
				}
				CF = CFbuf;
				new_Integer[k] = itoa(rez%10);
			}
			for(; j >= 0; j--, k--)
			{
				int A = atoi(integer->Integer[j]);
				CFbuf = 0;
				rez = A;
				if(rez < CF)
				{
					rez +=10;
					CFbuf++;
				}
				rez -= CF;
				CF = CFbuf;
				new_Integer[k] = itoa(rez%10);
			}
			if(CF)
				new_Integer[k--] = '1';
			if(new_Sign)
				new_Integer[k--] = '-';
			i = 0;
			while(new_Integer[i] == -51)
				i++;
			Update(new_Integer + i);
			free(new_Integer);
			return;
		}
	}
	else//+(2)-(1) 1 - this
	{
		if(great == 2)
		{
			int rez, CFbuf, i, j, k, CF = 0;
			for(i = integer->size - 1, j = size - 1, k = new_size - 1; i >= 0; i--, j--, k--)
			{
				int A = atoi(integer->Integer[i]);
				int B = atoi(Integer[j]);
				CFbuf = 0;
				if(A < B)
				{
					A += 10;
					CFbuf++;
				}
				rez = A - B;
				if(CF)
				{
					if(!rez)
					{
						rez += 10;
						CFbuf++;
					}
					rez -= CF;
				}
				CF = CFbuf;
				new_Integer[k] = itoa(rez%10);
			}
			for(; j >= 0; j--, k--)
			{
				int A = atoi(Integer[j]);
				CFbuf = 0;
				rez = A;
				if(rez < CF)
				{
					rez += 10;
					CFbuf++;
				}
				rez -= CF;
				CF = CFbuf;
				new_Integer[k] = itoa(rez%10);
			}
			if(CF)
				new_Integer[k--] = '1';
			if(new_Sign)
				new_Integer[k--] = '-';

			i = 0;
			while(new_Integer[i] == -51)
				i++;
			Update(new_Integer + i);
			free(new_Integer);
			return;
		}
		else
		{
			int rez, CFbuf, i, j, k, CF = 0;
			for(i = size - 1, j = integer->size - 1, k = new_size - 1; j >= 0; i--, j--, k--)
			{
				int A = atoi(Integer[i]);
				int B = atoi(integer->Integer[j]);
				CFbuf = 0;
				if(A < B)
				{
					A += 10;
					CFbuf++;
				}
				rez = A - B;
				if(CF)
				{
					if(!rez)
					{
						rez += 10;
						CFbuf++;
					}
					rez -= CF;
				}
				CF = CFbuf;
				new_Integer[k] = itoa(rez%10);
			}
			for(; i >= 0; i--, k--)
			{
				int A = atoi(Integer[i]);
				CFbuf = 0;
				if(A < CF)
				{
					A += 10;
					CFbuf++;
				}
				rez = A - CF;
				CF = CFbuf;
				new_Integer[k] = itoa(rez%10);
			}
			if(CF)
				new_Integer[k--] = '1';
			if(new_Sign)
				new_Integer[k--] = '-';
			i = 0;
			while(new_Integer[i] == -51)
				i++;
			Update(new_Integer + i);
			free(new_Integer);
			return;
		}
	}	
}

bigInt* bigInt::Subtraction(bigInt* integer)
{
	if(!integer)
		return NULL;
	integer->Sign = !integer->Sign;
	bigInt* rez = Summary(integer);
	integer->Sign = !integer->Sign;
	return rez;
}

void bigInt::SubtractionS(bigInt* integer)
{
	if(!integer)
		return;
	integer->Sign = !integer->Sign;
	SummaryS(integer);
	integer->Sign = !integer->Sign;
}

bigInt* bigInt::Multiplication(bigInt* integer)
{
	//второго числа нет
	if(!integer)
		return NULL;
	if(!integer->size || !size)
	{
		bigInt *zero = new bigInt(0);
		return zero;
	}
	bool new_Sign;
	bigInt *buf;
	char *new_Integer;
	bigInt *new_int, *cur;
	if (Sign == integer->Sign)
		new_Sign = false;
	else
		new_Sign = true;
	bool First_Sign = Sign, Second_Sign = integer->Sign;
	Sign = false; integer->Sign = false;
	if(*this > *integer)
	{
		buf = new bigInt(integer);
		cur = new bigInt(this);
	}
	else 
	{
		buf = new bigInt(this);
		cur = new bigInt(integer);
	}
	new_int = new bigInt(0);
	//////////////////////////////
	int rez, CF= 0, i, j, k, p, m, cur_size;
	for(i = cur->size - 1, p = 0; i >= 0; i--, p++)
	{
		int A = atoi(cur->Integer[i]);
		if(!A)
			continue;
		j = buf->size - 1;
		cur_size = buf->size + p + 1;
		new_Integer = (char*)malloc(cur_size+1);
		memset(new_Integer, -51, cur_size);
		new_Integer[cur_size] = 0;
		for(k = cur_size-1; j >=0; j--, k--)
		{
			if(A == 1)
			{
				memcpy(new_Integer + (cur_size - buf->size), buf->Integer, buf->size);
				k = cur_size - buf->size + 1;
				break;
			}
			int B = atoi(buf->Integer[j]);
			if(!B)
			{
				new_Integer[k] = itoa(CF);
				CF = 0;
				continue;
			}
			rez = A*B + CF;
			CF = rez / 10;			
			new_Integer[k] = itoa(rez%10);
		}
		if(CF)
			new_Integer[k++] = itoa(CF);
		new_Integer = shiftRight(new_Integer, p);
		m = 0;
		while(new_Integer[m] == -51)
			m++;
		bigInt *cur_int = new bigInt(new_Integer+m);
		new_int->SummaryS(cur_int);
		free(cur_int->Integer);
		free(new_Integer);
		CF = 0;
	}
	/////////////////
	new_int->Sign = new_Sign;
	Sign = First_Sign;
	integer->Sign = Second_Sign;
	free(buf->Integer);
	free(cur->Integer);
	return new_int;
}

void bigInt::MultiplicationS(bigInt* integer)
{
	//второго числа нет
	if(!integer)
		return;
	if(!integer->size)
	{
		Sign = false;
		size = 0;
		free(Integer);
		Integer = NULL;
		return;
	}
	if(!size)
		return;
	bool new_Sign;
	bigInt *buf;
	char *new_Integer;
	bigInt *new_int, *cur;
	if (Sign == integer->Sign)
		new_Sign = false;
	else
		new_Sign = true;
	bool Second_Sign = integer->Sign;
	Sign = false; integer->Sign = false;
	if(*this > *integer)
	{
		buf = new bigInt(integer);
		cur = new bigInt(this);
	}
	else 
	{
		buf = new bigInt(this);
		cur = new bigInt(integer);
	}
	new_int = new bigInt("0");
	//////////////////////////////
	int rez, CF = 0, i, j, k, p, m, cur_size;
	for(i = cur->size - 1, p = 0; i >= 0; i--, p++)
	{
		int A = atoi(cur->Integer[i]);
		if(!A)
			continue;
		
		j = buf->size - 1;
		cur_size = buf->size + p + 1;
		new_Integer = (char*)malloc(cur_size+1);
		memset(new_Integer, -51, cur_size);
		new_Integer[cur_size] = 0;
		for(k = cur_size-1; j >=0; j--, k--)
		{
			if(A == 1)
			{
				memcpy(new_Integer + (cur_size - buf->size), buf->Integer, buf->size);
				k = cur_size - buf->size + 1;
				break;
			}
			int B = atoi(buf->Integer[j]);
			if(!B)
			{
				new_Integer[k] = itoa(CF);
				CF = 0;
				continue;
			}
			rez = A*B + CF;
			CF = rez / 10;			
			new_Integer[k] = itoa(rez%10);
		}
		if(CF)
			new_Integer[k++] = itoa(CF);
		new_Integer = shiftRight(new_Integer, p);
		m = 0;
		while(new_Integer[m] == -51)
			m++;
		bigInt *cur_int = new bigInt(new_Integer+m);
		new_int->SummaryS(cur_int);
		CF = 0;
		free(cur_int);
		free(new_Integer);
	}
	/////////////////
	integer->Sign = Second_Sign;
	Update(new_int->Integer);
	Sign = new_Sign;
	free(buf->Integer);
	free(cur->Integer);
	free(new_int);
	return ;
}

bigInt* bigInt::DegreeToTen(bigInt* integer)
{
	bigInt *new_int = new bigInt(integer);
	new_int->MultiplicationS(new_int);
	new_int->MultiplicationS(new_int);
	new_int->MultiplicationS(integer);
	new_int->MultiplicationS(new_int);
	return new_int;
}

bigInt* bigInt::Degreed(bigInt* integer)
{
	if(!integer)
		return NULL;
	if(!integer->size)
	{
		bigInt *one = new bigInt(1);
		return one;
	}
	if(!size)
	{
		bigInt *zero = new bigInt(0);
		return zero;
	}
	bool new_sign;
	if(atoi(integer->Integer[size-1])%2)
		new_sign = Sign;
	else
		new_sign = true;
	bigInt** degreeNet = new bigInt*[integer->size], *new_int = new bigInt("1"), *buf;
	degreeNet[0] = new bigInt(this);
	for(int i = 1; i < integer->size; i++)
		degreeNet[i] = DegreeToTen(degreeNet[i - 1]);
	for(int i = 0; i < integer->size; i++)
	{	
		if(integer->Integer[i] == '0')
			continue;
		buf = new bigInt(degreeNet[integer->size - 1 - i]);
		for(int j = 1; j < atoi(integer->Integer[i]); j++)
			buf->MultiplicationS(degreeNet[integer->size - 1 - i]);
		new_int->MultiplicationS(buf);
		free(buf);
	}
	free(degreeNet);
	new_int->Sign = new_sign;
	return new_int;
}

void bigInt::DegreedS(bigInt *integer)
{
	if(!size)
		return;
	if(!integer)
		return;
	if(!integer->size)
	{
		Update("1");
		return;
	}
	if(!atoi(integer->Integer[size-1])%2)
		Sign = true;
	bigInt** degreeNet = new bigInt*[integer->size], *new_int = new bigInt("1"), *buf;
	degreeNet[0] = new bigInt(this);
	for(int i = 1; i < integer->size; i++)
		degreeNet[i] = DegreeToTen(degreeNet[i - 1]);
	for(int i = 0; i < integer->size; i++)
	{	
		if(integer->Integer[i] == '0')
			continue;
		buf = new bigInt(degreeNet[integer->size - 1 - i]);
		for(int j = 1; j < atoi(integer->Integer[i]); j++)
			buf->MultiplicationS(degreeNet[integer->size - 1 - i]);
		new_int->MultiplicationS(buf);
		free(buf);
	}
	free(degreeNet);
	this->Update(new_int->Integer);
	free(new_int);
}

bigInt* bigInt::Division(bigInt* integer)
{
	if(!integer)
		return NULL;
	if(!integer->size)
		return NULL;
	if(!size)
	{
		bigInt *zero = new bigInt(0);
		return zero;
	}
	bool new_Sign, end_div = false, good_div, good_devidend;
	bigInt *devidend, *devider, *new_int, *buf = new bigInt("0"), *buf_devider, *req;
	if (Sign == integer->Sign)
		new_Sign = false;
	else
		new_Sign = true;
	bool First_Sign = Sign, Second_Sign = integer->Sign;		
	Sign = false; integer->Sign = false;
	devidend = new bigInt(this);
	devider = integer;
	new_int = new bigInt("0");
	buf_devider = new bigInt(divisionInTwo(devidend->Integer));
	while(!end_div)
	{
		buf = buf_devider->Multiplication(devider);
		if(*devidend >= *buf)
			good_div = true;
		else 
			good_div = false;
		//	
		if(good_div)
		{
			devidend->SubtractionS(buf);
			new_int->SummaryS(buf_devider);
		}
		//
		if(*devidend >= *buf) // true - можем разделить false - не можем
			good_devidend = true;
		else
			good_devidend = false;
		//
		if(!good_devidend)
			buf_devider->Update(divisionInTwo(buf_devider->Integer));	
		//
		if(*devidend < *devider)
			end_div = true;
		else
			end_div = false;
	}
	integer->Sign = Second_Sign;
	Sign = First_Sign;
	new_int->Sign = new_Sign;
	req = new bigInt(devidend);
	free(buf);
	free(buf_devider);
	free(devidend);
	free(req);
	return new_int;
}

void bigInt::DivisionS(bigInt* integer)
{
	if(!integer)
		return;
	if(!integer->size || !size)
		return;
	bool new_Sign, end_div = false, good_div, good_devidend;
	bigInt *devidend, *devider, *new_int, *buf = new bigInt("0"), *buf_devider, *req;
	if (Sign == integer->Sign)
		new_Sign = false;
	else
		new_Sign = true;
	bool First_Sign = Sign, Second_Sign = integer->Sign;		
	Sign = false; integer->Sign = false;
	devidend = new bigInt(this);
	devider = integer;
	new_int = new bigInt("0");
	buf_devider = new bigInt(divisionInTwo(devidend->Integer));
	while(!end_div)
	{
		buf = buf_devider->Multiplication(devider);
		if(*devidend >= *buf)
			good_div = true;
		else
			good_div = false;
		//	
		if(good_div)
		{
			devidend->SubtractionS(buf);
			new_int->SummaryS(buf_devider);
		}
		//
		if(*devidend >= *buf) // true - можем разделить false - не можем
			good_devidend = true;
		else 
			good_devidend = false;
		//
		if(!good_devidend)
			buf_devider->Update(divisionInTwo(buf_devider->Integer));	
		//
		if(*devidend < *devider)
			end_div = true;
		else 
			end_div = false;
	}
	Update(new_int->Integer);
	Sign = new_Sign;
	req = new bigInt(devidend);
	new_int->Sign = new_Sign;
	free(buf);
	free(buf_devider);
	free(devidend);
	free(req);
	free(new_int);
}

bigInt* bigInt::Modulation(bigInt* integer)
{
	if(!integer)
		return NULL;
	if(!integer->size || !size)
	{
		bigInt *zero = new bigInt(0);
		return zero;
	}
	bool new_Sign, end_div = false, good_div, good_devidend;
	bigInt *devidend, *devider, *new_int, *buf = new bigInt("0"), *buf_devider, *req;
	if (Sign == integer->Sign)
		new_Sign = false;
	else
		new_Sign = true;
	bool First_Sign = Sign, Second_Sign = integer->Sign;		
	Sign = false; integer->Sign = false;
	devidend = new bigInt(this);
	devider = integer;
	new_int = new bigInt("0");
	buf_devider = new bigInt(divisionInTwo(devidend->Integer));
	while(!end_div)
	{
		buf = buf_devider->Multiplication(devider);
		if(*devidend >= *buf)
			good_div = true;
		else 
			good_div = false;
		//	
		if(good_div)
		{
			devidend->SubtractionS(buf);
			new_int->SummaryS(buf_devider);
		}
		//
		if(*devidend >= *buf) // true - можем разделить false - не можем
			good_devidend = true;
		else 
			good_devidend = false;
		//
		if(!good_devidend)
			buf_devider->Update(divisionInTwo(buf_devider->Integer));	
		//
		if(*devidend < *devider)
			end_div = true;
		else 
			end_div = false;
	}
	integer->Sign = Second_Sign;
	Sign = First_Sign;
	req = new bigInt(devidend);
	free(buf);
	free(buf_devider);
	free(devidend);
	free(new_int);
	return req;
}

void bigInt::ModulationS(bigInt* integer)
{
	if(!integer)
		return;
	if(!integer->size)
	{
		if(size)
		{
			Sign = false;
			size = 0;
			free(Integer);
			Integer = NULL;
		}
		return;
	}
	if(!size)
		return;
	bool new_Sign, end_div = false, good_div, good_devidend;
	bigInt *devidend, *devider, *new_int, *buf = new bigInt("0"), *buf_devider, *req;

	if (Sign == integer->Sign)
		new_Sign = false;
	else
		new_Sign = true;
	bool First_Sign = Sign, Second_Sign = integer->Sign;		
	Sign = false; integer->Sign = false;
	devidend = new bigInt(this);
	devider = integer;
	new_int = new bigInt("0");
	buf_devider = new bigInt(divisionInTwo(devidend->Integer));
	while(!end_div)
	{
		buf = buf_devider->Multiplication(devider);
		if(*devidend >= *buf)
			good_div = true;
		else
			good_div = false;
		//	
		if(good_div)
		{
			devidend->SubtractionS(buf);
			new_int->SummaryS(buf_devider);
		}
		//
		if(*devidend >= *buf) // true - можем разделить false - не можем
			good_devidend = true;
		else 
			good_devidend = false;
		//
		if(!good_devidend)
			buf_devider->Update(divisionInTwo(buf_devider->Integer));	
		//
		if(*devidend >= *devider)
			end_div = false;
		else 
			end_div = true;
	}
	integer->Sign = Second_Sign;
	Sign = First_Sign;
	req = new bigInt(devidend);
	free(buf);
	free(buf_devider);
	free(devidend);
	Update(req->Integer);
	free(req);
	free(new_int);
}

void bigInt::Clear()
{
	free(Integer);
	Sign = false;
	size = 0;
}

bigInt::~bigInt()
{
	free(Integer);
	Sign = false;
	size = 0;
}
