#ifndef SLAMANNOTATION_H
#define SLAMANNOTATION_H

#include <QAbstractListModel>

struct Annotation
{
Annotation(QString _l, int _x, int _y) :
    l{_l}, x{_x}, y{_y} {}
    QString l{"123"};
    int x{};
    int y{};

    operator QString() const
    {
        return l;
    }
};

class Chip : public QAbstractListModel
{	Q_OBJECT

public:
    explicit Chip(QObject* parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    int getAnnotationsListSize();
    bool isAnnotationsListEmpty();
    QList<Annotation>::const_iterator getBeginAnnotations() const;
    QList<Annotation>::const_iterator getEndAnnotations() const;

    void addSome();
    void removeAt(int index);
    void updateAt(const QModelIndex& index);

private:
    QList<Annotation> annotations;
};

#endif // SLAMANNOTATION_H
