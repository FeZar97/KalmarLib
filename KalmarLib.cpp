#include "KalmarLib.h"

// кодограмма управления режимами работы
void KalmarReceiver::sendConfigToPort() {

    // байтовый код, который будет отправлен в порт
    char code = 0x00;

    // в зависимости от выбранного режима определяется код режима работы
    switch(m_config)
    {
        case FOUR_CHANNEL:              // конфигурация 4
                                        // .   .   .   R3  R2  R1  N2  N1
            code = 0x0C;                // 0   0   0   0   1   1   0   0 = 0x0C
            break;

        case THREE_ONE_CHANNEL:         // конфигурация 3 + 1
                                        // .   .   .   R3  R2  R1  N2  N1
            code = 0x08;                // 0   0   0   0   1   0   0   0 = 0x08
            break;

        case TWO_TWO_CHANNEL:           // конфигурация 2 + 2
                                        // .   .   .   R3  R2  R1  N2  N1
            code = 0x10;                // 0   0   0   1   0   0   0   0 = 0x10
            break;

        case TWO_ONE_ONE_CHANNEL:       // конфигурация 2 + 1 + 1
                                        // .   .   .   R3  R2  R1  N2  N1
            code = 0x04;                // 0   0   0   0   0   1   0   0 = 0x04
            break;

        case ONE_ONE_ONE_ONE_CHANNEL:   // конфигурация 1 + 1 + 1 + 1
                                        // .   .   .   R3  R2  R1  N2  N1
            code = 0x00;                // 0   0   0   0   0   0   0   0 = 0x00
            break;
    }

    // отправка кода
    lptSendCode(m_lptAddress + LPT_DATA_REG, code);

    // СТРОБ ( 5 --- 4)
    lptSendCode(m_lptAddress + LPT_CONTROL_REG, 0x4); // 0 1 0 0
    lptSendCode(m_lptAddress + LPT_CONTROL_REG, 0x5); // 0 1 0 1
    lptSendCode(m_lptAddress + LPT_CONTROL_REG, 0x4); // 0 1 0 0
}

/*---------------------------------КОД УПРАВЛЕНИЯ РЕЖИМАМИ РАБОТЫ---------------------------------

R1 ,R2, R3 – код управления режимами работы
+----+----+----+----------------------------------------+-----------------+
| R3 | R2 | R1 |                Режим работы            |  Ведущий канал  |
+----+----+----+----------------------------------------+-----------------+
| 0	 | 0  | 0  |          Четыре автономных канала      |       Нет       |
+----+----+----+----------------------------------------+-----------------+
| 0	 | 0  | 1  | Два синхронных и два автономных канала	|      Второй     |
+----+----+----+----------------------------------------+-----------------+
| 0	 | 1  |	0  | Три синхронных и один автономный канал	|      Третий     |
+----+----+----+----------------------------------------+-----------------+
| 0	 | 1  |	1  |        Четыре синхронных канала        |    Четвертый    |
+----+----+----+----------------------------------------+-----------------+
| 1  | 0  |	0  |      Две пары  синхронных каналов      | Первый и третий |
+----+----+----+----------------------------------------+-----------------+


N1, N2 – код управляемого канала (для автономных каналов)
+----+----+-------------------+
| N2 | N1 |	Управляемый канал |
+----+----+-------------------+
| 0  | 0  |       Первый      |
+----+----+-------------------+
| 0  | 1  |       Второй      |
+----+----+-------------------+
| 1  | 0  |       Третий      |
+----+----+-------------------+
| 1  | 1  |      Четвертый    |
+----+----+-------------------+

При  синхронной работе каналов управление необходимо осуществлять только ведущим каналом,
на остальные оно поступает автоматически.

1. Алгоритм определения кодограммы:
   1) в соответствии с режимом работы из таблицы_1 берутся значения разрядов R3, R2 и R1;
   2) из таблицы_1 берется номер ВЕДУЩЕГО канала для СИНХРОННЫХ каналов;
   3) для данного номера ВЕДУЩЕГО канала по таблице_2 определяются значения разрядов N2 и N1;
   4) если в данном режиме работы предусмотрены АВТОНОМНЫЕ каналы, то им ставятся в соответствие
      УПРАВЛЯЮЩИЕ каналы, которые остались не занятыми в пункте 2.

2. ВЕДУЩИЙ канал - это канал, управляющий группой синхронных каналов (например в режиме 3+1 будет два управляющих канала: третий канал - ведущий для трех каналов и
*/
void KalmarReceiver::sendTractConfigToPort(KalmarTract* tract) {
    sendTractCentralFreqCode(tract);
    sendAnotherTractParamsCode(tract);
}

