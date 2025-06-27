#гематрия С
alphabet = ["A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"]
arr = []
dic = {}
import sys
try:
    for line in sys.stdin:
        word = line.strip().upper()
        G = 0
        for i in word:
            G+= alphabet.index(i) + 1
        dic[word] = G
except EOFError: # Ctrl-D
    pass
dict = dict(sorted(dic.items(), key=lambda item: (item[1], item[0]))) #сортировка по значению, потом по ключу в порядке возрастания
for key in dict:
    print(key)