from cs50 import SQL
import csv

db = SQL("sqlite:///students.db")

houses = []
students = []

# Retrieve the data from the CSV
with open("students.csv", "r") as file:
    data = csv.DictReader(file)
    id = 1
    for row in data:
        students.append(row)
        house = row["house"]

        # Check if the house already exists in houses list
        house_exists = any(
            existing_house["house_name"] == house for existing_house in houses
        )

        if not house_exists:
            houses.append({"house_name": house, "id": id, "head": row["head"]})
            id += 1


# Fill houses table with unique houses
for house in houses:
    db.execute(
        "INSERT OR IGNORE INTO houses (id, house_name, head) VALUES (?, ?, ?)",
        house["id"],
        house["house_name"],
        house["head"],
    )

for student in students:
    # Get house ID
    house_id = db.execute(
        "SELECT id FROM houses WHERE house_name = ?", student["house"]
    )
    house_id = house_id[0]["id"]

    # Fill students table
    db.execute(
        "INSERT OR IGNORE INTO students (id, student_name) VALUES (?, ?)",
        student["id"],
        student["student_name"],
    )

    # Fill assignments table
    db.execute(
        "INSERT OR IGNORE INTO assignments (student_id, house_id) VALUES (?, ?)",
        student["id"],
        house_id,
    )

