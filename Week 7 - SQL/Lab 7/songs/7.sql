-- Output a table with a single column and a single row containing the average energy on Drake's songs.
-- You should not make any assumptions about what Drake’s artist_id is.
   SELECT AVG(songs.energy) AS drake_energy
     FROM songs
     JOIN artists ON songs.artist_id = artists.id
    WHERE artists.name = 'Drake';
