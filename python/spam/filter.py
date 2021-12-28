import re

from corpus import Corpus

# List of criterias
SENDER_SUS_SYMBOLS = 2
CONTAIN_CAPS = 0.5
CONTAIN_SUS_WORDS = 1

IN_REPLY_TO = -5

# Border to tag email as SPAM
SPAM_INDEX_BORDER = 4


# counts the index of caps in a word
def caps_index(word):
    w_len = len(word)
    upper_idx = 0
    for i in range(len(word)):
        if word[i].isupper():
            upper_idx += 1
    if w_len > 0:
        return upper_idx / w_len
    else:
        return 0


# removes email, if sender has some name, otherwise just returns email
def split_sender(sender):
    sender_split = sender.rsplit(' ', 1)
    return sender_split[0]


# makes a dictionary from email file
def email_to_dict(name, text):
    email = {'name': name}
    # split all email data by '\n\n' once to find where content starts
    meta_and_content = text.split('\n\n', 1)
    # split email information on lines
    lines = meta_and_content[0].split('\n')
    # additional variable, which is needed when some of sectors takes more than 1 line
    prev = (lines[0].split(': ', 1))[0]
    for line in lines:
        tmp = line.split(': ', 1)
        if len(tmp) > 1:
            email[tmp[0]] = tmp[1]
            prev = tmp[0]
        else:
            email[prev] += tmp[0]
    email['Content'] = meta_and_content[1]
    return email


class MyFilter:
    """Very simple filter without any training, sadly"""
    def __init__(self):
        self.sus_words_default = ['weight', 'free', 'xxx', 'sex', 'hot ', 'insurance', 'now', 'drugs', 'oral', 'cancer']

    def train(self, directory):
        # my spam filter doesn't have training method
        return

    def test(self, directory):
        corpus = Corpus(directory)

        f = open(directory + "/" + "!prediction.txt", "w", encoding="utf-8")
        for name, email_body in corpus.emails():
            # get one email item as dictionary
            email_item = email_to_dict(name, email_body)
            spam_index = 0
            # START TESTING
            # Testing sender
            em_sender = split_sender(email_item['From'])

            # Checking sender string on containing "?" and "!" symbols
            if re.search(r'[\?,\!,-]', em_sender):
                spam_index += SENDER_SUS_SYMBOLS

            if any(sus in em_sender.lower() for sus in self.sus_words_default):
                spam_index += CONTAIN_SUS_WORDS

            # Reply section usually means, that email is a part of some dialogue between people
            if 'In-Reply-To' in email_item.keys():
                spam_index += IN_REPLY_TO

            # Subject
            if 'Subject' in email_item.keys():
                if (sus in email_item['Subject'].lower() for sus in self.sus_words_default):
                    spam_index += CONTAIN_SUS_WORDS

            # Checking content on suspicious words
            sus_words_in_content = 0
            for sussy in self.sus_words_default:
                if sussy in email_item['Content'].lower():
                    sus_words_in_content += CONTAIN_SUS_WORDS
            spam_index += sus_words_in_content

            # Checking uppercase
            for word in email_item['Content'].split(' '):
                if caps_index(word) > 0.5:
                    spam_index += CONTAIN_CAPS

            # STOP TESTING
            tag = 'OK'
            if spam_index > SPAM_INDEX_BORDER:
                tag = 'SPAM'

            f.write(email_item['name'] + ' ' + tag + '\n')

        f.close()
        return

