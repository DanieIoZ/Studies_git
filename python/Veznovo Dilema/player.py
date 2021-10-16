import random

class MyPlayer:
    def play(self):
        return random.choice(['R', 'P', 'S'])

if __name__ == "__main__":
    p = MyPlayer()
    for i in range(10):
        print(i, p.play())