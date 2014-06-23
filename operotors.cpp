#include "bigInt.h"

const bigInt& bigInt::operator=(const bigInt& integer)
{
	Update(integer.Integer);
	Sign = integer.Sign;
	size = integer.size;
	return *this;
}

bigInt& bigInt::operator+(const bigInt& integer)
{
	bigInt *rez = new bigInt(this);
	bigInt *buf = new bigInt(integer);
	return *rez->Summary(buf);
}

bigInt& bigInt::operator-(const bigInt& integer)
{
	bigInt *rez = new bigInt(this);
	bigInt *buf = new bigInt(integer);
	return *rez->Subtraction(buf);
}

bigInt& bigInt::operator-()
{
	this->Sign = !this->Sign;
	return *this;
}

bigInt& bigInt::operator++(int)
{
	bigInt one = "1", *Oldvar;
	Oldvar = new bigInt(this);
	this->SummaryS(&one);
	return *Oldvar;
}

bigInt& bigInt::operator++()
{
	bigInt one = "1";
	this->SummaryS(&one);
	return *this;
}

bigInt& bigInt::operator--(int)
{
	bigInt one = "1", *Oldvar;
	Oldvar = new bigInt(this);
	this->SubtractionS(&one);
	return *Oldvar;
}

bigInt& bigInt::operator--()
{
	bigInt one = "1";
	this->SubtractionS(&one);
	return *this;
}

bigInt& bigInt::operator+=(const bigInt& integer)
{
	bigInt *buf = new bigInt(integer);
	this->SummaryS(buf);
	return *this;
}

bigInt& bigInt::operator-=(const bigInt& integer)
{
	bigInt *buf = new bigInt(integer);
	this->SubtractionS(buf);
	return *this;
}

bigInt& bigInt::operator*(const bigInt& integer)
{
	bigInt *rez = new bigInt(this);
	bigInt *buf = new bigInt(integer);
	rez->MultiplicationS(buf);
	return *rez;
}

bigInt& bigInt::operator*=(const bigInt& integer)
{
	bigInt *buf = new bigInt(integer);
	this->MultiplicationS(buf);
	return *this;
}

bigInt& bigInt::operator/(const bigInt& integer)
{
	bigInt *rez = new bigInt(this);
	bigInt *buf = new bigInt(integer);
	rez->DivisionS(buf);
	return *rez;
}

bigInt& bigInt::operator/=(const bigInt& integer)
{
	bigInt *buf = new bigInt(integer);
	this->DivisionS(buf);
	return *this;
}

bigInt& bigInt::operator%(const bigInt& integer)
{
	bigInt *rez = new bigInt(this);
	bigInt *buf = new bigInt(integer);
	rez->ModulationS(buf);
	return *rez;
}

bigInt& bigInt::operator%=(const bigInt& integer)
{
	bigInt *buf = new bigInt(integer);
	this->ModulationS(buf);
	return *this;
}

bigInt& bigInt::operator^(const bigInt& integer)
{
	bigInt *rez = new bigInt(this);
	bigInt *buf = new bigInt(integer);
	rez->DegreedS(buf);
	return *rez;
}

bigInt& bigInt::operator^=(const bigInt& integer)
{
	bigInt *buf = new bigInt(integer);
	this->DegreedS(buf);
	return *this;
}

const bool bigInt::operator==(const bigInt& integer)
{
	if (Sign == integer.Sign) // знак
		if (size == integer.size) // кол-во разрядов
		{
			int i = 0, j = 0;;
			while(true)
			{			
				if(i == size)
					break;
				if(Integer[i] > integer.Integer[j])
					return false;
				else if(Integer[i] < integer.Integer[j])
					return false;
				else
				{
					i++; j++;
				}
			}
			return true;
		}
	return false;
}

const bool bigInt::operator!=(const bigInt& integer)
{
	if (Sign == integer.Sign) // знак
		if (size == integer.size) // кол-во разрядов
		{
			int i = 0, j = 0;;
			while(true)
			{			
				if(i == size)
					break;
				if(Integer[i] > integer.Integer[j])
					return true;
				else if(Integer[i] < integer.Integer[j])
					return true;
				else
				{
					i++; j++;
				}
			}
			return false;
		}
	return true;
}

