import threading
import socket
import json
import sys

class Client():
    # 基本客户端信息
    def __init__(self, localAddr: tuple, serverAddr: tuple):
        self.addr = localAddr
        self.serverAddr = serverAddr
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.bind(localAddr)
        self.auth = {}
        self.queue = []
        self.start()

    # 用户登录
    def login(self):
        name = str(input("[*] Username: "))
        pwd = str(input("[*] Password: "))
        self.auth = {
            "name": name,
            "pwd": pwd
        }

        msg = {}
        msg["auth"] = self.auth
        msg["type"] = "notice"
        msg = json.dumps(msg)
        msg = bytes(msg, encoding='utf-8')
        self.sock.sendto(msg, self.serverAddr)
        print("[*] Successfully joined the chatroom.")

    # 接收消息数据
    def recieve(self, addr: tuple):
        while True:
            msg, addr = self.sock.recvfrom(8192)
            msg = str(msg,encoding="utf-8")
            self.queue.append(msg)
            self.chatWindow()

    # 聊天界面
    def chatWindow(self):
        print("--------Messages--------")
        if len(self.queue)>=6:
            for msg in self.queue[-6:]:
                print(f'{msg} \n')
        else:
            for msg in self.queue:
                print(f'{msg} \n')
        print("-----------------------")
        print("[*] Function: b(broadcast) s(solo) l(list all users) e(exit).")

    # 打包消息
    def pack(self):
        msg = {}
        msg["auth"] = self.auth
        mode = input()
        if mode == "s":
            msg["type"] = "solo"
            msg["toWho"] = str(input("Username: "))
            msg["text"] = str(input("Content: "))
        elif mode == "b":
            msg["type"] = "broadcast"
            msg["text"] = str(input("Broadcast:"))
        elif mode == "l":
            msg["type"] = "show"
        elif mode == "e":
            msg["type"] = "exit"
        else:
            msg["type"] = ""
            print("Wrong command.\n Currently support: b(broadcast) s(solo) l(list all users) e(exit).")

        return msg
  
    # 开启不同线程
    def start(self):
        t = threading.Thread(target=self.recieve,args=(self.addr,))
        t.setDaemon(True)
        t.start()
        self.login()
        while True:
            msg = self.pack()
            msgbin = json.dumps(msg)
            msgbin = bytes(msgbin, encoding='utf-8')
            self.sock.sendto(msgbin, self.serverAddr)
            if msg["type"] == "exit":
                sys.exit(0)

# 程序入口点
if __name__ == "__main__":
    if len(sys.argv) < 5:
        print("参数不正确。")
        sys.exit(0)
    localHost = sys.argv[1]
    localPort = sys.argv[2]
    localAddr = (localHost,int(localPort))
    remoteHost = sys.argv[3]
    remotePort = sys.argv[4]
    remoteAddr = (remoteHost,int(remotePort))
    Client(localAddr,remoteAddr)
