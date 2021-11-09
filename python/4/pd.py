import random

def print_data(data):
    spacing = len(str(largest_num(data)))

    for i in range(len(data)):
        for j in range(len(data[i])):
            print(' ' * (spacing - len(str(data[i][j]))), data[i][j], end="")
        print()
    return

def generate_data(n_rows, n_cols):
    bits = []
    for i in range(n_rows):
        bits.append([])
        for j in range(n_cols):
            bits[i].append(random.getrandbits(1))
    return bits

def line_size(r,c,data):
    sum = 1
    left = True
    right = True
    for i in range (1,len(data[0])):
        if left and (c-i >= 0) and (data[r][c-i] == data[r][c]):
            sum += 1
        else:
            left = False
        if right and (c+i < len(data)) and (data[r][c+i] == data[r][c]):
            sum += 1
        else:
            right = False
    return sum

def column_size(r,c,data):
    sum = 1
    up = True
    down = True
    for i in range (1,len(data)):
        if up and (r-i >= 0) and (data[r-i][c] == data[r][c]):
            sum += 1
        else:
            up = False
        if down and (r+i < len(data)) and (data[r+i][c] == data[r][c]):
            sum += 1
        else:
            down = False
    return sum

def diag_size(r,c,data):
    sum = 1
    rising = [True,True]
    falling = [True, True]
    for i in range (1,min(len(data), len(data[0]))):
#-----------------------------------------------------------------------------------------------------#
        if rising[0] and (r-i >= 0) and (c+i < len(data[0])) and (data[r-i][c+i] == data[r][c]):
            sum += 1
        else:
            rising[0] = False
        if rising[1] and (r+i < len(data)) and (c-i >= 0) and (data[r+i][c-i] == data[r][c]):
            sum += 1
        else:
            rising[1] = False
#-----------------------------------------------------------------------------------------------------#
        if falling[0] and (r-i >= 0) and (c-i >= 0) and (data[r-i][c-i] == data[r][c]):
            sum += 1
        else:
            falling[0] = False
        if falling[1] and (r+i < len(data)) and (c+i < len(data[0])) and (data[r+i][c+i] == data[r][c]):
            sum += 1
        else:
            falling[1] = False
#-----------------------------------------------------------------------------------------------------#
    return sum

def region_size(r,c,data):
    sum = line_size(r,c,data)
    sum += column_size(r,c,data)
    return sum + diag_size(r,c,data) - 2
    

def largest_num(data):
    largest = 0
    for i in range (len(data)):
        if (largest < max(data[i])):
            largest = max(data[i])
    return largest

if __name__ == "__main__":
    #data = ((1,2,3,4,54828,6,7, 123, 9492, 923, 3472, 84, 842, 12), (8,9231,10,1121,12,13,14, 123, 9492, 923, 3472, 84, 842, 12), (15,16,1,18,19,4,21, 123, 9492, 923, 3472, 84, 842, 12), (15,16,1,18,19,4,21, 123, 9492, 923, 3472, 84, 842, 12), (15,16,1,18,19,4,21, 123, 9492, 923, 3472, 84, 842, 12), (15,16,1,18,19,4,21, 123, 9492, 923, 3472, 84, 842, 12))
    #print_data(data)
    #print("\n\n\n")
    data = generate_data(9, 8)
    print_data(data)
    print(line_size(3,3,data))
    print(column_size(3,3,data))
    print(diag_size(3,3,data))
    print(region_size(3,3,data))
