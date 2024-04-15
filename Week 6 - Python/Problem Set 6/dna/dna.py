import csv
import sys


def main():
    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    database = []
    STRs = []
    with open(sys.argv[1], "r") as file:
        csvReader = csv.DictReader(file)
        for person in csvReader:
            # Convert values to integers for all keys except 'name'
            database.append(
                {
                    key: int(value) if key != "name" else value
                    for key, value in person.items()
                }
            )
            # Add every STR to an array
            STRs = [key for key in person.keys() if key != "name"]

    # Read DNA sequence file into a variable
    sequence = ""
    with open(sys.argv[2], "r") as file:
        sequence = file.read()

    # Check database for matching profiles
    matches = {STR: longest_match(sequence, STR) for STR in STRs}

    matchFound = False
    for person in database:
        if all(person[STR] == matches[STR] for STR in STRs):
            print(person["name"])
            matchFound = True
            break

    if not matchFound:
        print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:
            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
