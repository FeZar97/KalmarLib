#ifndef KALMARKALIBRATOR_H
#define KALMARKALIBRATOR_H

#include <QObject>

class KalmarKalibrator : public QObject
{
        Q_OBJECT
    public:
        explicit KalmarKalibrator(QObject *parent = nullptr);

    signals:

};

#endif // KALMARKALIBRATOR_H