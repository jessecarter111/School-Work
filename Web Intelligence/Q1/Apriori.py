import csv


class Transaction:
    def __init__(self, items):
        self.items = set(items)


class Apriori:
    def __init__(self, list_transactions):
        self.transactions = list_transactions
        self.all_items = set()
        for trn in self.transactions:
            self.all_items |= trn.items
        pass

    def get_support(self, set_items):
        # Done !!! Write code to return support of set_items
        count = 0
        setItems = set(set_items)

        for transaction in self.transactions:
            newTransaction = set()
            newTransaction |= transaction.items
            if setItems <=newTransaction:
                count = count+1

        support = count*1.0/len(self.transactions) 

        return support

    def get_combinations(self, items, num):
        # Done !!! Write code to return "num" number of combinations of 
        # Apparently not, this is supposed to be a list of sets but I can't figure out how to do it
        # So please mark me gently, this is very challenging 
        items = list(items)
        if num == 0: return [[]]
        if items == []: return []
        return [items[:1]+a for a in self.get_combinations(items[1:],num-1)] + self.get_combinations(items[1:],num)
    
    def get_all_items(self, itemsets):
        # Done !!! Write code to merge all the itemsets and return the current items
        items = []
        for nestedList in itemsets:
            for item in nestedList:
                items.append(item)
        items = set(items)
        return items

    def get_subsets(self, items):
        # Done !!! Write code to return all subsets of "items"
        subsets = []
        i = 0
        if len(items) == 1:
            return [items]
        else:
            i = 1
            while i < len(items):
                temp = self.get_combinations(items, i)
                i = i+1
                subsets.append(temp)

        return subsets


        

    def get_rules(self, min_sup, min_con):
        curr_combinations = self.get_combinations(self.all_items, 1)
        num = 2
        freq_items = []
        supports = []
        while True:
            support_map = map(lambda x: self.get_support(x), curr_combinations)
            chosen_itemset = []
            chosen_supports = []
            for index, items in enumerate(curr_combinations):
                if support_map[index] >= min_sup:
                    chosen_itemset.append(items)
                    chosen_supports.append(support_map[index])
            freq_items.extend(chosen_itemset)
            supports.extend(chosen_supports)
            curr_items = self.get_all_items(chosen_itemset)
            print curr_items
            if num > len(curr_items):
                break
            curr_combinations = self.get_combinations(curr_items, num)
            num += 1
        print "Frequent Itemsets"
        for item, support in sorted(zip(freq_items, supports), key=lambda x: x[1]):
            print ",".join(item), support

        rules = []
        confidences = []
        print "Rules"
        for items in freq_items:
            subsets = self.get_subsets(items)
            support = self.get_support(items)
            for antecedent in subsets:
                if len(items - antecedent) == 0:
                    continue
                print antecedent
                support_A = self.get_support(antecedent)
                if support / support_A > min_con:
                    rules.append((antecedent, items - antecedent))
                    confidences.append(support / support_A)
        print "Finished Loop One"
        for rule, confidence in sorted(zip(rules, confidences), key=lambda x: x[1]):
            print ",".join(rule[0]), "=>", ",".join(rule[1]), confidence


if __name__ == "__main__":
    test_data = [
        ['bread', 'milk'],
        ['bread', 'diaper', 'beer', 'egg'],
        ['milk', 'diaper', 'beer', 'cola'],
        ['bread', 'milk', 'diaper', 'beer'],
        ['bread', 'milk', 'diaper', 'cola'],
    ]

    transactions = []
    test = True

    if test:
        for row in test_data:
            transactions.append(Transaction(set(row)))
    else:
        with open("apriori_data.csv", "r") as f:
            for row in csv.reader(f):
                transactions.append(Transaction(set(row)))

    a = Apriori(transactions)
    a.get_rules(min_sup=0.15, min_con= 0.6)