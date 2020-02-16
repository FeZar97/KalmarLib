#include "KalmarTract.h"

KalmarTract::KalmarTract(QObject* parent, KALMAR_TRACT_INDEX idx) : QObject(parent), m_tractIdx(idx)
{}

KALMAR_TRACT_INDEX KalmarTract::getTractIdx() const {
    return m_tractIdx;
}

void KalmarTract::setTractIdx(KALMAR_TRACT_INDEX tractIdx) {
    m_tractIdx = tractIdx;
}

KALMAR_TRACT_USAGE KalmarTract::getTractUsage() const {
    return m_tractUsage;
}

void KalmarTract::setTractUsage(const KALMAR_TRACT_USAGE& tractUsage) {
    m_tractUsage = tractUsage;
}

unsigned int KalmarTract::getCentralFreq() const {
    return m_centralFreq;
}

void KalmarTract::setCentralFreq(unsigned int centralFreq) {

    if(centralFreq >= KALMAR_TRACT_MIN_FREQ && centralFreq <= KALMAR_TRACT_MAX_FREQ) {
        m_centralFreq = centralFreq;
    } else {
        if(centralFreq < KALMAR_TRACT_MIN_FREQ) {
            m_centralFreq = KALMAR_TRACT_MIN_FREQ;
        } else {
            m_centralFreq = KALMAR_TRACT_MAX_FREQ;
        }
    }

    emit sendTractConfigToPort(this);
}

KALMAR_TRACT_IN_ATT_STATE KalmarTract::getInAttState() const {
    return m_inAttState;
}

void KalmarTract::setInAttState(const KALMAR_TRACT_IN_ATT_STATE& inAttState) {
    if(m_inAttState != inAttState) {
        m_inAttState = inAttState;
        emit sendTractConfigToPort(this);
    }
}

KALMAR_TRACT_HF_ATT_STATE KalmarTract::getHfAttState() const {
    return m_hfAttState;
}

void KalmarTract::setHfAttState(const KALMAR_TRACT_HF_ATT_STATE& hfAttState) {
    if(m_hfAttState != hfAttState) {
        m_hfAttState = hfAttState;
        emit sendTractConfigToPort(this);
    }
}

KALMAR_TRACT_IF_ATT_STATE KalmarTract::getIfAttState() const {
    return m_ifAttState;
}

void KalmarTract::setIfAttState(const KALMAR_TRACT_IF_ATT_STATE& ifAttState) {
    if(m_ifAttState != ifAttState) {
        m_ifAttState = ifAttState;
        emit sendTractConfigToPort(this);
    }
}

KALMAR_TRACT_IF_BAND KalmarTract::getIfBand() const {
    return m_ifBand;
}

void KalmarTract::setIfBand(const KALMAR_TRACT_IF_BAND& ifBand) {
    if(m_ifBand != ifBand) {
        m_ifBand = ifBand;
        emit sendTractConfigToPort(this);
    }
}

int KalmarTract::getPreselectorIdx() const {
    return m_preselectorIdx;
}

void KalmarTract::setPreselectorIdx(int preselectorIdx) {
    m_preselectorIdx = preselectorIdx;
}

KALMAR_TRACT_PRESELEKTOR_USAGE KalmarTract::getForcePreselektorUsage() const {
    return m_forcePreselektorUsage;
}

void KalmarTract::setForcePreselektorUsage(KALMAR_TRACT_PRESELEKTOR_USAGE forcePreselektorUsage) {
    m_forcePreselektorUsage = forcePreselektorUsage;
}

QString KalmarTract::getTractInfo() {
    return QString("CentralFreq: %1 Hz, InAttSate: %2, HfAttState: %3, IfAttState: %4, IfBand: %5")
            .arg(m_centralFreq)
            .arg(m_inAttState ? "ON " : "OFF ")
            .arg(m_hfAttState ? QString::number(m_hfAttState * KALMAR_TRACT_HF_ATT_STEP) + " dB " : "OFF ")
            .arg(m_ifAttState ? QString::number(m_ifAttState * KALMAR_TRACT_IF_ATT_STEP) + " dB " : "OFF ")
            .arg(QString("%1 kHz").arg((m_ifBand == FIRST_BAND ? "3" : (m_ifBand == SECOND_BAND ? "8" : (m_ifBand == THIRD_BAND ? "20" : "150")))));
}

void KalmarTract::setParams(unsigned int centralFreq, KALMAR_TRACT_IN_ATT_STATE inAttState, KALMAR_TRACT_HF_ATT_STATE hfAttState, KALMAR_TRACT_IF_ATT_STATE ifAttState, KALMAR_TRACT_IF_BAND ifBand) {
    blockSignals(true);
    setCentralFreq(centralFreq);
    setInAttState(inAttState);
    setHfAttState(hfAttState);
    setIfAttState(ifAttState);
    setIfBand(ifBand);
    blockSignals(false);

    emit sendTractConfigToPort(this);
}

void KalmarTract::setDefaultParams() {
    setParams();
}