// send shift code to tuning current tract
void KalmarReceiver::sendTractShiftCode(KalmarTract* tract) {
    char code = 0, geterodinNumber = 0;

    if(m_config < RPU_MIN_CONFIG || m_config > RPU_MAX_CONFIG)
        code = char(0xFF);

    switch(m_config)
    {
        //                        R3 R2 R1 N2 N1
        // 4 синхронных канала -  0  1  1  1  1 (все в соответствии с инструкцией)
        //                        0x0C(00001100)
        //                      + 0x03(00000011)
        //                      = 0x0F(00001111)
        case FOUR_CHANNEL: // 4
            geterodinNumber = 0x03; // по таблице_1 ВЕДУЩИМ каналом является четвертый
            code = 0x0C | geterodinNumber;
            break;

        //                                           R3 R2 R1 N2 N1
        // Три синхронных и один автономный канал -  0  1  0  1  0
        //                                           0x08(00001000)
        //                                         + 0x02(00000010)
        //                                         = 0x0A(00001010)
        case THREE_ONE_CHANNEL: // 3+1
            if(tract->getTractIdx() == FIRST_TRACT) // если это трехканальный тракт, то ВЕДУЩИМ каналом должен быть третий канал
                geterodinNumber = 0x02;
            else // для оставшегося АВТОНОМНОГО канала берется гетеродин 0x03
                geterodinNumber = 0x03;
            code = 0x08 | geterodinNumber;
            break;

        //                                R3 R2 R1 N2 N1          R3 R2 R1 N2 N1
        // Две пары синхронных каналов -  1  0  0  0  0           1  0  0  1  0
        //                                0x10(00010000)          0x10(00010000)
        //                              + 0x00(00000000)    и   + 0x02(00000010)
        //                              = 0x10(00010000)        = 0x12(00010010)
        case TWO_TWO_CHANNEL: // 2+2
            if(tract->getTractIdx() == FIRST_TRACT) // если это первая синхронная пара, то ВЕДУЩИМ каналом должен быть первый канал
                geterodinNumber = 0x00;
            else                 // если это вторая синхронная пара, то ВЕДУЩИМ каналом должен быть третий канал
                geterodinNumber = 0x02;
            code = 0x10 | geterodinNumber;
            break;

        //                                           R3 R2 R1 N2 N1
        // Два синхронных и два автономных канала -  0  0  1  0  1
        //                                           0x04(00000100)
        //                                         + 0x01(00000001)
        //                                         = 0x05(00000101)
        case TWO_ONE_ONE_CHANNEL: // 2+1+1
            if(tract->getTractIdx() == FIRST_TRACT) // если это первый (двухканальный синхронный) тракт, то ВЕДУЩИМ каналом должен быть второй канал
               geterodinNumber = 0x01;
            else if(tract->getTractIdx() == SECOND_TRACT) // если это второй тракт (первый из АВТОНОМНЫХ каналов), то УПРАВЛЯЮЩИМ каналом будет первый канал
               geterodinNumber = 0x00;
            else // если это третий тракт (второй из АВТОНОМНЫХ каналов), то УПРАВЛЯЮЩИМ каналом будет третий канал
               geterodinNumber = 0x02;
            code = 0x04 | geterodinNumber;
            break;

        //                             R3 R2 R1 N2 N1
        // Четыре автономных канала -  0  0  0  Х  Х
        //                             0x00(00000000)
        //                           + 0x0Х(000000ХХ)
        //                           = 0x0Х(000000ХХ)
        case  ONE_ONE_ONE_ONE_CHANNEL: // 1 + 1 + 1 + 1
            if(tract->getTractIdx() == FIRST_TRACT)      // если это первый тракт, то УПРАВЛЯЮЩИМ каналом будет первый канал
               geterodinNumber = 0x00;
            else if(tract->getTractIdx() == SECOND_TRACT) // если это второй тракт, то УПРАВЛЯЮЩИМ каналом будет второй канал
               geterodinNumber = 0x01;
            else if(tract->getTractIdx() == THIRD_TRACT) // если это третий тракт, то УПРАВЛЯЮЩИМ каналом будет третий канал
               geterodinNumber = 0x02;
            else                        // если это четвертый тракт, то УПРАВЛЯЮЩИМ каналом будет четвертый канал
                geterodinNumber = 0x03;
            code = geterodinNumber;
            break;
    }

    if(code != char(0xFF)){
        // комбинации из предыдущей функции ( R3 - R1 определяют режим трактов, N2 и N1 - код управляемго канала )
        // для 4 синхронных каналов код: Х Х Х R3 R2 R1 N2 N1
        //                               Х Х Х  0  1  1  1  1
        // с таким кодом  будут задействованы контакты DB25: 2, 3, 4, 5 => эквивалентное число:
        //                                                                 2(N1) + 4 + 8 + 16 + 0 = 30

        // код
        lptSendCode(m_lptAddress + LPT_DATA_REG, code);

        // строб по адресу 010 ( с учетом инверсии сигналов DB25)
        lptSendCode(m_lptAddress + LPT_CONTROL_REG, 0x4);
        lptSendCode(m_lptAddress + LPT_CONTROL_REG, 0x5);
        lptSendCode(m_lptAddress + LPT_CONTROL_REG, 0x4);
    }
}

