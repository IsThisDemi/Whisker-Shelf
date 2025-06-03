#ifndef UTILITY_DATA_MAPPER_JSON_FILE_H
#define UTILITY_DATA_MAPPER_JSON_FILE_H

#include <string>
#include <vector>

#include "../../Media/AbstractMedia.h"
#include "../Converter/Json/Json.h"

namespace Utility {
    namespace DataMapper {
        class JsonFile {
            private:
                std::string path;
            public:
                JsonFile(const std::string& path);
                static JsonFile fromPath(const std::string& path);
                const std::string& getPath() const;
                void setPath(const std::string& path);
                void store(const std::vector<Media::AbstractMedia*> medias);
                std::vector<Media::AbstractMedia*> load();
        };
    }
}

#endif