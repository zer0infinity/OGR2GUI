#ifndef OGR2OGRTHREAD_H
#define OGR2OGRTHREAD_H

#include <QThread>
#include <QString>
#include <QProgressBar>
#include <QTextEdit>

class ogr2ogrThread : public QThread
{
    Q_OBJECT
public:

protected:
    void run();
private:

};

#endif
