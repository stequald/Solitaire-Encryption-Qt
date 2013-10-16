#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "core/solitairecrypto.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    SolitaireCrypto* solitaire;
    std::string stdStringFromQString(QString str);
    QString qStringFromSTDString(std::string str);

public slots:
    void on_keyDeck();
    void on_shuffle();
    void on_generateKeystream();
    void on_go();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
