#include "mainwindow.h"
#include <QMessageBox>
#include <QGridLayout>
#include <QString>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    int i, j, counter = 0;
    for(i = 0; i < 4; i++)
        code[i] = (int) rand()%10;
    showCode();


    QGridLayout * mainLayout = new QGridLayout;
    for(i = 0; i < BUTTON_NBR; i++)
    {
        tabButton[i] = i;
    }
    melangeTab(tabButton, BUTTON_NBR);
    for(i = 0; i < BUTTON_NBR; i++)
    {
        m_pButtons[i] = new QPushButton(QString::number(tabButton[i]), this);
        m_pButtons[i]->setStyleSheet("background-color: white;");
        counter++;
    }

    counter = 0;
    for(j = 0; j < 2; j++)
    {
        for(i = 0; i < 5; i++)
        {
            connect(m_pButtons[counter], &QPushButton::clicked, this, &MainWindow::OnClickedPushButton);
            mainLayout->addWidget(m_pButtons[counter], j, i);
            counter++;
        }
    }

    m_pButtonOpen = new QPushButton("Ouvrir", this);
    m_pButtonOpen->setStyleSheet("background-color: white;");
    m_pButtonOpen->setEnabled(false);
    mainLayout->addWidget(m_pButtonOpen, 3, 0, 1, 5);
    connect(m_pButtons[counter], &QPushButton::clicked, this, &MainWindow::OnClickedPushButton);

    this->setCentralWidget(new QWidget(this));
    this->centralWidget()->setLayout(mainLayout);
}

void MainWindow::OnClickedPushButton()
{
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
        if(clickedButton->text() != "Ouvrir") // LES CHIFFRES
        {
            bool ok = false;
            int nombre = clickedButton->text().toInt(&ok, 10);
            // qDebug() << "nombre tapé: " << nombre;
            indice(nombre);
            validNombre(nombre);

            if(codeValide())
            {
                m_pButtonOpen->setStyleSheet("background-color: green;");
                m_pButtonOpen->setEnabled(true);
            }
            if (!codeValide())
            {
                m_pButtonOpen->setStyleSheet("background-color: white;");
                m_pButtonOpen->setEnabled(false);
            }
        }
        if(clickedButton->text() == "Ouvrir") // LE BOUTON OUVRIR
        {
            QMessageBox::information(this, "Message secret", "Voici le message secret:\n44 69 65 75 20 6c 65 20 6d c3 a9 63 68 61 6e 6f");
            close();
        }
}

void MainWindow::showCode()
{
    int i;
    std::string str = "\nCode du coffre fort: ";
    for(i = 0; i < 4; i++)
        str += std::to_string(code[i]) + " ";
    qDebug() <<  str.c_str();
}

void MainWindow::validNombre(int nbr)
{
    if(code[counterValid] == nbr)
        counterValid++;
    else
        counterValid = 0;
    // qDebug() << "counterValid = " << counterValid;
}

bool MainWindow::codeValide()
{
    if(counterValid >= 4)
        return true;
    else
        return false;
}

void MainWindow::melangeTab(int * tab, int taille)
{
    int i, temp, indice;
    for (i = 0; i < taille; ++i)
    {
        indice = (int) rand()%taille;
        temp = tab[i];
        tab[i] = tab[indice];
        tab[indice] = temp;
    }
}

void MainWindow::indice(int nbr)
{
    std::string str = "";
    if(nbr > code[counterValid])
        str = "Trop grand !";
    else if(nbr < code[counterValid])
        str = "Trop petit !";
    else
    {
        if ((4-1 - counterValid) != 0)
            str = "Bon numéro ! Plus que " + std::to_string(4-1 - counterValid) + " à trouver !";
        else
            str = "Bon numéro ! Vous allez pouvoir ouvrir le coffre !";
    }
    qDebug() << str.c_str();
}

MainWindow::~MainWindow()
{
}
