# Chris Huffman
# 2/18/15
# Assignment 4


# Python program that determines whether a given DNA sample matches that of a human, mouse, or neither


# I used these commands to locate the DNA files on my computer	
mouseDNA_filename = open("/home/user/Documents/mouseDNA.txt", "r")
humanDNA_filename = open("/home/user/Documents/humanDNA.txt", "r")
unknownDNA_filename = open("/home/user/Documents/unknownDNA.txt", "r")

# then I used the readline function so I could work with the files in python
mouseDNA = mouseDNA_filename.readline()
humanDNA = humanDNA_filename.readline()
unknownDNA = unknownDNA_filename.readline()

# I used two variables for hamming distance
hamming_distance = 0
hamming_distance_2 = 0

# the next for commands calculated the hamming distances between unknown/mouse and unknown/human DNAs
l = len(unknownDNA)

for i in range(0,l):
	if mouseDNA[i] != unknownDNA[i]:
		hamming_distance = hamming_distance + 1

for x in range(0,l):
	if humanDNA[x] != unknownDNA[x]:
		hamming_distance_2 = hamming_distance_2 + 1
		
# similarity scores converted to float using the equation on the assignment form 		
similarity_score = float(l - hamming_distance) / l
print("MouseCompare = %s" % (similarity_score))

similarity_score_2 = float(l - hamming_distance_2) / l
print("HumanCompare = %s" % (similarity_score_2))

# conditional equations to determine which DNA is closest to the unknown DNA sample
if (similarity_score_2 - similarity_score) < 0.0001:
	print("Identity cannot be determined.")
elif similarity_score < similarity_score_2 and similarity_score > 0.0001:
	print("Mouse.")
elif similarity_score_2 < similarity_score and similarity_score_2 > 0.0001:
	print("Human.")


