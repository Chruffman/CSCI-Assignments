#Chris Huffman 1/28/15
#Assignment 3 Problem 1
#TA - Upendra Sabnis

# Python program that calculates the passer rating of a quarterback given certain statistics as input

pass_completions = float(input("Enter pass completions"))
pass_attempts = float(input("Enter pass attempts"))
total_passing_yards = float(input("Enter total passing yards"))
touchdowns = float(input("Enter number of touchdowns"))
interceptions = float(input("Enter number of interceptions"))

completions_per_attempt = float(pass_completions / pass_attempts)
yards_per_attempt = float(total_passing_yards / pass_attempts)
touchdowns_per_attempt = float(touchdowns / pass_attempts)
intercepts_per_attempt = float(interceptions / pass_attempts)

C = (completions_per_attempt - 0.30) * 5
Y = (yards_per_attempt - 3) * 0.25
T = touchdowns_per_attempt * 20
I = 2.375 - (intercepts_per_attempt * 25)
Passer_Rating = (C + Y + T + I) / 6 * 100

print('The passer rating is %f') % Passer_Rating
