class MyMatrix:
    def __init__(self, mt_data = []):
        self.mt = mt_data
    def save(self, f_name):
        s = ""
        for i in range(len(self.mt)):
            s += str(self.mt[i][0])
            for j in range(1, len(self.mt[0])):
                s += ',' + str(self.mt[i][j])
            s += ';'
        with open(f_name, 'w+', encoding="utf-8") as f:
            f.write(s)
        
        
    def load(self, f_name):
        s = ""
        with open(f_name, 'r+', encoding='utf-8') as f:
            s = f.read()
        s_splitted = s.split(';')
        new_mt = []
        for i in range(len(s_splitted)-1):
            new_mt.append([])
            line = s_splitted[i].split(',')
            for j in range(len(line)):
                new_mt[i].append(int(line[j]))
        self.mt = new_mt

    def get_matrix(self):
        return self.mt

def count_chars_in_string(str):
    chars = { 'a' : 0 }
    for i in range(len(str)):
        if chars.get(str[i]):
            chars[str[i]] += 1
        else:
            chars[str[i]] = 1
    return chars

def count_chars_in_file(f_name):
    f_str = ""
    with open(f_name, "r+", encoding='utf-8') as f:
        f_str = f.read()
    freq = count_chars_in_string(f_str)
    items = list(freq.items())
    with open(f_name + ".freq", 'w+', encoding="utf-8") as f:
        for i in range(len(items)):
            f.write(items[i][0] + ": " + str(items[i][1]) + '\n')

if __name__=="__main__":
    a = MyMatrix([[1,2,3], [1,2,3]])
    a.save('m.txt')

    b = MyMatrix()
    b.load('m.txt')

    c = a.get_matrix() == b.get_matrix()
    print(c)

    my_str = "aabcccddddd"
    print(count_chars_in_string(my_str))
    count_chars_in_file('sometext.txt')