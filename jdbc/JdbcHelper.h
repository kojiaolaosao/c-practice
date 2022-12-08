//
// Created by qiwentao on 22-11-30.
//

#ifndef UNTITLED_JDBCHELPER_H
#define UNTITLED_JDBCHELPER_H
#pragma once

#include <iostream>
#include <string>
#include <functional>

//#include <mysql_driver.h>
//#include <mysql_connection.h>
#include <mysql/jdbc.h>


class JdbcHelper {
public:
    /** host: tcp://192.168.6.80:23306 自动重连*/
    JdbcHelper(const std::string &host, const std::string &username, const std::string &passwd,
               const std::string &database);

    virtual ~JdbcHelper();

    /** 连接 */
    int jdbc_connect(bool enableSSL);

    /** 断开连接 */
    int jdbc_close_connect();

    bool jdbc_is_connected();

    /** 设置是否自动提交事务 */
    int jdbc_set_auto_commit(bool auto_commit);

    /** 提交事务 */
    int jdbc_commit();

    /** 创建一个保存点 */
    sql::Savepoint *jdbc_save_point(const std::string &name);

    /** 回滚到一个保存点 */
    int jdbc_rollback_save_point(sql::Savepoint *point);

    /** 释放保存点， 必须调用(内存泄漏) */
    int jdbc_release_save_point(sql::Savepoint *point);


    /** stmt: setXXX(index, data), index是从1开始
    返回值: 受影响的行数 affected_rows , 修改没有发生变化, 会返回0  */
    int jdbc_executeUpdate(const std::string &sql,
                           std::function<void(sql::PreparedStatement *stmt)> prepCallBack,
                           std::function<void(sql::SQLException &e)> exceptionCallBack);

    /** stmt: setXXX(index, data), index是从1开始
    返回值: 0: 成功  */
    int jdbc_executeQuery(const std::string &sql,
                          std::function<void(sql::PreparedStatement *stmt)> prepCallBack,
                          std::function<void(sql::ResultSet *result)> resultCallBack,
                          std::function<void(sql::SQLException &e)> exceptionCallBack);

    void printSQLMeta(sql::ResultSetMetaData *metaData);

protected:
    void printSQLException(sql::SQLException &e, const std::string &sql);

private:
    std::string host;
    std::string username;
    std::string passwd;
    std::string database;

    bool m_enableSSL;

    sql::Driver *driver;
    sql::Connection *conn;
};

#endif //UNTITLED_JDBCHELPER_H



