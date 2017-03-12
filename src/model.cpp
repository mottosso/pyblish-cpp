#include "model.h"

Plugin::Plugin(const QString &name, const QString &family)
    : m_name(name), m_family(family)
{
}

QString Plugin::name() const
{
    return m_name;
}

QString Plugin::family() const
{
    return m_family;
}

Model::Model(QObject *parent)
    : QAbstractListModel(parent)
{
}

void Model::addPlugin(const Plugin &plugin)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_plugins << plugin;
    endInsertRows();
}

int Model::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_plugins.count();
}

QVariant Model::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_plugins.count())
    {
        return QVariant();
    }

    const Plugin &plugin = m_plugins[index.row()];

    if (role == NameRole)
    {
        return plugin.name();
    }
    else if (role == FamilyRole)
    {
        return plugin.family();
    }

    return QVariant();
}

QHash<int, QByteArray> Model::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[FamilyRole] = "family";
    return roles;
}
