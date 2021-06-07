import sys,getopt

#常量定义部分
# 6bit, 8bit, 9bit, 10bit, 12bit, 14bit, 16bit
bitDict = {"6":0, "8":1, "9":2, "10":3, "12":4, "14":5, "16":6}
yLowLimit = [4, 16, 32, 64, 256, 1024, 4096]
yRange = [55, 219, 438, 876, 3504, 14016, 56064]
bitRange = [63, 255, 511, 1023, 4095, 16383, 65535]
uvCenter = [32, 128, 256, 512, 2048, 8192, 32768]
uvRange = [56, 224, 448, 896, 3584, 14336, 57344]


# 函数定义部分
def usage():
    print("""
    颜色空间转换。
    支持的格式：
        YUV，特指 YCrCb (6位/8位/9位/10位/12位/14位/16位 TV Range, Full Range, Origin 相互之间的转换。
    参数注释：
        -h (--help) 显示此帮助
        -i (--input) 输入色彩空间和位数
            可用色彩空间： YUV_tv，YUV_full，YUV_origin
            可用位数： 6, 8, 9, 10, 12, 14, 16
        -d (--data) 输入数据
            格式： YUV: (y,u,v)
        -o (--output) 输出色彩空间和位数

        例： convert.py -i ('YUV_full',8) -d (132,44,233) -o ('YUV_tv',8)
    """)
    return


def bitconv(inbit, outbit, data):
    if inbit == outbit:
        outdata = data
    elif inbit < outbit:
        outdata = [i*(2**(outbit-inbit)) for i in data]
        print(tuple(outdata))
    elif inbit > outbit:
        outdata = [round(i/(2**(inbit-outbit))) for i in data]
    else:
        outdata = []
    return outdata


def tv2origin(inbit, data):
    outdata = []
    inbitkey = str(inbit)
    outdata.append((data[0] - yLowLimit[bitDict[inbitkey]]) / yRange[bitDict[inbitkey]])
    outdata.append((data[1] - uvCenter[bitDict[inbitkey]]) / uvRange[bitDict[inbitkey]])
    outdata.append((data[2] - uvCenter[bitDict[inbitkey]]) / uvRange[bitDict[inbitkey]])
    return outdata


def origin2tv(outbit, data):
    outdata = []
    outbitkey = str(outbit)
    outdata.append(round((data[0] * yRange[bitDict[outbitkey]]) + yLowLimit[bitDict[outbitkey]]))
    outdata.append(round((data[1] * uvRange[bitDict[outbitkey]]) + uvCenter[bitDict[outbitkey]]))
    outdata.append(round((data[2] * uvRange[bitDict[outbitkey]]) + uvCenter[bitDict[outbitkey]]))
    return outdata


def pc2origin(inbit, data):
    outdata = []
    outbitkey = str(inbit)
    outdata.append(data[0] / bitRange[bitDict[outbitkey]])
    outdata.append((data[1] - uvCenter[bitDict[outbitkey]]) / bitRange[bitDict[outbitkey]])
    outdata.append((data[2] - uvCenter[bitDict[outbitkey]]) / bitRange[bitDict[outbitkey]])
    return outdata


def origin2pc(outbit, data):
    outdata = []
    outbitkey = str(outbit)
    outdata.append(round(data[0] * bitRange[bitDict[outbitkey]]))
    outdata.append(round(data[1] * bitRange[bitDict[outbitkey]] + uvCenter[bitDict[outbitkey]]))
    outdata.append(round(data[2] * bitRange[bitDict[outbitkey]] + uvCenter[bitDict[outbitkey]]))
    return outdata


def tv2pc(inbit, outbit, data):
    outdata = origin2pc(outbit, tv2origin(inbit, data))
    return outdata


def pc2tv(inbit, outbit, data):
    outdata = origin2tv(outbit, pc2origin(inbit, data))
    return outdata


def tv2tv(inbit, outbit, data):
	outdata = origin2tv(outbit, tv2origin(inbit, data))
	return outdata

# 读参部分
opts, _ = getopt.getopt(sys.argv[1:], "-h-i:-d:-o:", ["help", "input=", "data=", "output="])
# 脚本执行
colorSpace = ["", ""]
colorBit = [0, 0]
inData = []

if len(sys.argv) == 1:
    usage()
    sys.exit()

for optName, optVal in opts:
    if optName in ("-h", "--help"):
        usage()
        sys.exit()
    elif optName in ("-i", "--input="):
        temp = list(eval(optVal))
        colorSpace[0] = temp[0]
        colorBit[0] = int(temp[1])
    elif optName in ("-o", "--output="):
        temp = list(eval(optVal))
        colorSpace[1] = temp[0]
        colorBit[1] = int(temp[1])
    elif optName in ("-d", "--data="):
        inData = list(eval(optVal))

if (colorSpace[0] == "YUV_tv") and (colorSpace[1] == "YUV_tv"):
    res = bitconv(colorBit[0], colorBit[1], inData)
elif (colorSpace[0] == "YUV_tv") and (colorSpace[1] == "YUV_origin"):
    res = tv2origin(colorBit[0], inData)
elif (colorSpace[0] == "YUV_origin") and (colorSpace[1] == "YUV_tv"):
    res = origin2tv(colorBit[1], inData)
elif (colorSpace[0] == "YUV_origin") and (colorSpace[1] == "YUV_origin"):
    res = inData
elif (colorSpace[0] == "YUV_full") and (colorSpace[1] == "YUV_origin"):
    res = pc2origin(colorBit[0], inData)
elif (colorSpace[0] == "YUV_origin") and (colorSpace[1] == "YUV_full"):
    res = origin2pc(colorBit[1], inData)
elif (colorSpace[0] == "YUV_full") and (colorSpace[1] == "YUV_full"):
    res = tv2tv(colorBit[0], colorBit[1], inData)
elif (colorSpace[0] == "YUV_tv") and (colorSpace[1] == "YUV_full"):
    res = tv2pc(colorBit[0], colorBit[1], inData)
elif (colorSpace[0] == "YUV_full") and (colorSpace[1] == "YUV_tv"):
    res = pc2tv(colorBit[0], colorBit[1], inData)
else:
    res = []

print(tuple(res))
