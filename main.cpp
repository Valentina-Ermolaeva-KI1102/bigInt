#include "bigInt.h"

void getFromFiles(char* file_1, char* file_2, bool modyle, bool binary, char* file_3, bigInt &A, bigInt &B, bigInt &C);
bool process(bigInt A, bigInt B, bigInt C, char operation, bool modele, bigInt& res);
void saveRes(char* file_4, bool binary, bigInt res);
void print_help();
void no_arguments();

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "rus");
	if(argc == 1)
		no_arguments();
	if(argc == 2)
	{
		if(!strcmp(argv[1], "--h"))
			print_help();
		return 0;
	}
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
	char *file_1 = argv[1], *file_2 = argv[3], *file_3 = argv[indexOfModuleFile], *file_4 = argv[4], operation = argv[2][0];
	bigInt A, B, C, res;
	getFromFiles(file_1, file_2, modyle, binary, file_3, A, B, C);
	if(!process(A, B, C, operation, modyle, res))
		return 1;
	saveRes(file_4, binary, res);
	return 0;
}

void getFromFiles(char* file_1, char* file_2, bool modyle, bool binary, char* file_3, bigInt &A, bigInt &B, bigInt &C)
{
	try
	{
		if(binary)
		{
			A.BinaryRead(file_1);
			B.BinaryRead(file_2);
			if(modyle)
				C.BinaryRead(file_3);
		}
		else
		{
			A.TextRead(file_1);
			B.TextRead(file_2);
			if (modyle)
				C.TextRead(file_3);
		}
	}
	catch (std::invalid_argument const & e)
	{
		std::cout<<e.what();
	}
}

bool process(bigInt A, bigInt B, bigInt C, char operation, bool modele, bigInt& res)
{
	if(modele)
	{
		switch (operation)
		{
			case '+':
			A %= C;
			B %= C;
			res = A + B;
			res %= C;
			return true;
		case '-':
			A %= C;
			B %= C;
			res = A - B;
			res %= C;
			return true;
		case 'x':
			A %= C;
			B %= C;
			res = A * B;
			res %= C;
			return true;
		case '/':
			res = A / B;
			res %= C;
			return true;
		case '%':
			res = A % B;
			res %= C;
			return true;
		case '^':
			A %= C;
			B %= C;
			res = A ^ B;
			res %= C;
			return true;
		default:
			return false;
		}
	}
	else
	{
		switch (operation)
		{
		case '+':
			res = A + B;
			return true;
		case '-':
			res = A - B;
			return true;
		case 'x':
			res = A * B;
			return true;
		case '/':
			res = A / B;
			return true;
		case '%':
			res = A % B;
			return true;
		case '^':
			res = A ^ B;
			return true;
		default:
			return false;
		}
	}
}

void saveRes(char* file_4, bool binary, bigInt res)
{
	try
	{
		if(binary)
			res.BinaryWrite(file_4);
		else
			res.TextWrite(file_4);
	}
	catch(std::invalid_argument const & e)
	{
		std::cout<<e.what();
	}
}

void print_help()
{
	std::cout<<"Usage: "<<std::endl;
	std::cout<<"kr4 <A filelame> <operation> <B filelame> <result filename> [-b] [<module filename>]"<<std::endl<<std::endl;
	std::cout<<"Parameters:"<<std::endl;
	std::cout<<"  operations:"<<std::endl;
	std::cout<<"    \"+\" - addition"<<std::endl;
	std::cout<<"    \"-\" - subtraction"<<std::endl;
	std::cout<<"    \"x\" - multiplication"<<std::endl;
	std::cout<<"    \"/\" - division" <<std::endl;
	std::cout<<"    \"%\" - taking the remainder"<<std::endl;
	std::cout<<"    \"^\" - involution (pow)"<<std::endl;
	std::cout<<"  -b for operations with binary files"<<std::endl;
}

void no_arguments()
{
	std::cout<<"Launched without parameters."<<std::endl;
	std::cout<<"Perform all kind of operations with entered numbers."<<std::endl;
	bigInt a, b, c;
	std::cout<<"Enter A: ";
	std::cin>>a;
	std::cout<<"Enter B: ";
	std::cin>>b;
	char op;
	std::cout<<"Enter operation: ";
	std::cin>>op;
	if(op == '$')
	{
		std::getchar();
		std::cout<<"Enter module: ";
		std::cin>>c;
	}
	switch(op)
	{
	case '+':
		std::cout<<"A + B = "<<a<< " + "<<b<<" = "<<(a + b)<<std::endl;
		break;
	case '-':
		std::cout<<"A - B = "<<a<<" - "<<b<<" = "<<(a - b)<<std::endl;
		break;
	case 'x':
		std::cout<<"A x B = "<<a<<" x "<<b<<" = "<<(a * b)<<std::endl;
		break;
	case '/':
		std::cout<<"A / B = "<<a<<" / "<<b<<" = "<<(a / b)<<std::endl;
		break;
	case '%':
		std::cout<<"A % B = "<<a<<" % "<<b<<" = "<<(a % b)<<std::endl;
		break;
	case '^':
		std::cout<<"A ^ B = "<<a<<" ^ "<<b<<" = "<<(a ^ b)<<std::endl;
		break;
	case '$':
		std::cout<<"A ^ B mod C = "<<a<<" ^ "<<b<<" mod "<<c<<" = "<<(((a % c) ^ (b % c)) % c)<<std::endl;
		break;
	}
}
