#ifndef KALMARTRACT_H
#define KALMARTRACT_H

#include <QObject>

#define     KALMAR_TRACT_DEFAULT_FREQ                  15000000
#define     KALMAR_TRACT_MAX_FREQ                      31999999
#define     KALMAR_TRACT_MIN_FREQ                      150000

#define     KALMAR_TRACT_DEFAULT_IN_ATT_STATE          IN_ATT_OFF
#define     KALMAR_TRACT_MIN_IN_ATT_IDX                IN_ATT_OFF
#define     KALMAR_TRACT_MAX_IN_ATT_IDX                IN_ATT_ON

#define     KALMAR_TRACT_DEFAULT_HF_ATT_STATE          HF_ATT_OFF
#define     KALMAR_TRACT_HF_ATT_STEP                   6
#define     KALMAR_TRACT_MIN_HF_ATT_IDX                HF_ATT_OFF / KALMAR_TRACT_HF_ATT_STEP
#define     KALMAR_TRACT_MAX_HF_ATT_IDX                HF_ATT_42DB / KALMAR_TRACT_HF_ATT_STEP

#define     KALMAR_TRACT_DEFAULT_IF_ATT_STATE          IF_ATT_OFF
#define     KALMAR_TRACT_IF_ATT_STEP                   2
#define     KALMAR_TRACT_MIN_IF_ATT_IDX                IF_ATT_OFF / KALMAR_TRACT_IF_ATT_STEP
#define     KALMAR_TRACT_MAX_IF_ATT_IDX                IF_ATT_30DB / KALMAR_TRACT_IF_ATT_STEP

#define     KALMAR_TRACT_DEFAULT_IF_BAND               SECOND_BAND
#define     KALMAR_TRACT_MIN_IF_BAND_IDX               FIRST_BAND
#define     KALMAR_TRACT_MAX_IF_BAND_IDX               FOURTH_BAND

// input attenuator states
enum KALMAR_TRACT_IN_ATT_STATE {
    IN_ATT_OFF,
    IN_ATT_ON
};

// high-frequency attenuator states
enum KALMAR_TRACT_HF_ATT_STATE {
    HF_ATT_OFF  = 0,
    HF_ATT_6DB  = 6,
    HF_ATT_12DB = 12,
    HF_ATT_18DB = 18,
    HF_ATT_24DB = 24,
    HF_ATT_30DB = 30,
    HF_ATT_36DB = 36,
    HF_ATT_42DB = 42
};

// intermediate-frequency attenuator states
enum KALMAR_TRACT_IF_ATT_STATE {
    IF_ATT_OFF  = 0,  IF_ATT_2DB = 2,   IF_ATT_4DB = 4,   IF_ATT_6DB = 6,
    IF_ATT_8DB  = 8,  IF_ATT_10DB = 10, IF_ATT_12DB = 12, IF_ATT_14DB = 14,
    IF_ATT_16DB = 16, IF_ATT_18DB = 18, IF_ATT_20DB = 20, IF_ATT_22DB = 22,
    IF_ATT_24DB = 24, IF_ATT_26DB = 26, IF_ATT_28DB = 28, IF_ATT_30DB = 30
};

// intermediate-frequency filters bands
enum KALMAR_TRACT_IF_BAND {
    FIRST_BAND,  //   3 kHz,
    SECOND_BAND, //   8 kHz,
    THIRD_BAND,  //  20 kHz,
    FOURTH_BAND  // 150 kHz,
};

// tract index
enum KALMAR_TRACT_INDEX {
    FIRST_TRACT = 1,
    SECOND_TRACT,
    THIRD_TRACT,
    FOURTH_TRACT
};

// tract usage
enum KALMAR_TRACT_USAGE {
    TRACT_NOT_USED,
    TRACT_USED
};

// force usage of tract preselectors
enum KALMAR_TRACT_PRESELEKTOR_USAGE {
    AUTO_DEFINING,
    FORCE_USAGE
};

class KalmarTract : public QObject
{
    Q_OBJECT

    KALMAR_TRACT_INDEX m_tractIdx;
    KALMAR_TRACT_USAGE m_tractUsage;
    
    unsigned int m_centralFreq;
    KALMAR_TRACT_IN_ATT_STATE m_inAttState;
    KALMAR_TRACT_HF_ATT_STATE m_hfAttState;
    KALMAR_TRACT_IF_ATT_STATE m_ifAttState;
    KALMAR_TRACT_IF_BAND m_ifBand;

    int m_preselectorIdx;
    KALMAR_TRACT_PRESELEKTOR_USAGE m_forcePreselektorUsage;
    
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
    void sendTractConfigToRpu(KALMAR_TRACT_INDEX m_tractIdx);
};

#endif // KALMARTRACT_H
