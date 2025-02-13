#include "rubik.hpp"

rubik::type getRubikTypeFromString(std::string str) {
  if (str == "CUB")
    return rubik::type::CUB;
  else if (str == "PIRAMIDE")
    return rubik::type::PIRAMIDE;
  else // if (str == "ESFERA")
    return rubik::type::ESFERA;
}

std::string getStringEnumFromRubikType(rubik::type t) {
  switch (t) {
  case rubik::type::CUB:
    return "CUB";
  case rubik::type::PIRAMIDE:
    return "PIRAMIDE";
  case rubik::type::ESFERA:
    return "ESFERA";
  default:
    return "";
  }
}

std::string rubikToString(rubik r) {
  return "{id=" + std::to_string(r.id) + ", nom=" + r.nom + ", pegatines=" + (r.pegatines ? 'y' : 'n') + ", tipus=" + getStringEnumFromRubikType(r.tipus) + " }";
}
