#ifndef __CODE25_H__
#define __CODE25_H__

#include "Barcode.h"

namespace sojet {
namespace barcode {

class Code25 : public Barcode {
public:
    enum Mode {
        /**
         * Standard Code 2 of 5 mode, also known as Code 2 of 5 Matrix. Encodes any
         * length numeric input (digits 0-9). This is the default mode.
         */
        STANDARD,

        /**
         * Interleaved Code 2 of 5. Encodes pairs of numbers, and so can only encode an even
         * number of digits (0-9). If an odd number of digits is entered a leading zero is
         * added. No check digit is calculated.
         */
        INTERLEAVED,

        /**
         * International Air Transport Agency variation of Code 2 of 5. Encodes any length
         * numeric input (digits 0-9) and does not include a check digit.
         */
        IATA,

        /**
         * Code 2 of 5 Data Logic. Encodes any length numeric input (digits 0-9) and does
         * not include a check digit.
         */
        DATA_LOGIC,

        /**
         * Industrial Code 2 of 5 which can encode any length numeric input (digits 0-9)
         * and does not include a check digit.
         */
        INDUSTRIAL,
    };

    Code25(float barHeight, float xdimension);
    ~Code25(){};

    /**
    * 获取条码模式
    * @return           STANDARD,
    *                   INTERLEAVED,
    *                   IATA,
    *                   DATA_LOGIC,
    *                   INDUSTRIAL,
    */
    int getMode();

    /**
    * 设置条码模式
    * @param           STANDARD,
    *                  INTERLEAVED,
    *                  IATA,
    *                  DATA_LOGIC,
    *                  INDUSTRIAL,
    */
    void setMode(int mode);

    /**
    * 判断是否添加校验字符
    * @return  ture:添加校验字符        false:不添加校验字符
    */
    bool hasCheckDigit();

    /**
    * 设置校验字符
    * @param  ture:添加校验字符        false:不添加校验字符
    */
    void setCheckDigit(bool en);

    /**
    * 设置校验字符是否可见
    * @param  ture:可见校验字符        false:隐藏校验字符
    */
    void setShowCheckDigits(bool showCheckDigits);

    /**
    * 获取校验字符是否可见
    * @return  ture:可见校验字符        false:隐藏校验字符
    */
    bool getShowCheckDigits();
};

}
}

#endif //__CODE25_H__
