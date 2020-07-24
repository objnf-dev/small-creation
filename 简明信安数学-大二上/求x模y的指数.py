import sys

def main():
	num1 = int(sys.argv[1])
	num2 = int(sys.argv[2])
	e = 1
	tmp = num2
	while(True):
		if tmp % num1 == 1:
			break
		else:
			e += 1
			tmp *= num2
	print("e=" + str(e))


if __name__ == '__main__':
	main()
