# # права доступа

op =  {'R' : 'read' , 'W' : 'write' , 'X' : 'execute' }
dic={}
for i in range(int(input("how many path and propirties ? "))):
    li=input().split(" ")
    dic[li[0]]=[op[li[i].upper()] for i in range (1,len(li))] # len from 1 to (length of li -1)

print(dic)

for i in range(int(input("how many operations ?"))):
    operation = input().split(" ")
    if operation[0] in dic[operation[1]]: # if value in dic[key]
        print('OK')
    else:
        print('Access denied')

