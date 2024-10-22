SELECT movies.title
FROM movies
JOIN stars AS star1 ON movies.id = star1.movie_id
JOIN people AS p1 ON star1.person_id = p1.id
JOIN stars AS star2 ON movies.id = star2.movie_id
JOIN people AS p2 ON star2.person_id = p2.id
WHERE p1.name = 'Bradley Cooper' AND p2.name = 'Jennifer Lawrence';
