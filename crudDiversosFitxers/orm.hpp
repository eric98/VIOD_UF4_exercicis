#pragma once

#include <pqxx/pqxx>
#include "rubik.hpp"
#include <iostream>

// Conté les funcions que simulen l'ORM

// ORM #1 'C'RUD, create
void createRubiksCube(pqxx::connection &conn, std::string nom, bool pegatines, rubik::type tipus);

// ORM #2 C'R'UD, read
void readRubiksCubes(pqxx::connection &conn);

// ORM #3 CR'U'D, update
void updateRubiksCubeById(pqxx::connection &conn, int id, std::string nom, bool pegatines, rubik::type tipus);

// ORM #4 CRU'D', delete
void deleteRubiksCubeById();
