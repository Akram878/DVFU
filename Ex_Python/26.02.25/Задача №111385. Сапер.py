#saper

L=[int(var) for var in input().split()]
matrix=[[0 for x in range(L[1])] for y in range (L[0])]
for i in range(L[2]):
    M=[int(var) for var in input().split()]
    matrix[(M[0])-1][(M[1])-1]= '*'


for i in range (0,len(matrix)):

    for j in range (0, len(matrix[i])):

        if matrix[i][j] == '*':

            for dx,dy in [(1,1),(0,1),(1,0),(-1,-1),(-1,0),(0,-1),(1,-1),(-1,1)]:
                x=i+dx
                y=j+dy

                if 0 == i  and 0 < j < len(matrix[i])-1:
                    if dx == -1 :
                        x, y = i, j
                elif 0 < i < len(matrix)-1 and 0 == j :
                    if (dy == -1):
                        x, y = i, j

                elif 0 == i and 0 ==j:
                    if(dx==-1 or dy==-1):
                        x,y=i,j

                elif  i==len(matrix)-1 and 0 < j < len(matrix[i])-1:
                    if (dx == 1):
                        x, y = i, j

                elif 0 < i < len(matrix)-1  and j==len(matrix[i])-1:
                    if (dy == 1):
                        x, y = i, j

                elif  i == len(matrix)-1  and j == len(matrix[i])-1:
                    if (dx == 1 or dy == 1):
                        x, y = i, j

                if (matrix[x][y] != '*'):
                    matrix[x][y] = matrix[x][y] + 1

for i in matrix:

   print(*i)




