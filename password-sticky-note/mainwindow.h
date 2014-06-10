#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:

        explicit MainWindow( QWidget *parent = 0 );
        ~MainWindow();

    private slots:

        void on_lockButton_clicked();

        void on_passwordLineEdit_returnPressed();
        void on_passwordLineEdit_textChanged( const QString &text );

        void on_showPasswordCheckBox_stateChanged( int state );

    private:

        static const QString filename;
        static const QString lockModeButtonText;
        static const QString openModeButtonText;
        static const QString emptyFileText;

        QString _filename();
        bool _saveToFile( const QString &contents );
        bool _openFile();
        QByteArray _password();

        QByteArray _encrypt( const QString &plaintext );
        QString _decrypt( const QByteArray &cipherText );

        Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
