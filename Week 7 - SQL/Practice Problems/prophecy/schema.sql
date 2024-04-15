   CREATE TABLE IF NOT EXISTS students (
          id INTEGER PRIMARY KEY NOT NULL,
          student_name TEXT NOT NULL
          );

   CREATE TABLE IF NOT EXISTS houses (
          id INTEGER PRIMARY KEY NOT NULL,
          house_name TEXT NOT NULL,
          head TEXT
          );

   CREATE TABLE IF NOT EXISTS assignments (
          student_id INTEGER NOT NULL,
          house_id INTEGER NOT NULL,
          FOREIGN KEY (student_id) REFERENCES students (id),
          FOREIGN KEY (house_id) REFERENCES houses (id),
          PRIMARY KEY (student_id, house_id)
          );

-- -- Querie to retrieve student assignments with house names instead of ids
-- SELECT students.student_name AS student_name, houses.house_name AS house_name
-- FROM assignments
-- JOIN students ON assignments.student_id = students.id
-- JOIN houses ON assignments.house_id = houses.id;
