#ifndef KALMARRECEIVER_H
#define KALMARRECEIVER_H

#include <QObject>
#include "KalmarDefinitions.h"

class KalmarReceiverPrivate;
class KalmarReceiver: public QObject
{
    Q_OBJECT

public:
    explicit KalmarReceiver(QObject* parent = nullptr, KALMAR_CONFIG config = KALMAR_DEFAULT_CONFIG);

// --- RECEIVER CONFIGURATIONS ---

    // lpt address [short]
    // default value: 0x0378
    // min: 0x0000, max: 0xFFFF
    short getLptAddress() const;
    void setLptAddress(short lptAddress);

    // kalmar configuration [KALMAR_CONFIG]
    // default value: FOUR_CHANNEL
    // min: FOUR_CHANNEL, max: ONE_ONE_ONE_ONE_CHANNEL
    KALMAR_CONFIG getConfig() const;
    void setConfig(const KALMAR_CONFIG& config);

// --- TRACT CONFIGURATIONS ---

    // central frequency [unsigned int]
    // default value: 15.000.000 (15 MHz)
    // min: 150.000 (150 kHz), max: 31.999.999 (15 MHz)
    unsigned int getTractCentralFreq(KALMAR_TRACT_INDEX idx) const;
    void setTractCentralFreq(KALMAR_TRACT_INDEX idx, unsigned int centralFreq);

    // input attenuator state [KALMAR_TRACT_IN_ATT_STATE]
    // default value: IN_ATT_OFF
    // min: IN_ATT_OFF, max: IN_ATT_ON
    KALMAR_TRACT_IN_ATT_STATE getTractInAttState(KALMAR_TRACT_INDEX idx) const;
    void setTractInAttState(KALMAR_TRACT_INDEX idx, const KALMAR_TRACT_IN_ATT_STATE& inAttState);

    // high-frequency attenuator state [KALMAR_TRACT_HF_ATT_STATE]
    // default value: HF_ATT_OFF
    // min: HF_ATT_OFF, max: HF_ATT_42DB
    KALMAR_TRACT_HF_ATT_STATE getTractHfAttState(KALMAR_TRACT_INDEX idx) const;
    void setTractHfAttState(KALMAR_TRACT_INDEX idx, const KALMAR_TRACT_HF_ATT_STATE& hfAttState);

    // intermediate-frequency attenuator state [KALMAR_TRACT_IF_ATT_STATE]
    // default value: IF_ATT_OFF
    // min: IF_ATT_OFF, max: IF_ATT_30DB
    KALMAR_TRACT_IF_ATT_STATE getTractIfAttState(KALMAR_TRACT_INDEX idx) const;
    void setTractIfAttState(KALMAR_TRACT_INDEX idx, const KALMAR_TRACT_IF_ATT_STATE& ifAttState);

    // intermediate-frequency filters bands [bands]
    // default value: THIRD_BAND
    // min: FIRST_BAND, max: FOURTH_BAND
    KALMAR_TRACT_IF_BAND getTractIfBand(KALMAR_TRACT_INDEX idx) const;
    void setTractIfBand(KALMAR_TRACT_INDEX idx, const KALMAR_TRACT_IF_BAND& ifBand);

    // used preselector index [int]
    // default value: auto selected
    // min: 0, max: 9
    int getTractPreselectorIdx(KALMAR_TRACT_INDEX idx) const;
    void setTractPreselectorIdx(KALMAR_TRACT_INDEX idx, int preselectorIdx);

    // flag of force preselector usage [KALMAR_TRACT_PRESELEKTOR_USAGE]
    // default value: AUTO_DEFINING
    // min: AUTO_DEFINING, max: FORCE_USAGE
    KALMAR_TRACT_PRESELEKTOR_USAGE getTractForcePreselektorUsage(KALMAR_TRACT_INDEX idx) const;
    void setTractForcePreselektorUsage(KALMAR_TRACT_INDEX idx, KALMAR_TRACT_PRESELEKTOR_USAGE forcePreselektorUsage);

// --- EXTENDED ---

    // returned string in format "CentralFreq: %1 Hz, InAttSate: %2, HfAttState: %3, IfAttState: %4, IfBand: %5"
    QString getTractInfo(KALMAR_TRACT_INDEX idx);
    // set params simultaneously
    void setTractParams(KALMAR_TRACT_INDEX idx,
                        unsigned int centralFreq,
                        KALMAR_TRACT_IN_ATT_STATE inAttState,
                        KALMAR_TRACT_HF_ATT_STATE hfAttState,
                        KALMAR_TRACT_IF_ATT_STATE ifAttState,
                        KALMAR_TRACT_IF_BAND ifBand);
    // set default params
    void setTractDefaultParams(KALMAR_TRACT_INDEX idx);

// --- KALIBRATOR CONFIGURATIONS ---

    // type of kalibrator modulation signal [KALMAR_KALIBRATOR_MOD_SIGNAL]
    // default value: KALIBRATOR_SINUS
    // min: KALIBRATOR_SINUS, max: KALIBRATOR_RADIOIMP
    KALMAR_KALIBRATOR_MOD_SIGNAL getKalibratorModSignalType() const;
    void setKalibratorModSignalType(const KALMAR_KALIBRATOR_MOD_SIGNAL& modSignalType);

    // kalibrator modulation frequency [unsigned int]
    // default value: 10000
    // min: 1000, max: 50000
    int getKalibratorModulationFreq() const;
    void setKalibratorModulationFreq(unsigned int modulationFreq);

    // kalibrator attenuator state [KALMAR_KALIBRATOR_ATT_STATE]
    // default value: KALIBRATOR_ATT_OFF
    // min: KALIBRATOR_ATT_OFF, max: KALIBRATOR_ATT_60DB
    KALMAR_KALIBRATOR_ATT_STATE getKalibratorAttState() const;
    void setKalibratorAttState(const KALMAR_KALIBRATOR_ATT_STATE& attState);

    // kalibrator out signal types [KALMAR_KALIBRATOR_OUT_TYPE]
    // default value: KALIBRATOR_INTERNAL
    // min: KALIBRATOR_INTERNAL, max: KALIBRATOR_EXTERNAL
    KALMAR_KALIBRATOR_OUT_TYPE getKalibratorOutType() const;
    void setKalibratorOutType(const KALMAR_KALIBRATOR_OUT_TYPE& outType);

    // kalibrator work state [KALMAR_KALIBRATOR_STATE]
    // default value: KALIBRATOR_OFF
    // min: KALIBRATOR_OFF, max: KALIBRATOR_ON
    KALMAR_KALIBRATOR_STATE getKalibratorWorkState() const;
    void setKalibratorWorkState(const KALMAR_KALIBRATOR_STATE& workState);

protected:
    KalmarReceiverPrivate* const d_kalmarReceiver;
    KalmarReceiver(KalmarReceiverPrivate &dd, QObject * parent);

private:
    Q_DECLARE_PRIVATE(KalmarReceiver);
};

#endif // KALMARRECEIVER_H
