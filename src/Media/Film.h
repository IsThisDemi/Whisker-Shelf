#ifndef MEDIA_FILM_H
#define MEDIA_FILM_H

#include "AbstractMedia.h"

namespace Media
{
    class Film : public AbstractMedia
    {
    private:
        std::string productionCompany;  /// Casa produttrice del film
        unsigned int duration; /// Durata in minuti
        std::string genre;     /// Genere cinematografico
        double budget;         /// Budget in dollari

    public:
        Film(
            const unsigned int id,
            const std::string title,
            const std::string author,
            const std::string description,
            const std::string productionCompany,
            const unsigned int duration,
            const std::string genre,
            const double budget,
            const std::string coverImage = "");

        // Getters
        const std::string &getProductionCompany() const;
        unsigned int getDuration() const;
        const std::string &getGenre() const;
        double getBudget() const;

        // Setters con method chaining
        Film &setProductionCompany(const std::string productionCompany);
        Film &setDuration(const unsigned int duration);
        Film &setGenre(const std::string genre);
        Film &setBudget(const double budget);

        // Clone method
        Film *clone() const;

        // Visitor pattern methods
        void accept(IConstVisitor &visitor) const;
        void accept(IVisitor &visitor);
    };
}

#endif