#include "mainwindow.h"
#include <QMessageBox>
#include <QGridLayout>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    int i, j, counter = 0;
    for(i = 0; i < 4; i++)
        code[i] = (int) rand()%10;
    showCode();

    QGridLayout * mainLayout = new QGridLayout();
    m_pTextEdit = new QTextEdit();
    //lecture du fichier de savegarde pour le mettre dans le TextEdit
    QFile file("save.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream flux (&file);

    m_pTextEdit->setText(flux.readAll());
    mainLayout->addWidget(m_pTextEdit, 0, 0, 1, 5);

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
    for(j = 2; j < 4; j++)
    {
        for(i = 0; i < 5; i++)
        {
            connect(m_pButtons[counter], &QPushButton::clicked, this, &MainWindow::OnClickedPushButton);
            mainLayout->addWidget(m_pButtons[counter], j, i);
            counter++;
        }
    }

    m_pButtonCipher = new QPushButton("Chiffrer", this);
    m_pButtonCipher->setStyleSheet("background-color: white;");

    m_pButtonDecipher = new QPushButton("Dechiffrer", this);
    m_pButtonDecipher->setStyleSheet("background-color: white;");

    mainLayout->addWidget(m_pButtonCipher, 5, 0, 1, 1);
    connect(m_pButtonCipher, &QPushButton::clicked, this, &MainWindow::OnClickedPushButton);

    mainLayout->addWidget(m_pButtonDecipher, 5, 1, 1, 1);
    connect(m_pButtonDecipher, &QPushButton::clicked, this, &MainWindow::OnClickedPushButton);

    m_pButtonSave = new QPushButton("Sauvegarder", this);
    m_pButtonSave->setStyleSheet("background-color: white;");

    m_pButtonOpen = new QPushButton("Ouvrir", this);
    m_pButtonOpen->setStyleSheet("background-color: white;");

    mainLayout->addWidget(m_pButtonSave, 5, 3, 1, 1);
    connect(m_pButtonSave, &QPushButton::clicked, this, &MainWindow::SaveFile);

    mainLayout->addWidget(m_pButtonOpen, 5, 4, 1, 1);
    connect(m_pButtonOpen, &QPushButton::clicked, this, &MainWindow::OpenFile);

    this->setCentralWidget(new QWidget(this));
    this->centralWidget()->setLayout(mainLayout);
}

void MainWindow::OnClickedPushButton()
{
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
        if(clickedButton->text() != "Chiffrer" && clickedButton->text() != "Dechiffrer") // LES CHIFFRES
        {
            bool ok = false;
            int nombre = clickedButton->text().toInt(&ok, 10);
            qDebug() << "nombre tapé: " << nombre;
            validNombre(nombre);

            if(codeValide())
            {
                m_pButtonDecipher->setStyleSheet("background-color: green;");
            }
            else
            {
                m_pButtonDecipher->setStyleSheet("background-color: white;");
            }
        }

        if(clickedButton->text() == "Chiffrer") // LE BOUTON CHIFFRER
        {
            cipherText();
        }
        if(clickedButton->text() == "Dechiffrer") // LE BOUTON DECHIFFER
        {
            if(codeValide())
            {
                decipherText();
            }
        }
}

void MainWindow::SaveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Sauvegarde", "", "Texte chiffré (*.ch);; Texte déchiffré (*.dech)");
    qDebug() << fileName;
    QFile file (fileName);
    if (!file.open(QIODevice::WriteOnly |QIODevice::Text))
    {
        qDebug() << "Echec!";
    }
    else
    {
        QTextStream flux(&file);
        flux << m_pTextEdit->toPlainText() << endl;
        file.close();
    }
}
void MainWindow::OpenFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Ouvrir", "", "Texte chiffré (*.ch);; Texte déchiffré (*.dech)");
    qDebug() << fileName;
    QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream flux (&file);
    m_pTextEdit->setText(flux.readAll());
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
    qDebug() << "counterValid = " << counterValid;
}

bool MainWindow::codeValide()
{
    if(counterValid == 4)
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

void MainWindow::cipherText()
{
    QString str = m_pTextEdit->toPlainText();
    qDebug() << "texte avant cryptage:" << str.toStdString().c_str();
    qDebug() << "de taille :" << str.length();
    QByteArray strQBA = str.toLatin1();
    int i;
    int ascii;
    QString strSortie = "";
    for(i = 0; i < str.length(); i++)
    {
        ascii = (int) strQBA[i];
        qDebug() << "ascii: " << ascii;
        if(ascii < 100)
        {
            strSortie.append(QString::number(ascii));
            strSortie.append(" ");
        }
        else if(ascii >= 100)
        {
            strSortie += strQBA[i];
            strSortie.append(" ");
        }

    }
    qDebug() << "texte apres cryptage:" << strSortie;
    m_pTextEdit->setText(strSortie);
}

void MainWindow::decipherText()
{
    QString strEntree = m_pTextEdit->toPlainText();
    qDebug() << strEntree.toStdString().c_str();
    int i;
    QString mot = "";
    QString strSortie = "";
    QChar c;
    int ascii;
    bool ok = false;
    for(i = 0; i < strEntree.length(); i++)
    {
        while (strEntree[i] != ' ' && i < strEntree.length()) {
            mot += strEntree[i];
            i++;
        }
        qDebug() << "mot:" << mot.toStdString().c_str();
        qDebug() << "est un nombre:" << isNumber(mot);
        if (isNumber(mot))
        {
            ok = false;
            ascii = mot.toInt(&ok, 10);
            qDebug() << "nombre:" << ascii;
            c = *(new QChar(ascii));
            qDebug() << "caratere induit" << c;
            strSortie += c;
        }
        else
            strSortie.append(mot);
        mot = "";
    }
    m_pTextEdit->setText(strSortie);
}

bool MainWindow::isNumber(QString mot)
{
    bool number = true;
    int i;
    for(i = 0; i < mot.length(); i++)
    {
        if(mot[i] < 48 || mot[i] > 57)
            number = false;
    }
    return number;
}

MainWindow::~MainWindow()
{
    QFile file ("save.txt");
    if (!file.open(QIODevice::WriteOnly |QIODevice::Text))
    {
        qDebug() << "Echec!";
    }
    else
    {
        QTextStream flux(&file);
        flux << m_pTextEdit->toPlainText() << endl;
        file.close();
    }
}
