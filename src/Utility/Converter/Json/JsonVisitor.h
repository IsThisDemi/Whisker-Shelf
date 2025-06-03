#ifndef UTILITY_CONVERTER_JSON_JSON_VISITOR_H
#define UTILITY_CONVERTER_JSON_JSON_VISITOR_H

#include <QJsonObject>
#include "../../../Media/IConstVisitor.h"
#include "../../../Media/Article.h"
#include "../../../Media/Audio.h"
#include "../../../Media/Book.h"
#include "../../../Media/Film.h"

#include "Json.h"

namespace Utility
{
    namespace Converter
    {
        namespace Json
        {

            class JsonVisitor : public Media::IConstVisitor
            {
            private:
                QJsonObject object;

            public:
                QJsonObject getObject() const;
                
                void visit(const Media::Article &article);
                void visit(const Media::Audio &audio);
                void visit(const Media::Book &book);
                void visit(const Media::Film &film);
            };
        }
    }
}

#endif