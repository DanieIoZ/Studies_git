import unittest
from confmat import BinaryConfusionMatrix

SPAM_TAG = 'SPAM'
HAM_TAG = 'OK'

class BinaryConfusionMatrixTest(unittest.TestCase):

    def SetUp(self):
        self.cm = BinaryConfusionMatrix(pos_tag = SPAM_TAG, neg_tag = HAM_TAG)

    def test_countersAreZero_afterCeration(self):
        self.SetUp()
        self.assertDictEqual(self.cm.as_dict(), {'tp': 0, 'tn': 0, 'fp': 0, 'fn': 0})
    
    def test_updateTPcorrectly(self):
        self.SetUp()
        self.cm.update(SPAM_TAG, SPAM_TAG)
        self.assertDictEqual(self.cm.as_dict(), {'tp': 1, 'tn': 0, 'fp': 0, 'fn': 0})
    
    def test_updateTNcorrectly(self):
        self.SetUp()
        self.cm.update(HAM_TAG, HAM_TAG)
        self.assertDictEqual(self.cm.as_dict(), {'tp': 0, 'tn': 1, 'fp': 0, 'fn': 0})

    def test_updateFPcorrectly(self):
        self.SetUp()
        self.cm.update(HAM_TAG, SPAM_TAG)
        self.assertDictEqual(self.cm.as_dict(), {'tp': 0, 'tn': 0, 'fp': 1, 'fn': 0})

    def test_updateFNcorrectly(self):
        self.SetUp()
        self.cm.update(SPAM_TAG, HAM_TAG)
        self.assertDictEqual(self.cm.as_dict(), {'tp': 0, 'tn': 0, 'fp': 0, 'fn': 1})

    def test_raisesValueError_forWrongTruthValue(self):
        self.SetUp()
        with self.assertRaises(ValueError):
            self.cm.update('a bad value', SPAM_TAG)

    def test_computerFromDicts_allCasesOnce(self):
        self.SetUp()
        truth_dict = {1: SPAM_TAG, 2: SPAM_TAG, 3: HAM_TAG, 4:HAM_TAG}
        pred_dict = {1: SPAM_TAG, 2: HAM_TAG, 3: SPAM_TAG, 4:HAM_TAG}

        self.cm.compute_from_dicts(truth_dict, pred_dict)
        self.assertDictEqual(self.cm.as_dict(), {'tp': 1, 'tn': 1, 'fp': 1, 'fn': 1})


if __name__ == "__main__":
    unittest.main()