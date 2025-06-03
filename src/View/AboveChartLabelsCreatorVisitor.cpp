#include "AboveChartLabelsCreatorVisitor.h"

namespace View
{

    // Constructor initializing the AboveChartWidget pointer
    AboveChartLabelsCreatorVisitor::AboveChartLabelsCreatorVisitor(AboveChartWidget *aboveChartWidget)
        : aboveChartWidget(aboveChartWidget) {}

    // Visit method for Article media
    void AboveChartLabelsCreatorVisitor::visit(const Media::Article &article)
    {
        // Create labels for Article media with its page count
        aboveChartWidget->createTheRestOfLabelsArticle(
            article.getJournalName(),
            article.getVolumeNumber(),
            article.getPageCount(),
            article.getDoi());
    }

    // Visit method for Audio media
    void AboveChartLabelsCreatorVisitor::visit(const Media::Audio &audio)
    {
        // Create labels for Audio media with its duration
        aboveChartWidget->createTheRestOfLabelsAudio(
            audio.getFormat(),
            audio.getArtist(),
            audio.getAlbum(),
            audio.getDuration());
    }

    // Visit method for Book media
    void AboveChartLabelsCreatorVisitor::visit(const Media::Book &book)
    {
        // Create labels for Book media with its page count
        aboveChartWidget->createTheRestOfLabelsBook(
            book.getPublisher(),
            book.getGenre(),
            book.getIsbn(),
            book.getPageCount());
    }

    // Visit method for Film media
    void AboveChartLabelsCreatorVisitor::visit(const Media::Film &film)
    {
        // Create labels for Film media with its duration
        aboveChartWidget->createTheRestOfLabelsFilm(
            film.getDirector(),
            film.getGenre(),
            film.getDuration(),
            film.getBudget());
    }

}
