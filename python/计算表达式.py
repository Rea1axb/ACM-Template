#多组输入，读取到文件末尾EOF结束
while True:
	try:
		line = input()
	except EOFError:
		break
	len = line.length()
	
	z = eval(line) #将line转化为表达式类型并运算
	print(z)