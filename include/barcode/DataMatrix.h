#ifndef __DATAMATRIX_H__
#define __DATAMATRIX_H__

#include "Barcode.h"

namespace sojet {
namespace barcode {

class DataMatrix : public Barcode {
public:
    /* Available symbol-sizes for Data Matrix. */
    enum Size {
        DMATRIX_SIZE_AUTO_SQUARE = 0, /* Compute size of Data Matrix symbol automatically */

        DMATRIX_SIZE_AUTO_RECT = 1, /* Compute size of Data Matrix symbol automatically */

        DMATRIX_SIZE_10x10 = 2, /* Fixed square symbol-size 10 x 10 */

        DMATRIX_SIZE_12x12 = 3, /* Fixed square symbol-size 12 x 12 */

        DMATRIX_SIZE_14x14 = 4, /* Fixed square symbol-size 14 x 14 */

        DMATRIX_SIZE_16x16 = 5, /* Fixed square symbol-size 16 x 16 */

        DMATRIX_SIZE_18x18 = 6, /* Fixed square symbol-size 18 x 18 */

        DMATRIX_SIZE_20x20 = 7, /* Fixed square symbol-size 20 x 20 */

        DMATRIX_SIZE_22x22 = 8, /* Fixed square symbol-size 22 x 22 */

        DMATRIX_SIZE_24x24 = 9, /* Fixed square symbol-size 24 x 24 */

        DMATRIX_SIZE_26x26 = 10, /* Fixed square symbol-size 26 x 26 */

        DMATRIX_SIZE_32x32 = 11, /* Fixed square symbol-size 32 x 32 */

        DMATRIX_SIZE_36x36 = 12, /* Fixed square symbol-size 36 x 36 */

        DMATRIX_SIZE_40x40 = 13, /* Fixed square symbol-size 40 x 40 */

        DMATRIX_SIZE_44x44 = 14, /* Fixed square symbol-size 44 x 44 */

        DMATRIX_SIZE_48x48 = 15, /* Fixed square symbol-size 48 x 48 */

        DMATRIX_SIZE_52x52 = 16, /* Fixed square symbol-size 52 x 52 */

        DMATRIX_SIZE_64x64 = 17, /* Fixed square symbol-size 64 x 64 */

        DMATRIX_SIZE_72x72 = 18, /* Fixed square symbol-size 72 x 72 */

        DMATRIX_SIZE_80x80 = 19, /* Fixed square symbol-size 80 x 80 */

        DMATRIX_SIZE_88x88 = 20, /* Fixed square symbol-size 88 x 88 */

        DMATRIX_SIZE_96x96 = 21, /* Fixed square symbol-size 96 x 96 */

        DMATRIX_SIZE_104x104 = 22, /* Fixed square symbol-size 104 x 104 */

        DMATRIX_SIZE_120x120 = 23, /* Fixed square symbol-size 120 x 120 */

        DMATRIX_SIZE_132x132 = 24, /* Fixed square symbol-size 132 x 132 */

        DMATRIX_SIZE_144x144 = 25, /* Fixed square symbol-size 144 x 144 */

        DMATRIX_SIZE_8x18 = 26, /* Fixed rectangular symbol-size 8 x 18 */

        DMATRIX_SIZE_8x32 = 27, /* Fixed rectangular symbol-size 8 x 32 */

        DMATRIX_SIZE_12x26 = 28, /* Fixed rectangular symbol-size 12 x 26 */

        DMATRIX_SIZE_12x36 = 29, /* Fixed rectangular symbol-size 12 x 36 */

        DMATRIX_SIZE_16x36 = 30, /* Fixed rectangular symbol-size 16 x 36 */

        DMATRIX_SIZE_16x48 = 31, /* Fixed rectangular symbol-size 16 x 48 */

        /* Extended Rectangular Data Matrix (DMRE) */

        DMATRIX_SIZE_8x48 = 32, /* Fixed rectangular symbol-size 8 x 48 (ISO21471) */

        DMATRIX_SIZE_8x64 = 33, /* Fixed rectangular symbol-size 8 x 64 (ISO21471) */

        DMATRIX_SIZE_8x80 = 34, /* Fixed rectangular symbol-size 8 x 80 (ISO21471) */

        DMATRIX_SIZE_8x96 = 35, /* Fixed rectangular symbol-size 8 x 96 (ISO21471) */

        DMATRIX_SIZE_8x120 = 36, /* Fixed rectangular symbol-size 8 x 120 (ISO21471) */

        DMATRIX_SIZE_8x144 = 37, /* Fixed rectangular symbol-size 8 x 144 (ISO21471) */

        DMATRIX_SIZE_12x64 = 38, /* Fixed rectangular symbol-size 12 x 64 (ISO21471) */

        DMATRIX_SIZE_12x88 = 39, /* Fixed rectangular symbol-size 12 x 88 (ISO21471) */

        DMATRIX_SIZE_16x64 = 40, /* Fixed rectangular symbol-size 16 x 64 (ISO21471) */

        DMATRIX_SIZE_20x36 = 41, /* Fixed rectangular symbol-size 20 x 36 (ISO21471) */

        DMATRIX_SIZE_20x44 = 42, /* Fixed rectangular symbol-size 20 x 44 (ISO21471) */

        DMATRIX_SIZE_20x64 = 43, /* Fixed rectangular symbol-size 20 x 64 (ISO21471) */

        DMATRIX_SIZE_22x48 = 44, /* Fixed rectangular symbol-size 22 x 48 (ISO21471) */

        DMATRIX_SIZE_24x48 = 45, /* Fixed rectangular symbol-size 24 x 48 (ISO21471) */

        DMATRIX_SIZE_24x64 = 46, /* Fixed rectangular symbol-size 24 x 64 (ISO21471) */

        DMATRIX_SIZE_26x40 = 47, /* Fixed rectangular symbol-size 26 x 40 (ISO21471) */

        DMATRIX_SIZE_26x48 = 48, /* Fixed rectangular symbol-size 26 x 48 (ISO21471) */

        DMATRIX_SIZE_26x64 = 49, /* Fixed rectangular symbol-size 26 x 64 (ISO21471) */
    };

    DataMatrix(float barHeight, float xdimension);
    ~DataMatrix(){};

    /**
    * 获取版本
    * @return  版本号(0 - 49)
    */
    int getVersion();

    /**
    * 设置版本
    * @param  版本号(0 - 49)
    */
    void setVersion(int version);

    /**
    * 获取分隔符
    * @return  true: GS分隔符       false:FNC1分隔符
    */
    bool getGSSeparator();

    /**
    * 设置分隔符
    * @param  true:GS分隔符      false:FNC1分隔符
    */
    void setGSSeparator(bool gsSep);
protected:
    /**
    * 判断是否支持GS1
    * @return  ture:支持GS1        false:不支持GS1
    */
    bool gs1Supported();
};

}
}

#endif
