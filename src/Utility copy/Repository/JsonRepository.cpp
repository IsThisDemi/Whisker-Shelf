#include "JsonRepository.h" // Include the JsonRepository header file

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
            // Iterate through the repository and delete all sensor objects
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
        const std::map<unsigned int, Sensor::AbstractSensor *> &JsonRepository::getRepository() const
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

        // Create a new sensor entry in the repository
        void JsonRepository::create(Sensor::AbstractSensor *sensor)
        {
            repository[sensor->getId()] = sensor; // Add the sensor to the repository with its ID as the key
        }

        // Read a sensor entry from the repository by ID
        Sensor::AbstractSensor *JsonRepository::read(const unsigned int id) const
        {
            auto it = repository.find(id); // Find the sensor by ID
            if (it == repository.end())
            {
                throw std::invalid_argument("Undefined id, sensor not found"); // Throw an exception if not found
            }
            return it->second; // Return the found sensor
        }

        // Update an existing sensor entry in the repository
        void JsonRepository::update(Sensor::AbstractSensor *sensor)
        {
            create(sensor); // Recreate the sensor entry (same as create)
        }

        // Remove a sensor entry from the repository by ID
        void JsonRepository::remove(const unsigned int id)
        {
            auto it = repository.find(id); // Find the sensor by ID
            if (it != repository.end())
            {
                delete it->second;    // Delete the sensor object
                repository.erase(it); // Remove the entry from the repository
            }
        }

        // Read all sensor entries from the repository
        std::vector<Sensor::AbstractSensor *> JsonRepository::readAll() const
        {
            std::vector<Sensor::AbstractSensor *> sensors; // Create a vector to hold sensors
            for (const auto &entry : repository)
            {
                sensors.push_back(entry.second); // Add each sensor to the vector
            }
            return sensors; // Return the vector of sensors
        }

        // Overwrite the repository with new sensor data
        void JsonRepository::overwrite(const std::vector<Sensor::AbstractSensor *> newSensors)
        {
            // Free the memory of current sensor objects
            for (const auto &pair : repository)
            {
                delete pair.second;
            }
            repository.clear(); // Clear the repository map

            // Iterate through the new sensors and add their clones to the repository
            for (Sensor::AbstractSensor *sensor : newSensors)
            {
                Sensor::AbstractSensor *clonedSensor = sensor->clone(); // Clone the sensor
                repository[clonedSensor->getId()] = clonedSensor;       // Add the clone to the repository
            }
        }

        // Store the repository data to a JSON file
        void JsonRepository::store()
        {
            data_mapper.store(readAll()); // Store all sensors to the file
        }

        // Load the repository data from a JSON file
        void JsonRepository::load()
        {
            std::vector<Sensor::AbstractSensor *> sensors(data_mapper.load()); // Load sensors from the file
            for (Sensor::AbstractSensor *sensor : sensors)
            {
                repository[sensor->getId()] = sensor; // Add each loaded sensor to the repository
            }
        }
    }
}
