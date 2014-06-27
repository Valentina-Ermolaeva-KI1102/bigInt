require './BigInt'

print "Enter A:"
int_1 = gets()
a = BigInt::BigInt.new(int_1)
print "Enter B:"
int_2 = gets()
b = BigInt::BigInt.new(int_2)
z = BigInt::BigInt.new(0)
print "NOD(", a.Print, ", ", b.Print, ") = "
while a*b!=z
	if a>b
		a = a % b
	else
		b = b % a
	end
end
if a<b
	print b.Print
else
	print a.Print
end
