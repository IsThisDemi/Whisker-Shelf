#include "Article.h"

namespace Media
{
    Article::Article(
        const unsigned int id,
        const std::string title,
        const std::string publishDate,
        const std::string author,
        const std::string description,
        const std::string journalName,
        const std::string volumeNumber,
        const unsigned int pageCount,
        const std::string doi)
        : AbstractMedia(id, title, publishDate, author, description),
          journalName(journalName),
          volumeNumber(volumeNumber),
          pageCount(pageCount),
          doi(doi)
    {
    }

    const std::string &Article::getJournalName() const
    {
        return journalName;
    }

    Article &Article::setJournalName(const std::string journalName)
    {
        this->journalName = journalName;
        return *this;
    }

    const std::string &Article::getVolumeNumber() const
    {
        return volumeNumber;
    }

    Article &Article::setVolumeNumber(const std::string volumeNumber)
    {
        this->volumeNumber = volumeNumber;
        return *this;
    }

    unsigned int Article::getPageCount() const
    {
        return pageCount;
    }

    Article &Article::setPageCount(const unsigned int pageCount)
    {
        this->pageCount = pageCount;
        return *this;
    }

    const std::string &Article::getDoi() const
    {
        return doi;
    }

    Article &Article::setDoi(const std::string doi)
    {
        this->doi = doi;
        return *this;
    }

    Article *Article::clone() const
    {
        return new Article(*this);
    }

    void Article::accept(IConstVisitor &visitor) const
    {
        visitor.visit(*this);
    }

    void Article::accept(IVisitor &visitor)
    {
        visitor.visit(*this);
    }
}