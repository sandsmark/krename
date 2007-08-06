/***************************************************************************
                         krenamemodel.cpp  -  description
                             -------------------
    begin                : Sun Apr 25 2007
    copyright            : (C) 2007 by Dominik Seichter
    email                : domseichter@web.de
***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "krenamemodel.h"

#include <klocale.h>

KRenameModel::KRenameModel( KRenameFile::List* vector )
    : QAbstractListModel(),
      m_vector( vector )
{

}

KRenameModel::~KRenameModel()
{

}

int KRenameModel::rowCount ( const QModelIndex & parent ) const
{
    return m_vector->size();
}

QVariant KRenameModel::data ( const QModelIndex & index, int role ) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_vector->size())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        return m_vector->at(index.row()).toString();
    }
    else
        return QVariant();
}

Qt::ItemFlags KRenameModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;
    
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool KRenameModel::setData(const QModelIndex &index,
                           const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
    
        //stringList.replace(index.row(), value.toString());
        emit dataChanged(index, index);
        return true;
    }
 
    return false;
}

void KRenameModel::addFile( const KRenameFile & file )
{
    this->beginInsertRows( QModelIndex(), 0, m_vector->size() );
    m_vector->push_back( file );
    this->endInsertRows();
}

void KRenameModel::removeFiles( const QList<int> & remove )
{
    int offset = 0;

    QList<int> copy( remove );
    qSort( copy );

    QList<int>::const_iterator it = copy.begin();
    this->beginRemoveRows( QModelIndex(), *it, copy.back() );
    while( it != copy.end() )
    {
        qDebug("About to remove: %i\n", *it );
        m_vector->erase( m_vector->begin() + *it - offset );

        ++offset;
        ++it;
    }

    this->endRemoveRows();
}


KRenamePreviewModel::KRenamePreviewModel( KRenameFile::List* vector )
    : m_vector( vector )
{

}

KRenamePreviewModel::~KRenamePreviewModel()
{

}

int KRenamePreviewModel::rowCount ( const QModelIndex & parent ) const
{
    return m_vector->size();
}

int KRenamePreviewModel::columnCount ( const QModelIndex & parent ) const
{
    return 2;
}

QVariant KRenamePreviewModel::headerData ( int section, Qt::Orientation orientation, int role ) const
{
    if (orientation != Qt::Horizontal || section >= 2 || role != Qt::DisplayRole )
        return QVariant();

    return section ? i18n("Origin") : i18n("Renamed");
} 

QVariant KRenamePreviewModel::data ( const QModelIndex & index, int role ) const
{
    if (!index.isValid())
        return QVariant();
    
    if (index.row() >= m_vector->size())
        return QVariant();
    
    if (index.column() >= 2 )
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        KRenameFile file = m_vector->at(index.row());
        QString filename;
        QString extension;

        if( index.column() )
        {
            filename  = file.dstFilename();
            extension = file.dstExtension();
        }
        else
        {
            filename  = file.srcFilename();
            extension = file.srcExtension();
        }

        if( !extension.isEmpty() )
        {
            filename += ".";
            filename += extension;
        }

        if( filename.isEmpty() )
        {
            filename = index.column() ? file.dstDirectory() : file.srcDirectory();
        }

        return filename;
    }
    else
        return QVariant();
    
}

QModelIndex KRenamePreviewModel::parent ( const QModelIndex & index ) const
{
    return QModelIndex();
}

QModelIndex KRenamePreviewModel::sibling ( int row, int column, const QModelIndex & index ) const
{
    return QModelIndex();
}

void KRenamePreviewModel::refresh() 
{
    emit reset();
}


#include "krenamemodel.moc"