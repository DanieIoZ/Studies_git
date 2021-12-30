class BinaryConfusionMatrix:
    def __init__(self, pos_tag, neg_tag):
        self.tp = 0
        self.tn = 0
        self.fp = 0
        self.fn = 0
        self.pos_tag = pos_tag
        self.neg_tag = neg_tag

    def as_dict(self):
        return {'tp': self.tp, 'tn': self.tn, 'fp': self.fp, 'fn': self.fn}

    def check_value_of(self, value):
        if value not in (self.pos_tag, self.neg_tag):
            raise ValueError('The parameters must be %s or %s' \
                             % (self.pos_tag, self.neg_tag))

    def compute_from_dicts(self, truth_dict, pred_dict):
        for key in truth_dict:
            self.update(truth_dict[key], pred_dict[key])

    def update(self, truth, prediction):
        self.check_value_of(truth)
        self.check_value_of(prediction)

        if prediction == self.pos_tag:
            if truth == self.pos_tag:
                self.tp += 1
            else:
                self.fp += 1
        else:
            if truth == self.pos_tag:
                self.fn += 1
            else:
                self.tn += 1
