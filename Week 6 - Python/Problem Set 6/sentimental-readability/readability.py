def main():
    text = input("Text: ")
    L = countLetters(text) / countWords(text) * 100
    S = countSentences(text) / countWords(text) * 100
    index = round(0.0588 * L - 0.296 * S - 15.8)

    if index < 1:
        print("Before Grade 1")

    elif index > 16:
        print("Grade 16+")

    else:
        print("Grade", index)


def countLetters(text):
    totalLetters = 0
    for char in text:
        if char.isalnum():
            totalLetters += 1

    return totalLetters


def countWords(text):
    return text.count(" ") + 1


def countSentences(text):
    totalSentences = 0
    for char in text:
        if char in ["!", ".", "?"]:
            totalSentences += 1

    return totalSentences


main()
