#include "tabledb.h"


tabledb::tabledb(QWidget *parent)
    : QWidget{parent}
{
    this->ConnectDB();
    currentTableName = "mytascs";
    if(this->GetCount() == 0)
    {
        this->CreateTable();
    }
    model = new QSqlQueryModel(this);
    view = new QTableView(this);

}

tabledb::~tabledb()
{
    delete model;
    delete view;
}

bool tabledb::ConnectDB()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./tascs.db");
    if(!db.open())
    {
        qDebug() << "База не создана.\n";
        return false;
    }
    return true;
}

bool tabledb::CreateTable()
{
    QSqlQuery query;
    QString command =   "CREATE TABLE mytascs ("
                        "id INTEGER PRIMARY KEY NOT NULL,"
                        "name VARCHAR(20),"
                        "date VARCHAR(10),"
                        "progress VARCHAR(2) );";
    if(!query.exec(command))
    {
        qDebug() << "Таблица не создана.\n";
        return false;
    }
    currentTableName = "mytascs";
    return true;
}

bool tabledb::AddRow(QString name, QString date, QString progress)
{
    QSqlQuery query;
    QString str =   "INSERT INTO " + currentTableName + " (name, date, progress) "
                        "VALUES('%1', '%2', '%3');";
    QString command = str.arg(name).arg(date).arg(progress);
    if(!query.exec(command))
    {
        qDebug() << "Запись не создана.\n";
        return false;
    }
    return true;
}

void tabledb::ViewTascs()
{
    model->setQuery("SELECT * FROM " + currentTableName + " ;");
    view->setMinimumWidth(800);
    view->setMinimumHeight(500);
    view->setModel(model);
    this->show();
}

int tabledb::GetCount()
{
    QSqlQuery query;
    QString command = "SELECT COUNT (*) FROM " + currentTableName + " ;";
    query.exec(command);
    query.first();
    return query.value(0).toInt();;

}
