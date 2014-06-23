#include "bigInt.h"

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "rus");
	if(argc < 4)
	{
		std::cout<<"Слишком мало параметров.";
		return 1;
	}
	int indexOfModuleFile;
	bool binary = false, modyle = false;
	if(argc > 5)
	{	
		if(!strcmp(argv[5], "-b"))
		{
			binary = true;
			if(argc > 6)
			{
				modyle = true;
				indexOfModuleFile = 6;
			}
		}
		else
		{
			modyle = true;
			indexOfModuleFile = 5;
		}
	}
	bigInt int_1(argv[1], binary);
	bigInt int_2(argv[3], binary);
	bigInt int_3, int_4;
	if(modyle)
	{
		if(binary)
			int_3.BinaryRead(argv[indexOfModuleFile]);
		else 
			int_3.TextRead(argv[indexOfModuleFile]);
	}
	switch(argv[2][0])
	{
	case '+':
		int_4 = int_1 + int_2;
		break;
	case '-':
		int_4 = int_1 - int_2;
		break;
	case '/':
		int_4 = int_1 / int_2;
		break;
	case '*':
		int_4 = int_1 * int_2;
		break;
	case '^':
		int_4 = int_1 ^ int_2;
		break;
	case '%':
		int_4 = int_1 % int_2;
		break;
	}
	if(modyle)
		int_4 %= int_3;
	if(binary)
		int_4.BinaryWrite(argv[4]);
	else
		int_4.TextWrite(argv[4]);
	return 0;
}



/*int main(int argc, char** argv)
{
	setlocale(LC_ALL, "rus");
	bigInt int_1("in.txt", true);
	bigInt int_2("in2.txt", false);
	/*bigInt newint("");
	bigInt newint2(newint);
	std::cin>>newint>>newint2;
	std::cout<<newint*newint2;
	bigInt int_3, int_4, int_5, int_6, int_7;
	int_3 = int_1; int_6 = int_2;
	int_4 =	int_1 + int_2;
	int_6 += int_1; int_7 = int_2;
	int_5 = int_1 - int_2;
	int_7 -= int_1; int_6 = int_2;
	int_3 = int_1 * int_2;
	int_6 *= int_1; int_7 = int_2;
	int_4 = int_1 / int_2;
	int_7 /= int_1; int_6 = int_2;
	int_5 = int_1 % int_2;
	int_6 %= int_1; int_7 = int_2;
	int_3 = int_1.Degreed(&int_2);
	int_7 ^= int_1;
	int_5 = int_4++;
	int_3 = ++int_5;
	int_6 = int_4--;
	int_5 = --int_4;
	-int_5;
	bool q, g, l, gq, lq;
	q = int_1 == int_2;
	g = int_1 > int_2;
	l = int_1 < int_2;
	gq = int_1 >= int_2;
	lq = int_1 <= int_2;*/
	bigInt k(1000);
	bigInt j(-15);
	bigInt l(0);
	std::cout<<"\n"<<j*k<<" "<<j*l<<" "<<k+l+j<<std::endl;
	TextWrite(&(int_1*int_2), "out.txt");
	//system("pause");
	return 0;
}*/
