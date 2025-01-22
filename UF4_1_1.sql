-- Creació de base de dades biblioteca
CREATE DATABASE biblioteca;
-- > Comprovació: Llista les bases de dades del SGBD
\l

-- Connexió a la base de dades biblioteca
\c biblioteca
-- > Comprovació: Ens sortirà "biblioteca=#" a la consola

-- a) Creació de taula desenvolupadors
CREATE TABLE desenvolupadors (
        -- Afegim un CHECK per a simular el UNSIGNED (valor major o igual a 0)
        id INT CHECK (id >= 0), 
        nom VARCHAR(20),
        PRIMARY KEY (id)
);

-- > Comprovació: Descripció de la taula desenvolupadors
\d desenvolupadors;

-- b) Creació de taula videojocs
CREATE TABLE videojocs (
        -- Afegim un CHECK per a simular el UNSIGNED (valor major o igual a 0)
        id INT CHECK (id >= 0), 
        nom VARCHAR(45),
        data_sortida DATE,
        -- Afegim un CHECK per a simular ENUM dels valors ('SURVIVAL', 'RPG', 'METROIDVANIA', 'ACTION ADVENTURE')
        genere VARCHAR CHECK (genere IN ('SURVIVAL', 'RPG', 'METROIDVANIA', 'ACTION ADVENTURE')),
        preu NUMERIC(6,2),
        img_portada BYTEA,
        -- Afegim un CHECK per a simular el UNSIGNED (valor major o igual a 0)
        id_desenvolupador INT CHECK (id_desenvolupador >= 0),
        PRIMARY KEY (id),
        FOREIGN KEY (id_desenvolupador) REFERENCES desenvolupadors (id)
);

-- > Comprovació: Descripció de la taula videojocs
\d videojocs;

-- c) Insereix les següents dades.
INSERT INTO desenvolupadors (id, nom) VALUES
(1, 'Team Cherry'), (2, 'Konami'), (3, 'Valve');
INSERT INTO videojocs VALUES
(1, 'Hollow Knight', '2017-02-24', 'METROIDVANIA', 14.99, NULL, 1),
(2, 'Silent Hill 2', '2001-09-24', 'SURVIVAL', 49.99, NULL, 2),
(3, 'Portal', '2007-10-10', 'ACTION ADVENTURE', 19.99, NULL, 3);

-- > Comprovació: Consultem el contingut de les taules
SELECT * FROM desenvolupadors;
SELECT * FROM videojocs;
