#ifndef UTILITY_CONVERTER_JSON_READER_H
#define UTILITY_CONVERTER_JSON_READER_H

#include <map>
#include <QJsonObject>

#include "IReader.h"
#include "Json.h"

namespace Utility {
    namespace Converter {
        namespace Json {
            class Reader : public IReader {
                private:
                    std::map<unsigned int, Media::AbstractMedia*> cache;

                    Media::AbstractMedia *readArticle(const QJsonObject &object) const;
                    Media::AbstractMedia *readAudio(const QJsonObject &object) const;
                    Media::AbstractMedia *readBook(const QJsonObject &object) const;
                    Media::AbstractMedia *readFilm(const QJsonObject &object) const;
                public:
                    const std::map<unsigned int, Media::AbstractMedia*> &getCache() const;
                    Reader& clear();
                    Media::AbstractMedia* read(const QJsonObject& object); 
            };
        }
    }
}

#endif