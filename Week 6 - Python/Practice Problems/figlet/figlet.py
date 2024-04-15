from pyfiglet import Figlet
import sys
import random

figlet = Figlet()

# Validate user arguments
if len(sys.argv) == 1:
    figlet.setFont(font=random.choice(figlet.getFonts()))

elif (
    len(sys.argv) == 3
    and sys.argv[1].lower() in ["-f", "--font"]
    and sys.argv[2].lower() in figlet.getFonts()
):
    figlet.setFont(font=sys.argv[2].lower())
else:
    sys.exit("Invalid usage")

text = input("Input: ")

print('Output:', figlet.renderText(text))
