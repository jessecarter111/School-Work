from __future__ import division
import math
import numpy as np
from sklearn.tree import DecisionTreeClassifier



class Node:
    def __init__(self,data):
        """
            self.data - training_data for this node
            self.majority_class - the class to predict if this is a leaf Node
            self.split_attr - the attribute used to make the branch
            self.split_value - the value of the attribute used for splitting
            self.left - Node object trained on all data having split_attr <= split_value
            self.right - Node object trained on all data having split_attr > split_value
        """
        self.data = data
        self.majority_class = None
        self.split_attr = None
        self.split_value = None
        self.left = None
        self.right = None

    def compute_entropy(self,classes):
        """
            !!! Given a list(distribution) of classes, return the entropy.
            Ex: I/p - [1,1,1]
                O/p - 0
        """
        n_classes = list(set(classes))
        n_counts = [0]*len(n_classes)
        indexes = range(len(n_classes))

        for value in classes:
            for index in indexes:
                if value == n_classes[index]:
                    n_counts[index] += 1

        entropy = 0
        count = sum(n_counts)
        for value in n_counts:
            prob = value/count
            entropy += -(prob*(math.log(prob,2)))

        return entropy

        pass

    def get_values_and_classes(self,attr):
        """
        *** Fill in this documentation string
        :param attr: The index corresponding to the attribute 
        :return: A list of all the attribute in question and the class they belong to
        """
        return [(self.data[ind][attr],self.data[ind].class_) for ind in range(len(self.data))]

    def get_left_split(self,attr,value):
        """
        *** Fill in this documentation string
        :param attr: The index of the attribute 
        :param value: (prev_value*next_value)/2
        :return: All examples with a corresponding attribute <= value
        """
        return [datum for datum in self.data if datum[attr]<=value]

    def get_right_split(self,attr,value):
        """
        *** Fill in this documentation string
        :param attr: The index of the attribute
        :param value: (prev_value*next_value)/2
        :return: All examples with a corresponding attribute > value
        """
        return [datum for datum in self.data if datum[attr]>value]

    def get_data_for_left(self):
        """
        *** Fill in this documentation string
        :return: All examples with entropy <= split value
        """
        return [datum for datum in self.data if datum[self.split_attr] <= self.split_value]

    def get_data_for_right(self):
        """
        *** Fill in this documentation string
        :return: All examples with entropy > split value
        """
        return [datum for datum in self.data if datum[self.split_attr] > self.split_value]

    def is_pure(self):
        """
        *** Fill in this documentation string
        :return: True or False if is is a leaf node
        """
        return len(set([x.class_ for x in self.data])) == 1

    def get_class(self,datum):
        """
        This method passes the datum through the nodes of the tree
        recursively till the leaf node and returns the class.
        :param datum: object of the Datum class
        :return: label of the datum
        """
        # !!! Write code.
        if self.majority_class == None:
            if datum[self.split_attr] > self.split_value:
                return self.right.get_class(datum)
            else:
                return self.left.get_class(datum)
        return self.majority_class
        pass

    def compute_best_split(self):
        attrs_entropies = {ind:{"gain":0,"value":0} for ind in range(len(self.data[0].features))}
        current_entropy = self.compute_entropy([datum.class_ for datum in self.data])

        for ind in range(len(self.data[0].features)):
            values_and_classes = self.get_values_and_classes(ind)
            values = sorted([x[0] for x in values_and_classes])
            len_values = len(values)
            best_value = None
            best_gain = 0
            for prev_value,next_value in zip(values,values[1:]):
                value = (prev_value + next_value) / 2

                # !!! Using the above get_* methods, write code to compute gain for each value of the attribute.
                leftSplit = self.get_left_split(ind, value)
                leftList = [example.class_ for example in leftSplit]
                leftEnt = self.compute_entropy(leftList)
                leftLen = float(len(leftList))

                rightSplit = self.get_right_split(ind, value)
                rightList = [example.class_ for example in rightSplit]
                rightEnt = self.compute_entropy(rightList)
                rightLen = float(len(rightList))

                new_entropy = ((rightLen)/len_values*rightEnt + (leftLen)/len_values*leftEnt)
                gain = current_entropy - new_entropy

                if gain>best_gain:
                    best_gain = gain
                    best_value = value
            attrs_entropies[ind]["gain"] = best_gain
            attrs_entropies[ind]["value"] = best_value

        self.split_attr = max(attrs_entropies,key=lambda x:attrs_entropies[x]["gain"])
        self.split_value = attrs_entropies[self.split_attr]["value"]

class Datum:
    def __init__(self,features,class_):
        self.features = features
        self.class_ = class_

    def __getitem__(self, item):
        # *** Read about operator overloading
        return self.features[item]

class DecisionTree:
    def __init__(self,train_data,test_data):
        self.root = Node(train_data)
        self.test_data = test_data

    def train(self):
        """
        Code to train the decision tree recursively.
        :return: A Decision Tree trained on the Trainning Dataset
        """
        stack_nodes = [self.root]

        # !!! Write code to train decision tree. If the node is pure, set the majority_class attribute.
        # Use .pop(0) to pop the top of the stack
        while len(stack_nodes) > 0:
            node = stack_nodes.pop(0)
            purity = node.is_pure()

            if (purity):
                node.majority_class = node.data[0].class_
            else:
                node.compute_best_split()

                node.right = Node(node.get_data_for_right())
                stack_nodes.append(node.right)

                node.left = Node(node.get_data_for_left())
                stack_nodes.append(node.left)
        pass

    def predict(self, datum):
        return self.root.get_class(datum)

    def test_accuracy(self):
        pos = 0
        for datum in self.test_data:
            pred_class = self.predict(datum)
            if pred_class == datum.class_:
                pos += 1
        return pos/len(self.test_data)

if __name__ == "__main__":
    np.random.seed(5)
    iris_data = np.loadtxt('iris.data', delimiter=',')
    np.random.shuffle(iris_data)
    features = iris_data[:, 0:4]
    targets = iris_data[:, 4]
    data_size = int(0.8*features.shape[0])
    train_feats, train_classes = features[:data_size].tolist(), targets[:data_size].tolist()
    test_feats, test_classes = features[data_size:].tolist(), targets[data_size:].tolist()
    train_data = [Datum(feats,class_) for feats,class_ in zip(train_feats,train_classes)]
    test_data = [Datum(feats,class_) for feats,class_ in zip(test_feats,test_classes)]

    dt = DecisionTree(train_data,test_data)
    dt.train()
    print(dt.test_accuracy())

    dt = DecisionTreeClassifier(criterion="entropy")
    dt.fit(train_feats,train_classes)
    print(np.mean(dt.predict(test_feats)==test_classes))
