#ifndef KALMARRECEIVER_H
#define KALMARRECEIVER_H

#include <QObject>
#include "KalmarReceiver_global.h"
#include "KalmarDefinitions.h"

class KalmarReceiverPrivate;

class KALMARRECEIVER_EXPORT KalmarReceiver: public QObject
{
    KalmarReceiverPrivate* receiver;

public:
    explicit KalmarReceiver(QObject* parent = nullptr);

// receiver configurations
    short getLptAddress() const;
    void setLptAddress(short lptAddress);

    KALMAR_CONFIG getConfig() const;
    void setConfig(const KALMAR_CONFIG& config);

// tract configurations
    unsigned int getCentralFreq(KALMAR_TRACT_INDEX idx) const;
    void setCentralFreq(KALMAR_TRACT_INDEX idx, unsigned int centralFreq);

    KALMAR_TRACT_IN_ATT_STATE getInAttState(KALMAR_TRACT_INDEX idx) const;
    void setInAttState(KALMAR_TRACT_INDEX idx, const KALMAR_TRACT_IN_ATT_STATE& inAttState);

    KALMAR_TRACT_HF_ATT_STATE getHfAttState(KALMAR_TRACT_INDEX idx) const;
    void setHfAttState(KALMAR_TRACT_INDEX idx, const KALMAR_TRACT_HF_ATT_STATE& hfAttState);

    KALMAR_TRACT_IF_ATT_STATE getIfAttState(KALMAR_TRACT_INDEX idx) const;
    void setIfAttState(KALMAR_TRACT_INDEX idx, const KALMAR_TRACT_IF_ATT_STATE& ifAttState);

    KALMAR_TRACT_IF_BAND getIfBand(KALMAR_TRACT_INDEX idx) const;
    void setIfBand(KALMAR_TRACT_INDEX idx, const KALMAR_TRACT_IF_BAND& ifBand);

    int getPreselectorIdx(KALMAR_TRACT_INDEX idx) const;
    void setPreselectorIdx(KALMAR_TRACT_INDEX idx, int preselectorIdx);

    KALMAR_TRACT_PRESELEKTOR_USAGE getForcePreselektorUsage(KALMAR_TRACT_INDEX idx) const;
    void setForcePreselektorUsage(KALMAR_TRACT_INDEX idx, KALMAR_TRACT_PRESELEKTOR_USAGE forcePreselektorUsage);

    // extended
    QString getTractInfo(KALMAR_TRACT_INDEX idx);
    void setParams(KALMAR_TRACT_INDEX idx,
                   unsigned int centralFreq,
                   KALMAR_TRACT_IN_ATT_STATE inAttState,
                   KALMAR_TRACT_HF_ATT_STATE hfAttState,
                   KALMAR_TRACT_IF_ATT_STATE ifAttState,
                   KALMAR_TRACT_IF_BAND ifBand);
    void setDefaultParams(KALMAR_TRACT_INDEX idx);

// kalibrator configurations
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
};

#endif // KALMARRECEIVER_H
