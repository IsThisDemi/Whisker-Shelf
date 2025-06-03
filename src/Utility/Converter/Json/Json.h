#ifndef UTILITY_CONVERTER_JSON_JSON_H
#define UTILITY_CONVERTER_JSON_JSON_H

#include "Reader.h"
#include "../../../Media/AbstractMedia.h"
#include "JsonVisitor.h"

namespace Utility {
    namespace Converter {
        namespace Json {
            class Json {
                public:
                    static QJsonObject fromObject(const Media::AbstractMedia& media);
                    static Media::AbstractMedia& toObject(const QJsonObject& json);
            };
        }
    }
}

#endif