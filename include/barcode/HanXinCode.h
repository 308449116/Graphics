#ifndef __HANXIN_CODE_H__
#define __HANXIN_CODE_H__

#include "Barcode.h"

namespace sojet {
namespace barcode {

class HanXinCode : public Barcode {
public:

    enum ErrorCorrectionLevel {
        /* Auto */
        HANXIN_EC_AUTO = 0,

        /* Lowest level. Data recovery capacity is approximately up to 8% .*/
        HANXIN_EC_LOW = 1,

        /* Default EC-Level. Up to 15% */
        HANXIN_EC_MEDIUM = 2,

        /* Up to 23% */
        HANXIN_EC_QUARTIL = 3,

        /* Highest level. Up to 30% */
        HANXIN_EC_HIGH = 4
    };

    /* Available symbol-sizes for QR-Code. */
    enum Version {
        /* Compute size of HanXinCode symbol automatically */
        HANXIN_VER_AUTO = 0,

        /* Fixed symbol-size 23 x 23 squares (Version 1)  */
        HANXIN_VER_1 = 1,

        /* Fixed symbol-size 25 x 25 squares (Version 2)  */
        HANXIN_VER_2 = 2,

        /* Fixed symbol-size 27 x 27 squares (Version 3)  */
        HANXIN_VER_3 = 3,

        /* Fixed symbol-size 29 x 29 squares (Version 4)  */
        HANXIN_VER_4 = 4,

        /* Fixed symbol-size 31 x 31 squares (Version 5)  */
        HANXIN_VER_5 = 5,

        /* Fixed symbol-size 33 x 33 squares (Version 6)  */
        HANXIN_VER_6 = 6,

        /* Fixed symbol-size 35 x 35 squares (Version 7)  */
        HANXIN_VER_7 = 7,

        /* Fixed symbol-size 37 x 37 squares (Version 8)  */
        HANXIN_VER_8 = 8,

        /* Fixed symbol-size 39 x 39 squares (Version 9)  */
        HANXIN_VER_9 = 9,

        /* Fixed symbol-size 41 x 41 squares (Version 10)  */
        HANXIN_VER_10 = 10,

        /* Fixed symbol-size 43 x 43 squares (Version 11)  */
        HANXIN_VER_11 = 11,

        /* Fixed symbol-size 45 x 45 squares (Version 12)  */
        HANXIN_VER_12 = 12,

        /* Fixed symbol-size 47 x 47 squares (Version 13)  */
        HANXIN_VER_13 = 13,

        /* Fixed symbol-size 49 x 49 squares (Version 14)  */
        HANXIN_VER_14 = 14,

        /* Fixed symbol-size 51 x 51 squares (Version 15)  */
        HANXIN_VER_15 = 15,

        /* Fixed symbol-size 53 x 53 squares (Version 16)  */
        HANXIN_VER_16 = 16,

        /* Fixed symbol-size 55 x 55 squares (Version 17)  */
        HANXIN_VER_17 = 17,

        /* Fixed symbol-size 57 x 57 squares (Version 18)  */
        HANXIN_VER_18 = 18,

        /* Fixed symbol-size 59 x 59 squares (Version 19)  */
        HANXIN_VER_19 = 19,

        /* Fixed symbol-size 61 x 61 squares (Version 20)  */
        HANXIN_VER_20 = 20,

        /* Fixed symbol-size 63 x 63 squares (Version 21)  */
        HANXIN_VER_21 = 21,

        /* Fixed symbol-size 65 x 65 squares (Version 22)  */
        HANXIN_VER_22 = 22,

        /* Fixed symbol-size 67 x 67 squares (Version 23)  */
        HANXIN_VER_23 = 23,

        /* Fixed symbol-size 69 x 69 squares (Version 24)  */
        HANXIN_VER_24 = 24,

        /* Fixed symbol-size 71 x 71 squares (Version 25)  */
        HANXIN_VER_25 = 25,

        /* Fixed symbol-size 73 x 73 squares (Version 26)  */
        HANXIN_VER_26 = 26,

