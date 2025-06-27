# #страны и города

m={}
for i in range (int(input("num of country"))):
    m.update({input("name of country "):[c for c in input("name of cities in country").split()]})

m1=[]
for i in range (int(input("how many cities do you know them countries"))):
    m1.append(input(str(i+1)+"- name of city :" ))

def search(d,value):
    for key , val in d.items():
                if i in val:
                 print(key)


for i in m1:
    search(m,i)


# num = int(input())
# sts = {}
# for i in range(num):
#     st = input().split(" ")
#     for r in range(1, len(st)):
#         sts[st[r]] = st[0]
#
# numcity = int(input())
# for e in range(numcity):
#     print(sts.get(input()))
