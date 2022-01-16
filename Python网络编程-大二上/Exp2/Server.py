#!/usr/bin/python3
# 导入需要的包
import random
import socket
import json
import threading
import sys

# IP地址和端口绑定
if len(sys.argv) < 3:
    print("参数不正确")
    sys.exit(0)
ip = sys.argv[1]
port = int(sys.argv[2])

# 创建socket并监听
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind((ip, port))
sock.listen(10)

# 用于多线程的函数
def client_link(csock: socket.socket, addr: list):
    print("[*] Accepted connection from " + str(addr[0]) + ":" + str(addr[1]))
    nums = [0, 0, 0, 0]
    # 接收数据并判断需要进行的操作
    while True:
        data = csock.recv(4096)
        if not data:
            print("EOF")
            break
        res = json.loads(data)
        # 结束游戏，结束线程
        if res["op"] == "quit":
            break
        # 初始化游戏
        elif res["op"] == "init":
            nums[0] = random.randint(1, 6)
            nums[1] = random.randint(1, 6)
            req = {
                "op": "init",
                "numA": nums[0],
                "numB": nums[1]
            }
            req_s = json.dumps(req)
            csock.send(req_s.encode("utf-8"))
            del req, req_s, res
        # 用户押注后，游戏主体
        elif res["op"] == "game":
            nums[2] = random.randint(1, 6)
            nums[3] = random.randint(1, 6)
            win_type = 0
            type_data = ["", "tc", "dc", "kp", "qx", "dd", "sx", "qt"]
            type_revdata = {
                "tc": 1,
                "dc": 2,
                "kp": 3,
                "qx": 4,
                "dd": 5,
                "sx": 6
            }
            user_type = type_revdata[res["type"]]
            # 判断输赢类型
            if nums[0] == nums[2] and nums[1] == nums[3]:
                win_type = 1
            elif nums[0] == nums[3] and nums[1] == nums[2]:
                win_type = 2
            elif nums[2] != nums[3] and nums[2] % 2 == 0 and nums[3] % 2 == 0:
                win_type = 3
            elif nums[2] + nums[3] == 7:
                win_type = 4
            elif nums[2] % 2 == 1 and nums[3] % 2 == 1:
                win_type = 5
            elif nums[2] + nums[3] in [3, 5, 9, 11]:
                win_type = 6
            else:
                win_type = 7
            if user_type < win_type or win_type == 7:
                req = {
                    "op": "lose",
                    "type": type_data[win_type],
                    "numA": nums[2],
                    "numB": nums[3],
                    "val": res["val"]
                }
                req_s = json.dumps(req)
                csock.send(req_s.encode("utf-8"))
            else:
                gift_tbl = {
                    "tc": 35,
                    "dc": 17,
                    "kp": 5,
                    "qx": 5,
                    "dd": 3,
                    "sx": 2
                }
                req = {
                    "op": "win",
                    "type": type_data[user_type],
                    "numA": nums[2],
                    "numB": nums[3],
                    "val": int(res["val"]) * gift_tbl[type_data[user_type]]
                }
                req_s = json.dumps(req)
                csock.send(req_s.encode("utf-8"))
                del req, req_s, res

# 接受TCP请求
while True:
    sock_c, addr_c = sock.accept()
    # 启动线程处理游戏
    t = threading.Thread(target=client_link, args=(sock_c, addr_c))
    t.start()
