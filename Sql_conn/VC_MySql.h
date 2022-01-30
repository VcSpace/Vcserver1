#ifndef VCSERVER_VC_MYSQL_H
#define VCSERVER_VC_MYSQL_H

#include <mysql/mysql.h>
#include <string>

namespace vc
{

    class VC_Mysql
    {
    public:
        VC_Mysql();
        ~VC_Mysql();

        void init_sql();
        void conn_sql();
        void client_login();
        void client_join();

    private:
        std::string sql_username;
        std::string sql_password;
        std::string sql_database;
        std::string sql_table;

    };
} //vc

#endif //VCSERVER_VC_MYSQL_H
