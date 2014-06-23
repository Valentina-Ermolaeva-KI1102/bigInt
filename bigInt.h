#include <fstream>
#include <iostream>
#include <malloc.h>


class bigInt
{
	char* Integer;
	bool Sign; //false - '+'; true - '-'
	int size;
	void Update(char *integer);
public:
	bigInt();
	bigInt(char *FName, bool Binary);
	bigInt(int integer);
	bigInt(char *integer);
	bigInt(bigInt *integer);
	bigInt* BinaryRead(char *FName);
	bigInt* TextRead(char *FName);
	void BinaryWrite(char *FName);
	void TextWrite(char *FName);
	friend void BinaryWrite(bigInt *integer, char *FName);
	friend void TextWrite(bigInt *integer, char *FName);
	//
	bigInt* Rezult(char* intager);
	bigInt* Summary(bigInt* integer);
	bigInt* Subtraction(bigInt* integer);
	bigInt* Multiplication(bigInt* integer);
	bigInt* Degreed(bigInt* integer);
	bigInt* Division(bigInt* integer);
	bigInt* Modulation(bigInt* integer);
	bigInt* DegreeToTen(bigInt* integer);
	void SummaryS(bigInt* integer);
	void SubtractionS(bigInt* integer);
	void MultiplicationS(bigInt* integer);
	void DegreedS(bigInt *integer);
	void DivisionS(bigInt* integer);
	void ModulationS(bigInt* integer);
	void Clear();

	//унарный =
	const bigInt & operator=(const bigInt& integer);	
	//бинарный +
	bigInt& operator+(const bigInt& integer);	
	//унарный -
	bigInt& operator-();
	//бинарный -
	bigInt& operator-(const bigInt& integer);
	//префиксна инкремент
	bigInt& operator++(); // косяк SumS
	// потфиксная
	bigInt& operator++(int);
	//префиксна декремент
	bigInt& operator--();
	// потфиксная
	bigInt& operator--(int);
	//бинарный +=
	bigInt& operator+=(const bigInt& integer);
	//бинарный -=
	bigInt& operator-=(const bigInt& integer);
	//бинарный *
	bigInt& operator*(const bigInt& integer);
	//бинарный *=
	bigInt& operator*=(const bigInt& integer);
	//бинарный /
	bigInt& operator/(const bigInt& integer);
	//бинарный /=
	bigInt& operator/=(const bigInt& integer);
	//бинарный %
	bigInt& operator%(const bigInt& integer);
	//бинарный %=
	bigInt& operator%=(const bigInt& integer);
	//бинарный ^
	 bigInt& operator^(const bigInt& integer);
	//бинарный ^=
	bigInt& operator^=(const bigInt& integer);
	//бинарный ==
	const bool operator==(const bigInt& integer);
	//бинарный !=
	const bool operator!=(const bigInt& integer);
	//бинарный <
	const bool operator<(const bigInt& integer);
	//бинарный >
	const bool operator>(const bigInt& integer);
	//бинарный <=
	const bool operator<=(const bigInt& integer);
	//бинарный >=
	const bool operator>=(const bigInt& integer);

	friend std::istream &operator>>(std::istream& in, bigInt& integer);

	friend std::ostream &operator<<(std::ostream& out, bigInt& integer);

	~bigInt();
};

void BinaryWrite(bigInt *integer, char *FName);
void TextWrite(bigInt *integer, char *FName);
int atoi(char ch);
char itoa(int i);
char* shiftRight(char *integer, int p);
char* divisionInTwo(char *integer);
