#англо-латинский словарь
import re
dic = {}
arr = []
for i in range(int(input())):
    words = re.split(r', |-| ', input())
    words = [w for w in words if w.strip()]
    for t in words[1:]:
        # arr.append(t)
        dic[t] = dic.get(t, []).append(words[0])
    # dic[words[0]] = words[1:]

arr = sorted(arr)
print(dic, arr)

for lat in sorted(dic.key()):
    for eng in sorted(dic[lat]):
        {}