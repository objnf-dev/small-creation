num = int(input())
used = []
stepped = []

for i in range(num):
    used.append(0)

def dfs(step):
    for i in range(num):
        if used[i] == 0 :
            used[i]=1
            stepped.append(i+1)
            if step==num:
                for j in range(num):
                    print(stepped[j],' ',end='')
                print()
            else:
                dfs(step+1)
            stepped.pop()
            used[i]=0

dfs(1)
