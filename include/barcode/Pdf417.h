#ifndef __PDF417_H__
#define __PDF417_H__

#include "Barcode.h"

namespace sojet {
namespace barcode {

class Pdf417 : public Barcode {
public:
    enum Mode {
        /** Normal PDF417. */
        NORMAL,
        /** Truncated PDF417. */
        TRUNCATED,
        /** MicroPDF417. */
        MICRO
    };

    Pdf417(float barHeight, float xdimension);
    ~Pdf417(){};

    /**
    * 获取条码模式
    * @return           NORMAL,
    *                   TRUNCATED,
    *                   MICRO
    */
    int getMode();

    /**
    * 设置条码模式
    * @param           STANDARD,
    *                  TRUNCATED,
    *                  MICRO,
    */
    void setMode(int mode);

    /**
     * 获取列数
     * @return 符号列数(1 - 30)
     */
    int getDataColumns();

    /**
     * 设置列数
     * @return 符号列数(1 - 30)
     */
    void setDataColumns(int columns);

    /**
    * 获取条码的行数(部分条码是由多行条码堆叠组成的，如：PDF 417等)
    *@return     条码的行数(3 - 90)
    */
    int getBarcodeRows();

    /**
    * 设置条码的行数(部分条码是由多行条码堆叠组成的，如：PDF 417等)
    *@param     条码的行数(3 - 90)
    */
    void setBarcodeRows(int rows);

    /**
    * 获取纠错等级
    * @return  纠错等级(0 - 8)
    */
    int getECLevel();

    /**
    * 设置纠错等级
    * @return  纠错等级(0 - 8)
    */
    void setECLevel(int level);
};

}
}

#endif //__PDF417_H__
