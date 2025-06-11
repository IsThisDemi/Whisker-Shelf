#ifndef MEDIA_ABSTRACT_MEDIA_H
#define MEDIA_ABSTRACT_MEDIA_H

#include <string>
#include <vector>
#include <random>

#include "IConstVisitor.h"
#include "IVisitor.h"
#include "MediaObserver.h"

namespace Media {
    class AbstractMedia {
        private:
            const unsigned int id;
            std::string title;
            std::string author;
            std::string description;
            std::string coverImage;
            MediaObserver *observer;
        
        protected:
            AbstractMedia(
                const unsigned int id, 
                const std::string title, 
                const std::string author,
                const std::string description,
                const std::string coverImage = ""
            );
        
        public:
            virtual ~AbstractMedia();
            unsigned int getId() const;
            const std::string getTitle() const;
            AbstractMedia& setTitle(const std::string title);
            const std::string getAuthor() const;
            AbstractMedia& setAuthor(const std::string author);
            const std::string getDescription() const;
            AbstractMedia& setDescription(const std::string description);
            
            virtual const std::string getCoverImage() const;
            virtual AbstractMedia& setCoverImage(const std::string coverImage);

            MediaObserver* getObserver() const;
            void setObserver(MediaObserver *newObserver);

            virtual AbstractMedia *clone() const = 0;
            virtual void accept(IConstVisitor& visitor) const = 0;
            virtual void accept(IVisitor& visitor) = 0;
    };
}


#endif