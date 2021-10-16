import random

doors = [False,False,False]
doors[random.randint(0,2)] = True
print("Choose a door (0..2)")
choice = int(input())
print("Your choice is the door number ", choice)

Wrong_Choice = random.randint(0,2)
while (doors[Wrong_Choice] == True) or (Wrong_Choice == choice):
    Wrong_Choice = random.randint(0,2)

print("There is no your new car behind the door number ",Wrong_Choice, 
". But you still have a chance to think again and change the door you've chosen. You wanna keep your choice or select an another door?")
choice = int(input())
while choice == Wrong_Choice:
    print("You already know that this door is wrong, choose another one")
    choice = int(input())
    
if doors[choice] == True:
    print("Congratulations, you won a new car!!!!!!!")
else:
    print("You're a loser, bye")

