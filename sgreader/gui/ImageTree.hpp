#ifndef IMAGETREE_HPP
#define IMAGETREE_HPP

#include <QtWidgets/QTreeWidget>

class ImageTree : public QTreeWidget
{
        Q_OBJECT

    public:
        ImageTree(QWidget *parent = nullptr);

    protected:
        void keyPressEvent(QKeyEvent* event);
};

#endif // IMAGETREE_HPP
