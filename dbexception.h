#ifndef DBEXCEPTION_H
#define DBEXCEPTION_H

#include <QObject>
#include <QException>

class DBException : public QException
{
public:
    explicit DBException(const QString &err);
    QString what();

private:
    QString error;
signals:

public slots:
};

#endif // DBEXCEPTION_H
