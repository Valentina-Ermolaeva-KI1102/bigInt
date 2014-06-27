%module BigInt
%{
#include "bigInt.h"
%}
%rename(_let) BigInt::operator =(const BigInt& integer);
%rename(_prefinc) BigInt::operator ++();
%rename(_postinc) BigInt::operator ++(int);
%rename(_prefdec) BigInt::operator --();
%rename(_postdec) BigInt::operator --(int);
%rename(_ladd) BigInt::operator +=(const BigInt& integer);
%rename(_lsub) BigInt::operator -=(const BigInt& integer);
%rename(_lmul) BigInt::operator *=(const BigInt& integer);
%rename(_ldiv) BigInt::operator /=(const BigInt& integer);
%rename(_lmod) BigInt::operator %=(const BigInt& integer);
%rename(_lmmul) BigInt::operator ^=(const BigInt& integer);
%rename(_ne) BigInt::operator !=(const BigInt& integer);

%include "bigInt.h" 
