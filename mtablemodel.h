#ifndef MTABLEMODEL_H
#define MTABLEMODEL_H

#include <QObject>
#include <QSqlTableModel>
#include <QColor>

class MTableModel : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit MTableModel(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase());
    QVariant data(const QModelIndex &idx, int role) const;

signals:

public slots:
};

#endif // MTABLEMODEL_H
