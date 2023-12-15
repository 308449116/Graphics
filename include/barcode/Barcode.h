#ifndef __BARCODE_H__
#define __BARCODE_H__

#include "BarcodeCommon.h"
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <string.h>
#include <math.h>

struct zint_symbol;

namespace sojet {
namespace barcode {

struct barcode_rect {
    float x, y, height, width;
    int colour;
    void set(float x, float y, float width, float height, float xdimensions, int colour = -1){
        this->x = x * xdimensions;
        this->y = y * xdimensions;
        this->height = height * xdimensions;
        this->width = width * xdimensions;
        this->colour = colour;
    }
 };

struct barcode_string {
    float x, y, fsizeScale, fTextMargin, fXDimensions;
    float width; /* Suggested string width, may be 0 if none recommended */
    int length;
    std::string text;
    void set(const char*text, float x, float y, float width, float fsizeScale = 1.0f){
        this->x = x * this->fXDimensions;
        this->y = y * this->fXDimensions + this->fTextMargin;
        this->fsizeScale = fsizeScale;
        this->width = width * this->fXDimensions;
        this->length = strlen(text);
        this->text = text;
    }
};

struct barcode_circle {
    float x, y, width, diameter;
    int colour;
    void set(float x, float y, float diameter, float width, int colour, float xdimensions){
        this->x = x * xdimensions;
        this->y = y * xdimensions;
        this->width = width * xdimensions;
        this->diameter = diameter * xdimensions;
        this->colour = colour;
    }
 };

struct barcode_hexagon {
    float x, y, diameter;
    void set(float x, float y, float diameter, float xdimensions){
        this->x = x * xdimensions;
        this->y = y * xdimensions;
        this->diameter = diameter * xdimensions;
    }
 };

class Barcode{
public:
    /**
     * The location of a bar code's human-readable text.
     */
    enum HumanReadableLocation {
        /** Do not display the human-readable text. */
        HUMAN_READABLE_NONE,

        /** Display the human-readable text below the bar code. */
        HUMAN_READABLE_BOTTOM,

        /** Display the human-readable text above the bar code. */
        HUMAN_READABLE_TOP
    };

    enum DataType {
        BINARY,
        UNICODE,
        GS1,
        HIBC
    };

    /**
    * 构造函数
    *@param barHeight：条码高度,一个xdimension的高度(barHeight/xdimension)
    *@param xdimension：X维缩放比例
    */
    Barcode(float barHeight, float xdimension);
    virtual ~Barcode();

    /**
    * 获取X维度缩放比例
    *@return     缩放比例
    */
    float getXDimensions();

    /**
    * 设置X维度缩放比例
    *@param     X维缩放比例
    */
    void setXDimensions(float xdimensions);

    /**
    * Barcode height in X-dimensions (ignored for fixed-width barcodes)
    * 获取X-dimensions = 1的条码高度
    * @return  条码高度
    */
    float getBarHeight();

    /**
    * Barcode height in X-dimensions (ignored for fixed-width barcodes)
    * 设置X-dimensions = 1的条码高度
    * @param  条码高度
    */
    void setBarHeight(float barHeight);

    /**
    * 获取数据编码类型
    * @return  DATA_MODE(Binary):0  UNICODE_MODE(UTF-8):1  GS1_MODE(GS1):2
    */
    int getDataType();

    /**
    * GS1数据内容校验
    * @return  true:不校验       false:校验
    */
    bool isGS1NoCheck();

    /**
    * 设置数据编码类型(GS1 数据类型还可以设置是否对于数据内容进行校验)
    * @param dataType： DATA_MODE(Binary):0  UNICODE_MODE(UTF-8):1  GS1_MODE(GS1):2
    * @param bGS1NoCheck： true:不校验GS1数据格式               false:校验GS1数据格式
    * @param bParseEscapes true:解析转义字符                  false:不解析转义字符
    */
    void setDataType(int dataType, bool bGS1NoCheck = false, bool bParseEscapes  = false);

    /**
    * 获取条码两边的空白区域宽度
    * @return  空白区域宽度
    */
    int getQuietZoneWidth();

    /**
    * 设置条码两边的空白区域宽度
    * @param  空白区域宽度
    */
    void setQuietZoneWidth(int iQuietZoneWidth);

    /**
    * 获取条码上下的空白区域高度(注意：一维码上下的空白区域在文本外)
    * @return  空白区域高度
    */
    int getQuietZoneHeight();

    /**
    * 设置条码上下的空白区域高度(注意：一维码上下的空白区域在文本外)
    * @param  空白区域高度
    */
    void setQuietZoneHeight(int iQuietZoneHeight);

    /**
    * 获取条码的宽度(包括空白区域和边框大小)
    * @return  条码的宽度
    */
    float getWidth();

    /**
    * 获取条码的高度(包括空白区域和边框大小，不包括文本高度和文本与条码的边距)
    * @return  条码的高度
    */
    float getHeight();

    /**
    * 获取是否显示文本内容
    * @return   0:不显示       1:显示
    */
    int getHumanReadableLocation();

    /**
    * 设置是否显示文本内容
    * @param   0:不显示       1:显示
    */
    void setHumanReadableLocation(int humanReadableLocation);

    /**
    * 获取文本的外边距
    *@return   文本的外边距
    */
    int getTextMargin();

    /**
    * 设置文本的高度
    *@param   文本的高度
    */
    void setTextMargin(int margin);

