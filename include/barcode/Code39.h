#ifndef __CODE39_H__
#define __CODE39_H__

#include "Barcode.h"

namespace sojet {
namespace barcode {

class Code39 : public Barcode {
public:
    enum Mode {
        /**
         * Standard Code 39 mode
         */
        STANDARD,

        /**
         * Extended  Code 39. this symbology expands on Standard Code 39
         * to provide support for the full 7-bit ASCII character set.
         */
        EXTENDED
    };
    Code39(float barHeight, float xdimension);
    ~Code39(){};

    /**
    * 获取条码模式
    * @return           STANDARD
    *                   EXTENDED
    */
    int getMode();

    /**
    * 设置条码模式
    * @param           STANDARD
    *                  EXTENDED
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
};

}
}

#endif //__CODE39_H__
