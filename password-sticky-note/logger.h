#ifndef __Logger_h__
#define __Logger_h__

#include <QDebug>
#include <QRegExp>
#include <QString>
#include <typeinfo>

// These chars are used to flag custom qDebug messages. IE qNotify() prepends
// the normal qDebug message with a non-printable char '\x10'
// See LogMessageHandler::logString()
#define __NOTIFY '\x10'
#define __DEBUG_BLUE '\x11' 
#define __DEBUG_DARK_MAGENTA '\x12'
#define __DEBUG_DARK_GREEN '\x13'

#define qNotify() qDebug() << __NOTIFY
#define qDebugBlue() qDebug() << __DEBUG_BLUE               // print debug statements in blue
#define qDebugMagenta() qDebug() << __DEBUG_DARK_MAGENTA    // print debug statements in dark magenta
#define qDebugGreen() qDebug() << __DEBUG_DARK_GREEN        // print debug statements in dark green

#define __CLASS__ qPrintable(QString(typeid(*this).name()).remove(QRegExp("^\\d+")))

#ifdef Q_OS_WIN32
#  define __CLASS_FUNCTION__ __FUNCTION__
#else
#  define __CLASS_FUNCTION__ qPrintable(QString("%1::%2") \
                                  .arg(__CLASS__)         \
                                  .arg(__FUNCTION__))
#endif


#endif // __Logger_h__
