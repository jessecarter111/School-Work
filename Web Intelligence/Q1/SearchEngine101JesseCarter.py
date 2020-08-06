import numpy as np
import os
import re
from nltk.corpus import stopwords

class SearchEngine101:
    def __init__(self, dir):
        all_files = os.listdir('data')
        self.text_content = [open(dir + '/' + file_name).read() for file_name in all_files]
        self.preprocess()
        self.index()
        print "Preprocessing and Indexing done..."

    def preprocess(self):
        """
        Cleans self.texts and sets the cleaned_texts attribute.
        """
        self.cleaned_texts = []

        # !!! remove non-letter occurrences from the texts
        # Use regex: re.sub
        self.cleaned_texts = re.sub('\W+',' ', str(self.text_content))

        # !!! convert into lowercase
        # Use .lower()
        self.cleaned_texts.lower()
        #print self.cleaned_texts

    def tokenize(self, text):
        """
        Will split a text into words and remove stop words
        :param text: string - can be a document or a query
        :return: list - a list of words
        """

        # !!! Split the text into a sequence of words and store it in words
        words = text.split()

        # !!! remove stopwords"
        # Follow https://stackoverflow.com/questions/5486337/how-to-remove-stop-words-using-nltk-or-python
        words = [word for word in words if word not in stopwords.words('english')]

        return words


    def index(self):
    	#Why use an iterator? 
        split_texts = [self.tokenize(text) for text in self.cleaned_texts]

        # We'll use a dictionary (HashMap) for storing the inverted index
        # Key : word
        # Value : The list of its occurences where the doc id represents the position in the list
        self.inverted_index = {}

        for index,split_text in enumerate(split_texts):
            split_text = set(split_text)
            for word in split_text:
                self.inverted_index[word] = self.inverted_index.get(word, [])
                self.inverted_index[word].append(index)

        # !!! sort all the values of the dictionary

    def intersection(self, list1, list2):
        """
        Should return intersection of list1 and list2
        :param list1: list of integers
        :param list2: list of integers
        :return:
        """
        intersection = []

        for word in list1 and list2:
        	if word not in intersection:
        		intersection.append(word)

        # !!! populate the intersection list and return
        return intersection

    def filter(self, query):
        """
        Returns the filtered list of texts [both cleaned and original] which contain the query terms
        :param query: string - user query
        :return: filterd_list: list - list of documents that contain the query terms
        """
        query_terms = self.tokenize(query)

        # Retrieve ??? for each of the terms in the query
        document_lists = [self.inverted_index[term] for term in query_terms]

        # !!! Optimise the document lists for faster intersection

        # Now, iteratively take intersection
        document_indices = document_lists[0]
        for document_list in document_lists[1:]:
            document_indices = self.intersection(document_indices, document_list)


        return [self.cleaned_texts[index] for index in document_indices], [self.text_content[index] for index in document_indices]


    def vectorize(self, filtered_texts, query):
        """
        Store the vectors and vectorizer.
        """
        self.vectors = None
        self.vectorizer = None

        # !!! Use TfIdfVectorizer. It automatically converts into a matrix.

    def retrieve_ranked_list(self):
        """
        Return the indices of text_vectors in decreasing order of cosine similarity and the scores
        :return: indices, scores: indices of top 10 documents and scores of all documents
        """
        similarities = []

        # !!! Populate the similarities array with cosine similarities between text_vectors and query_vector

        # Return the top 10 indices of the similarities array
        return np.argsort(similarities)[::-1][:10], similarities

    def print_list(self,text_content, scores, text_indices):
        print len(text_indices), "Results Found!\n"
        print "*******************************\n"
        for index in text_indices:
            print scores[index]
            print text_content[index]
            print "*******************************\n"

    def search(self, query):
        filtered_clean, filtered_orig = self.filter(query)
        self.vectorize(filtered_texts=filtered_clean, query=query)
        text_indices, scores = self.retrieve_ranked_list()
        self.print_list(text_content=filtered_orig, scores= scores, text_indices=text_indices)

    def analyse(self):
        """
        This is for your custom code. Use it to analyse IDF/TF-IDF and construct queries.
        :return:
        """
        pass

if __name__ == "__main__":
    # Write the driver code here
    engine = SearchEngine101(dir = "data")
    engine.search("dalhousie university")