const bool bigInt::operator<(const bigInt& integer) //-149 <-127 но не работает...
{
	if(Sign == true && integer.Sign == false)
		return true;
	if(Sign != integer.Sign)
		return false;
	if(size > integer.size) // кол-во разрядов
		return Sign;
	if(size < integer.size)
		return !Sign;
	int i = 0, j = 0;;
	while(true)
	{			
		if(i == size)
			break;
		if(Integer[i] > integer.Integer[j])
			return Sign;
		else if(Integer[i] < integer.Integer[j])
			return !Sign;
		else
		{
			i++; j++;
		}
	}
	return false;
}
		
const bool bigInt::operator>(const bigInt& integer)
{
	if(Sign == false && integer.Sign == true)
		return true;
	if(Sign != integer.Sign)
		return false;
	if(size > integer.size) // кол-во разрядов
		return !Sign;
	if(size < integer.size)
		return Sign;
	int i = 0, j = 0;;
	while(true)
	{			
		if(i == size)
			break;
		if(Integer[i] > integer.Integer[j])
			return !Sign;
		else if(Integer[i] < integer.Integer[j])
			return Sign;
		else
		{
			i++; j++;
		}
	}
	return false;
}

const bool bigInt::operator<=(const bigInt& integer)
{
	if(Sign == true && integer.Sign == false)
		return true;
	if(Sign != integer.Sign)
		return false;
	if(size > integer.size) // кол-во разрядов
		return Sign;
	if(size < integer.size)
		return !Sign;
	int i = 0, j = 0;;
	while(true)
	{			
		if(i == size)
			break;
		if(Integer[i] > integer.Integer[j])
			return Sign;
		else if(Integer[i] < integer.Integer[j])
			return !Sign;
		else
		{
			i++; j++;
		}
	}
	return true;
}

const bool bigInt::operator>=(const bigInt& integer)
{
	if(Sign == false && integer.Sign == true)
		return true;
	if(Sign != integer.Sign)
		return false;
	if(size > integer.size) // кол-во разрядов
		return !Sign;
	if(size < integer.size)
		return Sign;
	int i = 0, j = 0;;
	while(true)
	{			
		if(i == size)
			break;
		if(Integer[i] > integer.Integer[j])
			return !Sign;
		else if(Integer[i] < integer.Integer[j])
			return Sign;
		else
		{
			i++; j++;
		}
	}
	return true;
}

std::istream &operator>>(std::istream &in, bigInt &integer)
{
	char buf, *buffer;
	integer.size = 0;
	in.get(buf);
	if(buf == '-')
	{
		integer.Sign = true;
		in.get(buf);
	}
	else if(buf == '+')
	{
		integer.Sign = false;
		in.get(buf);
	}
	else if(isdigit(buf))
		integer.Sign = false;
	else
	{
		std::cout<<"error input stream!\n";
		return in;
	}
	int i = 0;
	while(buf == '0' && isdigit(buf))
	{
		in.get(buf);
	}
	integer.Integer = (char*)malloc(0);
	while(!in.eof() && isdigit(buf))
	{
		integer.size++;
		buffer = (char*)malloc(integer.size+1);
		memcpy(buffer, integer.Integer, integer.size-1);
		buffer[i] = buf;
		free(integer.Integer);
		integer.Integer = (char*)malloc(integer.size+1);
		memcpy(integer.Integer, buffer, integer.size);
		free(buffer);
		i++;
		in.get(buf);
	}
	integer.Integer[i] = 0;
	return in;
}

std::ostream &operator<<(std::ostream &out, bigInt &integer)
{
	if(!&integer)
		return out;
	if(!integer.Integer || !integer.size)
	{
		out<<'0';
		return out;
	}
	if(integer.Sign)
		out<<'-';
	for(int i = 0; i < integer.size; i++)
		out<<integer.Integer[i];
	return out;
}
