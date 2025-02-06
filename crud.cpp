#include <iostream>
#include <pqxx/pqxx>
#include <pqxx/prepared_statement>

struct rubik {
  enum type {
    CUB = 1, PIRAMIDE = 2, ESFERA = 3
  };

  int id;
  std::string nom;
  bool pegatines;
  type tipus;
};

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

// ORM #1 'C'RUD, create
void createRubiksCube(pqxx::connection &conn, std::string nom, bool pegatines, rubik::type tipus) {
  /* Create a transactional object. */
  pqxx::work w(conn);

  /* Execute SQL query */
  w.exec_prepared("insert", nom, pegatines ? "TRUE" : "FALSE", getStringEnumFromRubikType(tipus));
  w.commit();
}

// ORM #2 C'R'UD, read
void readRubiksCubes(pqxx::connection &conn) {
  /* Create a non-transactional object. */
  pqxx::nontransaction n(conn);

  /* Execute SQL query */
  pqxx::result r(n.exec_prepared("select"));

  /* List down all the records */
  for (pqxx::result::const_iterator c = r.begin(); c != r.end(); ++c) {

    rubik rubikAux;
    rubikAux.id = c[0].as <int> ();
    rubikAux.nom = c[1].as <std::string> ();
    rubikAux.pegatines = c[2].as <bool> ();
    rubikAux.tipus = getRubikTypeFromString(c[3].as <std::string> ());

    std::cout << rubikToString(rubikAux) << std::endl;
  }
}

// ORM #3 CR'U'D, update
void updateRubiksCubeById(pqxx::connection &conn, int id, std::string nom, bool pegatines, rubik::type tipus) {
  /* Create a transactional object. */
  pqxx::work w(conn);

  /* Execute SQL query */
  w.exec_prepared("update", id, nom, pegatines ? "TRUE" : "FALSE", getStringEnumFromRubikType(tipus));
  w.commit();
}

// ORM #4 CRU'D', delete
void deleteRubiksCubeById() {
  // TODO
}


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
      std::cout << "#4 Eliminar cubs de rubik" << std::endl;
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
