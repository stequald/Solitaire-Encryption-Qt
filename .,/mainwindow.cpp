#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString appTitle("Solitaire Encryption");
    setWindowTitle(appTitle);

    connect( ui->keyButton, SIGNAL( clicked() ), this, SLOT( on_keyDeck() ) );
    connect( ui->shuffleButton, SIGNAL( clicked() ), this, SLOT( on_shuffle() ) );
    connect( ui->keyGenButton, SIGNAL( clicked() ), this, SLOT( on_generateKeystream() ) );
    connect( ui->goPushButton, SIGNAL( clicked() ), this, SLOT( on_go() ) );

    solitaire = new SolitaireCrypto;
    QString qtext = qStringFromSTDString(solitaire->getDeck());
    ui->deckTextEdit->setText(qtext);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_keyDeck()
{
    std::string key =  stdStringFromQString(ui->passkeyTextEdit->toPlainText());
    solitaire->on_keyDeck(key);
    QString qtext = qStringFromSTDString(solitaire->getDeck());
    ui->deckTextEdit->setText(qtext);
}

void MainWindow::on_shuffle()
{
    solitaire->on_shuffle();
    QString qtext = qStringFromSTDString(solitaire->getDeck());
    ui->deckTextEdit->setText(qtext);
}

void MainWindow::on_generateKeystream()
{
    QString msgLen = ui->msgLenLineEdit->text();
    int n = msgLen.toInt();

    if (n <= 0) return; //return if msgLen not number or > 0

    solitaire->on_generateKeystream(n);
    QString qtext = qStringFromSTDString(solitaire->getKeystream());
    ui->keystreamTextEdit->setText(qtext);

    QString qqtext = qStringFromSTDString(solitaire->getDeck());
    ui->deckTextEdit->setText(qqtext);
}

void MainWindow::on_go()
{
    std::string text =  stdStringFromQString(ui->keystreamTextEdit->toPlainText());
    solitaire->setKeystream(text);

    if (ui->encryptRadioButton->isChecked()) {
        std::string text =  stdStringFromQString(ui->cleartextTextEdit->toPlainText());
        solitaire->on_encrypt(text);
        std::string t(solitaire->getCiphertext());
        QString tt = qStringFromSTDString(t);
        ui->ciphertextTextEdit->setText(tt);
    }
    else if (ui->decryptRadioButton->isChecked()) {
        std::string text =  stdStringFromQString(ui->ciphertextTextEdit->toPlainText());
        solitaire->on_decrypt(text);
        std::string t(solitaire->getCleartext());
        QString tt = qStringFromSTDString(t);
        ui->cleartextTextEdit->setText(tt);
    }
    else {
        std::cout << "option not selected." << std::endl;
    }

}


std::string MainWindow::stdStringFromQString(QString str) {
    std::string s = str.toUtf8().constData();
    return s;
}

QString MainWindow::qStringFromSTDString(std::string str) {
    QString qstr = QString::fromStdString(str);
    return qstr;
}
