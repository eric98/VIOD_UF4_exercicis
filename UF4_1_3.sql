-- Exercici3. Amb l’ajuda dels apunts i de la documentació, recrea la base de 
-- dades empresa.

-- == PREPARACIÓ ==
-- Creem la base de dades empresa
CREATE DATABASE empresa;
-- > Comprovació
\l

-- Ens connectem a la base de dades empresa
\c empresa;

-- == APARTATS DE L'EXERCICI ==
-- a) Crea l’objecte tipus adreca amb els atributs carrer, ciutat i codi_postal.
CREATE TYPE adreca AS (
	carrer VARCHAR(50),
	ciutat VARCHAR(50),
	codi_postal INT
);

-- > Comprovació
\d adreca;

-- b) Crea l’objecte tipus persona amb els atributs nom, casada, edat i adreca.
CREATE TYPE persona AS (
	nom VARCHAR(30),
	casada BOOLEAN,
	edat SMALLINT,
	adreca adreca
);

-- > Comprovació
\d persona;

-- c) Crea la taula treballadors amb els camps id, persona, sou i carrec.
CREATE TABLE treballadors (
	id SERIAL,
	persona persona,
	sou INT,
	carrec VARCHAR(15),
	PRIMARY KEY (id)
);

-- > Comprovació
\d treballadors;

-- d) Insereix 3 registres a la taula treballadors.
-- adreca: (carrer, ciutat, codi_postal)
-- persona: (nom, casada, edat, adreca)
INSERT INTO treballadors (persona, sou, carrec)
	VALUES (ROW('Pepito', FALSE, 35, ROW('C\ M', 'Barcelona', 08330)), 1200, 'Pràctiques'),
	 (ROW('Shrek', TRUE, 32, ROW('C\ Ciénaga', 'Paris', 12345)), 5600, 'Cap'),
	 (ROW('Spiderman', FALSE, 20, ROW('C\ Tia Mey', 'New York', 55333)), 1500, 'Col·laborador');

-- > Comprovació
SELECT * FROM treballadors;

-- e) Llista els camps nom i sou de tots els treballadors.
SELECT (persona).nom, sou FROM treballadors;
