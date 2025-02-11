-- #0 Ens connectem al SGBD PostgreSQL
-- $ sudo -i -u postgres
-- $ psql

-- #1 Creem i ens connectem a la base de dades puzzles
CREATE DATABASE puzzles;
\c puzzles;

-- #2 Creem els objectes relacionals amb els que interactuarà crud.cpp (ENUM type, TABLE rubiks)
CREATE TYPE type_rubik AS ENUM ('CUB', 'PIRAMIDE', 'ESFERA');
CREATE TABLE rubiks (
	id SERIAL PRIMARY KEY,
	nom VARCHAR(20),
	pegatines BOOL,
	tipus type_rubik
);

-- #3 Inserim algunes dades inicials
INSERT INTO rubiks (nom, pegatines, tipus)
  VALUES ('3x3x3', TRUE, 'CUB'),
  ('Pyraminx', FALSE, 'PIRAMIDE'),
  ('Gearball', TRUE, 'ESFERA');
