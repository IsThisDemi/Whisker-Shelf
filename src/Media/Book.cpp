#include "Book.h"

namespace Media
{
    Book::Book(
        const unsigned int id,
        const std::string title,
        const std::string publishDate,
        const std::string author,
        const std::string description,
        const std::string isbn,
        const unsigned int pageCount,
        const std::string publisher,
        const std::string genre)
        : AbstractMedia(id, title, publishDate, author, description),
          isbn(isbn),
          pageCount(pageCount),
          publisher(publisher),
          genre(genre)
    {
    }

    const std::string &Book::getIsbn() const
    {
        return isbn;
    }

    Book &Book::setIsbn(const std::string isbn)
    {
        this->isbn = isbn;
        return *this;
    }

    unsigned int Book::getPageCount() const
    {
        return pageCount;
    }

    Book &Book::setPageCount(const unsigned int pageCount)
    {
        this->pageCount = pageCount;
        return *this;
    }

    const std::string &Book::getPublisher() const
    {
        return publisher;
    }

    Book &Book::setPublisher(const std::string publisher)
    {
        this->publisher = publisher;
        return *this;
    }

    const std::string &Book::getGenre() const
    {
        return genre;
    }

    Book &Book::setGenre(const std::string genre)
    {
        this->genre = genre;
        return *this;
    }

    Book *Book::clone() const
    {
        return new Book(*this);
    }

    void Book::accept(IConstVisitor &visitor) const
    {
        visitor.visit(*this);
    }

    void Book::accept(IVisitor &visitor)
    {
        visitor.visit(*this);
    }
}