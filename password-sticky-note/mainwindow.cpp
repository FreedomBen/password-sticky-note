
#include <QDir>
#include <QFile>
#include <QtDebug>

#include <openssl/aes.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"


const QString MainWindow::filename = "/.passwords";
const QString MainWindow::lockModeButtonText = "Lock and E&xit";
const QString MainWindow::openModeButtonText = "&Open and Unlock";


MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow( parent ),
    ui( new Ui::MainWindow )
{
    ui->setupUi( this );

    ui->lockButton->setText( openModeButtonText );
    ui->textEdit->setText( "The password file is currently locked.  Please enter the password to unlock it" );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lockButton_clicked()
{
    if( ui->lockButton->text() == openModeButtonText )
    {
        if( !_openFile() )
        {
            ui->textEdit->setText( "There was a problem unlocking the password file.  Please double check the password." );
        }
    }
    else
    {

    }
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

bool MainWindow::_openFile()
{
    QFile file( QDir::homePath() + filename );

    if( !file.exists() )
    {
        return true;
    }

    if( !file.open( QIODevice::ReadOnly ) )
    {
        ui->textEdit->setText( "Error reading file.  Please verify correct permissions" );
        return false;
    }

    QByteArray enc = file.readAll();

    QString dec = _decrypt( enc );

    if( !dec.isEmpty() )
        ui->textEdit->setText( dec );

    return !dec.isEmpty();
}

static const unsigned char key[] = {
    0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
    0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
};

QByteArray MainWindow::_encrypt( const QString &plaintext )
{
    unsigned char text[ plaintext.length() ];

    for( int i=0; i<plaintext.length(); ++i )
    {
        text[i] = plaintext.at( i ).toAscii();
    }

    int enc_len = plaintext.length() * 2 * sizeof( char );
    unsigned char * enc_out = static_cast<unsigned char *>( malloc( enc_len ) );
    memset( enc_out, 0, enc_len );

    AES_KEY enc_key;

    AES_set_encrypt_key( key, 128, &enc_key );
    AES_encrypt( text, enc_out, &enc_key );

    int lastchar = 0;
    for( int i = enc_len-2; i>=0; --i )
    {
        if( enc_out[i] != 0 )
        {
            lastchar = i+1;
            break;
        }
    }

    QByteArray retval;

    for( int i=0; i<lastchar; ++i )
        retval.append( enc_out[i] );

    Q_ASSERT( lastchar != 0 );
    Q_ASSERT( lastchar < enc_len );

    free( enc_out );

    return retval;
}

QString MainWindow::_decrypt( const QByteArray &cipherText )
{
    unsigned char enc[cipherText.length()];

    for( int i=0; i<cipherText.length(); ++i )
        enc[i] = cipherText.at( i );

    int dec_len = cipherText.count() * 2 * sizeof( char );
    unsigned char * dec_out = static_cast<unsigned char *>( malloc( dec_len ) );
    memset( dec_out, 0, dec_len );

    AES_KEY dec_key;

    AES_set_decrypt_key( key, 128, &dec_key );
    AES_decrypt( enc, dec_out, &dec_key );

    QString retval( reinterpret_cast<char*>( dec_out ) );
    free( dec_out );
    return retval;
}
