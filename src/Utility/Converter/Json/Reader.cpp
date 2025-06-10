#include "Reader.h"

// Utility includes
#include <stdexcept>
#include <QJsonArray>
#include <iostream>

// Media includes
#include "Media/Audio.h"
#include "Media/Article.h"
#include "Media/Book.h"
#include "Media/Film.h"

namespace Utility {
    namespace Converter {
        namespace Json {
            const std::map<unsigned int, Media::AbstractMedia*>& Reader::getCache() const {
                // Returns the cache of media objects
                return cache;
            }

            Reader& Reader::clear() {
                // Clears the cache of media objects
                cache.clear();
                return *this;
            }

            Media::AbstractMedia* Reader::read(const QJsonObject& object) {
                // Reads a media from a JSON object
                QJsonValue type = object.value("type");
                if (type.isUndefined()) {
                    throw std::invalid_argument("Missing media type.");
                }

                const unsigned int identifier = object.value("id").toInt();
                if (cache.count(identifier) > 0) {
                    return cache[identifier];
                }

                if (type.toString() == "Article") {
                    return readArticle(object);
                } else if (type.toString() == "Audio") {
                    return readAudio(object);
                } else if (type.toString() == "Book") {
                    return readBook(object);
                } else if (type.toString() == "Film") {
                    return readFilm(object);
                } else {
                    throw std::invalid_argument("Unknown media type.");
                }
            }

            Media::AbstractMedia* Reader::readArticle(const QJsonObject& object) const {
                // Reads an Article media from a JSON object
                return new Media::Article(
                    object.value("id").toInt(),
                    object.value("title").toString().toStdString(),
                    object.value("publishDate").toString().toStdString(),
                    object.value("author").toString().toStdString(),
                    object.value("description").toString().toStdString(),
                    object.value("journalName").toString().toStdString(),
                    object.value("volumeNumber").toString().toStdString(),
                    object.value("pageCount").toInt(),
                    object.value("doi").toString().toStdString(),
                    object.value("coverImage").toString().toStdString()
                );
            }

            Media::AbstractMedia* Reader::readAudio(const QJsonObject& object) const {
                // Reads an Audio media from a JSON object
                return new Media::Audio(
                    object.value("id").toInt(),
                    object.value("title").toString().toStdString(),
                    object.value("publishDate").toString().toStdString(),
                    object.value("author").toString().toStdString(),
                    object.value("description").toString().toStdString(),
                    object.value("duration").toDouble(),
                    object.value("format").toString().toStdString(),
                    object.value("album").toString().toStdString(),
                    object.value("coverImage").toString().toStdString()
                );
            }

            Media::AbstractMedia* Reader::readBook(const QJsonObject& object) const {
                // Reads a Book media from a JSON object
                return new Media::Book(
                    object.value("id").toInt(),
                    object.value("title").toString().toStdString(),
                    object.value("publishDate").toString().toStdString(),
                    object.value("author").toString().toStdString(),
                    object.value("description").toString().toStdString(),
                    object.value("isbn").toString().toStdString(),
                    object.value("pageCount").toInt(),
                    object.value("publisher").toString().toStdString(),
                    object.value("genre").toString().toStdString(),
                    object.value("coverImage").toString().toStdString()
                );
            }

            Media::AbstractMedia* Reader::readFilm(const QJsonObject& object) const {
                // Reads a Film media from a JSON object
                return new Media::Film(
                    object.value("id").toInt(),
                    object.value("title").toString().toStdString(),
                    object.value("publishDate").toString().toStdString(),
                    object.value("author").toString().toStdString(),
                    object.value("description").toString().toStdString(),
                    object.value("director").toString().toStdString(),
                    object.value("duration").toDouble(),
                    object.value("genre").toString().toStdString(),
                    object.value("budget").toDouble(),
                    object.value("coverImage").toString().toStdString()
                );
            }
        }
    }
}