    /**
    * 获取保护框类型
    *@return   保护框类型
    */
    int getBearerBarType();

    /**
    * 设置一维码文本的偏移
    *@param   文本的高度
    */
    void setTextOffset(float offset);

    /**
    * 获取一维码文本的偏移
    *@return   保护框类型
    */
    int getTextOffset();

    /**
    * 设置保护框类型
    *@param   保护框类型
    */
    void setBearerBarType(int type);

    /**
    * 获取条码边框的厚度
    *@return     条码边框的厚度
    */
    int getBearerBarThickness();

    /**
    * 设置条码边框的厚度
    *@param     条码边框的厚度
    */
    void setBearerBarThickness(int thickness);

    /**
    * 设置文本的高度
    *@param   文本的高度
    */
    void setTextHeight(int iTextHeight);

    /**
    * 获取错误信息
    *@return    错误信息
    */
    const char* getErrorInfo();

    /**
    * 编码条码
    *@param 文本信息
    *@param 文本长度
    *@return    0:成功      其他:失败
    */
    int encode(const char* text, int length);

    /**
    * 获取条码中所有的矩形信息
    *@return 条码中所有的矩形信息
    */
    const std::vector<barcode_rect>& getVectorRect();

    /**
    * 获取条码中所有的圆信息
    *@return 条码中所有的圆信息
    */
    const std::vector<barcode_circle>& getVectorCircle();

    /**
    * 获取条码中所有的多边形信息
    *@return 条码中所有的多边形信息
    */
    const std::vector<barcode_hexagon>& getVectorHexagon();

    /**
    * 获取条码中所有的字符串信息
    *@return 条码中所有的字符串信息
    */
    const std::vector<barcode_string>& getVectorString();

private:
    int native_encode(const char* text, int length);
    /**
    * 将编码后的条码数据缓存到容器
    *@return 0:成功 1-4:告警 >4:错误
    */
    int bufferVector();
    /**
    * 编码条码,并将编码后的条码数据缓存到容器
    *@param 文本信息
    *@param 文本长度
    *@return 0:成功 1-4:告警 >4:错误
    */
    int encodeAndBufferVector(unsigned char *input, int length);

    int plot_vector();
    int is_extendable(const int symbology);
    int is_composite(int symbology);
    int module_is_set(const struct zint_symbol *symbol, const int y_coord, const int x_coord);
    /* Indicates which symbologies can have row binding
    * Note: if change this must also change version in frontend/main.c */
    int is_stackable(const int symbology);
    void error_tag(char error_string[], int error_number);
    int is_matrix(const int symbology);
    float stripf(const float arg);
    int is_sane(const unsigned int flg, const unsigned char source[], const int length);
    void to_upper(unsigned char source[], const int length);
    /* Split UPC/EAN add-on text into various constituents */
    void out_upcean_split_text(int upceanflag, unsigned char text[],unsigned char textpart1[5], unsigned char textpart2[7], unsigned char textpart3[7],unsigned char textpart4[2]);
    /* Return minimum quiet zones for each symbology */
    int out_quiet_zones(const struct zint_symbol *symbol, const int hide_text,float *left, float *right, float *top, float *bottom);
    /* Return true (1-8) if a module is colour, otherwise false (0) */
    int module_colour_is_set(const struct zint_symbol *symbol, const int y_coord, const int x_coord);
    /* Set left (x), top (y), right and bottom offsets for whitespace */
    void out_set_whitespace_offsets(const struct zint_symbol *symbol, const int hide_text,
                float *xoffset, float *yoffset, float *roffset, float *boffset, const float scaler,
                int *xoffset_si, int *yoffset_si, int *roffset_si, int *boffset_si);
    /* Set composite offset and main width excluding addon (for start of addon calc) and addon text, returning
       UPC/EAN type */
    int out_process_upcean(const struct zint_symbol *symbol, int *p_main_width, int *p_comp_xoffset,unsigned char addon[6], int *p_addon_gap);
    /* Calculate large bar height i.e. linear bars with zero row height that respond to the symbol height.
       If scaler `si` non-zero (raster), then large_bar_height if non-zero or else row heights will be rounded
       to nearest pixel and symbol height adjusted */
    float out_large_bar_height(struct zint_symbol *symbol, int si, int *row_heights_si, int *symbol_height_si);
    /* Check colour options are good. Note: using raster.c error nos 651-654 */
    int out_check_colour_options(struct zint_symbol *symbol);
    /* Returns 1 if symbology has fixed aspect ratio (matrix design) */
    int is_fixed_ratio(const int symbology);
    /* Returns 1 if symbology is a matrix design renderable as dots */
    int is_dotty(const int symbology);
    void clearBarcode();

protected:
    virtual bool gs1Supported();

protected:
    zint_symbol* symbol;                //zint 符号结构体
    float m_fGuardPatternExtraHeight;   //ENA/UPC条码，防护图案额外高度

private:
    float m_fBarcodeWidth;      //条码宽度
    float m_fBarcodeHeight;     //条码高度
    int m_iTextMargin;          //文本外边距
    int m_iTextHeight;          //文本的高度
    float m_XDimensions;        //X-Dimensions 密度
    float m_fTextOffset;        //一维码文本偏移

    std::vector<barcode_rect> m_vecRect;
    std::vector<barcode_circle> m_vecCircle;
    std::vector<barcode_hexagon> m_vecHexagon;
    std::vector<barcode_string> m_vecString;
};

}
}

#endif //__BARCODE_H__
