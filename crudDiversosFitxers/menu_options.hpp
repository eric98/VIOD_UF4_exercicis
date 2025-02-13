#pragma once

#include <pqxx/pqxx>
#include <iostream>
#include "orm.hpp"

// Conté els submenús segons cada opció del menú principal
//	1 ... Inserir cub
// 	2 ... Llegir cubs
// 	3 ... Actualitzar cub
//	4 ... Eliminar cub

// Menu functions #1
void insertRubikOption(pqxx::connection &conn);

// Menu functions #2
void selectRubikOption(pqxx::connection &conn);

// Menu functions #3
void updateRubikOption(pqxx::connection &conn);

// Menu functions #4
void deleteRubikOption(pqxx::connection &conn);
