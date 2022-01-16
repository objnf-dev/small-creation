import sys, getopt, random


def usage():
    print("""
    RemoveGrain 不同模式下的数据处理。
    
    参数说明：
        --help 显示此帮助信息。
        --mode=-1 (0/1/2/3/4/11/19/20) 计算模式。
        --data=[3*3 list] 输入数据，为3x3列表。
        
    命令示例：
        main.py --help
        main.py --mode=2 --data=[[3,4,5],[4,5,6],[5,6,7]]
    
    """)
    sys.exit()


def sum33(indata, center=True):
    totalnum = 0
    for i in range(3):
        for j in range(3):
            totalnum += indata[i][j]
    if center is False:
        totalnum -= indata[1][1]
    return totalnum


def get_median33(indata):
    tmplist = []
    for i in range(3):
        for j in range(3):
            tmplist.append(indata[i][j])
    tmplist.sort()
    return tmplist[4]


def get_list33(indata):
    tmplist = []
    for i in range(3):
        for j in range(3):
            if i==1 and j==1:
                continue
            else:
                tmplist.append(indata[i][j])
    tmplist.sort()
    return tmplist


def printres(indata):
    for i in range(3):
        for j in range(3):
            print(str(indata[i][j]) + " ", end='')
        print()
    sys.exit()


mode = 0
randata = [[random.randint(0, 9) for i in range(3)] for j in range(3)]
data = [[]]

opts, _ = getopt.getopt(sys.argv[1:], "", ["help", "mode=", "data="])

if len(sys.argv) == 1:
    usage()
    sys.exit()

for optname, optval in opts:
    if optname in ("--help"):
        usage()
    elif optname in ("--mode="):
        mode = int(optval)
    elif optname in ("--data="):
        data = eval(optval)

print("Mode: " + str(mode))
print("Result: ")

if mode == -1:
    printres(randata)
elif mode == 0:
    printres(data)
elif mode == 20:
    data[1][1] = int(round(sum33(data, True) / 9.0))
    printres(data)
elif mode == 19:
    data[1][1] = int(round(sum33(data, False) / 8.0))
    printres(data)
elif mode == 11:
    weight1 = data[0][0] + data[0][2] + data[2][0] + data[2][2]
    weight2 = (data[0][1] + data[1][0] + data[1][2] + data[2][1]) * 2
    weight4 = data[1][1] * 4
    data[1][1] = (weight1 + weight2 + weight4) / (16 * 9)
    printres(data)
elif mode == 1:
    mid = get_median33(data)
    listsort = get_list33(data)
    if data[1][1] < mid and data[1][1] < listsort[0]:
        data[1][1] = listsort[0]
    elif data[1][1] >= mid and data[1][1] > listsort[7]:
        data[1][1] = listsort[7]
    printres(data)
elif mode == 2:
    mid = get_median33(data)
    listsort = get_list33(data)
    if data[1][1] < mid and data[1][1] < listsort[1]:
        data[1][1] = listsort[1]
    elif data[1][1] >= mid and data[1][1] > listsort[6]:
        data[1][1] = listsort[6]
    printres(data)
elif mode == 3:
    mid = get_median33(data)
    listsort = get_list33(data)
    if data[1][1] < mid and data[1][1] < listsort[2]:
        data[1][1] = listsort[2]
    elif data[1][1] >= mid and data[1][1] > listsort[5]:
        data[1][1] = listsort[5]
    printres(data)
elif mode == 4:
    mid = get_median33(data)
    listsort = get_list33(data)
    if data[1][1] < mid and data[1][1] < listsort[3]:
        data[1][1] = listsort[3]
    elif data[1][1] >= mid and data[1][1] > listsort[4]:
        data[1][1] = listsort[4]
    printres(data)
else:
    print("Mode值输入错误。")
    sys.exit()
