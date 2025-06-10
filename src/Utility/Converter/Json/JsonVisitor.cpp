#include "JsonVisitor.h"
#include <QJsonArray>

namespace Utility
{
    namespace Converter
    {
        namespace Json
        {
            // Getter for the JSON object created by the visitor
            QJsonObject JsonVisitor::getObject() const
            {
                return object; // Return the current JSON object
            }

            // Visit method for Article media
            void JsonVisitor::visit(const Media::Article &article)
            {
                QJsonObject article_object;
                // Insert key-value pairs into the JSON object
                article_object.insert("type", QJsonValue::fromVariant("Article"));
                article_object.insert("id", QJsonValue::fromVariant(article.getId()));
                article_object.insert("title", QJsonValue::fromVariant(article.getTitle().c_str()));
                article_object.insert("publishDate", QJsonValue::fromVariant(article.getPublishDate().c_str()));
                article_object.insert("author", QJsonValue::fromVariant(article.getAuthor().c_str()));
                article_object.insert("description", QJsonValue::fromVariant(article.getDescription().c_str()));
                article_object.insert("coverImage", QJsonValue::fromVariant(article.getCoverImage().c_str()));
                article_object.insert("journalName", QJsonValue::fromVariant(article.getJournalName().c_str()));
                article_object.insert("volumeNumber", QJsonValue::fromVariant(article.getVolumeNumber().c_str()));
                article_object.insert("pageCount", QJsonValue::fromVariant(article.getPageCount()));
                article_object.insert("doi", QJsonValue::fromVariant(article.getDoi().c_str()));
                object = article_object; // Update the main JSON object
            }
            // Visit method for Audio media
            void JsonVisitor::visit(const Media::Audio &audio)
            {
                QJsonObject audio_object;
                // Insert key-value pairs into the JSON object
                audio_object.insert("type", QJsonValue::fromVariant("Audio"));
                audio_object.insert("id", QJsonValue::fromVariant(audio.getId()));
                audio_object.insert("title", QJsonValue::fromVariant(audio.getTitle().c_str()));
                audio_object.insert("publishDate", QJsonValue::fromVariant(audio.getPublishDate().c_str()));
                audio_object.insert("author", QJsonValue::fromVariant(audio.getAuthor().c_str()));
                audio_object.insert("description", QJsonValue::fromVariant(audio.getDescription().c_str()));
                audio_object.insert("coverImage", QJsonValue::fromVariant(audio.getCoverImage().c_str()));
                audio_object.insert("duration", QJsonValue::fromVariant(audio.getDuration()));
                audio_object.insert("format", QJsonValue::fromVariant(audio.getFormat().c_str()));
                audio_object.insert("album", QJsonValue::fromVariant(audio.getAlbum().c_str()));
                object = audio_object; // Update the main JSON object
            }
            // Visit method for Book media
            void JsonVisitor::visit(const Media::Book &book)
            {
                QJsonObject book_object;
                // Insert key-value pairs into the JSON object
                book_object.insert("type", QJsonValue::fromVariant("Book"));
                book_object.insert("id", QJsonValue::fromVariant(book.getId()));
                book_object.insert("title", QJsonValue::fromVariant(book.getTitle().c_str()));
                book_object.insert("publishDate", QJsonValue::fromVariant(book.getPublishDate().c_str()));
                book_object.insert("author", QJsonValue::fromVariant(book.getAuthor().c_str()));
                book_object.insert("description", QJsonValue::fromVariant(book.getDescription().c_str()));
                book_object.insert("coverImage", QJsonValue::fromVariant(book.getCoverImage().c_str()));
                book_object.insert("isbn", QJsonValue::fromVariant(book.getIsbn().c_str()));
                book_object.insert("pageCount", QJsonValue::fromVariant(book.getPageCount()));
                book_object.insert("publisher", QJsonValue::fromVariant(book.getPublisher().c_str()));
                book_object.insert("genre", QJsonValue::fromVariant(book.getGenre().c_str()));
                object = book_object; // Update the main JSON object
            }
            // Visit method for Film media
            void JsonVisitor::visit(const Media::Film &film)
            {
                QJsonObject film_object;
                // Insert key-value pairs into the JSON object
                film_object.insert("type", QJsonValue::fromVariant("Film"));
                film_object.insert("id", QJsonValue::fromVariant(film.getId()));
                film_object.insert("title", QJsonValue::fromVariant(film.getTitle().c_str()));
                film_object.insert("publishDate", QJsonValue::fromVariant(film.getPublishDate().c_str()));
                film_object.insert("author", QJsonValue::fromVariant(film.getAuthor().c_str()));
                film_object.insert("description", QJsonValue::fromVariant(film.getDescription().c_str()));
                film_object.insert("coverImage", QJsonValue::fromVariant(film.getCoverImage().c_str()));
                film_object.insert("productionCompany", QJsonValue::fromVariant(film.getProductionCompany().c_str()));
                film_object.insert("duration", QJsonValue::fromVariant(film.getDuration()));
                film_object.insert("genre", QJsonValue::fromVariant(film.getGenre().c_str()));
                film_object.insert("budget", QJsonValue::fromVariant(film.getBudget()));
                object = film_object; // Update the main JSON object
            }
        }
    }
}
