#ifndef KALMARRECEIVER_P_H
#define KALMARRECEIVER_P_H

#include "KalmarReceiver.h"
#include <windows.h>
#include "KalmarTract.h"
#include "KalmarKalibrator.h"

#define     KALMAR_MIN_CONFIG              FOUR_CHANNEL
#define     KALMAR_MAX_CONFIG              ONE_ONE_ONE_ONE_CHANNEL

typedef void	(__stdcall *LptSendCodeFct)(unsigned short, unsigned char);

class KalmarReceiverPrivate: public QObject
{
    Q_OBJECT
    Q_DECLARE_PUBLIC(KalmarReceiver);

    LptSendCodeFct lptSendCode;

    short m_lptAddress;
    KALMAR_CONFIG m_config;

public:
    explicit KalmarReceiverPrivate(QObject *parent = nullptr, KALMAR_CONFIG config = KALMAR_DEFAULT_CONFIG);
    virtual ~KalmarReceiverPrivate();

    KalmarReceiver* q_ptr;

    KalmarTract m_firstTract{this, FIRST_TRACT};
    KalmarTract m_secondTract{this, SECOND_TRACT};
    KalmarTract m_thirdTract{this, THIRD_TRACT};
    KalmarTract m_fourthTract{this, FOURTH_TRACT};

    KalmarKalibrator m_kalibrator;

    // rpu codes
    void sendConfigToPort();

    // tract codes
    void sendTractShiftCode(KalmarTract* tract);
    void sendTractCentralFreqCode(KalmarTract* tract);
    void sendTractAnotherParamsCode(KalmarTract* tract);
    void sendTractConfigToPort(KalmarTract* tract);

    // kalibrator codes
    void sendKalibratorModulationFreqToPort();
    void sendKalibratorAttStateToPort();
    void sendKalibratorWorkStateToPort();
    void sendKalibratorSignalTypeToPort(KALMAR_TRACT_INDEX supportTractIdx = FIRST_TRACT);

    // extended
    void changeTractActive();

    short getLptAddress() const;
    void setLptAddress(short lptAddress);

    KALMAR_CONFIG getConfig() const;
    void setConfig(const KALMAR_CONFIG& config);
};

#endif // KALMARRECEIVER_P_H
