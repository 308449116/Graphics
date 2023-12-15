#ifndef __CODE93_H__
#define __CODE93_H__

#include "Barcode.h"

namespace sojet {
namespace barcode {

class Code93 : public Barcode {
public:
    Code93(float barHeight, float xdimension);
    ~Code93(){};

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

#endif //__CODE93_H__
