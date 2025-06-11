#ifndef MEDIA_AUDIO_H
#define MEDIA_AUDIO_H

#include "AbstractMedia.h"

namespace Media
{
    class Audio : public AbstractMedia
    {
    private:
        unsigned int duration; /// Durata in secondi
        std::string format;    /// Formato dell'audio (MP3, FLAC, etc.)
        std::string album;     /// Album/raccolta

    public:
        Audio(
            const unsigned int id,
            const std::string title,
            const std::string author,
            const std::string description,
            const unsigned int duration,
            const std::string format,
            const std::string album,
            const std::string coverImage = "");

        // Getters
        unsigned int getDuration() const;
        const std::string &getFormat() const;
        const std::string &getAlbum() const;

        // Setters con method chaining
        Audio &setDuration(const unsigned int duration);
        Audio &setFormat(const std::string format);
        Audio &setAlbum(const std::string album);

        // Clone method
        Audio *clone() const;

        // Visitor pattern methods
        void accept(IConstVisitor &visitor) const;
        void accept(IVisitor &visitor);
    };
}

#endif