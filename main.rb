# coding: utf-8
require './BigInt'
require './Func.rb'

if ARGV.length < 4
	Func.noArguments
	exit -1
end
arguments = Func.getArguments
a, b, modulus = Func.getFromFiles(arguments[0], arguments[2], arguments[4], arguments[5])
isProcess, res = Func.process(a, b, modulus, arguments[1])
puts isProcess
if not isProcess
	exit -1
end
print "A = ", a.Print, "\n"
print "B = ", b.Print, "\n"
if not arguments === " "
	print "M = ", modulus.Print, "\n"
end
print "R = ", res.Print, "\n"
Func.saveRes(arguments[3],  arguments[4], res)
