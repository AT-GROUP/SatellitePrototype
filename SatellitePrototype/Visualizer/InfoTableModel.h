#ifndef INFOTABLEMODEL_H
#define INFOTABLEMODEL_H

#include <QAbstractTableModel>
#include <QVariant>

class InfoTableModel : public QAbstractTableModel
{
    Q_OBJECT
    public:
        explicit InfoTableModel(QString n, QObject *parent = 0);
        void updateData(std::tuple<int, QString, QString> incomingData);
        QMap<int, QPair<QString, QString>> *pDataStorage;
    private:

        int rowCount(const QModelIndex &parent) const;
        int columnCount(const QModelIndex &parent) const;
        QVariant data(const QModelIndex &index, int role) const;

};

#endif // INFOTABLEMODEL_H
