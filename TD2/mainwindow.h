#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <stdlib.h>
#include <time.h>
#include <QTextEdit>

#define BUTTON_NBR 10

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void OnClickedPushButton();
    void SaveFile();
    void OpenFile();
    void showCode();
    void validNombre(int nbr);
    bool codeValide();
    void melangeTab(int * tab, int taille);
    void decipherText();
    void cipherText();
    bool isNumber(QString mot);

    ~MainWindow();
private:
    QLabel *m_pLabel;
    QPushButton *m_pButtons[BUTTON_NBR];
    QPushButton *m_pButtonCipher;
    QPushButton *m_pButtonDecipher;
    QPushButton *m_pButtonSave;
    QPushButton *m_pButtonOpen;
    QTextEdit *m_pTextEdit ;

    int tabButton[BUTTON_NBR];
    // int const code [4] = {0, 0, 0, 0};
    int code[4];
    int counterValid = 0;
};

#endif // MAINWINDOW_H