        /* Fixed symbol-size 75 x 75 squares (Version 27)  */
        HANXIN_VER_27 = 27,

        /* Fixed symbol-size 77 x 77 squares (Version 28)  */
        HANXIN_VER_28 = 28,

        /* Fixed symbol-size 79 x 79 squares (Version 29)  */
        HANXIN_VER_29 = 29,

        /* Fixed symbol-size 81 x 81 squares (Version 30)  */
        HANXIN_VER_30 = 30,

        /* Fixed symbol-size 83 x 83 squares (Version 31)  */
        HANXIN_VER_31 = 31,

        /* Fixed symbol-size 85 x 85 squares (Version 32)  */
        HANXIN_VER_32 = 32,

        /* Fixed symbol-size 87 x 87 squares (Version 33)  */
        HANXIN_VER_33 = 33,

        /* Fixed symbol-size 89 x 89 squares (Version 34)  */
        HANXIN_VER_34 = 34,

        /* Fixed symbol-size 91 x 91 squares (Version 35)  */
        HANXIN_VER_35 = 35,

        /* Fixed symbol-size 93 x 93 squares (Version 36)  */
        HANXIN_VER_36 = 36,

        /* Fixed symbol-size 95 x 95 squares (Version 37)  */
        HANXIN_VER_37 = 37,

        /* Fixed symbol-size 97 x 97 squares (Version 38)  */
        HANXIN_VER_38 = 38,

        /* Fixed symbol-size 99 x 99 squares (Version 39)  */
        HANXIN_VER_39 = 39,

        /* Fixed symbol-size 101 x 101 squares (Version 40)  */
        HANXIN_VER_40 = 40,

        /* Fixed symbol-size 103 x 23 squares (Version 41)  */
        HANXIN_VER_41 = 41,

        /* Fixed symbol-size 105 x 105 squares (Version 42)  */
        HANXIN_VER_42 = 42,

        /* Fixed symbol-size 107 x 107 squares (Version 43)  */
        HANXIN_VER_43 = 43,

        /* Fixed symbol-size 109 x 109 squares (Version 44)  */
        HANXIN_VER_44 = 44,

        /* Fixed symbol-size 111 x 111 squares (Version 45)  */
        HANXIN_VER_45 = 45,

        /* Fixed symbol-size 113 x 113 squares (Version 46)  */
        HANXIN_VER_46 = 46,

        /* Fixed symbol-size 115 x 115 squares (Version 47)  */
        HANXIN_VER_47 = 47,

        /* Fixed symbol-size 117 x 117 squares (Version 48)  */
        HANXIN_VER_48 = 48,

        /* Fixed symbol-size 119 x 119 squares (Version 49)  */
        HANXIN_VER_49 = 49,

        /* Fixed symbol-size 121 x 121 squares (Version 50)  */
        HANXIN_VER_50 = 50,

        /* Fixed symbol-size 123 x 123 squares (Version 51)  */
        HANXIN_VER_51 = 51,

        /* Fixed symbol-size 125 x 125 squares (Version 52)  */
        HANXIN_VER_52 = 52,

        /* Fixed symbol-size 127 x 127 squares (Version 53)  */
        HANXIN_VER_53 = 53,

        /* Fixed symbol-size 129 x 129 squares (Version 54)  */
        HANXIN_VER_54 = 54,

        /* Fixed symbol-size 131 x 131 squares (Version 55)  */
        HANXIN_VER_55 = 55,

        /* Fixed symbol-size 133 x 133 squares (Version 56)  */
        HANXIN_VER_56 = 56,

        /* Fixed symbol-size 135 x 135 squares (Version 57)  */
        HANXIN_VER_57 = 57,

        /* Fixed symbol-size 137 x 137 squares (Version 58)  */
        HANXIN_VER_58 = 58,

        /* Fixed symbol-size 139 x 139 squares (Version 59)  */
        HANXIN_VER_59 = 59,

        /* Fixed symbol-size 141 x 141 squares (Version 60)  */
        HANXIN_VER_60 = 60,

        /* Fixed symbol-size 143 x 143 squares (Version 61)  */
        HANXIN_VER_61 = 61,

