#ifndef KALMARLIB_H
#define KALMARLIB_H

#include <QObject>
#include <windows.h>

#include "KalmarLib_global.h"
#include "KalmarTract.h"

#define     RPU_DEFAULT_LPT                         0x378

#define     RPU_DEFAULT_CONFIG                      FOUR_CHANNEL
#define     RPU_MIN_CONFIG                          FOUR_CHANNEL
#define     RPU_MAX_CONFIG                          ONE_ONE_ONE_ONE_CHANNEL

#define     RPU_NUMBER_OF_PRESELECTORS              10

// DB25 sections
enum LPT_SECTION {
    LPT_DATA_REG,
    LPT_STATE_REG,
    LPT_CONTROL_REG,
    LPT_EPP_ADDRESS,
    LPT_EPP_DATA
};

// RPU tracts configurations
enum RPU_CONFIG {
    FOUR_CHANNEL,            // 1 ~ 4 channels,
    THREE_ONE_CHANNEL,       // 2 ~ 3 channels + 1 channel,
    TWO_TWO_CHANNEL,         // 3 ~ 2 channels + 2 channels,
    TWO_ONE_ONE_CHANNEL,     // 4 ~ 2 channels + 1 channel + 1 channel,
    ONE_ONE_ONE_ONE_CHANNEL  // 5 ~ 1 channel  + 1 channel + 1 channel + 1 channel
};

class KALMARLIB_EXPORT KalmarReceiver : public QObject
{
    Q_OBJECT

    LptSendCodeFct lptSendCode;

    short m_lptAddress;
    RPU_CONFIG m_config;

    KalmarTract m_firstTract{this, FIRST_TRACT};
    KalmarTract m_secondTract{this, SECOND_TRACT};
    KalmarTract m_thirdTract{this, THIRD_TRACT};
    KalmarTract m_fourthTract{this, FOURTH_TRACT};

    void sendConfigToPort();

    void sendTractShiftCode(KalmarTract* tract);
    void sendTractCentralFreqCode(KalmarTract* tract);
    void sendAnotherTractParamsCode(KalmarTract* tract);
    void sendTractConfigToPort(KalmarTract* tract);

    void changeTractActive();

public:
    explicit KalmarReceiver(QObject *parent = nullptr, RPU_CONFIG config = RPU_DEFAULT_CONFIG);

    short getLptAddress() const;
    void setLptAddress(short lptAddress);

    RPU_CONFIG getConfig() const;
    void setConfig(const RPU_CONFIG& config);
};

#endif // KALMARLIB_H
