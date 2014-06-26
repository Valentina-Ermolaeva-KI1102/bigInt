require './BigInt'
module Func
	def self.noArguments
		puts "Launched without parameters."
		puts "Perform all kind of operations with entered numbers."
		print "Enter A:"
		int_1 = gets()
		a = BigInt::BigInt.new(int_1)
		print "Enter B:"
		int_2 = gets()
		b = BigInt::BigInt.new(int_2)
		print "A + B = ", a.Print, " + ", b.Print, " = ", (a+b).Print,  "\n"
		print "A - B = ", a.Print, " - ", b.Print, " = ", (a-b).Print, "\n"
		print "A * B = ", a.Print, " * ", b.Print, " = ", (a*b).Print, "\n"

		if b != BigInt::BigInt.new(0)
			print "A / B = ", a.Print, " / ", b.Print, " = ", (a/b).Print, "\n"
			print "A % B = ", a.Print, " % ", b.Print, " = ", (a%b).Print, "\n"
		else
			puts "Division by zero"
		end
		print "A ^ B = ", a.Print, " ^ ", b.Print,  " = ", (a^b).Print, "\n"
		puts "That's all"

	end
	def self.getArguments
		fileA = ARGV[0]
		fileB = ARGV[2]
		operation = ARGV[1]
		fileRes = ARGV[3]
		binary = false
		fileMod = " "
		if ARGV.length > 4
			if ARGV[4] === "-b"
				binary = true
				if ARGV.length > 5
					fileMod = ARGV[5]
				end
			else
				fileMod = ARGV[4]
			end
		end
		arguments = [fileA, operation, fileB, fileRes, binary, fileMod]
		return arguments
	end
	 
	def self.getFromFiles (fileA, fileB, binary, fileMod)
		if binary == "true"
			a = BigInt::BigInt.new(fileA, true)
			b = BigInt::BigInt.new(fileB, true)
			if not fileMod === " "
				modulus = BigInt::BigInt.new(fileMod, true)
			end
		else
			a = BigInt::BigInt.new(fileA, false)
			b = BigInt::BigInt.new(fileB, false)
			if not fileMod === " "
				modulus = BigInt::BigInt.new(fileMod, false)
			end
		end
		return a, b, modulus
	end

	def self.process(a, b, modulus, operation)
		zero = BigInt::BigInt.new(0)
		res = zero
		if (modulus < zero)
			print "Negative modulus!"
			return false, res
		end
		if (modulus > zero)
			a %= modulus
			b %= modulus
		end
		if operation == '+'
			res = a + b
		elsif operation == '-'
			res = a - b
		elsif operation == '*'
			res = a * b
		elsif operation == '/'
			if b == zero
				print "Division by zero"
				return false, res
			end
			res = a / b
		elsif operation == '%'
			if (b == zero)
				print "Division by zero"
				return false, res
			end
			res = a % b
		elsif operation == '^'
			res = a ^ b
		end		
		if modulus > zero
			res = res % modulus
		end
		return true, res
	end

	def self.saveRes(fileRes, binary, res)
		if binary
			res.BinaryWrite(fileRes)
		else
			res.TextWrite(fileRes)
		end
	end
end
