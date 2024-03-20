#include "numericattribute.h"

NumericAttribute::NumericAttribute(AttributeType type, NodeBase *parentNode)
    : AttributeBase(type, parentNode)
{
    m_value = 0;
}

NumericAttribute::~NumericAttribute()
{

}

void NumericAttribute::setSuffixType(SuffixType type)
{
    if (m_suffixType == type) {
        return;
    }

    m_suffixType = type;
    emit suffixTypeChanged(m_suffixType);
}

NumericAttribute::SuffixType NumericAttribute::suffixType() const
{
    return m_suffixType;
}

qreal NumericAttribute::convertToPixels(qreal len, SuffixType type)
{
    switch (type) {
        case SuffixType::ST_PERCENT:
            return len * 100;
        case SuffixType::ST_PX:
            break;
        case SuffixType::ST_PC:
            break;
        case SuffixType::ST_PT:
            return len * 1.25;
        case SuffixType::ST_MM:
            return len * 3.543307;
        case SuffixType::ST_CM:
            return len * 35.43307;
        case SuffixType::ST_IN:
            return len * 90;
        case SuffixType::ST_OTHER:
            break;
        default:
            break;
    }

    return len;
}

qreal NumericAttribute::convertFormPixels(qreal len, SuffixType type)
{
    switch (type) {
        case SuffixType::ST_PERCENT:
                return len / 100.0f;
        case SuffixType::ST_PX:
                break;
        case SuffixType::ST_PC:
                break;
        case SuffixType::ST_PT:
                return len / 1.25;
        case SuffixType::ST_MM:
                return len / 3.543307;
        case SuffixType::ST_CM:
                return len / 35.43307;
        case SuffixType::ST_IN:
                return len / 90;
        case SuffixType::ST_OTHER:
                break;
        default:
                break;
    }

    return len;
}
