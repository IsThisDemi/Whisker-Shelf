#include "Film.h"

namespace Media
{
    Film::Film(
        const unsigned int id,
        const std::string title,
        const std::string author,
        const std::string description,
        const std::string productionCompany,
        const unsigned int duration,
        const std::string genre,
        const double budget,
        const std::string coverImage)
        : AbstractMedia(id, title, author, description, coverImage),
          productionCompany(productionCompany),
          duration(duration),
          genre(genre),
          budget(budget)
    {
    }

    const std::string &Film::getProductionCompany() const
    {
        return productionCompany;
    }

    Film &Film::setProductionCompany(const std::string productionCompany)
    {
        this->productionCompany = productionCompany;
        return *this;
    }

    unsigned int Film::getDuration() const
    {
        return duration;
    }

    Film &Film::setDuration(const unsigned int duration)
    {
        this->duration = duration;
        return *this;
    }

    const std::string &Film::getGenre() const
    {
        return genre;
    }

    Film &Film::setGenre(const std::string genre)
    {
        this->genre = genre;
        return *this;
    }

    double Film::getBudget() const
    {
        return budget;
    }

    Film &Film::setBudget(const double budget)
    {
        this->budget = budget;
        return *this;
    }

    Film *Film::clone() const
    {
        return new Film(*this);
    }

    void Film::accept(IConstVisitor &visitor) const
    {
        visitor.visit(*this);
    }

    void Film::accept(IVisitor &visitor)
    {
        visitor.visit(*this);
    }
}