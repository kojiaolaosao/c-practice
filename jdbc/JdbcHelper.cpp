//
// Created by qiwentao on 22-11-30.
//
#include "JdbcHelper.h"


JdbcHelper::JdbcHelper(const std::string &host, const std::string &username, const std::string &passwd,
                       const std::string &database) {
    this->host = host;
    this->username = username;
    this->passwd = passwd;
    this->database = database;

    this->conn = NULL;

    try {
        this->driver = get_driver_instance();
    }
    catch (sql::SQLException &e) {
        this->printSQLException(e, "get_driver_instance");
    }

    if (driver == NULL) {
        std::cout << "driver is null" << std::endl;
    }
}


JdbcHelper::~JdbcHelper() {
}


int JdbcHelper::jdbc_connect(bool enableSSL) {
    if (NULL != conn) {
        return -1;
    }
    this->m_enableSSL = enableSSL;

    try {
        sql::ConnectOptionsMap opts;
        opts["hostName"] = this->host;
        opts["userName"] = this->username;
        opts["password"] = this->passwd;
        if (enableSSL) {
            // 默认使用SSL
        } else {
            opts["OPT_SSL_MODE"] = sql::SSL_MODE_DISABLED;
        }
        opts["OPT_RECONNECT"] = sql::ConnectPropertyVal(true);

        this->conn = driver->connect(opts);

        if (NULL == conn) {
            printf("conn id null\n");
            return -2;
        }

        // 选择数据库
        sql::SQLString catalog(this->database);
        conn->setSchema(catalog);

        return 0;
    }
    catch (sql::SQLException &e) {
        this->printSQLException(e, "connect");
    }

    return -3;
}


int JdbcHelper::jdbc_close_connect() {
    if (conn) {
        conn->close();
        delete conn;
        conn = NULL;

        return 0;
    }

    return -1;
}

bool JdbcHelper::jdbc_is_connected() {
    if (conn) {
        return (conn->isClosed() == false);
    } else {
        this->jdbc_connect(m_enableSSL);
    }

    return false;
}

int JdbcHelper::jdbc_set_auto_commit(bool auto_commit) {
    if (NULL == conn || conn->isClosed()) {
        printf("jdbc conn is closed\n");
        return -1;
    }

    try {
        conn->setAutoCommit(auto_commit);
        return 0;
    }
    catch (sql::SQLException &e) {
        this->printSQLException(e, "setAutoCommit");
    }

    return -2;
}

int JdbcHelper::jdbc_commit() {
    if (NULL == conn || conn->isClosed()) {
        printf("jdbc conn is closed\n");
        return -1;
    }

    try {
        conn->commit();
        return 0;
    }
    catch (sql::SQLException &e) {
        this->printSQLException(e, "commit");
    }

    return -2;
}

sql::Savepoint *JdbcHelper::jdbc_save_point(const std::string &name) {
    if (NULL == conn || conn->isClosed()) {
        printf("jdbc conn is closed\n");
        return NULL;
    }

    try {
        sql::SQLString savePointName(name);
        return conn->setSavepoint(savePointName);
    }
    catch (sql::SQLException &e) {
        this->printSQLException(e, "setSavepoint");
    }

    return NULL;
}

int JdbcHelper::jdbc_rollback_save_point(sql::Savepoint *point) {
    if (NULL == conn || conn->isClosed()) {
        printf("jdbc conn is closed\n");
        return -1;
    }
    if (NULL == point) {
        return -2;
    }

    try {
        conn->rollback(point);
        return 0;
    }
    catch (sql::SQLException &e) {
        this->printSQLException(e, "rollback");
    }

    return -3;
}

int JdbcHelper::jdbc_release_save_point(sql::Savepoint *point) {
    if (NULL == conn || conn->isClosed()) {
        printf("jdbc conn is closed\n");
        return -1;
    }
    if (NULL == point) {
        return -2;
    }

    int rc = -1;
    try {
        conn->releaseSavepoint(point);
        rc = 0;
    }
    catch (sql::SQLException &e) {
        this->printSQLException(e, "releaseSavepoint");
        rc = -3;
    }

    delete point;

    return rc;
}