/*---------------------------------КОД УПРАВЛЕНИЯ ПЕРВЫМ ГЕТЕРОДИНОМ---------------------------------

 D1...D3  - 32-ти  разрядный последовательный код частоты настройки блока первого гетеродина записывается в
 регистры 3-х БИС интегральных синтезаторов частот КФ1015ПЛ4.
 Первые 13 разрядов кода управляют делителем опорного сигнала ОД,
 следующие 18 разрядов управляют основным счетчиком  N, а 32-й разряд изменяет коэффициент деления
 предварительного делителя основного счетчика P.
 Запись информации в БИС осуществляется начиная с первого разряда.

 Формат управляющего слова:
   +----+----+---+----+-----+-----+-----------+----------+
   | 32 | 31 |30 | 29 | 28* | 27* | 26 ... 14 | 13 ... 1 |
   +----+----+---+----+-----+-----+-----------+----------+
   | P  |                    N                |   ОД     |
   +----+-------------------------------------+----------+

    * при P=1 игнорируются. (27 и 28 разряды)

 Информационные разряды D1...D3 сопровождаются импульсами синхронизации С1. Запись информации во входной регистр
 БИС осуществляется по заднему фронту синхроимпульсов. После окончания записи информации во входной регистр БИС
 производится ее перезапись в рабочий регистр одиночным импульсом Т положительной полярности.

 Значения опорных делителей и признаков коэффициентов деления предварительных делителей постоянные:
      OД1 = 100,  P1 = 0;
      OД2 = 10,   P2 = 1;
      OД3 = 100,  P3 = 1;

 Расчет требуемых коэффициентов деления основных делителей производится следующим образом.
 Определяется частота первого гетеродина:
    F = Fн + Fпч1,
 где частота настройки Fн и первая промежуточная частота Fпч1 взяты в кГц.,
    Fпч1 = 65500 кГц.
 Величины коэффициентов деления N для каждой их трех БИС определяются следующим образом:
    A = int{ ( F - 1000 * int{ (F / 1000) } ) / 500 };
    N1 = F - 1000 * int{F / 1000} + 3000 - A * 1000;
    N2 = int{F / 1000} - 3 + A;
    N3 = int{F / 100} + int{ ( (N1-2500) - 100 * int{ (N1-2500) / 100 } ) / 50 };
 где А - промежуточная  константа ;
 int{ } - целая часть числа, заключенного в скобки.
*/
void KalmarReceiver::sendTractCentralFreqCode(KalmarTract* tract) {

    sendTractShiftCode(tract);

    int freqOfGeterodin = tract->getCentralFreq() / 1000 + 65500;
    int A  = int( ( freqOfGeterodin - 1000 * ( int(freqOfGeterodin / 1000) ) ) / 500);
    int N1 = freqOfGeterodin - 1000 * ( int(freqOfGeterodin / 1000) ) + 3000 - A * 1000;
    int N2 = int(freqOfGeterodin / 1000) - 3 + A;
    int N3 = int(freqOfGeterodin / 100) + int( ( (N1 - 2500) - 100 * int( (N1 - 2500) / 100) ) / 50);
    int D1 = int((0x64 << 19) | (N1 << 1)    );
    int D2 = int((0x0A << 19) | (N2 << 1) | 1);
    int D3 = int((0x64 << 19) | (N3 << 1) | 1);
    char code = 0;

    // учет особенности при P=1
    D2 = (0x0A << 19) | (D2 & 0xF) | (((D2 >> 4) & 0x1FFF) << 6);
    D3 = (0x64 << 19) | (D3 & 0xF) | (((D3 >> 4) & 0x1FFF) << 6);

    // предварительный сброс последней единички (1010)
    lptSendCode(m_lptAddress + LPT_CONTROL_REG, 0xA);

    for(int i = 0; i < 32; i++) {
        code = 0x8;
        code |=  char(((D1 >> 31) << 2) | ((D2 >> 31) << 1) | (D3 >> 31));

        lptSendCode(m_lptAddress + LPT_DATA_REG, code);

        // СТРОБ  ( B -- A )
        lptSendCode(m_lptAddress + LPT_CONTROL_REG, 0xB);
        lptSendCode(m_lptAddress + LPT_CONTROL_REG, 0xA);

        code ^= 0x08;
        lptSendCode(m_lptAddress + LPT_DATA_REG, code);

        // СТРОБ  ( B -- A )
        lptSendCode(m_lptAddress + LPT_CONTROL_REG, 0xB);
        lptSendCode(m_lptAddress + LPT_CONTROL_REG, 0xA);

        D1 <<= 1;
        D2 <<= 1;
        D3 <<= 1;
    }

    code = 0x00;
    lptSendCode(m_lptAddress + LPT_DATA_REG, code);
    // СТРОБ  ( B -- A )
    lptSendCode(m_lptAddress + LPT_CONTROL_REG, 0xB);
    lptSendCode(m_lptAddress + LPT_CONTROL_REG, 0xA);

    code = 0x10;
    lptSendCode(m_lptAddress + LPT_DATA_REG, code);
    // СТРОБ  ( B -- A )
    lptSendCode(m_lptAddress + LPT_CONTROL_REG, 0xB);
    lptSendCode(m_lptAddress + LPT_CONTROL_REG, 0xA);

    code = 0x00;
    lptSendCode(m_lptAddress + LPT_DATA_REG, code);
    // СТРОБ  ( B -- A )
    lptSendCode(m_lptAddress + LPT_CONTROL_REG, 0xB);
    lptSendCode(m_lptAddress + LPT_CONTROL_REG, 0xA);
}

