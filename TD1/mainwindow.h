#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <stdlib.h>
#include <time.h>

#define BUTTON_NBR 10

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void OnClickedPushButton();
    void showCode();
    void validNombre(int nbr);
    bool codeValide();
    void melangeTab(int * tab, int taille);
    void indice(int nbr);
    ~MainWindow();
private:
    QLabel *m_pLabel;
    QPushButton *m_pButtons[BUTTON_NBR];
    QPushButton *m_pButtonOpen;
    int tabButton[BUTTON_NBR];
    // int const code [4] = {2, 4, 2, 9};
    int code[4];
    int counterValid = 0;
};

#endif // MAINWINDOW_H
