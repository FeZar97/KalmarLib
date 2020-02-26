#ifndef KALMARTRACT_H
#define KALMARTRACT_H

#include <QObject>
#include "KalmarDefinitions.h"

#define     KALMAR_TRACT_MAX_FREQ                      31999999
#define     KALMAR_TRACT_MIN_FREQ                      150000

#define     KALMAR_TRACT_MIN_IN_ATT_IDX                IN_ATT_OFF
#define     KALMAR_TRACT_MAX_IN_ATT_IDX                IN_ATT_ON

#define     KALMAR_TRACT_HF_ATT_STEP                   6
#define     KALMAR_TRACT_MIN_HF_ATT_IDX                HF_ATT_OFF / KALMAR_TRACT_HF_ATT_STEP
#define     KALMAR_TRACT_MAX_HF_ATT_IDX                HF_ATT_42DB / KALMAR_TRACT_HF_ATT_STEP

#define     KALMAR_TRACT_IF_ATT_STEP                   2
#define     KALMAR_TRACT_MIN_IF_ATT_IDX                IF_ATT_OFF / KALMAR_TRACT_IF_ATT_STEP
#define     KALMAR_TRACT_MAX_IF_ATT_IDX                IF_ATT_30DB / KALMAR_TRACT_IF_ATT_STEP

#define     KALMAR_TRACT_MIN_IF_BAND_IDX               FIRST_BAND
#define     KALMAR_TRACT_MAX_IF_BAND_IDX               FOURTH_BAND

class KalmarTract : public QObject
{
    Q_OBJECT

    KALMAR_TRACT_INDEX m_tractIdx;
    KALMAR_TRACT_USAGE m_tractUsage;

    unsigned int m_centralFreq{KALMAR_TRACT_DEFAULT_FREQ};
    KALMAR_TRACT_IN_ATT_STATE m_inAttState{KALMAR_TRACT_DEFAULT_IN_ATT_STATE};
    KALMAR_TRACT_HF_ATT_STATE m_hfAttState{KALMAR_TRACT_DEFAULT_HF_ATT_STATE};
    KALMAR_TRACT_IF_ATT_STATE m_ifAttState{KALMAR_TRACT_DEFAULT_IF_ATT_STATE};
    KALMAR_TRACT_IF_BAND m_ifBand{KALMAR_TRACT_DEFAULT_IF_BAND};

    int m_preselectorIdx;
    KALMAR_TRACT_PRESELEKTOR_USAGE m_forcePreselektorUsage{KALMAR_TRACT_DEFAULT_PRES_USAGE};
    
public:
    explicit KalmarTract(QObject *parent = nullptr, KALMAR_TRACT_INDEX idx = FIRST_TRACT);
    
    KALMAR_TRACT_INDEX getTractIdx() const;
    void setTractIdx(KALMAR_TRACT_INDEX tractIdx);

    KALMAR_TRACT_USAGE getTractUsage() const;
    void setTractUsage(const KALMAR_TRACT_USAGE& tractUsage);
    
    unsigned int getCentralFreq() const;
    void setCentralFreq(unsigned int centralFreq);
    
    KALMAR_TRACT_IN_ATT_STATE getInAttState() const;
    void setInAttState(const KALMAR_TRACT_IN_ATT_STATE& inAttState);
    
    KALMAR_TRACT_HF_ATT_STATE getHfAttState() const;
    void setHfAttState(const KALMAR_TRACT_HF_ATT_STATE& hfAttState);
    
    KALMAR_TRACT_IF_ATT_STATE getIfAttState() const;
    void setIfAttState(const KALMAR_TRACT_IF_ATT_STATE& ifAttState);
    
    KALMAR_TRACT_IF_BAND getIfBand() const;
    void setIfBand(const KALMAR_TRACT_IF_BAND& ifBand);

    int getPreselectorIdx() const;
    void setPreselectorIdx(int preselectorIdx);

    KALMAR_TRACT_PRESELEKTOR_USAGE getForcePreselektorUsage() const;
    void setForcePreselektorUsage(KALMAR_TRACT_PRESELEKTOR_USAGE forcePreselektorUsage);

    // extended
    QString getTractInfo();
    void setParams(unsigned int centralFreq = KALMAR_TRACT_DEFAULT_FREQ,
                   KALMAR_TRACT_IN_ATT_STATE inAttState = KALMAR_TRACT_DEFAULT_IN_ATT_STATE,
                   KALMAR_TRACT_HF_ATT_STATE hfAttState = KALMAR_TRACT_DEFAULT_HF_ATT_STATE,
                   KALMAR_TRACT_IF_ATT_STATE ifAttState = KALMAR_TRACT_DEFAULT_IF_ATT_STATE,
                   KALMAR_TRACT_IF_BAND ifBand = KALMAR_TRACT_DEFAULT_IF_BAND);
    void setDefaultParams();

signals:
    void sendTractConfigToPort(KalmarTract* tractPtr);
};

#endif // KALMARTRACT_H
