#ifndef MEDIA_BOOK_H
#define MEDIA_BOOK_H

#include "AbstractMedia.h"

namespace Media
{
    class Book : public AbstractMedia
    {
    private:
        std::string isbn;       /// Codice ISBN del libro
        unsigned int pageCount; /// Numero di pagine
        std::string publisher;  /// Casa editrice
        std::string genre;      /// Genere letterario

    public:
        Book(
            const unsigned int id,
            const std::string title,
            const std::string publishDate,
            const std::string author,
            const std::string description,
            const std::string isbn,
            const unsigned int pageCount,
            const std::string publisher,
            const std::string genre);

        // Getters
        const std::string &getIsbn() const;
        unsigned int getPageCount() const;
        const std::string &getPublisher() const;
        const std::string &getGenre() const;

        // Setters con method chaining
        Book &setIsbn(const std::string isbn);
        Book &setPageCount(const unsigned int pageCount);
        Book &setPublisher(const std::string publisher);
        Book &setGenre(const std::string genre);

        // Clone method
        Book *clone() const;

        // Visitor pattern methods
        void accept(IConstVisitor &visitor) const;
        void accept(IVisitor &visitor);
    };
}

#endif