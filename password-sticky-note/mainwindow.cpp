
#include <QDir>
#include <QFile>
#include <QtDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"


const QString filename = "/.passwords";
const QString MainWindow::lockModeButtonText = "Lock and E&xit";
const QString MainWindow::openModeButtonText = "&Open and Unlock";


MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow( parent ),
    ui( new Ui::MainWindow )
{
    ui->setupUi( this );

    ui->lockButton->setText( lockModeButtonText );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lockButton_clicked()
{
    qDebug() << QDir::homePath();
}

void MainWindow::on_passwordLineEdit_returnPressed()
{
    if( !ui->passwordLineEdit->text().isEmpty() )
        on_lockButton_clicked();
}

void MainWindow::on_passwordLineEdit_textChanged( const QString &text )
{
    Q_UNUSED( text );
    ui->lockButton->setEnabled( !ui->passwordLineEdit->text().isEmpty() );
}

void MainWindow::_openFile()
{
    QFile file( QDir::homePath() + filename );
}
