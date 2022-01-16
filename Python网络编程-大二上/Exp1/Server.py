import socket
import json
import sys

class Server():
    # 基本服务器信息
    def __init__(self, address: tuple):
        self.addr = address
        self.userList = {}
        self.userOnline = []
        print("[*] Server started on {}:{}.".format(addr[0], addr[1]))
        self.recieve(self.addr)

    # 向指定的地址发送数据
    def send(self, msg: bytes, addr: tuple):
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        s.sendto(msg, addr)

    # 增加用户
    def addUser(self, auth: dict, addr: tuple):
        self.userList[auth["name"]] = {}
        self.userList[auth["name"]]["addr"] = addr
        self.userList[auth["name"]]["pwd"] = auth["pwd"]

    # 验证用户名密码是否正确
    def auth(self, auth: dict, addr: tuple):
        if auth["name"] not in self.userList:
            self.addUser(auth,addr)
            self.userOnline.append(auth["name"])
            return True
        else:
            if auth["pwd"] == self.userList[auth["name"]]["pwd"]:
                if auth["name"] not in self.userOnline:
                    self.userOnline.append(auth["name"])
                return True
            else:
                return False
    
    # 发送单人消息
    def solo(self, text: str, addr, username: str =""):
        text = bytes(text, encoding="utf-8")
        if username in self.userOnline:
            addr = self.userList[username]["addr"]
            print("[*] Send secret message to {}.".format(username))
            self.send(text,addr)
        else:
            print("[!] Message sending failed. Target user offline?")
            self.send(text,addr)

    # 发送多人消息（广播）
    def boardcast(self, text: str):
        text = bytes(text, encoding='utf-8')
        for user in self.userOnline:
            print("[*] Boardcasting message :{}".format(str(text, encoding="utf-8")))
            self.send(text,self.userList[user]["addr"])

    # 处理收到的数据
    def handle(self, msg: dict, addr: tuple):
        if self.auth(msg["auth"],addr):
            if msg["type"] == "broadcast":
                text = ("[Broadcast] "+msg["auth"]["name"]+": "+msg["text"])
                self.boardcast(text)
            elif msg["type"] == "solo":
                text = ("[Secret] "+msg["auth"]["name"]+": "+msg["text"])
                self.solo(text,addr,msg["toWho"])
            elif msg["type"] == "notice":
                text = ("[System] "+msg["auth"]["name"]+" joined the chatroom.")
                self.boardcast(text)
            elif msg["type"] == "show":
                text = "[System] All online users:\n"
                for user in self.userOnline:
                    text = text + user + "\n"
                self.solo(text,addr,msg["auth"]["name"])
            elif msg["type"] == "exit":
                self.userOnline.remove(msg["auth"]["name"])
            else:
                pass
        else:
            text = ("[!] Login failed")
            self.solo(text,addr)

    # 接受用户发送的数据
    def recieve(self, addr: tuple):
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        sock.bind(addr)
        while True:
            msg, addr = sock.recvfrom(8192)
            msg = json.loads(msg)
            self.handle(msg,addr)

# 程序入口
if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("参数不正确。")
        sys.exit(0)
    ip = sys.argv[1]
    port = sys.argv[2]
    addr = (ip,int(port))
    Server(addr)
