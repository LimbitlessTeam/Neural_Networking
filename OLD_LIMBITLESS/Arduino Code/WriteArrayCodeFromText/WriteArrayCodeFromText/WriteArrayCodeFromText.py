import numpy as np
import matplotlib.pyplot as plt
#import scipy.optimize as opt

Zj = np.array([], dtype = float)
Zr = np.array([], dtype = float)
K = np.array([], dtype = float)


print("opening and reading...")
Kcode = open("code.txt", 'w')
Kfile = open("tocode.txt", 'r')


a = Kfile.read()
print("file read.")
t = np.array(a.split("\n"))

arrayName = input("Enter array name: ")

Kcode.write("double[] " + arrayName + " = {")
n = 0
while(n < t.size):
    try:
        print("\""+ t[n] + "\"")
        Kcode.write(t[n] + ", ")
    except ValueError:
        print("couldn't append \"" + t[n] + "\"")
    n = n+1

Kcode.write("};")

Kcode.write("\n\n\n\n\n\n\n")

#Kcode.write("double[] "+ arrayName + " = [")
#n = 0
#while(n < t.size):
#    try:
#        print("\""+ t[n] + "\"")
#        Kcode.write(t[n] + ", ")
#    except ValueError:
#        print("couldn't append \"" + t[n] + "\"")
#    n = n+1

#Kfile.close()
#Kcode.close()
