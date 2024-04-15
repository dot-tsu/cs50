def main():
    creditCardNumber = int(input("What's your credit card number? "))
    print(creditCardType(creditCardNumber))


def validateCard(creditCardNumber):
    sumOfProductDigits = 0
    odd = False

    # Scroll through digits
    while creditCardNumber != 0:
        lastDigit = creditCardNumber % 10
        creditCardNumber //= 10

        # Multiply every other digit by 2, starting with the number’s second-to-last digit.
        if odd:
            lastDigit *= 2
            if lastDigit > 9:
                lastDigit -= 9
        odd = not odd

        # Sum up all digits
        sumOfProductDigits += lastDigit

    # If it's divisible by 10, the card is valid.
    return sumOfProductDigits % 10 == 0


def creditCardType(creditCardNumber):
    # Check if the card is valid
    if not validateCard(creditCardNumber):
        return "INVALID"

    cardNumberSTR = str(creditCardNumber)

    # Calculate length of the number.
    length = len(cardNumberSTR)

    # Calculate first digits.
    firstDigits = int(cardNumberSTR[:2])

    # Return the type of card based on first digits and length.
    if (length == 13 or length == 16) and cardNumberSTR.startswith("4"):
        return "VISA"
    if length == 16 and firstDigits in [51, 52, 53, 54, 55]:
        return "MASTERCARD"
    if length == 15 and firstDigits in [34, 37]:
        return "AMEX"

    return "INVALID"


main()
