#include "ChipModel.h"

#include <QIcon>
#include <QUuid>
#include <QDebug>

Chip::Chip(QObject* parent) : QAbstractListModel(parent)
{
}

int Chip::rowCount(const QModelIndex &parent) const
{
    return annotations.size();
}

QVariant Chip::data(const QModelIndex &index, int role) const
{
        if (!index.isValid()) return QVariant();
        if (index.row() >= annotations.size()) return QVariant();

        if (role == Qt::DisplayRole)
        {
            return QVariant(annotations.at(index.row()).l);
        }
        else if (role == Qt::DecorationRole)
        {
                return QVariant(QIcon(":/i/i/cpu-ARM-icon.png"));
        }
        else
        {
            return QVariant();
        }
}

int Chip::getAnnotationsListSize()
{
    return annotations.size();
}

bool Chip::isAnnotationsListEmpty()
{
    return annotations.empty();
}

QList<Annotation>::const_iterator Chip::getBeginAnnotations() const
{
    return annotations.constBegin();
}

QList<Annotation>::const_iterator Chip::getEndAnnotations() const
{
    return annotations.constEnd();
}

void Chip::clearModel()
{
    beginResetModel();
    annotations.clear();
    endResetModel();
    emit onAnnotationModelChanged();
}


void Chip::addSome()
{
    beginInsertRows( QModelIndex(), 0, 0 );
    annotations.push_back(Annotation(QUuid::createUuid().toString().mid(1, 4), 1, 2));
    endInsertRows();
    emit onAnnotationModelChanged();
}

void Chip::removeAt(int index)
{
    beginRemoveRows(QModelIndex(), 0, 0);
    annotations.removeAt(index);
    endRemoveRows();
    emit onAnnotationModelChanged();
}

void Chip::updateAt(const QModelIndex& index)
{
    annotations[index.row()].l ="@new";
    emit dataChanged(index, index);
    emit onAnnotationModelChanged();
}

