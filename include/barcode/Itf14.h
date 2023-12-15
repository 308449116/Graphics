#ifndef __ITF14_H__
#define __ITF14_H__

#include "Barcode.h"

namespace sojet {
namespace barcode {

class Itf14 : public Barcode {
public:
    Itf14(float barHeight, float xdimension);
    ~Itf14(){};

    /**
    * 是否设置空白区域
    * @param  ture:不设置        false:设置
    */
    void setNoQuietZones(bool isNoQuietZones);
};

}
}

#endif //__ITF14_H__