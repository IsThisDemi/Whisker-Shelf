#include "JsonRepository.h"

namespace Utility
{
    namespace Repository
    {

        // Constructor that initializes the repository with a DataMapper and loads data
        JsonRepository::JsonRepository(DataMapper::JsonFile data_mapper) : data_mapper(data_mapper)
        {
            load(); // Load data from the file
        }

        // Destructor to clean up dynamically allocated memory
        JsonRepository::~JsonRepository()
        {
            // Iterate through the repository and delete all media objects
            for (const auto &pair : repository)
            {
                delete pair.second;
            }
            repository.clear(); // Clear the repository map
        }

        // Static method to create a JsonRepository from a file path
        JsonRepository JsonRepository::fromPath(const std::string path)
        {
            DataMapper::JsonFile data_mapper = DataMapper::JsonFile::fromPath(path); // Create a DataMapper from the path
            JsonRepository repository(data_mapper);                                  // Create a JsonRepository with the DataMapper
            return repository;                                                       // Return the created repository
        }

        // Get the DataMapper object
        const DataMapper::JsonFile &JsonRepository::getDataMapper() const
        {
            return data_mapper; // Return the data_mapper
        }

        // Get the repository map
        const std::map<unsigned int, Media::AbstractMedia *> &JsonRepository::getRepository() const
        {
            return repository; // Return the repository map
        }

        // Get the path of the data file
        const std::string &JsonRepository::getPath() const
        {
            return data_mapper.getPath(); // Return the file path from the data_mapper
        }

        // Set the path of the data file
        void JsonRepository::setPath(std::string path)
        {
            data_mapper.setPath(path); // Set the new path in the data_mapper
        }

        // Create a new media entry in the repository
        void JsonRepository::create(Media::AbstractMedia *media)
        {
            repository[media->getId()] = media; // Add the media to the repository with its ID as the key
        }

        // Read a media entry from the repository by ID
        Media::AbstractMedia *JsonRepository::read(const unsigned int id) const
        {
            auto it = repository.find(id); // Find the media by ID
            if (it == repository.end())
            {
                throw std::invalid_argument("Undefined id, media not found"); // Throw an exception if not found
            }
            return it->second; // Return the found media
        }

        // Update an existing media entry in the repository
        void JsonRepository::update(Media::AbstractMedia *media)
        {
            create(media); // Recreate the media entry (same as create)
        }

        // Remove a media entry from the repository by ID
        void JsonRepository::remove(const unsigned int id)
        {
            auto it = repository.find(id); // Find the media by ID
            if (it != repository.end())
            {
                delete it->second;    // Delete the media object
                repository.erase(it); // Remove the entry from the repository
            }
        }

        // Read all medias entries from the repository
        std::vector<Media::AbstractMedia *> JsonRepository::readAll() const
        {
            std::vector<Media::AbstractMedia *> medias; // Create a vector to hold medias
            for (const auto &entry : repository)
            {
                medias.push_back(entry.second); // Add each media to the vector
            }
            return medias; // Return the vector of medias
        }

        // Overwrite the repository with new media data
        void JsonRepository::overwrite(const std::vector<Media::AbstractMedia *> newMedias)
        {
            // Free the memory of current media objects
            for (const auto &pair : repository)
            {
                delete pair.second;
            }
            repository.clear(); // Clear the repository map

            // Iterate through the new medias and add their clones to the repository
            for (Media::AbstractMedia *media : newMedias)
            {
                Media::AbstractMedia *clonedMedia = media->clone(); // Clone the media
                repository[clonedMedia->getId()] = clonedMedia;       // Add the clone to the repository
            }
        }

        // Store the repository data to a JSON file
        void JsonRepository::store()
        {
            data_mapper.store(readAll()); // Store all medias to the file
        }

        // Load the repository data from a JSON file
        void JsonRepository::load()
        {
            std::vector<Media::AbstractMedia *> medias(data_mapper.load()); // Load medias from the file
            for (Media::AbstractMedia *media : medias)
            {
                repository[media->getId()] = media; // Add each loaded media to the repository
            }
        }
    }
}
