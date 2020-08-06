import numpy as np
from sklearn.naive_bayes import GaussianNB
import math


class GaussianDistribution:
    def __init__(self, classes, data_size):
        """
        Initialise the data structures to store the learned parameters
        :param classes: The list of classes
        :param data_size: The size of the complete training data
        """
        self.classes = classes
        self.data_size = data_size
        self.conditional_prob = {class_:{} for class_ in classes} # Conditional Probability Table for storing parameters useful to compute P(feat|class_)
        self.class_prob = {} # Stores the priors

    def index_data(self, data, class_):
        """
        Write code to estimate the parameters. 
        :param data: All training data that belong to class_
        :param class_: The label of all the data points. 
        :return:  Doesn't return anything
        """
        # !!! Write code to compute and store the parameters in self.conditional_prob[class_].
        for feat_index in range(len(data[0])):
        
            values = [i[feat_index] for i in data]
            
            deviation = np.std(values)
            mean = np.mean(values)

            self.conditional_prob[class_][feat_index] = [mean, deviation]

        # !!! Write code to compute prior.
        # Seems like it's been done for us?
        self.class_prob[class_] = float(len(data))/self.data_size

    def prob(self, feature_index, feature_value, class_):
        """
        !!! Write code to return P(feature_index = feature_value | class = class_)
        :param feature_index: the index of the current attribute being evaluated
        :param feature_value: the current 
        :param class_: 
        :return: probability
        """

        deviation = self.conditional_prob[class_][feature_index][1]
        mean = self.conditional_prob[class_][feature_index][0]

        val1 = math.pow((feature_value - mean), 2)
        val1 = val1/math.pow(deviation, 2)

        val2 = 2*math.pi*math.pow(deviation, 2)
        val2 = 1/(math.sqrt(val2))

        probability = val2 * math.exp(-val1)

        return probability


class NaiveBayes:
    def __init__(self, train_data, train_classes, test_data, test_classes, prob_distribution = GaussianDistribution):
        self.train_data = train_data
        self.train_classes = train_classes
        self.test_data = test_data
        self.test_classes = test_classes

        self.distribution = prob_distribution(set(train_classes), len(self.train_data))

    def train(self):
        """
        Trains the algorithm by gathering information from the given data set.
        :return: Doesn't return anything
        """
        for class_ in set(self.train_classes):
            data = map(lambda (ind, datum): datum, filter(lambda (ind, datum): self.train_classes[ind] == class_, enumerate(self.train_data)))
            self.distribution.index_data(data, class_)

    def predict(self, datum):
        """
        Uses the previous training to predict the class of a given data set.
        :param datum: The example whose class we wish to predict
        :return: The example's predicted class
        """
        probs = {}
        for class_ in set(self.train_classes):
            probs[class_] = self.distribution.class_prob[class_] * reduce(lambda x,y:x*y, [self.distribution.prob(feat_ind_feat[0],feat_ind_feat[1],class_) for feat_ind_feat in enumerate(datum)])
        return max(probs, key=lambda x:probs[x])

    def test_accuracy(self):
        pos = 0.0
        for index, datum in enumerate(self.test_data):
            pred_class = self.predict(datum)
            if pred_class == self.test_classes[index]:
                pos += 1
        return pos/len(self.test_data)


if __name__ == "__main__":
    np.random.seed(5)
    iris_data = np.loadtxt('iris.data', delimiter=',')
    np.random.shuffle(iris_data)
    features = iris_data[:, 0:4]
    targets = iris_data[:, 4]
    data_size = int(0.8*features.shape[0])
    train_data, train_classes = features[:data_size].tolist(), targets[:data_size].tolist()
    test_data, test_classes = features[data_size:].tolist(), targets[data_size:].tolist()
    nb = NaiveBayes(train_data, train_classes, test_data, test_classes)
    nb.train()
    print nb.test_accuracy()

    nb = GaussianNB()
    nb.fit(train_data,train_classes)
    print np.mean(nb.predict(test_data) == test_classes)

    # !!! In the last week : Print out parameters learned by SkLearn and compare with yours.
