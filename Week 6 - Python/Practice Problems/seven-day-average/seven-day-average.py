import csv
import requests


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# TODO: Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):
    new_cases = {}
    previous_cases = {}

    for row in reader:
        state = row["state"]
        cases = int(row["cases"])

        if state not in new_cases:
            new_cases[state] = []

        if state not in previous_cases:
            previous_cases[state] = cases
        else:
            new_cases[state].append(cases - previous_cases[state])
            previous_cases[state] = cases

        if len(new_cases[state]) > 14:
            new_cases[state].pop(0)

    return new_cases


import csv
import requests


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print("\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):
    new_cases = {}
    previous_cases = {}

    for row in reader:
        state = row["state"]
        cases = int(row["cases"])

        if state not in new_cases:
            new_cases[state] = []

        if state not in previous_cases:
            previous_cases[state] = cases
        else:
            new_cases[state].append(cases - previous_cases[state])
            previous_cases[state] = cases

        if len(new_cases[state]) > 14:
            new_cases[state].pop(0)

    return new_cases


# Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):
    for state in states:
        cases = new_cases[state]

        if len(cases) < 7:
            print(f"Insufficient data for state: {state}")
            continue

        this_week_average = sum(cases[-7:]) / 7
        last_week_average = sum(cases[-14:-7]) / 7

        try:
            percent_change = (
                (this_week_average - last_week_average) / last_week_average
            ) * 100
        except ZeroDivisionError:
            percent_change = 0.0

        if percent_change < 0:
            print(
                f"{state} had a 7-day average of {int(this_week_average)} and a decrease of {abs(int(percent_change))}%."
            )
        elif percent_change > 0:
            print(
                f"{state} had a 7-day average of {int(this_week_average)} and an increase of {abs(int(percent_change))}%."
            )
        else:
            print(
                f"{state} had a 7-day average of {int(this_week_average)} and no change in cases."
            )

main()
