-- Output a table with a single column for the name of each song by Post Malone.
-- You should not make any assumptions about what Post Malone’s artist_id is.
   SELECT songs.name AS post_malone_songs
     FROM songs
     JOIN artists ON songs.artist_id = artists.id
    WHERE artists.name = 'Post Malone';
