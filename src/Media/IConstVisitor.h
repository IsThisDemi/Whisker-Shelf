#ifndef MEDIA_I_CONST_VISITOR_H
#define MEDIA_I_CONST_VISITOR_H

namespace Media {
    class Book;
    class Article;
    class Audio;
    class Film;

    class IConstVisitor {
        public:
            virtual ~IConstVisitor() = default;
            virtual void visit(const Book& book) = 0;
            virtual void visit(const Article& article) = 0;
            virtual void visit(const Audio& audio) = 0;
            virtual void visit(const Film& film) = 0;
    };
}
#endif