        /* Fixed symbol-size 145 x 145 squares (Version 62)  */
        HANXIN_VER_62 = 62,

        /* Fixed symbol-size 147 x 147 squares (Version 63)  */
        HANXIN_VER_63 = 63,

        /* Fixed symbol-size 149 x 149 squares (Version 64)  */
        HANXIN_VER_64 = 64,

        /* Fixed symbol-size 151 x 151 squares (Version 65)  */
        HANXIN_VER_65 = 65,

        /* Fixed symbol-size 153 x 153 squares (Version 66)  */
        HANXIN_VER_66 = 66,

        /* Fixed symbol-size 155 x 155 squares (Version 67)  */
        HANXIN_VER_67 = 67,

        /* Fixed symbol-size 157 x 157 squares (Version 68)  */
        HANXIN_VER_68 = 68,

        /* Fixed symbol-size 159 x 159 squares (Version 69)  */
        HANXIN_VER_69 = 69,

        /* Fixed symbol-size 161 x 161 squares (Version 70)  */
        HANXIN_VER_70 = 70,

        /* Fixed symbol-size 163 x 163 squares (Version 71)  */
        HANXIN_VER_71 = 71,

        /* Fixed symbol-size 165 x 165 squares (Version 72)  */
        HANXIN_VER_72 = 72,

        /* Fixed symbol-size 167 x 167 squares (Version 73)  */
        HANXIN_VER_73 = 73,

        /* Fixed symbol-size 169 x 169 squares (Version 74)  */
        HANXIN_VER_74 = 74,

        /* Fixed symbol-size 171 x 171 squares (Version 75)  */
        HANXIN_VER_75 = 75,

        /* Fixed symbol-size 173 x 173 squares (Version 76)  */
        HANXIN_VER_76 = 76,

        /* Fixed symbol-size 175 x 175 squares (Version 77)  */
        HANXIN_VER_77 = 77,

        /* Fixed symbol-size 177 x 177 squares (Version 78)  */
        HANXIN_VER_78 = 78,

        /* Fixed symbol-size 179 x 179 squares (Version 79)  */
        HANXIN_VER_79 = 79,

        /* Fixed symbol-size 181 x 181 squares (Version 80)  */
        HANXIN_VER_80 = 80,

        /* Fixed symbol-size 183 x 183 squares (Version 81)  */
        HANXIN_VER_81 = 81,

        /* Fixed symbol-size 185 x 185 squares (Version 82)  */
        HANXIN_VER_82 = 82,

        /* Fixed symbol-size 187 x 187 squares (Version 83)  */
        HANXIN_VER_83 = 83,

        /* Fixed symbol-size 189 x 189 squares (Version 84)  */
        HANXIN_VER_84 = 84
    };

    /**
     * Available mask patterns
     */
    enum Mask {
        HANXIN_MASK_AUTO = -1, /* Default: Mask is computed automatically (time consuming!) */
        HANXIN_MASK_0 = 0, /* Use fixed mask 0 */
        HANXIN_MASK_1 = 1, /* Use fixed mask 1 */
        HANXIN_MASK_2 = 2, /* Use fixed mask 2 */
        HANXIN_MASK_3 = 3  /* Use fixed mask 3 */
    };

    HanXinCode(float barHeight, float xdimension);

    ~HanXinCode(){};

    /**
    * 获取版本
    * @return  版本号(0 - 84)
    */
    int getVersion();

    /**
    * 设置版本
    * @param  版本号(0 - 84)
    */
    void setVersion(int version);

    /**
    * 获取纠错等级
    * @return  纠错等级(0 - 4)
    */
    int getECLevel();

    /**
    * 设置纠错等级
    * @return  纠错等级(0 - 4)
    */
    void setECLevel(int level);

    /**
    * 获取掩码
    * @return  掩码(0 - 3)
    */
    int getMask();

    /**
    * 设置掩码
    * @return  掩码(0 - 3)
    */
    void setMask(int mask);

};

}
}

#endif //__HANXIN_CODE_H__