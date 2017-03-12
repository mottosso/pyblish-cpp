#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

class QPushButton;
class QListWidgetItem;
class QTextStream;

class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    void onItemChanged(QListWidgetItem* item);

signals:

public slots:

private:
    QPushButton *m_button1;
    QPushButton *m_button2;
};

#endif // WINDOW_H
