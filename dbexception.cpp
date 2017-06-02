#include "dbexception.h"

DBException::DBException(const QString &err)
    : error(err)
{

}

QString DBException::what()
{
    /// TODO: switch-case using
    return error;
}
