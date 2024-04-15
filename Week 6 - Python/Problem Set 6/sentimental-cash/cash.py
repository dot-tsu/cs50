# Ask how much change in dollars the customer is owed
dollars = 0
while dollars <= 0:
    try:
        dollars = float(input("Change owed in dollars: $"))
        if dollars <= 0:
            print("Please enter a value greater than 0.")
    except ValueError:
        print("Please enter a valid number.")

# Convert dollars to cents
cents = int(dollars * 100)

# Calculate the number of quarters to give the customer
quarters = cents // 25
cents %= 25

# Calculate the number of dimes to give the customer
dimes = cents // 10
cents %= 10

# Calculate the number of nickels to give the customer
nickels = cents // 5
cents %= 5

# Calculate the number of pennies to give the customer
pennies = cents

# Sum coins
coins = quarters + dimes + nickels + pennies

# Print total number of coins to give the customer
print(coins)
