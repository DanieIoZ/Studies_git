import utils
from confmat import BinaryConfusionMatrix

SPAM_TAG = 'SPAM'
HAM_TAG = 'OK'

def quality_score(tp, tn, fp, fn):
    return (tp + tn) / (tp + tn + 10*fp + fn)

def compute_quality_for_corpus(corpus_dir):
    results = {'truth': utils.read_classification_from_file(corpus_dir + "/" + "!truth.txt"), 'prediction': utils.read_classification_from_file(corpus_dir + "/" + "!prediction.txt")}
    
    cfmat = BinaryConfusionMatrix(pos_tag = SPAM_TAG, neg_tag = HAM_TAG)
    cfmat.compute_from_dicts(results['truth'], results["prediction"])
    matrix_for_quality = cfmat.as_dict() 
    return quality_score(matrix_for_quality['tp'], matrix_for_quality['tn'], matrix_for_quality['fp'], matrix_for_quality['fn'])