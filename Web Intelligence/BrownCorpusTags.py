import nltk
import operator
from nltk.corpus import brown
from tabulate import tabulate

tags = brown.tagged_words()
cfd = nltk.ConditionalFreqDist(tags)

ntags = [(condition, len(cfd[condition])) for condition in cfd.conditions()]

tags_by_num = []

i = 0
while i < 11:
    temp = 0
    for (word, num) in ntags:
        if num == i:
            temp += 1
    tags_by_num.append((i, temp))
    i += 1

#Prints the table for part 1
print "Part 1"
print tabulate(tags_by_num)
print

#Find word with most distinct tags
desiredWord = ('', 0)
for value in ntags:
    if value[1] > desiredWord[1]:
        desiredWord = value

print "Part 2"
print "The Word with most distinct tags is: ",desiredWord
print

distinct_tags = [tag for tag in cfd[desiredWord[0]]]
tagged_sents = brown.tagged_sents()

# go through each sentence in the corpus. 
# go through each tag in the sentence
print "************"
for sentence in tagged_sents:
    for (word, tag) in sentence:
        for distinct_tag in distinct_tags:
            if distinct_tag == tag and (word == 'That' or word == 'that'):
                print sentence
                distinct_tags.remove(distinct_tag)
                print "************"
                break
print

#Determine the tags with the greatest number of distinct words. 
tagFreq = {}
for element in tags:
    if element[1] in tagFreq:
        tagFreq[element[1]] += 1
    else:
        tagFreq[element[1]] = 0

sortedFreq = sorted(tagFreq.items(), key=operator.itemgetter(1), reverse=True)[:10]
print "Part 3"
print tabulate(sortedFreq)








