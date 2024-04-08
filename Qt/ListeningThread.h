#ifndef LISTENINGTHREAD_H
#define LISTENINGTHREAD_H

#include <QThread>

class ListeningThread : public QThread
{
    Q_OBJECT

    public:
        ListeningThread();
};

#endif