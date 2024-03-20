#ifndef NUMERICATTRIBUTE_H
#define NUMERICATTRIBUTE_H

#include "attributebase.h"

class NumericAttribute : public AttributeBase
{
    Q_OBJECT

public:
    enum SuffixType {
        ST_NONE,
        ST_PERCENT,
        ST_PX,
        ST_PC,
        ST_PT,
        ST_MM,
        ST_CM,
        ST_IN,
        ST_OTHER
    };

    NumericAttribute(AttributeType type, NodeBase *parentNode = nullptr);
    ~NumericAttribute();

    void setSuffixType(SuffixType type);
    SuffixType suffixType() const;

    static qreal convertToPixels(qreal len, SuffixType type);
    static qreal convertFormPixels(qreal len, SuffixType type);
//    static qreal convertToPercent(qreal len, SuffixType type);
//    static qreal convertToPica(qreal len, SuffixType type);
//    static qreal convertToPoint(qreal len, SuffixType type);
//    static qreal convertToMillimeter(qreal len, SuffixType type);
//    static qreal convertToCentimeter(qreal len, SuffixType type);
//    static qreal convertToInch(qreal len, SuffixType type);
signals:
    void suffixTypeChanged(SuffixType type);

protected:
    SuffixType m_suffixType = ST_NONE;
};
#endif // NUMERICATTRIBUTE_H
