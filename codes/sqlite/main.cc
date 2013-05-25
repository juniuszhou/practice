#include "sqlite3.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;
const string db_name = "email";

const string account_table_name = "account";
const string account_table_structure = "( \
             account_id integer \
            ,server_id integer\
            ,user_name text NOT NULL \
            ,password text NOT NULL)";

class sqliteWrapper
{
public:
    sqliteWrapper();
    ~sqliteWrapper();
    int select();
    int insert(int i);
    int update();
    int remove();
    int createTable(string name, string structure);
    int connect(string dbName);
private:
    sqlite3 * mPDb;
    string mDbName;
};
int sqliteWrapper::connect(string dbName)
{
    mDbName = dbName;
    char * errMsg;
    int rc = sqlite3_open(dbName.c_str(),&mPDb);
    cout << "connect result" << rc << endl;
    if (rc != 0)
        cout << errMsg << endl;
    return rc;
}
int sqliteWrapper::createTable(string name, string structure)
{
    char * errMsg;
    ostringstream     queryStr ;
    queryStr << "CREATE TABLE " << account_table_name;
        queryStr<< account_table_structure <<";";
               
    int rc = sqlite3_exec(mPDb,
               queryStr.str().c_str(),
               NULL,
               NULL,
               &errMsg);
    if (rc != 0)
        cout << errMsg << endl;
    cout << "createTable result " << rc << endl;

}
sqliteWrapper::sqliteWrapper(){}
sqliteWrapper::~sqliteWrapper(){
    sqlite3_close(mPDb);
    }
int sqliteWrapper::select()
{
    ostringstream     queryStr ;
    sqlite3_stmt * pStmt = NULL;
    queryStr << "select * from " << account_table_name  << ";";
    int rc = sqlite3_prepare(mPDb,
               queryStr.str().c_str(),
               queryStr.str().size(),
               &pStmt,NULL);
    cout << "sqlite3_prepare result " << rc << endl;
    rc = sqlite3_step(pStmt);//each step will return a row
    cout << "sqlite3_step result " << rc << endl;
    rc = sqlite3_column_int(pStmt, 1);
    cout << "sqlite3_column_int result " << rc << endl;
    cout << sqlite3_column_text(pStmt, 3) << endl;
    rc = sqlite3_step(pStmt);
    cout << "sqlite3_step result " << rc << endl;
    rc = sqlite3_column_int(pStmt, 1);
    cout << "sqlite3_column_int result " << rc << endl;
    cout << sqlite3_column_text(pStmt, 3) << endl;
    rc = sqlite3_step(pStmt);
    cout << "sqlite3_step result " << rc << endl;
    sqlite3_finalize(pStmt);
}

int sqliteWrapper::insert(int i)
{
char * errMsg;
    ostringstream     queryStr ;
    queryStr << "insert into " << account_table_name;
    queryStr << " values (" << i << "," << i <<",'junius','Junius');";
               
    int rc = sqlite3_exec(mPDb,
               queryStr.str().c_str(),
               NULL,
               NULL,
               &errMsg);
    if (rc != 0)
        cout << errMsg << endl;
    cout << "insert result " << rc << endl;
}
int sqliteWrapper::update(){}
int sqliteWrapper::remove(){}

int main()
{

    sqliteWrapper sql;
    sql.connect(db_name);
    //sql.createTable(account_table_name,account_table_structure);
    //sql.insert(3);
    sql.select();

    return 0;
}
