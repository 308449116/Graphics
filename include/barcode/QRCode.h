#ifndef __QRCODE_H__
#define __QRCODE_H__

#include "Barcode.h"

namespace sojet {
namespace barcode {

class QRCode : public Barcode {
public:
    /**
     * <p>See ISO 18004:2006, 6.5.1. This enum encapsulates the four error correction levels
     * defined by the QR code standard.</p>
     */
    enum ErrorCorrectionLevel {
        /* Auto */
        QRCODE_EC_AUTO = 0,

        /* Lowest level. Data recovery capacity is approximately up to 7% .*/
        QRCODE_EC_LOW = 1,

        /* Default EC-Level. Up to 15% */
        QRCODE_EC_MEDIUM = 2,

        /* Up to 25% */
        QRCODE_EC_QUARTIL = 3,

        /* Highest level. Up to 30% */
        QRCODE_EC_HIGH = 4,
    };

    /* Available symbol-sizes for QR-Code. */
    enum Version {
        /* Compute size of QR-Code symbol automatically */
        QRCODE_VER_AUTO = 0,

        /* Fixed symbol-size 21 x 21 squares (Version 1)  */
        QRCODE_VER_1 = 1,

        /* Fixed symbol-size 25 x 25 squares (Version 2)  */
        QRCODE_VER_2 = 2,

        /* Fixed symbol-size 29 x 29 squares (Version 3)  */
        QRCODE_VER_3 = 3,

        /* Fixed symbol-size 33 x 33 squares (Version 4)  */
        QRCODE_VER_4 = 4,

        /* Fixed symbol-size 37 x 37 squares (Version 5)  */
        QRCODE_VER_5 = 5,

        /* Fixed symbol-size 41 x 41 squares (Version 6)  */
        QRCODE_VER_6 = 6,

        /* Fixed symbol-size 45 x 45 squares (Version 7)  */
        QRCODE_VER_7 = 7,

        /* Fixed symbol-size 49 x 49 squares (Version 8)  */
        QRCODE_VER_8 = 8,

        /* Fixed symbol-size 53 x 53 squares (Version 9)  */
        QRCODE_VER_9 = 9,

        /* Fixed symbol-size 57 x 57 squares (Version 10)  */
        QRCODE_VER_10 = 10,

        /* Fixed symbol-size 61 x 61 squares (Version 11)  */
        QRCODE_VER_11 = 11,

        /* Fixed symbol-size 65 x 65 squares (Version 12)  */
        QRCODE_VER_12 = 12,

        /* Fixed symbol-size 69 x 69 squares (Version 13)  */
        QRCODE_VER_13 = 13,

        /* Fixed symbol-size 73 x 73 squares (Version 14)  */
        QRCODE_VER_14 = 14,

        /* Fixed symbol-size 77 x 77 squares (Version 15)  */
        QRCODE_VER_15 = 15,

        /* Fixed symbol-size 81 x 81 squares (Version 16)  */
        QRCODE_VER_16 = 16,

        /* Fixed symbol-size 85 x 85 squares (Version 17)  */
        QRCODE_VER_17 = 17,

        /* Fixed symbol-size 89 x 89 squares (Version 18)  */
        QRCODE_VER_18 = 18,

        /* Fixed symbol-size 93 x 93 squares (Version 19)  */
        QRCODE_VER_19 = 19,

        /* Fixed symbol-size 97 x 97 squares (Version 20)  */
        QRCODE_VER_20 = 20,

        /* Fixed symbol-size 101 x 101 squares (Version 21)  */
        QRCODE_VER_21 = 21,

        /* Fixed symbol-size 105 x 105 squares (Version 22)  */
        QRCODE_VER_22 = 22,

        /* Fixed symbol-size 109 x 109 squares (Version 23)  */
        QRCODE_VER_23 = 23,

        /* Fixed symbol-size 113 x 113 squares (Version 24)  */
        QRCODE_VER_24 = 24,

        /* Fixed symbol-size 117 x 117 squares (Version 25)  */
        QRCODE_VER_25 = 25,

        /* Fixed symbol-size 121 x 121 squares (Version 26)  */
        QRCODE_VER_26 = 26,

        /* Fixed symbol-size 125 x 125 squares (Version 27)  */
        QRCODE_VER_27 = 27,

        /* Fixed symbol-size 129 x 129 squares (Version 28)  */
        QRCODE_VER_28 = 28,

        /* Fixed symbol-size 133 x 133 squares (Version 29)  */
        QRCODE_VER_29 = 29,

        /* Fixed symbol-size 137 x 137 squares (Version 30)  */
        QRCODE_VER_30 = 30,

        /* Fixed symbol-size 141 x 141 squares (Version 31)  */
        QRCODE_VER_31 = 31,

        /* Fixed symbol-size 145 x 145 squares (Version 32)  */
        QRCODE_VER_32 = 32,

        /* Fixed symbol-size 149 x 149 squares (Version 33)  */
        QRCODE_VER_33 = 33,

        /* Fixed symbol-size 153 x 153 squares (Version 34)  */
        QRCODE_VER_34 = 34,

        /* Fixed symbol-size 157 x 157 squares (Version 35)  */
        QRCODE_VER_35 = 35,

        /* Fixed symbol-size 161 x 161 squares (Version 36)  */
        QRCODE_VER_36 = 36,

        /* Fixed symbol-size 165 x 165 squares (Version 37)  */
        QRCODE_VER_37 = 37,

        /* Fixed symbol-size 169 x 169 squares (Version 38)  */
        QRCODE_VER_38 = 38,

        /* Fixed symbol-size 173 x 173 squares (Version 39)  */
        QRCODE_VER_39 = 39,

        /* Fixed symbol-size 177 x 177 squares (Version 40)  */
        QRCODE_VER_40 = 40,
    };

    /**
     * Available mask patterns for QR-Code.
     */
    enum Mask {
        QRCODE_MASK_AUTO = -1, /* Default: Mask is computed automatically (time consuming!) */
        QRCODE_MASK_0 = 0, /* Use fixed mask 0 */
        QRCODE_MASK_1 = 1, /* Use fixed mask 1 */
        QRCODE_MASK_2 = 2, /* Use fixed mask 2 */
        QRCODE_MASK_3 = 3, /* Use fixed mask 3 */
        QRCODE_MASK_4 = 4, /* Use fixed mask 4 */
        QRCODE_MASK_5 = 5, /* Use fixed mask 5 */
        QRCODE_MASK_6 = 6, /* Use fixed mask 6 */
        QRCODE_MASK_7 = 7, /* Use fixed mask 7 */
    };

    QRCode(float barHeight, float xdimension);
    ~QRCode(){};

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
    * @return  版本号(0 - 40)
    */
    int getVersion();

    /**
    * 设置版本
    * @param  版本号(0 - 40)
    */
    void setVersion(int version);
protected:
    /**
    * 判断是否支持GS1
    * @return  ture:支持GS1        false:不支持GS1
    */
    bool gs1Supported();
};

}
}

#endif // __QRCODE_H__
