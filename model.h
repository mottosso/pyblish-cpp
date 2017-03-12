#ifndef MODEL_H
#define MODEL_H

#include <QAbstractListModel>

class Plugin
{
public:
	Plugin(const QString &name, const QString &family);

	QString name() const;
	QString family() const;

private:
	QString m_name;
	QString m_family;
};

class Model : public QAbstractListModel
{
    Q_OBJECT
public:
    enum PluginRoles {
        NameRole = Qt::UserRole + 1,
        FamilyRole
    };

    explicit Model(QObject *parent = 0);

    void addPlugin(const Plugin &plugin);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
	QList<Plugin> m_plugins;

};

#endif // MODEL_H
