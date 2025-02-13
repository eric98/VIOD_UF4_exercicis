#pragma once

#include <string>

// Conté l'estructura que manipulen a la nostra base de dades.
// 	També conté les funcions necessàries per manipular
// 	les dades del nostre 'rubik'

struct rubik {
  enum type {
    CUB = 1, PIRAMIDE = 2, ESFERA = 3
  };

  int id;
  std::string nom;
  bool pegatines;
  type tipus;
};

rubik::type getRubikTypeFromString(std::string str);
std::string getStringEnumFromRubikType(rubik::type t);
std::string rubikToString(rubik r);
