#ifndef MEDIA_I_VISITOR_H
#define MEDIA_I_VISITOR_H

namespace Media
{
    class Book;
    class Article;
    class Audio;
    class Film;

    class IVisitor
    {
    public:
        virtual ~IVisitor(){};
        virtual void visit(Book &book) = 0;
        virtual void visit(Article &article) = 0;
        virtual void visit(Audio &audio) = 0;
        virtual void visit(Film &film) = 0;
    };
}
#endif