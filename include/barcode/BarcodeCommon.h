#ifndef __BARCODECOMMON_H__
#define __BARCODECOMMON_H__

namespace sojet {
namespace barcode {

/**
 * Enumerates barcode formats known to this package. Please keep alphabetized.
 */
enum BarcodeFormat {
    /** Aztec 2D barcode format. */
    AZTEC,

    /** CODABAR 1D format. */
    CODABAR,

    CODE_25,

    /** Code 39 1D format. */
    CODE_39,

    /** Code 93 1D format. */
    CODE_93,

    /** Code 128 1D format. */
    CODE_128,

    /** Data Matrix 2D barcode format. */
    DATA_MATRIX,

    /** EAN 1D format. */
    EAN,

    /** EAN-128 1D format. */
    EAN_128,

    GRID_MATRIX,

    /** MaxiCode 2D barcode format. */
    MAXICODE,

    /** PDF417 format. */
    PDF_417,

    /** QR Code 2D barcode format. */
    QR_CODE,

    /** RSS 14 */
    RSS_14,

    /** RSS EXPANDED */
    RSS_EXPANDED,

    /** UPC-A 1D format. */
    UPC_A,

    /** UPC-E 1D format. */
    UPC_E,

    /** UPC/EAN extension format. Not a stand-alone format. */
    UPC_EAN_EXTENSION,

    /** ITF-14 1D format. */
    ITF_14,

    /** Han Xin Code 2D format. */
    HanXin
};

/**
 * Supported bearer bar types.
 */
enum BearerBarType {
    /* No bearer bar. */
    BEARER_BAR_NONE = 0,

    /* Bearer Bar is drawn on the upper side of the bar code. */
    BEARER_BAR_TOP= 1,

    /* Bearer Bar is drawn on the bottom side of the bar code. */
    BEARER_BAR_BOTTOM = 2,

    /* Bearer Bar is drawn on top and bottom of the bar code. */
    BEARER_BAR_BIND = 3,

    /* Bearer Bar is drawn on all sides of the bar code. */
    BEARER_BAR_RECT = 4,
};

}
}

#endif// __BARCODECOMMON_H__