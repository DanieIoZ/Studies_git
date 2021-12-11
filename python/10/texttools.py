def count_rows_and_words(filename):
    with open(filename, "r+", encoding='utf-8') as f:
        lines = f.readlines()
        sum = 0
        for i in range(len(lines)):
            sum += len(lines[i].split())

    return (len(lines), sum)

def compute_word_frequencies(filename):
    words = {}
    with open(filename, "r+", encoding='utf-8') as f:
        lines = f.readlines()
        for i in range(len(lines)):
            words_tmp = lines[i].split()
            for j in range(len(words_tmp)):
                if (words_tmp[j] in words.keys()):
                    words[words_tmp[j]] += 1
                else: 
                    words[words_tmp[j]] = 1
    return words

if __name__ == "__main__":
    filename = input()
    print(compute_word_frequencies(filename))
