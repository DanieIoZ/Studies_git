import random

def print_data(data):
    spacing = len(str(largest_num(data)))

    for i in range(len(data)):
        for j in range(len(data[i])):
            print(' ' * (spacing - len(str(data[i][j]))), data[i][j], end="")
        print('\n')
    return

def generate_data(n_rows, n_cols):
    bits = []
    for i in range(n_rows):
        bits.append([])
        for j in range(n_cols):
            bits[i].append(random.getrandbits(1))
    return bits

def line_size(r,c,data):
    return 

def largest_num(data):
    largest = 0
    for i in range (len(data)):
        if (largest < max(data[i])):
            largest = max(data[i])
    return largest

if __name__ == "__main__":
    data = ((1,2,3,4,54828,6,7, 123, 9492, 923, 3472, 84, 842, 12), (8,9231,10,1121,12,13,14, 123, 9492, 923, 3472, 84, 842, 12), (15,16,1,18,19,4,21, 123, 9492, 923, 3472, 84, 842, 12), (15,16,1,18,19,4,21, 123, 9492, 923, 3472, 84, 842, 12), (15,16,1,18,19,4,21, 123, 9492, 923, 3472, 84, 842, 12), (15,16,1,18,19,4,21, 123, 9492, 923, 3472, 84, 842, 12))
    print_data(data)
    print("\n\n\n")
    data = generate_data(15, 20)
    print_data(data)
