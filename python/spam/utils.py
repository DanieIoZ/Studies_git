def read_classification_from_file(filename):
    data = {}
    with open(filename, 'r', encoding='utf-8') as f:
        lines = f.readlines()
        for i in range(len(lines)):
            classification = lines[i].split()
            data[classification[0]] = classification[1]
    return data
