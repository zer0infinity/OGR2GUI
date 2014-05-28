#ifndef OGR2OGRTHREAD_H
#define OGR2OGRTHREAD_H

#include <QThread>

class ogr2ogrThread : public QThread
{
    Q_OBJECT
public:

protected:
    void run();
private:

};

#endif