/*---------------------------------КОД УПРАВЛЕНИЯ БЛОКАМИ ПРИЕМНИКОВ---------------------------------
D4 - 14-ти разрядный последовательный код управления блоками приемников

Формат управляющего слова:
+----+----+----+----+----+---+--------+---+---+---+---+---+---+---+
| 14 | 13 | 12 | 11 | 10 | 9 |	  8   | 7 | 6 | 5 | 4 | 3 | 2 | 1 |
+----+----+----+----+----+---+--------+---+---+---+---+---+---+---+
|  Полоса |       Прес       | Атт Вх |   Атт ВЧ  |    Атт ПЧ     |
+----+----+----+----+----+---+--------+---+---+---+---+---+---+---+

Полоса – код полосы пропускания задается в соответствии с таблицей.
+--------------+---------+
| Полоса       | Разряды |
| пропускания, +----+----+
| кГц          | 13 | 14 |
+--------------+----+----+
|     150  *   |  0	|  0 |
+--------------+----+----+
|     20       |  0	|  1 |
+--------------+----+----+
|     8        |  1	|  0 |
+--------------+----+----+
|     3    *   |  1	|  1 |
+--------------+----+----+
* кодограммы для фильтров 150 и 3 кГц неправильные: для 150 кГц - 1 1, а для 3 кГц - 0 0;

Прес - код преселектора, задается в соответствии с таблицей
+---------------+---------------+
| Частота, кГц  |    Разряды    |
|               +---+---+---+---+
|               | 9 | 10| 11| 12|
+---------------+---+---+---+---+
| 200 - 1000    | 1 | 1 | 1 | 1 |
+---------------+---+---+---+---+
| 1000 - 1500   | 1	| 0	| 0	| 0 |
+---------------+---+---+---+---+
| 1500 - 2200   | 0	| 1	| 1	| 1 |
+---------------+---+---+---+---+
| 2200 - 3200   | 0	| 1	| 1	| 0 |
+---------------+---+---+---+---+
| 3200 - 4700   | 0	| 1	| 0	| 1 |
+---------------+---+---+---+---+
| 4700 - 6800   | 0	| 1	| 0	| 0 |
+---------------+---+---+---+---+
| 6800 - 9900   | 0	| 0	| 1	| 1 |
+---------------+---+---+---+---+
| 9900- 14400   | 0	| 0	| 1	| 0 |
+---------------+---+---+---+---+
| 14400 - 20700 | 0	| 0	| 0	| 1 |
+---------------+---+---+---+---+
| 20700 - 32000 | 0	| 0	| 0	| 0 |
+---------------+---+---+---+---+

Атт Вх - код включения входного аттенюатора 20 дБ (1 – вкл, 0 - выкл.)

Атт ВЧ - двоичный код  аттенюатора ВЧ (дискрет 6 дБ)
  7 разряд -  6 дБ,
  6 разряд - 12 дБ,
  5 разряд - 24 дБ.

Атт ПЧ - двоичный код  аттенюатора ПЧ (дискрет 2 дБ)
 4 разряд - 2 дБ,
 3 разряд - 4 дБ,
 2 разряд - 8 дБ,
 1 разряд - 16 дБ.

Информационная последовательность D4 сопровождается импульсами синхронизации С2 и стробом Е положительной полярности.
Запись информации во входные регистры блоков приемника осуществляется по переднему фронту синхроимпульсов,
начиная с первого разряда.

Управление блоками приемников и первого гетеродина может осуществляться как одновременно,
так и независимо друг от друга.
*/
void KalmarReceiver::sendAnotherTractParamsCode(KalmarTract* tract) {

    sendTractShiftCode(tract);

    short ifBandMask, preselektorMask, inAttMask, hfAttMask, ifAttMask, D4;
    int carrier_kHz = tract->getCentralFreq() / 1000;
    char code;

    /* маска полосы
     * расхождение с документацией:
     *                 для полосы 150 кГц должен быть код 0x0000,
     *                 для 20 кГц - 0x0001,
     *                 для 8 кГц - 0x0002,
     *                 для 3 кГц - 0x0003
     *
     * UPD 06.09.17
     * после проверки на РПУ:
     * код 0x0000 соответсвует полосе 3 кГц
     * код 0x0003 соответсвует полосе 150 кГц
     * коды для полос 8 и 20 кГц не изменились
    */
    switch(tract->getIfBand()) {
        case FIRST_BAND: // 3 кГц
            ifBandMask = 0;
            break;

        case SECOND_BAND: // 8 кГц
            ifBandMask = 2;
            break;

        case THIRD_BAND: // 20 кГц
            ifBandMask = 1;
            break;

        case FOURTH_BAND: // 150 кГц
            ifBandMask = 3;
            break;

        default:
            ifBandMask = 3;
            break;
    }

    /*
     * определение маски преселектора
     * UPD 7.9.2017
     * все кодограммы корректны
     */
    if(tract->getForcePreselektorUsage() == AUTO_DEFINING){
        if(carrier_kHz > 200 && carrier_kHz <= 1000)
           preselektorMask = 9;

        if(carrier_kHz > 1000 && carrier_kHz <= 1500)
           preselektorMask = 8;

        if(carrier_kHz > 1500 && carrier_kHz <= 2200)
           preselektorMask = 7;

        if(carrier_kHz > 2200 && carrier_kHz <= 3200)
           preselektorMask = 6;

        if(carrier_kHz > 3200 && carrier_kHz <= 4700)
           preselektorMask = 5;

        if(carrier_kHz > 4700 && carrier_kHz <= 6800)
           preselektorMask = 4;

        if(carrier_kHz > 6800 && carrier_kHz <= 9900)
           preselektorMask = 3;

        if(carrier_kHz > 9900 && carrier_kHz <= 14400)
           preselektorMask = 2;

        if(carrier_kHz > 14400 && carrier_kHz <= 20700)
           preselektorMask = 1;

        if(carrier_kHz > 20700 && carrier_kHz <= 32000)
           preselektorMask = 0;
    }else{
        preselektorMask = 9 - tract->getPreselectorIdx();
    }

    if(tract->getInAttState() == IN_ATT_ON) {
       inAttMask = 1;
    } else {
       inAttMask = 0;
    }

    // маска АттВЧ
    hfAttMask = tract->getHfAttState() / KALMAR_TRACT_HF_ATT_STEP;

    // маска АттПЧ
    ifAttMask = tract->getIfAttState() / KALMAR_TRACT_IF_ATT_STEP;

    // формирование в D4 последовательный 14-ти разрядный код
    D4 = short((ifBandMask << 12) | (preselektorMask << 8) | (inAttMask << 7) | (hfAttMask << 4) | ifAttMask) << 2;

    lptSendCode(m_lptAddress + LPT_CONTROL_REG, 0xA);

    for(int i = 0; i < 14; i++){
        code  = char(0x80);

        code |= char( (D4 & 0x8000) >> 10 );
        lptSendCode(m_lptAddress + LPT_DATA_REG, code);
        // СТРОБ  ( B -- A )
        lptSendCode(m_lptAddress + LPT_CONTROL_REG, 0xB);
        lptSendCode(m_lptAddress + LPT_CONTROL_REG, 0xA);

        code ^= 0x40;
        lptSendCode(m_lptAddress + LPT_DATA_REG, code);
        // СТРОБ  ( B -- A )
        lptSendCode(m_lptAddress + LPT_CONTROL_REG, 0xB);
        lptSendCode(m_lptAddress + LPT_CONTROL_REG, 0xA);

        D4 <<= 1;
    }

    code = 0x00;
    lptSendCode(m_lptAddress + LPT_DATA_REG, code);
    // СТРОБ  ( B -- A )
    lptSendCode(m_lptAddress + LPT_CONTROL_REG, 0xB);
    lptSendCode(m_lptAddress + LPT_CONTROL_REG, 0xA);
}

