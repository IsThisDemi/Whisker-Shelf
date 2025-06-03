#ifndef UTILITY_CONVERTER_JSON_IREADER_H
#define UTILITY_CONVERTER_JSON_IREADER_H

#include <QJsonObject>
#include "../../../Media/AbstractMedia.h"

namespace Utility {
    namespace Converter {
        namespace Json {
            class IReader {
                public:
                    virtual ~IReader(){};
                    virtual Media::AbstractMedia* read(const QJsonObject& object) = 0;
            };
        }
    }
}
#endif