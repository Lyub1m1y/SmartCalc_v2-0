#ifndef VIEW_H
#define VIEW_H

#include <QDebug>
#include <QDesktopServices>
#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <QUrl>
#include <QVector>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class View; }
QT_END_NAMESPACE

class View : public QMainWindow
{
    Q_OBJECT

public:
    View(QWidget *parent = nullptr);
    ~View();

private:
    Ui::View *ui;
};
#endif // VIEW_H
