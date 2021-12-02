def count_rows_and_words(filename)
{
    with open(filename, "r", encoding='utf-8') as f:
        lines = f.readlines()
        sum = 0
        for i in range(len(lines)):
            sum += len(split(lines[i]))

    return (len(lines), sum)

}




if "__name__" == "__main__":
    filename = input()
    print(count_rows_and_words(filename))
