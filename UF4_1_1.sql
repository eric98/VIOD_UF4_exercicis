-- Creació de base de dades biblioteca
CREATE DATABASE biblioteca;
-- > Comprovació: Llista les bases de dades del SGBD
\l

-- Connexió a la base de dades biblioteca
\c biblioteca
-- > Comprovació: Ens sortirà "biblioteca=#" a la consola

-- a) Creació de taula desenvolupadors
CREATE TABLE desenvolupadors (
        id INT CHECK (id >= 0),
        nom VARCHAR(20),
        PRIMARY KEY (id)
);

-- > Comprovació: Descripció de la taula desenvolupadors
\d desenvolupadors;

-- b) Creació de taula videojocs
CREATE TABLE videojocs (
        id INT CHECK (id >= 0),
        nom VARCHAR(45),
        data_sortida DATE,
        genere VARCHAR CHECK (genere IN ('SURVIVAL', 'RPG', 'METROIDVANIA', 'ACTION ADVENTURE')),
        preu NUMERIC(6,2),
        img_portada BYTEA,
        id_desenvolupador INT CHECK (id_desenvolupador >= 0),
        PRIMARY KEY (id),
        FOREIGN KEY (id_desenvolupador) REFERENCES desenvolupadors (id)
);

-- > Comprovació: Descripció de la taula videojocs
\d videojocs;