// tract usage for current m_config
void KalmarReceiver::changeTractActive() {
    switch(m_config){
        case FOUR_CHANNEL:
            m_firstTract.setTractUsage(TRACT_USED);
            m_secondTract.setTractUsage(TRACT_NOT_USED);
            m_thirdTract.setTractUsage(TRACT_NOT_USED);
            m_fourthTract.setTractUsage(TRACT_NOT_USED);
            break;

        case THREE_ONE_CHANNEL:
        case TWO_TWO_CHANNEL:
            m_firstTract.setTractUsage(TRACT_USED);
            m_secondTract.setTractUsage(TRACT_USED);
            m_thirdTract.setTractUsage(TRACT_NOT_USED);
            m_fourthTract.setTractUsage(TRACT_NOT_USED);
            break;

        case TWO_ONE_ONE_CHANNEL:
            m_firstTract.setTractUsage(TRACT_USED);
            m_secondTract.setTractUsage(TRACT_USED);
            m_thirdTract.setTractUsage(TRACT_USED);
            m_fourthTract.setTractUsage(TRACT_NOT_USED);
            break;

        case ONE_ONE_ONE_ONE_CHANNEL:
            m_firstTract.setTractUsage(TRACT_USED);
            m_secondTract.setTractUsage(TRACT_USED);
            m_thirdTract.setTractUsage(TRACT_USED);
            m_fourthTract.setTractUsage(TRACT_NOT_USED);
            break;
    }
}

KalmarReceiver::KalmarReceiver(QObject* parent, RPU_CONFIG config): QObject(parent), m_config(config) {

    changeTractActive();
}

RPU_CONFIG KalmarReceiver::getConfig() const {
    return m_config;
}

void KalmarReceiver::setConfig(const RPU_CONFIG& config) {
    m_config = config;
    changeTractActive();
    sendConfigToPort();
}

short KalmarReceiver::getLptAddress() const {
    return m_lptAddress;
}

void KalmarReceiver::setLptAddress(short lptAddress) {
    m_lptAddress = lptAddress;
}
