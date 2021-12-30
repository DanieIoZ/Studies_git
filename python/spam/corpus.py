import os


class Corpus:
    def __init__(self, directory):
        self.dir = directory

    def emails(self):
        for name in os.listdir(self.dir):
            if name[0] == "!":
                continue 
            with open(self.dir + "/" + name, "r", encoding="utf-8") as f:
                email_body = f.read()
                yield [name, email_body]
