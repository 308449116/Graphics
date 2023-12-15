#include "canvasbarcodeitem.h"
#include "BarcodeCommon.h"
#include "Barcode.h"
#include "Codabar.h"
#include "Code25.h"
#include "Code39.h"
#include "Code93.h"
#include "Code128.h"
#include "DataMatrix.h"
#include "Ean.h"
#include "GridMatrix.h"
#include "Pdf417.h"
#include "MaxiCode.h"
#include "QRCode.h"
#include "UPC.h"
#include "Itf14.h"
#include "HanXinCode.h"
#include "Barcode.h"

#include <QPainter>

using namespace sojet::barcode;

CanvasBarcodeItem::CanvasBarcodeItem(QGraphicsItem* parentItem)
    : CanvasItemBase (parentItem)
{
    encode();
}

CanvasBarcodeItem::~CanvasBarcodeItem()
{

}

//void CanvasBarcodeItem::setSize(int width, int height)
//{
//    m_size.setWidth(width);
//    m_size.setHeight(height);

//    this->prepareGeometryChange();
//}

void CanvasBarcodeItem::customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->save();

    QBrush brush(Qt::SolidPattern);
    brush.setColor(Qt::black);
//    painter->setRenderHint(QPainter::Antialiasing);
    painter->scale(m_scaleX, m_scaleY);

    // Plot rectangles
    const std::vector<barcode_rect>& vectRect = m_barcode->getVectorRect();
    for (int i = 0; i < vectRect.size(); i++) {
//        qDebug() << QRectF(vectRect[i].x, vectRect[i].y, vectRect[i].width, vectRect[i].height);
//        qDebug("x:%f, y%f",vectRect[i].x,vectRect[i].y);

        painter->fillRect(QRectF(vectRect[i].x, vectRect[i].y, vectRect[i].width, vectRect[i].height), brush);
    }

    // Plot hexagons
    const std::vector<barcode_hexagon>& vectHexagon = m_barcode->getVectorHexagon();
    for (int i = 0; i < vectHexagon.size(); i++) {
        float previous_diameter = vectHexagon[i].diameter;
        float radius = 0.5 * previous_diameter;
        float half_radius = 0.25 * previous_diameter;
        float half_sqrt3_radius = 0.43301270189221932338 * previous_diameter;

        QPainterPath pt;
        pt.moveTo(vectHexagon[i].x, vectHexagon[i].y + radius);
        pt.lineTo(vectHexagon[i].x + half_sqrt3_radius, vectHexagon[i].y + half_radius);
        pt.lineTo(vectHexagon[i].x + half_sqrt3_radius, vectHexagon[i].y - half_radius);
        pt.lineTo(vectHexagon[i].x, vectHexagon[i].y - radius);
        pt.lineTo(vectHexagon[i].x - half_sqrt3_radius, vectHexagon[i].y - half_radius);
        pt.lineTo(vectHexagon[i].x - half_sqrt3_radius, vectHexagon[i].y + half_radius);
        pt.lineTo(vectHexagon[i].x, vectHexagon[i].y + radius);
        painter->fillPath(pt, brush);
    }

    // Plot dots (circles)
    const std::vector<barcode_circle>& vectCircle = m_barcode->getVectorCircle();
    if (!vectCircle.empty()) {
        QPen p;
        qreal radius = 0.0;
        for (int i = 0; i < vectCircle.size(); i++) {
            if (vectCircle[i].colour){
//                p.setBlendMode(BlendMode::SRC);
                // 没有缓存，只能画白色不能画透明色， 因为原来的背景会在第一次循环被清除掉
                p.setColor(0xFFFFFFFF);
            }
//            p.setColor(m_fgColor);
            radius = vectCircle[i].diameter * 0.5;
            p.setWidthF(vectCircle[i].width);
            painter->setPen(p);
            painter->setBrush(vectCircle[i].width? Qt::NoBrush : brush);
            painter->drawEllipse(QPointF(vectCircle[i].x, vectCircle[i].y), radius, radius);
        }
    }

    // Plot text
    const std::vector<barcode_string>& vectString = m_barcode->getVectorString();
    if (vectString.size() <= 0)
        return;

    QFont font;
    font.setPixelSize(50);
    for (int i = 0; i < vectString.size(); i++) {
        QString textContent = vectString[i].text.c_str();
        font.setPixelSize(50 * vectString[i].fsizeScale);
        painter->setFont(font);
        QFontMetricsF fm(font);
        QRectF rect = fm.boundingRect(textContent);
        int x = vectString[i].x - (rect.width() / 2.0);
        if (x < 0)
            x = 0;
        painter->drawText(QPointF(x, vectString[i].y + rect.height()), textContent);
//        qDebug() << "vectString:" << QPointF(vectString[i].x, vectString[i].y);
    }

    painter->restore();
}

