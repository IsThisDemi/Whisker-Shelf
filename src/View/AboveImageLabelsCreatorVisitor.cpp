#include "AboveImageLabelsCreatorVisitor.h"

namespace View {

AboveImageLabelsCreatorVisitor::AboveImageLabelsCreatorVisitor(AboveImageWidget* aboveImageWidget)
    : aboveImageWidget(aboveImageWidget) {}

void AboveImageLabelsCreatorVisitor::visit(const Media::Article& article) {
    // Chiama il metodo di AboveImageWidget per Article
    aboveImageWidget->createTheRestOfLabelsArticle(
        article.getJournalName(),
        article.getVolumeNumber(),
        article.getPageCount(),
        article.getDoi()
    );
}

void AboveImageLabelsCreatorVisitor::visit(const Media::Audio& audio) {
    // Chiama il metodo di AboveImageWidget per Audio
    aboveImageWidget->createTheRestOfLabelsAudio(
        audio.getFormat(),
        audio.getAlbum(),
        audio.getDuration()
    );
}

void AboveImageLabelsCreatorVisitor::visit(const Media::Book& book) {
    // Chiama il metodo di AboveImageWidget per Book
    aboveImageWidget->createTheRestOfLabelsBook(
        book.getPublisher(),
        book.getGenre(),
        book.getIsbn(),
        book.getPageCount()
    );
}

void AboveImageLabelsCreatorVisitor::visit(const Media::Film& film) {
    // Chiama il metodo di AboveImageWidget per Film
    aboveImageWidget->createTheRestOfLabelsFilm(
        film.getProductionCompany(),
        film.getGenre(),
        film.getDuration(),
        film.getBudget()
    );
}

}
