-- Write a SQL query to determine the average rating of all movies released in 2012.
-- Your query should output a table with a single column and a single row (not counting the header) containing the average rating.
   SELECT AVG(ratings.rating) AS average_rating
     FROM ratings
     JOIN movies ON movie_id = movies.id
    WHERE movies.year = 2012;
