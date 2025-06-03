#include "JsonFile.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>  

namespace Utility
{
    namespace DataMapper
    {
        // Constructor to initialize JsonFile with a file path
        JsonFile::JsonFile(const std::string &path)
            : path(path)  // Initialize the path member with the provided path
        {
        }

        // Static method to create a JsonFile instance from a file path
        JsonFile JsonFile::fromPath(const std::string &path)
        {
            JsonFile data_mapper(path);  // Create a JsonFile object with the specified path
            return data_mapper;  // Return the created object
        }

        // Getter for the file path
        const std::string &JsonFile::getPath() const
        {
            return path;  // Return the current file path
        }

        // Setter for the file path
        void JsonFile::setPath(const std::string &path)
        {
            this->path = path;  // Set the path member to the new path
        }

        // Store media data to a JSON file
        void JsonFile::store(const std::vector<Media::AbstractMedia *> medias)
        {
            QJsonArray json_medias;  // Create a JSON array to hold media data

            // Iterate over the medias and convert each to a JSON object
            for (const Media::AbstractMedia* media : medias)
            {
                json_medias.push_back(Converter::Json::Json::fromObject(*media));
            }

            QJsonDocument document(json_medias);  // Create a JSON document from the array
            QFile json_file(path.c_str());  // Open the file at the specified path
            json_file.open(QFile::WriteOnly);  // Open the file in write-only mode
            json_file.write(document.toJson());  // Write the JSON data to the file
            json_file.close();  // Close the file
        }

        // Load media data from a JSON file
        std::vector<Media::AbstractMedia *> JsonFile::load()
        {
            std::vector<Media::AbstractMedia *> medias;  // Create a vector to hold the media objects
            QFile json_file(path.c_str());  // Open the file at the specified path
            json_file.open(QFile::ReadOnly);  // Open the file in read-only mode
            QByteArray data = json_file.readAll();  // Read all data from the file
            json_file.close();  // Close the file

            QJsonDocument document = QJsonDocument::fromJson(data);  // Create a JSON document from the data
            QJsonArray json_medias = document.array();  // Get the JSON array from the document

            // Iterate over the JSON array and convert each JSON object to a media object
            for (const QJsonValue &value : json_medias)
            {
                QJsonObject json_object = value.toObject();
                medias.push_back(&(Converter::Json::Json::toObject(json_object)));
            }

            return medias;  // Return the vector of media objects
        }
    }
}