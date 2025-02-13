#include "orm.hpp"

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
