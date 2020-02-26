#ifndef KALMARDEFINITIONS_H
#define KALMARDEFINITIONS_H

#define     KALMAR_DEFAULT_LPT                     0x378
#define     KALMAR_DEFAULT_CONFIG                  FOUR_CHANNEL
#define     KALMAR_MAX_TRACT_NUMBER                4

#define     KALMAR_KALIBRATOR_DEFAULT_SIGNAL_TYPE  KALIBRATOR_SINUS
#define     KALMAR_KALIBRATOR_DEFAULT_MOD_FREQ     10000
#define     KALMAR_KALIBRATOR_DEFAULT_ATT_STATE    KALIBRATOR_ATT_OFF
#define     KALMAR_KALIBRATOR_DEFAULT_OUT          KALIBRATOR_INTERNAL
#define     KALMAR_KALIBRATOR_DEFAULT_WORK_STATE   KALIBRATOR_OFF

#define     KALMAR_TRACT_DEFAULT_FREQ              15000000
#define     KALMAR_TRACT_DEFAULT_IN_ATT_STATE      IN_ATT_OFF
#define     KALMAR_TRACT_DEFAULT_HF_ATT_STATE      HF_ATT_OFF
#define     KALMAR_TRACT_DEFAULT_IF_ATT_STATE      IF_ATT_OFF
#define     KALMAR_TRACT_DEFAULT_IF_BAND           SECOND_BAND
#define     KALMAR_TRACT_DEFAULT_PRES_USAGE        AUTO_DEFINING

#define     KALMAR_PRESELEKTORS_NUMBER             10

// RPU configurations
enum KALMAR_CONFIG {
    FOUR_CHANNEL,            // 1 ~ 4 channels,
    THREE_ONE_CHANNEL,       // 2 ~ 3 channels + 1 channel,
    TWO_TWO_CHANNEL,         // 3 ~ 2 channels + 2 channels,
    TWO_ONE_ONE_CHANNEL,     // 4 ~ 2 channels + 1 channel + 1 channel,
    ONE_ONE_ONE_ONE_CHANNEL  // 5 ~ 1 channel  + 1 channel + 1 channel + 1 channel
};

// input attenuator states
enum KALMAR_TRACT_IN_ATT_STATE {
    IN_ATT_OFF,
    IN_ATT_ON
};

// high-frequency attenuator states
enum KALMAR_TRACT_HF_ATT_STATE {
    HF_ATT_OFF  = 0,  HF_ATT_6DB  = 6,  HF_ATT_12DB = 12, HF_ATT_18DB = 18,
    HF_ATT_24DB = 24, HF_ATT_30DB = 30, HF_ATT_36DB = 36, HF_ATT_42DB = 42
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

// kalibrator modulation signal states
enum KALMAR_KALIBRATOR_MOD_SIGNAL {
    KALIBRATOR_SINUS,
    KALIBRATOR_RADIOIMP
};

// kalibrator state
enum KALMAR_KALIBRATOR_STATE {
    KALIBRATOR_OFF,
    KALIBRATOR_ON
};

// kalibrator out signal types
enum KALMAR_KALIBRATOR_OUT_TYPE {
    KALIBRATOR_INTERNAL,
    KALIBRATOR_EXTERNAL
};

// kalibrator attenuator states
enum KALMAR_KALIBRATOR_ATT_STATE {
    KALIBRATOR_ATT_OFF  = 0,  KALIBRATOR_ATT_2DB  = 2,  KALIBRATOR_ATT_4DB  = 4,
    KALIBRATOR_ATT_6DB  = 6,  KALIBRATOR_ATT_8DB  = 8,  KALIBRATOR_ATT_10DB = 10,
    KALIBRATOR_ATT_12DB = 12, KALIBRATOR_ATT_14DB = 14, KALIBRATOR_ATT_16DB = 16,
    KALIBRATOR_ATT_18DB = 18, KALIBRATOR_ATT_20DB = 20, KALIBRATOR_ATT_22DB = 22,
    KALIBRATOR_ATT_24DB = 24, KALIBRATOR_ATT_26DB = 26, KALIBRATOR_ATT_28DB = 28,
    KALIBRATOR_ATT_30DB = 30, KALIBRATOR_ATT_32DB = 32, KALIBRATOR_ATT_34DB = 34,
    KALIBRATOR_ATT_36DB = 36, KALIBRATOR_ATT_38DB = 38, KALIBRATOR_ATT_40DB = 40,
    KALIBRATOR_ATT_42DB = 42, KALIBRATOR_ATT_44DB = 44, KALIBRATOR_ATT_46DB = 46,
    KALIBRATOR_ATT_48DB = 48, KALIBRATOR_ATT_50DB = 50, KALIBRATOR_ATT_52DB = 52,
    KALIBRATOR_ATT_54DB = 54, KALIBRATOR_ATT_56DB = 56, KALIBRATOR_ATT_58DB = 58,
    KALIBRATOR_ATT_60DB = 60
};

// central frequencies of preselektors
const static unsigned int kalmarCenterFrequenciesOfPreselektors[] = {600000,  1250000, 1850000,  2700000,  3800000,
                                                                     5250000, 7350000, 12150000, 17550000, 26350000};

struct TractSettings {
    unsigned int centralFreq;
    KALMAR_TRACT_IN_ATT_STATE inAttState;
    KALMAR_TRACT_HF_ATT_STATE hfAttState;
    KALMAR_TRACT_IF_ATT_STATE ifAttState;
    KALMAR_TRACT_IF_BAND ifBand;
    int preselectorIdx;
    KALMAR_TRACT_PRESELEKTOR_USAGE forcePreselektorUsage;
};

struct KalibratorSettings {
    KALMAR_KALIBRATOR_MOD_SIGNAL m_modSignalType{KALMAR_KALIBRATOR_DEFAULT_SIGNAL_TYPE};
    int                          m_modulationFreq{KALMAR_KALIBRATOR_DEFAULT_MOD_FREQ};
    KALMAR_KALIBRATOR_ATT_STATE  m_attState{KALMAR_KALIBRATOR_DEFAULT_ATT_STATE};
    KALMAR_KALIBRATOR_OUT_TYPE   m_outType{KALMAR_KALIBRATOR_DEFAULT_OUT};
    KALMAR_KALIBRATOR_STATE      m_workState{KALMAR_KALIBRATOR_DEFAULT_WORK_STATE};
};

// structure of kalmar parameters
struct KalmarSettings {
    TractSettings tractsSettings[KALMAR_MAX_TRACT_NUMBER];

};

#endif // KALMARDEFINITIONS_H
