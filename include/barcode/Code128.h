#ifndef __CODE128_H__
#define __CODE128_H__

#include "Barcode.h"

namespace sojet {
namespace barcode {

class Code128 : public Barcode {
public:
    Code128(float barHeight, float xdimension);
    ~Code128(){};
protected:
    /**
    * 判断是否支持GS1
    * @return  ture:支持GS1        false:不支持GS1
    */
    bool gs1Supported();
};

}
}

#endif //__CODE128_H__
