-- Write a SQL query to list the names of all people who have directed a movie that received a rating of at least 9.0.
-- Your query should output a table with a single column for the name of each person.
-- If a person directed more than one movie that received a rating of at least 9.0, they should only appear in your results once.
   SELECT DISTINCT people.name
     FROM directors
     JOIN people ON directors.person_id = people.id
     JOIN movies ON directors.movie_id = movies.id
     JOIN ratings ON movies.id = ratings.movie_id
    WHERE ratings.rating >= 9.0;
