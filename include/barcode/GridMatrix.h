#ifndef __GRIDMATRIX_H__
#define __GRIDMATRIX_H__

#include "Barcode.h"

namespace sojet {
namespace barcode {

class GridMatrix : public Barcode {
public:
    enum ErrorCorrectionLevel {
        GRID_MATRIX_EC_AUTO = 0,

        /* Approximately 10% */
        GRID_MATRIX_EC_10 = 1,

        /* Approximately 20% */
        GRID_MATRIX_EC_20 = 2,

        /* Approximately 30% */
        GRID_MATRIX_EC_30 = 3,

        /* Approximately 40% */
        GRID_MATRIX_EC_40 = 4,

        /* Approximately 50% */
        GRID_MATRIX_EC_50 = 5,
    };

    /* Available symbol-sizes for Grid Matrix. */
    enum Version {
        /* Compute size of Grid Matrix symbol automatically */
        GRID_MATRIX_VER_AUTO = 0,

        /* Fixed symbol-size 18 x 18 squares (Version 1)  */
        GRID_MATRIX_VER_1 = 1,

        /* Fixed symbol-size 30 x 30 squares (Version 2)  */
        GRID_MATRIX_VER_2 = 2,

        /* Fixed symbol-size 42 x 42 squares (Version 3)  */
        GRID_MATRIX_VER_3 = 3,

        /* Fixed symbol-size 54 x 54 squares (Version 4)  */
        GRID_MATRIX_VER_4 = 4,

        /* Fixed symbol-size 66 x 66 squares (Version 5)  */
        GRID_MATRIX_VER_5 = 5,

        /* Fixed symbol-size 78 x 78 squares (Version 6)  */
        GRID_MATRIX_VER_6 = 6,

        /* Fixed symbol-size 90 x 90 squares (Version 7)  */
        GRID_MATRIX_VER_7 = 7,

        /* Fixed symbol-size 102 x 102 squares (Version 8)  */
        GRID_MATRIX_VER_8 = 8,

        /* Fixed symbol-size 114 x 114 squares (Version 9)  */
        GRID_MATRIX_VER_9 = 9,

        /* Fixed symbol-size 126 x 126 squares (Version 10)  */
        GRID_MATRIX_VER_10 = 10,

        /* Fixed symbol-size 138 x 138 squares (Version 11)  */
        GRID_MATRIX_VER_11 = 11,

        /* Fixed symbol-size 150 x 150 squares (Version 12)  */
        GRID_MATRIX_VER_12 = 12,

        /* Fixed symbol-size 162 x 162 squares (Version 13)  */
        GRID_MATRIX_VER_13 = 13
    };
    GridMatrix(float barHeight, float xdimension);
    ~GridMatrix(){};

    /**
    * 获取纠错等级
    * @return  纠错等级(0 - 5)
    */
    int getECLevel();

    /**
    * 设置纠错等级
    * @return  纠错等级(0 - 5)
    */
    void setECLevel(int level);

    /**
    * 获取版本
    * @return  版本号(0 - 13)
    */
    int getVersion();

    /**
    * 设置版本
    * @param  版本号(0 - 13)
    */
    void setVersion(int version);
};

}
}

#endif //__GRIDMATRIX_H__
