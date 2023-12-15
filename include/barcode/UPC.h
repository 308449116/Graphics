#ifndef __UPC_H__
#define __UPC_H__

#include "Barcode.h"

namespace sojet {
namespace barcode {

class UPC : public Barcode {
public:
    enum Mode {
        UPCA,
        UPCE
    };

    UPC(float barHeight, float xdimension);
    ~UPC(){};

    /**
    * 获取条码模式
    * @return           UPCA
    *                   UPCE
    */
    int getMode();

    /**
    * 设置条码模式
    * @param           UPCA
    *                  UPCE
    */
    void setMode(int mode);

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

#endif //__UPC_H__
