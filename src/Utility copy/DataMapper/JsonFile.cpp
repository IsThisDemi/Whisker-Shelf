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

        // Store sensor data to a JSON file
        void JsonFile::store(const std::vector<Sensor::AbstractSensor *> sensors)
        {
            QJsonArray json_sensors;  // Create a JSON array to hold sensor data

            // Iterate over the sensors and convert each to a JSON object
            for (const Sensor::AbstractSensor* sensor : sensors)
            {
                json_sensors.push_back(Converter::Json::Json::fromObject(*sensor));
            }

            QJsonDocument document(json_sensors);  // Create a JSON document from the array
            QFile json_file(path.c_str());  // Open the file at the specified path
            json_file.open(QFile::WriteOnly);  // Open the file in write-only mode
            json_file.write(document.toJson());  // Write the JSON data to the file
            json_file.close();  // Close the file
        }

        // Load sensor data from a JSON file
        std::vector<Sensor::AbstractSensor *> JsonFile::load()
        {
            std::vector<Sensor::AbstractSensor *> sensors;  // Create a vector to hold the sensor objects
            QFile json_file(path.c_str());  // Open the file at the specified path
            json_file.open(QFile::ReadOnly);  // Open the file in read-only mode
            QByteArray data = json_file.readAll();  // Read all data from the file
            json_file.close();  // Close the file

            QJsonDocument document = QJsonDocument::fromJson(data);  // Create a JSON document from the data
            QJsonArray json_sensors = document.array();  // Get the JSON array from the document

            // Iterate over the JSON array and convert each JSON object to a sensor object
            for (const QJsonValue &value : json_sensors)
            {
                QJsonObject json_object = value.toObject();
                sensors.push_back(&(Converter::Json::Json::toObject(json_object)));
            }

            return sensors;  // Return the vector of sensor objects
        }
    }
}