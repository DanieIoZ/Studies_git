
def value_count(data, value):
    sum = 0
    for i in range(len(data)):
        for j in range(len(data[i])):
            if data[i][j] == value:
                sum += 1
    return sum

def value_positions(data, value):
    points = []
    for i in range(len(data)):
        for j in range(len(data[i])):
            if data[i][j] == value:
                points.append((i,j))
    return points

if __name__=="__main__":
    data = [[0, -1, 1], [-1, 0, -1], [1, 0, -1]]
    value = 0
    count = value_count(data, value)
    print(count)

    value = -1
    positions = value_positions(data, value)
    print(positions)