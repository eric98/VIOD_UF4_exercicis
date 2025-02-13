#include <iostream>
#include <pqxx/pqxx>
#include <pqxx/prepared_statement>

#include "menu_options.hpp"

// Versió del fitxer crud.cpp distribuit entre diversos fitxers.
// 	Podem compilar-ho amb la següent comanda (important afegir el paràmetre -lpqxx)
// 	$ g++ -o main main.cpp menu_options.cpp orm.cpp rubik.cpp -lpqxx

// Fitxer principal. Conté el menú de l'aplicació
int main(int argc, char * argv[]) {
  char * sql;

  try {
    pqxx::connection conn("dbname = puzzles user = postgres password = eric");
    if (conn.is_open()) {
      std::cout << "Opened database successfully: " << conn.dbname() << std::endl;
    } else {
      std::cout << "Can't open database" << std::endl;
      return 1;
    }

    conn.prepare("select", "SELECT * from rubiks ORDER BY id");
    conn.prepare("insert", "INSERT INTO rubiks (nom, pegatines, tipus) VALUES ($1,$2,$3);");
    conn.prepare("update", "UPDATE rubiks SET nom=$2, pegatines=$3, tipus=$4 WHERE id=$1;");
    // TODO: prepare delete

    int opcioUsuari = 0;
    do {
      std::cout << "\n== Benvingut a la biblioteca de cubs de rubik ==" << std::endl;
      std::cout << "#1 Inserir un cub de rubik" << std::endl;
      std::cout << "#2 Llegir els cubs de rubik" << std::endl;
      std::cout << "#3 Actualitzar els cubs de rubik" << std::endl;
      std::cout << "#4 Eliminar un cub de rubik" << std::endl;
      std::cout << "#5 Sortir" << std::endl;

      std::cout << "\nQuina opció vols fer? " << std::flush;
      std::cin >> opcioUsuari;
      std::cout << std::endl;

      switch (opcioUsuari) {
      case 1:
        insertRubikOption(conn);
        break;
      case 2:
        selectRubikOption(conn);
        break;
      case 3:
        updateRubikOption(conn);
        break;
      case 4:
        deleteRubikOption(conn);
        break;
      case 5:
        std::cout << "Agur!" << std::endl;
      }
    }
    while (opcioUsuari != 5);

  } catch (const std::exception & e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  return 0;
}
