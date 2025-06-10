#include "Audio.h"

namespace Media
{
    Audio::Audio(
        const unsigned int id,
        const std::string title,
        const std::string publishDate,
        const std::string author,
        const std::string description,
        const unsigned int duration,
        const std::string format,
        const std::string album,
        const std::string coverImage)
        : AbstractMedia(id, title, publishDate, author, description, coverImage),
          duration(duration),
          format(format),
          album(album)
    {
    }

    unsigned int Audio::getDuration() const
    {
        return duration;
    }

    Audio &Audio::setDuration(const unsigned int duration)
    {
        this->duration = duration;
        return *this;
    }

    const std::string &Audio::getFormat() const
    {
        return format;
    }

    Audio &Audio::setFormat(const std::string format)
    {
        this->format = format;
        return *this;
    }



    const std::string &Audio::getAlbum() const
    {
        return album;
    }

    Audio &Audio::setAlbum(const std::string album)
    {
        this->album = album;
        return *this;
    }

    Audio *Audio::clone() const
    {
        return new Audio(*this);
    }

    void Audio::accept(IConstVisitor &visitor) const
    {
        visitor.visit(*this);
    }

    void Audio::accept(IVisitor &visitor)
    {
        visitor.visit(*this);
    }
}