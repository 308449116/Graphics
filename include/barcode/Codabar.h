#ifndef __CODABAR_H__
#define __CODABAR_H__

#include "Barcode.h"

namespace sojet {
namespace barcode {

class Codabar : public Barcode {
public:
    Codabar(float barHeight, float xdimension);
    ~Codabar();

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

#endif //__CODABAR_H__
