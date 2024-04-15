from cs50 import get_string

greeting = get_string("Greeting: ")

greeting = greeting.lower()

if "hello" in greeting:
    moneyOwed = 0

elif greeting.startswith('h'):
    moneyOwed = 20

else:
    moneyOwed = 100

print(f'${moneyOwed}')
