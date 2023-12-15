#ifndef __EAN_H__
#define __EAN_H__

#include "Barcode.h"

namespace sojet {
namespace barcode {

class Ean : public Barcode {
public:
    Ean(float barHeight, float xdimension);
    ~Ean(){};

    /**
    * 获取防护栏高度
    * @return  防护栏高度
    */
    float getGuardPatternExtraHeight();

    /**
    * 设置防护栏高度
    * @return  防护栏高度
    */
    void setGuardPatternExtraHeight(float guardPatternExtraHeight);
};


}
}

#endif //__EAN_H__