void CanvasBarcodeItem::encode()
{
    QString text = "jpkg";
    float xdimension = 2;
    float barHeight = 80 / xdimension;
    switch (BarcodeFormat::CODE_128) {
    case BarcodeFormat::CODABAR: {
        m_barcode = QSharedPointer<Barcode>(new Codabar(barHeight, xdimension));
        break;
    }
    case BarcodeFormat::CODE_25: {
        Code25* code25 = new Code25(barHeight, xdimension);
        code25->setMode(0);
        m_barcode = QSharedPointer<Barcode>(code25);
        break;
    }
    case BarcodeFormat::CODE_39: {
        Code39* code39 = new Code39(barHeight, xdimension);
        code39->setCheckDigit(false);
        m_barcode = QSharedPointer<Barcode>(code39);
        break;
    }
    case BarcodeFormat::CODE_93: {
        Code93* code93 = new Code93(barHeight, xdimension);
        //code93->setShowCheckDigits(true);
        m_barcode = QSharedPointer<Barcode>(code93);
        break;
    }
    case BarcodeFormat::CODE_128: {
        m_barcode = QSharedPointer<Barcode>(new Code128(barHeight, xdimension));
        break;
    }
    case BarcodeFormat::DATA_MATRIX: {
        DataMatrix* dataMatrix = new DataMatrix(barHeight, xdimension);
        dataMatrix->setVersion(0);
        dataMatrix->setGSSeparator(false);
        m_barcode = QSharedPointer<Barcode>(dataMatrix);
        break;
    }
    case BarcodeFormat::EAN: {
        m_barcode = QSharedPointer<Barcode>(new Ean(barHeight, xdimension));
        break;
    }
    case BarcodeFormat::GRID_MATRIX: {
        GridMatrix* gridMatrix = new GridMatrix(barHeight, xdimension);
        gridMatrix->setECLevel(0);
        gridMatrix->setVersion(0);
        m_barcode = QSharedPointer<Barcode>(gridMatrix);
        break;
    }
    case BarcodeFormat::MAXICODE: {
        m_barcode = QSharedPointer<Barcode>(new MaxiCode(barHeight, xdimension));
        break;
    }
    case BarcodeFormat::PDF_417: {
        /* don't need bar height */
        Pdf417* pdf417 = new Pdf417(0, xdimension);
        pdf417->setDataColumns(1);
        pdf417->setECLevel(0);
        m_barcode = QSharedPointer<Barcode>(pdf417);
        break;
    }
    case BarcodeFormat::QR_CODE: {
        QRCode* qrCode = new QRCode(barHeight, xdimension);
        qrCode->setECLevel(0);
        qrCode->setVersion(0);
        m_barcode = QSharedPointer<Barcode>(qrCode);
        break;
    }
    case BarcodeFormat::UPC_A: {
        UPC* upc = new UPC(barHeight, xdimension);
        upc->setMode(UPC::UPCA);
        m_barcode = QSharedPointer<Barcode>(upc);
        break;
    }
    case BarcodeFormat::UPC_E: {
        UPC* upc = new UPC(barHeight, xdimension);
        upc->setMode(UPC::UPCE);
        m_barcode = QSharedPointer<Barcode>(upc);
        break;
    }
    case BarcodeFormat::ITF_14: {
        Itf14* itf14 = new Itf14(barHeight, xdimension);
        //itf14->setNoQuietZones(false);
        m_barcode = QSharedPointer<Barcode>(itf14);
        break;
    }
    case BarcodeFormat::HanXin: {
        HanXinCode* hanXinCode = new HanXinCode(barHeight, xdimension);
        hanXinCode->setECLevel(0);
        hanXinCode->setVersion(0);
        //hanXinCode->setMask(-1);
        m_barcode = QSharedPointer<Barcode>(hanXinCode);
        break;
    }
    default:
        m_barcode = QSharedPointer<Barcode>(new Barcode(barHeight, xdimension));
        break;
    }

    int hrl = 1;
//    switch (barcodeObject.getHumanReadable()) {
//    case BarcodeObject::HUMAN_READABLE_BOTTOM:
//        hrl = Barcode::HUMAN_READABLE_BOTTOM;
//        break;
//    case BarcodeObject::HUMAN_READABLE_TOP:
//        hrl = Barcode::HUMAN_READABLE_TOP;
//        break;
//    }
    m_barcode->setHumanReadableLocation(hrl);

    int dataType = 0;
//    switch (barcodeObject.getDataType()) {
//    case BarcodeObject::DATA_TYPE_BINARY:
//        dataType = Barcode::BINARY;
//        break;
//    case BarcodeObject::DATA_TYPE_UNICODE:
//        dataType = Barcode::UNICODE;
//        break;
//    case BarcodeObject::DATA_TYPE_GS1:
//        dataType = Barcode::GS1;
//        //text = text.replace('(', '[').replace(')', ']');
//        break;
//        //case BarcodeObject::DATA_TYPE_HIBC:
//        //    dataType = Barcode::HIBC;
//        //    break;
//    }

    m_barcode->setDataType(dataType, false, false);
    m_barcode->setTextMargin(0);
    m_barcode->setTextHeight(100);
    m_barcode->setTextOffset(0);
//    if (barcodeObject.getFormat() == BarcodeFormat::ITF_14 &&
//        barcodeObject.getBearerBarType() == BearerBarType::BEARER_BAR_NONE) {
//        m_barcode->setBearerBarType(BearerBarType::BEARER_BAR_RECT);
//        m_barcode->setBearerBarThickness(0);
//    } else {
//        m_barcode->setBearerBarType(barcodeObject.getBearerBarType());
//        m_barcode->setBearerBarThickness(barcodeObject.getBearerBarThickness());
//    }

//    m_barcode->setQuietZoneWidth(barcodeObject.getQuietZone());
//    if (barcodeObject.getFormat() == BarcodeFormat::AZTEC ||
//        barcodeObject.getFormat() == BarcodeFormat::DATA_MATRIX ||
//        barcodeObject.getFormat() == BarcodeFormat::GRID_MATRIX ||
//        barcodeObject.getFormat() == BarcodeFormat::MAXICODE ||
//        barcodeObject.getFormat() == BarcodeFormat::QR_CODE) {
//        m_barcode->setQuietZoneHeight(barcodeObject.getQuietZone());
//    }

    int iRet = m_barcode->encode(text.toUtf8().data(), text.length());
    if (iRet != 0) {
        std::string sErrorMsg = m_barcode->getErrorInfo();
//        delete m_barcode;
        qDebug("m_barcode encoding failed : %s", m_barcode->getErrorInfo());
        //Log::efmt("BarcodeObjectDecoder", "m_barcode encoding failed : %s", m_barcode->getErrorInfo());
        //throw BarcodeException(sErrorMsg);
    }

    if (m_barcode->getHumanReadableLocation()) {
        QFont font;
        font.setPixelSize(50);
        QFontMetricsF fm(font);
        QRectF rect = fm.boundingRect(text);
        m_originSize = m_size = QSizeF(qMax(m_barcode->getWidth(), rect.width()), m_barcode->getHeight() + rect.height() + fm.descent());
    } else {
        m_originSize = m_size = QSizeF(m_barcode->getWidth(), m_barcode->getHeight());
    }
}

void CanvasBarcodeItem::onValueChanged(void)
{
    this->update();
}

void CanvasBarcodeItem::onRoundValueChanged(const QVariant& value)
{
    this->setItemResizeable(true);
    this->setItemResizeRatio(value.toBool(), 1.0);

    if (value.toBool())
    {
        int width = m_size.width();
        m_size.setHeight(width);
        this->prepareGeometryChange();
    }
}

