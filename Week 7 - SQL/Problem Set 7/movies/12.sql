-- Write a SQL query to list the titles of all movies in which both Bradley Cooper and Jennifer Lawrence starred.
-- Your query should output a table with a single column for the title of each movie.
-- You may assume that there is only one person in the database with the name Bradley Cooper.
-- You may assume that there is only one person in the database with the name Jennifer Lawrence.
   SELECT DISTINCT movies.title
     FROM movies
     JOIN stars ON movies.id = stars.movie_id
     JOIN people ON stars.person_id = people.id
    WHERE movies.id IN (
             SELECT movie_id
               FROM stars
               JOIN people ON stars.person_id = people.id
              WHERE people.name = 'Bradley Cooper'
          )
      AND movies.id IN (
             SELECT movie_id
               FROM stars
               JOIN people ON stars.person_id = people.id
              WHERE people.name = 'Jennifer Lawrence'
          );
