import sys
from datetime import datetime

if(len(sys.argv) != 3):
    print("Program needs 2 arguments")
    exit

input_file = sys.argv[1]
output_file = sys.argv[2]

matrix1 = []
matrix2 = []
data_type = []
with open(input_file, "r") as file:
    program_type = file.readline()

    if(program_type[0] != "1"):
        print("Input file contains Invalid OpCode\n")
        exit

    data_type = file.readline()

    dimensions = file.readline()

    for i in range(4096):
        row = file.readline()

        numbers = row.split()

        matrix1.append(numbers)
    
    dimensions = file.readline()

    for i in range(4096):
        row = file.readline()

        numbers = row.split()

        matrix2.append(numbers)

        if data_type[0] == "1" or data_type[0] == "3":
            for j in range(4096):
                matrix2[i][j] = int(numbers[j])
        else:
            for j in range(4096):
                matrix2[i][j] = float(numbers[j])

for i in range(4096):
    
    if data_type[0] == "1" or data_type[0] == "3":
        for j in range(4096):
            matrix1[i][j] = int(matrix1[i][j])
            matrix2[i][j] = int(matrix2[i][j])
    else:
        for j in range(4096):
            matrix1[i][j] = float(matrix1[i][j])
            matrix2[i][j] = int(matrix2[i][j])


matrix3 = []

for i in range(4096):
    line = []
    for j in range(4096):
        if(data_type[0] == "1" or data_type[0] == "3"):
            line.append(0)
        else:
            line.append(float(0))
    matrix3.append(line)

c = datetime.now()
print(c)

for i in range(4096):
    for j in range(4096):
        for k in range(4096):
            matrix3[i][j] += matrix1[i][k] * matrix2[k][j]

f= datetime.now()
print(f)

for i in range(4096):
    for j in range(4096):
        matrix3[i][j] = str(matrix3[i][j])

with open(output_file, "w") as file:
    file.write(f"{data_type[0]}\n4096X4096\n")
    for row in matrix3:
        for num in row:
            file.write(num+" ")
        file.write("\n")
