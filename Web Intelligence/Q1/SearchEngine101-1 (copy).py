import numpy as np
import os
import re
from nltk.corpus import stopwords
from sklearn.feature_extraction.text import TfidfVectorizer
from scipy.spatial.distance import cosine

class SearchEngine101:
    def __init__(self, dir):
        all_files = os.listdir(dir)
        self.text_content = [open(dir + "/" + file_name).read() for file_name in all_files]
        self.preprocess()
        self.index()
        print "Preprocessing and Indexing done..."

    def preprocess(self):
        """
        Cleans self.texts and sets the cleaned_texts attribute.
        """
        self.cleaned_texts = []

        # Done !!! remove non-letter occurrences from the texts
        # Use regex: re.sub
        for i in self.text_content:
            temp = re.sub('[^a-zA-Z\s]|','',i)
            self.cleaned_texts.append(temp)

        # Done !!! convert into lowercase 
        # Use .lower()
        temp = []
        for i in self.cleaned_texts:
            temp.append(i.lower())

        self.cleaned_texts = temp

    def tokenize(self, text):
        """
        Will split a text into words and remove stop words
        :param text: string - can be a document or a query
        :return: list - a list of words
        """
        words = None

        # Done !!! Split the text into a sequence of words and store it in words
        # Use .split()
        words = text.split()

        # Done !!! remove stopwords
        words = [word for word in words if word not in stopwords.words('english')]
        
        return words

    def index(self):

        split_texts = [self.tokenize(text) for text in self.cleaned_texts]
        # We'll use a dictionary (HashMap) for storing the inverted index
        # Key : word
        # Value : The DocIDs relevant to the word
        self.inverted_index = {}

        for index,split_text in enumerate(split_texts):
            split_text = set(split_text)
            for word in split_text:
                self.inverted_index[word] = self.inverted_index.get(word, [])
                self.inverted_index[word].append(index)

        # !!! sort all the values of the dictionary, redundant as the way they are inserted
        # in they dict means they will already be sorted
        # for key in self.inverted_index:
        #     self.inverted_index[key] = sorted(self.inverted_index[key])

    def intersection(self, list1, list2):
        """
        Should return intersection of list1 and list2
        :param list1: list of integers
        :param list2: list of integers
        :return: intersection
        """
        intersection = []

        # Done !!! populate the intersection list and return
        list1 = set(list1)
        intersection = list1.intersection(list2)

        return intersection

    def filter(self, query):
        """
        Returns the filtered list of texts [both cleaned and original] which contain the query terms
        :param query: string - user query
        :return: filterd_list: list - list of documents that contain the query terms
        """
        query_terms = self.tokenize(query)

        # Retrieve List of DocIDs for each of the terms in the query
        document_lists = [self.inverted_index[term] for term in query_terms]

        # !!! Optimise the document lists for faster intersection, also redundant
        # the doc_lists are already sorted so we are just doing it twice :p
        # document_lists = [sorted(item) for item in document_lists]
        
        # Now, iteratively take intersection
        document_indices = document_lists[0]
        for document_list in document_lists[1:]:
            document_indices = self.intersection(document_indices, document_list)

        return [self.cleaned_texts[index] for index in document_indices], [self.text_content[index] for index in document_indices]


    def vectorize(self, filtered_texts, query):
        """
        Store the vectors and vectorizer.
        """
        #query = self.tokenize(query)
        self.vectors = []
        self.vectorizer = TfidfVectorizer(lowercase=True, stop_words="english", norm=None, use_idf=True, smooth_idf=False,
                                     sublinear_tf=False, decode_error="ignore")
        
        filtered_texts.append(query)
        # !!! Use TfIdfVectorizer. It automatically converts into a matrix.
        text = [query] + filtered_texts
        self.vectors = self.vectorizer.fit_transform(text)

    def retrieve_ranked_list(self):
        """
        Return the indices of text_vectors in decreasing order of cosine similarity and the scores
        :return: indices, scores: indices of top 10 documents and scores of all documents
        """
        similarities = []
        dimensions = self.vectors.get_shape()
        rows = dimensions[0]

        # !!! Populate the similarities array with cosine similarities between text_vectors and query_vector
        similarities = [cosine(self.vectors.getrow(index).todense(),self.vectors.getrow(0).todense()) for index in range(0,rows-2)]
        
        #print similarities
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
        self.preprocess()
        self.index()

        #Analysis to determine the most frequently used word in the set
        hold = []
        word = ''
        print "Determining the most frequently used word in the database ......."
        for key in self.inverted_index:
            if len(self.inverted_index[key]) > len(hold):
                hold = self.inverted_index[key]
                word = key
        print word
        print hold
        #Analysis determined that the most frequently used word was "subject", this is likely because
        #all of the documents are emails, which for the most part contain a subject line.

        print "Accesing the order of the documents retrieved .........."
        i = 0
        output = []
        while (i < 3):
            output.append(self.search("school work"))
            i += i 
        i = 0
        while (i < 2):
            if output[i] != output[i+1]:
                print "Different result returned for same query"

        #The same output is returned each time, and sense the search engine only cares if the document
        #contains all the search terms, it will return the same order of documents. The contents of the documents
        #is also irrelevant as they are only being searched on whether they contain the query terms or not, not how
        #relevant they are to the actually query in terms of semantic meaning
        pass

if __name__ == "__main__":
    # Write the driver code here
    engine = SearchEngine101(dir = "data")
    #engine.analyse()
    engine.search("science stuff")
    #engine.search("dalhousie university")
    