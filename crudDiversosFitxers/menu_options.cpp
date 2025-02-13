#include "menu_options.hpp"

// Menu functions #1
void insertRubikOption(pqxx::connection &conn) {

  // 1. Mostrem el formulari de creació d'un nou cub de rubik
  std::cout << "== Menú de creació de cub de rubik ==" << std::endl;

  std::string nomAux;
  std::cout << "Nom: " << std::flush;
  std::cin >> nomAux;

  char hasStickers;
  std::cout << "Conté pegatines? [y/n]: " << std::flush;
  std::cin >> hasStickers;
  bool pegatinesAux = (hasStickers == 'y');

  int tipus;
  std::cout << "Tipus (Cub = 1, Piràmide = 2, Esfera = 3) [1/2/3]: " << std::flush;
  std::cin >> tipus;
  rubik::type tipusAux = (rubik::type) tipus;

  // 2. Preguntem a l'usuari si les dades són correctes
  char confirm;
  std::cout << "\n... creant cub: {nom=" + nomAux + ", pegatines=" + (pegatinesAux ? 'y' : 'n') + ", tipus=" + std::to_string(tipusAux) + "}" << std::endl;
  std::cout << "Les dades són correctes? [y/n]: " << std::flush;
  std::cin >> confirm;

  if (confirm == 'y') {

    // 3. Creem el cub de rubik amb les dades rebudes del formulari
    std::cout << "\n... executant consulta preparada ..." << std::endl;
    createRubiksCube(conn,nomAux,pegatinesAux,tipusAux);
    std::cout << "--> Operació INSERT executada exitosament" << std::endl;

  }
}

// Menu functions #2
void selectRubikOption(pqxx::connection &conn) {
  std::cout << "... executant consulta preparada ..." << std::endl;
  readRubiksCubes(conn);
  std::cout << "--> Operació SELECT executada exitosament" << std::endl;
}

// Menu functions #3
void updateRubikOption(pqxx::connection &conn) {
  // TODO

  // 1. Mostrem els cubs de rubiks existents (SELECT)
  // 2. Preguntem per l'id del cub de rubik que es vol modificar
  // 3. Creem un cub de rubik amb les noves dades però amb el mateix id
  // 4. Executem la funció updateRubik()
}

// Menu functions #4
void deleteRubikOption(pqxx::connection &conn) {
  // TODO

  // 1. Mostrem els cubs de rubiks existents (SELECT)
  // 2. Preguntem per l'id del cub de rubik que es vol esborrar
  // 3. Executem la funció deleteRubik()
}

