#ifndef UTILITY_REPOSITORY_JSON_REPOSITORY_H
#define UTILITY_REPOSITORY_JSON_REPOSITORY_H

#include <map>
#include <string>

#include "IRepository.h"
#include "../DataMapper/JsonFile.h"

namespace Utility {
    namespace Repository {
        class JsonRepository : public IRepository {
            private:
                Utility::DataMapper::JsonFile data_mapper;
                std::map<unsigned int, Media::AbstractMedia*> repository;
            public:
                JsonRepository(Utility::DataMapper::JsonFile data_mapper);
                ~JsonRepository() override;

                static JsonRepository fromPath(const std::string path);
                const DataMapper::JsonFile &getDataMapper() const;
                const std::map<unsigned int, Media::AbstractMedia *> &getRepository() const;
                const std::string &getPath() const;
                void setPath(std::string path);
                void create(Media::AbstractMedia *media) override;
                Media::AbstractMedia *read(const unsigned int identifier) const override;
                void update(Media::AbstractMedia *media) override;
                void remove(const unsigned int identifier) override;
                std::vector<Media::AbstractMedia *> readAll() const override;
                void overwrite(const std::vector<Media::AbstractMedia *> newMedias) override;
                void store();
                void load();
        };
    }
}
#endif