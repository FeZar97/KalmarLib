#include "KalmarKalibrator.h"

KALMAR_KALIBRATOR_MOD_SIGNAL KalmarKalibrator::getModSignalType() const {
    return m_modSignalType;
}

void KalmarKalibrator::setModSignalType(const KALMAR_KALIBRATOR_MOD_SIGNAL& signalType) {
    m_modSignalType = signalType;
    emit sendKalibratorSignalTypeToPort(FIRST_TRACT);
    emit sendKalibratorWorkStateToPort();
}

int KalmarKalibrator::getModulationFreq() const {
    return m_modulationFreq;
}

void KalmarKalibrator::setModulationFreq(int modulationFreq) {

    if(modulationFreq < KALMAR_KALIBRATOR_MIN_MOD_FREQ) {
        m_modulationFreq = KALMAR_KALIBRATOR_MIN_MOD_FREQ;
    } else if(modulationFreq > KALMAR_KALIBRATOR_MAX_MOD_FREQ) {
        m_modulationFreq = KALMAR_KALIBRATOR_MAX_MOD_FREQ;
    } else {
        m_modulationFreq = modulationFreq;
    }

    emit sendKalibratorModulationFreqToPort();
}

KALMAR_KALIBRATOR_ATT_STATE KalmarKalibrator::getAttState() const {
    return m_attState;
}

void KalmarKalibrator::setAttState(const KALMAR_KALIBRATOR_ATT_STATE& attState) {
    m_attState = attState;
    emit sendKalibratorAttStateToPort();
}

KALMAR_KALIBRATOR_OUT_TYPE KalmarKalibrator::getOutType() const {
    return m_outType;
}

void KalmarKalibrator::setOutType(const KALMAR_KALIBRATOR_OUT_TYPE& outType) {
    m_outType = outType;
    emit sendKalibratorSignalTypeToPort(FIRST_TRACT);
    emit sendKalibratorWorkStateToPort();
}

KALMAR_KALIBRATOR_STATE KalmarKalibrator::getWorkState() const {
    return m_workState;
}

void KalmarKalibrator::setWorkState(const KALMAR_KALIBRATOR_STATE& workState) {
    m_workState = workState;
    emit sendKalibratorWorkStateToPort();
}

KalmarKalibrator::KalmarKalibrator(QObject *parent) : QObject(parent) {}
