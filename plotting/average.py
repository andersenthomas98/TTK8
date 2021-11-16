import os

dir = os.path.dirname(os.path.abspath(__file__))

filename = os.path.join(dir, 'motor10w.txt')

file = open(filename, "r")

list = file.readlines()

sum = 0
for l in list:
    l = float(l)
    sum += l


print("average = "+ str(sum/len(list)))
file.close()