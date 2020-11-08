# By submitting this assignment, I agree to the following:
#   "Aggies do not lie, cheat, or steal, or tolerate those who do."
#   "I have not given or received any unauthorized aid on this assignment."
#
# Name:         Tony Yang
# UIN:          228009469
# Section:      215
# Assignment:   Lab 9b_Act2
# Date:         25 October 2019
#I've been to four countries during my life. 
filename = input("What is the desginated file name? ")
filename = filename + ".csv" #Must use .csv file so I add .csv at the end
#user inputs for math calculations
P = float(input("What is the loan amount? "))
N = int(input("What is the number of months the loan will be repaid? "))
i = float(input("What is the annual interest rate (Note this should be a decimal number, not a percentage: 0.025 not 2.5%)? "))
M = P * ((i/12) / (1 - (1 + (i / 12))**(-1 * N))) #monthly payment 
intrest = P * (i / 12) #intrest payment
#header settings
filewrite = open(filename,"w")
filewrite.write("Month" + ",")
filewrite.write("Beginning balance" + ",")
filewrite.write("Monthly intrest" + ",")
filewrite.write("Accured intrest" + ",")
filewrite.write("Final balance" + "," + "\n")
month =  0 #month counter
#below is the 1st line for month 0
filewrite.write(str(month) + ",")
filewrite.write(",")
filewrite.write(",")
filewrite.write(",")
filewrite.write("$ " + str(P) + "\n")
begin = P #begining value
AccInt = 0 #accured interest 
final = P #final value
MonInt = 0 #monthly interest
for f in range(N):
    month += 1 #month counts up by one
    filewrite.write(str(month) + ",") #writing month
    begin1 = round(final,2) #rounding for displaying purposes but not calculation purposes
    filewrite.write("$ " + str(begin1) + ",")
    MonInt = begin * (i / 12) #monthly interest calculation
    MonInt1 = round(MonInt,2) #rounding for displaying purposes
    filewrite.write("$ " + str(MonInt1) + ",")
    AccInt = AccInt + MonInt #accured interst 
    AccInt1 = round(AccInt, 2)#rounding for displaying purposes 
    filewrite.write("$ " + str(AccInt1) + ",")
    subtract = M - MonInt
    final = begin - subtract # calculating final value using unrounded values
    final1 = round(final,2)
    filewrite.write("$ " + str(final1) + "\n")
    begin = final #setting final value to begining value for next calculation 
filewrite.close()

