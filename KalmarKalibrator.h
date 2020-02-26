#ifndef KALMARKALIBRATOR_H
#define KALMARKALIBRATOR_H

#include <QObject>
#include "KalmarDefinitions.h"

#define     KALMAR_KALIBRATOR_MIN_MOD_FREQ         1000
#define     KALMAR_KALIBRATOR_MAX_MOD_FREQ         50000
#define     KALMAR_KALIBRATOR_ATT_STEP             2

class KalmarKalibrator : public QObject
{
    Q_OBJECT

    KALMAR_KALIBRATOR_MOD_SIGNAL m_modSignalType{KALMAR_KALIBRATOR_DEFAULT_SIGNAL_TYPE};
    int                          m_modulationFreq{KALMAR_KALIBRATOR_DEFAULT_MOD_FREQ};
    KALMAR_KALIBRATOR_ATT_STATE  m_attState{KALMAR_KALIBRATOR_DEFAULT_ATT_STATE};
    KALMAR_KALIBRATOR_OUT_TYPE   m_outType{KALMAR_KALIBRATOR_DEFAULT_OUT};
    KALMAR_KALIBRATOR_STATE      m_workState{KALMAR_KALIBRATOR_DEFAULT_WORK_STATE};

public:
    explicit KalmarKalibrator(QObject *parent = nullptr);

    KALMAR_KALIBRATOR_MOD_SIGNAL getModSignalType() const;
    void setModSignalType(const KALMAR_KALIBRATOR_MOD_SIGNAL& modSignalType);

    int getModulationFreq() const;
    void setModulationFreq(int modulationFreq);

    KALMAR_KALIBRATOR_ATT_STATE getAttState() const;
    void setAttState(const KALMAR_KALIBRATOR_ATT_STATE& attState);

    KALMAR_KALIBRATOR_OUT_TYPE getOutType() const;
    void setOutType(const KALMAR_KALIBRATOR_OUT_TYPE& outType);

    KALMAR_KALIBRATOR_STATE getWorkState() const;
    void setWorkState(const KALMAR_KALIBRATOR_STATE& workState);

signals:
    void sendKalibratorModulationFreqToPort();
    void sendKalibratorAttStateToPort();
    void sendKalibratorWorkStateToPort();
    void sendKalibratorSignalTypeToPort(KALMAR_TRACT_INDEX supportTractIdx);
};

#endif // KALMARKALIBRATOR_H
