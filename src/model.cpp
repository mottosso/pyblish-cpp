#include <QJsonObject>
#include <iostream>
#include "model.h"


Model::Model(QObject *parent)
    : QAbstractListModel(parent)
{
}

void Model::addItem(const QJsonObject &item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_items << item;
    endInsertRows();
}

int Model::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_items.count();
}

QVariant Model::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_items.count())
    {
        return QVariant();
    }

    const QJsonObject &item = m_items[index.row()];

    QString key = roleName(role);
    return item.value(key).toString();
}

QString Model::roleName(int role) const
{
    return roleNames().value(role);
}

QHash<int, QByteArray> Model::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[NameRole] = "name";
    roles[FamilyRole] = "family";
    roles[TypeRole] = "type";
    roles[IsProcessingRole] = "isProcessing";
    roles[IsToggledRole] = "isToggled";

    return roles;
}
