#ifndef __MAXICODE_H__
#define __MAXICODE_H__

#include "Barcode.h"

namespace sojet {
namespace barcode {

class MaxiCode : public Barcode {
public:
    MaxiCode(float barHeight, float xdimension);
    ~MaxiCode(){};
};

}
}

#endif //__MAXICODE_H__
