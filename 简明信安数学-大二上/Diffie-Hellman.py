import numpy

print("请输入素数p：")
p = int(input())
print("请输入p的一个原根a：")
a = int(input())

user_a = numpy.random.randint(1, p)
user_b = numpy.random.randint(1, p)

pub = [(a ** user_a) % p, (a ** user_b) % p]

a_key = (pub[1] ** user_a) % p
b_key = (pub[0] ** user_b) % p

print("A的密钥为：" + str(a_key))
print("B的密钥为：" + str(b_key))

if a_key == b_key:
    print("A、B密钥相同")
