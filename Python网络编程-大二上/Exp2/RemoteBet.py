#!/usr/bin/python3
# 导入相关包
import socket
import json
import sys

# 骰子的样式
dice_tpl = '''\
        ┌──────┐,┌──────┐,┌──────┐,┌──────┐,┌──────┐,┌──────┐
        │      │,│  ●  │,│●    │,│●  ●│,│●  ●│,│●  ●│
        │  ●  │,│      │,│  ●  │,│      │,│  ●  │,│●  ●│
        │      │,│  ●  │,│    ●│,│●  ●│,│●  ●│,│●  ●│
        └──────┘,└──────┘,└──────┘,└──────┘,└──────┘,└──────┘
        '''
dice_lines = dice_tpl.split('\n')
for i in range(5):
    dice_lines[i] = dice_lines[i].split(',')
dice = ['', '', '', '', '', '']
for i in range(6):
    for j in range(5):
        dice[i] += (dice_lines[j][i] + '\n')

# 服务器IP和端口
if len(sys.argv) < 3:
    print("参数不正确")
    sys.exit(0)
ip = sys.argv[1]
port = sys.argv[2]

# 建立连接
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((ip, int(port)))
print("[*] Connected to server " + ip + ":" + port)

# 初始化游戏
print("庄家唱道：新开盘！预叫头彩！")
print("庄家将两枚玉骰往银盘中一撒。")
# 发送初始化请求
req = {
    "op": "init"
}
req_s = json.dumps(req)
sock.send(req_s.encode("utf-8"))
# 接收数据
data = sock.recv(4096)
if not data:
    print("EOF")
    sys.exit(0)
res = json.loads(data)
# 展示头彩骰号
print(dice[res["numA"]])
print(dice[res["numB"]])
print("庄家唱道：头彩骰号是" + str(res["numA"] + 1) + "、" + str(res["numB"] + 1) + "。")
del req, req_s, data, res

# 接受用户押注
print("输入你压的值：")
user_input = input()
user_data = user_input.split(" ")
# 向服务器发送压注信息
req = {
    "op": "game",
    "type": user_data[1],
    "val": user_data[2]
}
req_s = json.dumps(req)
sock.send(req_s.encode("utf-8"))
del req, req_s
# 接收服务器返回的游戏结果
print("庄家将两枚玉骰扔进两个金盅，一手持一盅摇将起来。")
data = sock.recv(4096)
if not data:
    print("EOF")
    sys.exit(0)
res = json.loads(data)
# 展示游戏的结果，包括骰号、输赢种类和钱数
print("庄家将左手的金盅倒扣在银盘上，玉骰滚了出来。")
print(dice[res["numA"] - 1])
print("庄家将右手的金盅倒扣在银盘上，玉骰滚了出来。")
print(dice[res["numB"] - 1])
win_type = {
    "tc": "头彩",
    "dc": "大彩",
    "kp": "空盘",
    "qx": "七星",
    "dd": "单对",
    "sx": "散星",
    "qt": "未中"
}
print("庄家叫道：{}、{}……{}。".format(res["numA"], res["numB"], win_type[res["type"]]))
if res["op"] == "win":
    print("你赢了" + str(res["val"]) + user_data[3] + "。")
elif res["op"] == "lose":
    print("你输了" + str(res["val"]) + user_data[3] + "。")

# 结束游戏
req = {
    "op": "quit"
}
req_s = json.dumps(req)
sock.send(req_s.encode("utf-8"))
sock.close()
print("游戏结束。")
