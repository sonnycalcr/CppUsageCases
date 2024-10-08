#include "main.h"
#include <sqlite3.h>
#include <string>

int selectData(const char *filename, std::string sql) {
  sqlite3 *db;
  sqlite3_stmt *stmt;

  // std::string sql = "SELECT * FROM xiaoheulpbtbl where length(key) = 6 limit 100;";

  int exit = sqlite3_open(filename, &db);

  if (exit) {
    std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
    return exit;
  }

  exit = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);

  if (exit != SQLITE_OK) {
    std::cerr << "Error selecting data: " << sqlite3_errmsg(db) << std::endl;
    return exit;
  }

  std::cout << "key" << " \t " << "value" << " \t " << "weight" << std::endl;
  // std::string res = "";
  while (sqlite3_step(stmt) == SQLITE_ROW) {
    std::cout << sqlite3_column_text(stmt, 0) << " \t " << sqlite3_column_text(stmt, 1) << " \t " << sqlite3_column_int(stmt, 2) << std::endl;
    // res += std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)));
  }
  // std::cout << '"' << res << '"' << "," << std::endl;

  sqlite3_finalize(stmt);
  sqlite3_close(db);
  return 0;
}

int main(int argc, char *argv[]) {
  std::string db_path = "/home/sonnycalcr/EDisk/PyCodes/IMECodes/FanyDictForIME/makecikudb/xnheulpb/makedb/out/flyciku.db";
  // char a = 'a';
  // for (int i = 0; i < 26; i++) {
  //   a = 'a' + i;
  //   std::string sql = std::string("select * from xiaoheulpbtbl where key  like \"") + a + "_\" order by weight desc limit 32";
  //   selectData(db_path.c_str(), sql);
  // }
  std::string sql = "select * from xiaoheulpbtbl where key  like \"n_u_\" order by weight desc limit 32";
  selectData(db_path.c_str(), sql);
  return 0;
}