int JdbcHelper::jdbc_executeUpdate(
        const std::string &sql,
        std::function<void(sql::PreparedStatement *stmt)> prepCallBack,
        std::function<void(sql::SQLException &e)> exceptionCallBack) {
    if (NULL == conn || conn->isClosed()) {
        printf("jdbc conn is closed\n");
        return -1;
    }

    int row_affected = -1;
    sql::PreparedStatement *stmt = NULL;

    try {
        do {
            sql::SQLString sqlString(sql);
            stmt = conn->prepareStatement(sqlString);
            if (NULL == stmt) {
                row_affected = -2;
                break;
            }

            sql::ParameterMetaData *paramMetaData = stmt->getParameterMetaData();
            if (paramMetaData) {
                if (paramMetaData->getParameterCount() > 0) {
                    if (prepCallBack) {
                        prepCallBack(stmt);
                    }
                }
            }

            row_affected = stmt->executeUpdate(); // 插入数据
        } while (false);
    }
    catch (sql::SQLException &e) {
        this->printSQLException(e, sql);

        if (exceptionCallBack) {
            exceptionCallBack(e);
        }
    }

    if (stmt) {
        try {
            stmt->close();
        }
        catch (sql::SQLException &e) {
            this->printSQLException(e, "close stmt res");
        }
        delete stmt;
    }

    return row_affected;
}


int JdbcHelper::jdbc_executeQuery(
        const std::string &sql,
        std::function<void(sql::PreparedStatement *stmt)> prepCallBack,
        std::function<void(sql::ResultSet *result)> resultCallBack,
        std::function<void(sql::SQLException &e)> exceptionCallBack) {
    if (NULL == conn || conn->isClosed()) {
        printf("jdbc conn is closed\n");
        return -1;
    }

    int rc = -1;
    sql::PreparedStatement *prep_stmt = NULL;
    sql::ResultSet *res = NULL;

    try {
        do {
            // std::cout << "SQL: " << sql << std::endl;
            sql::SQLString sqlString(sql);

            prep_stmt = conn->prepareStatement(sqlString);
            if (NULL == prep_stmt) {
                rc = -2;
                break;
            }

            if (prepCallBack) {
                sql::ParameterMetaData *paramMetaData = prep_stmt->getParameterMetaData();
                if (paramMetaData && paramMetaData->getParameterCount() > 0) {
                    prepCallBack(prep_stmt);
                }
            }

            res = prep_stmt->executeQuery(); // 查询数据
            if (NULL == res) {
                rc = -3;
                break;
            }

            if (resultCallBack) {
                sql::ResultSetMetaData *metaData = prep_stmt->getMetaData();
                if (metaData && metaData->getColumnCount() > 0) {
                    // printSQLMeta(metaData);
                    resultCallBack(res);
                }
            }

            rc = 0;
        } while (false);
    }
    catch (sql::SQLException &e) {
        // if (e.getErrorCode() == CR_SERVER_LOST) { } // in errmsg.h of mysqlclient
        printSQLException(e, sql);

        if (exceptionCallBack) {
            exceptionCallBack(e);
        }
    }

    if (prep_stmt) {
        try {
            prep_stmt->close();
        }
        catch (sql::SQLException &e) {
            this->printSQLException(e, "close stmt");
        }
        delete prep_stmt;
    }
    if (res) {
        try {
            res->close();
        }
        catch (sql::SQLException &e) {
            this->printSQLException(e, "close stmt res");
        }
        delete res;
    }

    return rc;
}

void JdbcHelper::printSQLException(sql::SQLException &e, const std::string &sql) {
    std::cout << "message: " << e.what() << std::endl;
    std::cout << "code: " << e.getErrorCode() << std::endl;
    std::cout << "state: " << e.getSQLState() << std::endl;
    std::cout << "sql: " << sql << std::endl;
}

void JdbcHelper::printSQLMeta(sql::ResultSetMetaData *metaData) {
    int columnCount = metaData->getColumnCount();
    for (int i = 1; i <= columnCount; i++) {
        std::cout << "column: " << i << ", name: " << metaData->getColumnName(i) << ", type: "
                  << metaData->getColumnTypeName(i) << std::endl;
    }
}