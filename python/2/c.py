def find_max(index, index_max, listik):
    return (find_max(index+1, index, listik) if listik[index] > listik[index_max] else  find_max(index+1, index_max, listik)) if index < len(listik)-1 else listik[index_max]


if __name__ == "__main__":
    listikkk = [1,4,6,8,2897,3,4,6,23,52,2,3,32,323,62,9]
    print(find_max(1,0,listikkk))

    