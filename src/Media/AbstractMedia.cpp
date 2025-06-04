#include "AbstractMedia.h"

namespace Media
{
    // Constructor
    // Initialize fields with parameters
    AbstractMedia::AbstractMedia(
        const unsigned int id,
        const std::string title,
        const std::string publishDate,
        const std::string author,
        const std::string description,
        const std::string coverImage) : id(id), title(title), publishDate(publishDate), author(author), description(description), coverImage(coverImage) {}

    // Destructor
    // Default destructor
    AbstractMedia::~AbstractMedia() {}

    // Get the id of the media
    unsigned int AbstractMedia::getId() const
    {
        return id;
    }

    // Get the title of the media
    const std::string AbstractMedia::getTitle() const
    {
        return title;
    }

    // Set the title of the media
    // Return a reference to the media
    AbstractMedia &AbstractMedia::setTitle(const std::string title)
    {
        this->title = title;
        return *this;
    }

    // Get the publish date of the media
    const std::string AbstractMedia::getPublishDate() const
    {
        return publishDate;
    }

    // Set the publish date of the media
    // Return a reference to the media
    AbstractMedia &AbstractMedia::setPublishDate(const std::string publishDate)
    {
        this->publishDate = publishDate;
        return *this;
    }

    // Get the author of the media
    const std::string AbstractMedia::getAuthor() const
    {
        return author;
    }

    // Set the author of the media
    // Return a reference to the media
    AbstractMedia &AbstractMedia::setAuthor(const std::string author)
    {
        this->author = author;
        return *this;
    }

    // Get the description of the media
    const std::string AbstractMedia::getDescription() const
    {
        return description;
    }

    // Set the description of the media
    // Return a reference to the media
    AbstractMedia &AbstractMedia::setDescription(const std::string description)
    {
        this->description = description;
        return *this;
    }

    // Get the observer of the media
    MediaObserver *AbstractMedia::getObserver() const
    {
        return observer;
    }

    // Set the observer of the media
    void AbstractMedia::setObserver(MediaObserver *newObserver)
    {
        observer = newObserver;
    }

    // Get the cover image path of the media
    const std::string AbstractMedia::getCoverImage() const
    {
        return coverImage;
    }

    // Set the cover image path of the media
    // Return a reference to the media
    AbstractMedia& AbstractMedia::setCoverImage(const std::string coverImage)
    {
        this->coverImage = coverImage;
        return *this;
    }
}