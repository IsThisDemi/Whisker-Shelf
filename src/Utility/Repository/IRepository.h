#ifndef UTILITY_REPOSITORY_IREPOSITORY_H
#define UTILITY_REPOSITORY_IREPOSITORY_H

#include <vector>
#include "../../Media/AbstractMedia.h"

namespace Utility {
    namespace Repository {
        class IRepository {
            public:
                virtual ~IRepository() = default;
                virtual void create(Media::AbstractMedia* media) = 0;
                virtual Media::AbstractMedia* read(const unsigned int id) const = 0;
                virtual void update(Media::AbstractMedia* media) = 0;
                virtual void remove(const unsigned int id) = 0;
                virtual std::vector<Media::AbstractMedia*> readAll() const = 0;
                virtual void overwrite(const std::vector<Media::AbstractMedia*> newMedias) = 0;
        };
    }
}

#endif