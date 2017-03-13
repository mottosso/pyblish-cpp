#ifndef MODEL_H
#define MODEL_H

#include <QAbstractListModel>


class Model : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ItemRoles {
        NameRole = Qt::UserRole + 1,
        FamilyRole,
        TypeRole,
        IsProcessingRole,
        IsToggledRole
    };

    explicit Model(QObject *parent = 0);

    void addItem(const QJsonObject &item);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QString roleName(int role) const;

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
	QList<QJsonObject> m_items;

};

#endif // MODEL_H
