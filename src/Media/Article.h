#ifndef MEDIA_ARTICLE_H
#define MEDIA_ARTICLE_H

#include "AbstractMedia.h"

namespace Media
{
    class Article : public AbstractMedia
    {
    private:
        std::string journalName;  /// Nome della rivista
        std::string volumeNumber; /// Volume/numero della rivista
        unsigned int pageCount;   /// Numero di pagine
        std::string doi;          /// Digital Object Identifier
        std::string coverImage;   /// Copertina dell'articolo

    public:
        Article(
            const unsigned int id,
            const std::string title,
            const std::string publishDate,
            const std::string author,
            const std::string description,
            const std::string journalName,
            const std::string volumeNumber,
            const unsigned int pageCount,
            const std::string doi,
            const std::string coverImage = "");

        // Getters
        const std::string &getJournalName() const;
        const std::string &getVolumeNumber() const;
        unsigned int getPageCount() const;
        const std::string &getDoi() const;
        const std::string getCoverImage() const override;

        // Setters con method chaining
        Article &setJournalName(const std::string journalName);
        Article &setVolumeNumber(const std::string volumeNumber);
        Article &setPageCount(const unsigned int pageCount);
        Article &setDoi(const std::string doi);
        Article& setCoverImage(const std::string coverImage) override;

        // Clone method
        Article *clone() const override;

        // Visitor pattern methods
        void accept(IConstVisitor &visitor) const override;
        void accept(IVisitor &visitor) override;
    };
}

#endif