#include <iostream>
#include <pqxx/pqxx>

using namespace std;
using namespace pqxx;

void insertRubik(char * sql, connection& C) {

    /* Create SQL statement */
      sql = "INSERT INTO rubiks (id, nom) "  \
         "VALUES (1, '333');";

      /* Create a transactional object. */
      work W(C);

      /* Execute SQL query */
      W.exec( sql );
      W.commit();
      cout << "Records created successfully" << endl;

}

void selectRubik(char * sql, connection& C) {
    /* Create SQL statement */
      sql = "SELECT * from rubiks";

      /* Create a non-transactional object. */
      nontransaction N(C);

      /* Execute SQL query */
      result R( N.exec( sql ));

      /* List down all the records */
      for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
         cout << "ID = " << c[0].as<int>() << endl;
         cout << "nom = " << c[1].as<string>() << endl;
      }
      cout << "Operation done successfully" << endl;
}

void updateRubik(char * sql, connection& C) {
    // TODO
}

void deleteRubik(char * sql, connection& C) {
    // TODO
}

int main(int argc, char* argv[]) {
   char * sql;

   try {
      connection C("dbname = puzzles user = postgres password = eric");
      if (C.is_open()) {
         cout << "Opened database successfully: " << C.dbname() << endl;
      } else {
         cout << "Can't open database" << endl;
         return 1;
      }

      int opcioUsuari = 0;
      do {
        cout << "\n\nBenvingut a la biblioteca de cubs de rubik!" << endl;
        cout << "#1 Inserir un cub de rubik" << endl;
        cout << "#2 Llegir els cubs de rubik" << endl;
        cout << "#3 Actualitzar els cubs de rubik" << endl;
        cout << "#4 Eliminar cubs de rubik" << endl;
        cout << "#5 Sortir" << endl;

        cout << "\nQuina opció vols fer? " << flush;
        cin >> opcioUsuari;

        switch(opcioUsuari) {
            case 1:
                insertRubik(sql, C);
                break;
            case 2:
                selectRubik(sql, C);
                break;
            case 3:
                updateRubik(sql, C);
                break;
            case 4:
                deleteRubik(sql, C);
                break;
            case 5:
                cout << "Agur!" << endl;

          }
      }
      while (opcioUsuari != 5);


   } catch (const std::exception &e) {
      cerr << e.what() << std::endl;
      return 1;
   }

   return 0;
}
