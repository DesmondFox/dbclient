#include "mtablemodel.h"

MTableModel::MTableModel(QObject *parent, QSqlDatabase db) : QSqlTableModel(parent, db)
{

}

QVariant MTableModel::data(const QModelIndex &idx, int role) const
{
    if (role == Qt::BackgroundRole)
    {
        if (!QSqlTableModel::data(this->index(idx.row(), 1)).toString().isEmpty())
        {
            QVariant v = QColor(200, 200, 200, 200);
            return v;
        }
    }
    if (role == Qt::DisplayRole)
    {
        return QSqlTableModel::data(idx);
    }

    return QVariant();
}
