#include "ImageTree.hpp"

#include <QtGui/QKeyEvent>

#include "AnimationController.hpp"



ImageTree::ImageTree(QWidget* parent) :
    QTreeWidget(parent)
{

}



void ImageTree::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_PageUp) {
        auto selectionIndex(selectionModel()->currentIndex());
        auto newSelectionIndex(selectionIndex.siblingAtRow(selectionIndex.row() - AnimationController::IMAGE_ANIMATION_STEP));
        if (!newSelectionIndex.isValid()) {
            newSelectionIndex = selectionIndex.siblingAtRow(0);
        }
        selectionModel()->setCurrentIndex(newSelectionIndex, QItemSelectionModel::SelectCurrent);
    }
    else if (event->key() == Qt::Key_PageDown) {
        auto selectionIndex(selectionModel()->currentIndex());
        auto newSelectionIndex(selectionIndex.siblingAtRow(selectionIndex.row() + AnimationController::IMAGE_ANIMATION_STEP));
        if (!newSelectionIndex.isValid()) {
            newSelectionIndex = selectionIndex.siblingAtRow(model()->rowCount() - 1);
        }
        selectionModel()->setCurrentIndex(newSelectionIndex, QItemSelectionModel::SelectCurrent);
    }
    else {
        QTreeWidget::keyPressEvent(event);
    }
}
