/***************************************************************************
                          krenamefile.h  -  description
                             -------------------
    begin                : Wed Apr 18 2007
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

#ifndef _KRENAME_FILE_H_
#define _KRENAME_FILE_H_

#include <QVector>

#include <kurl.h>

/** An enum to describe the mode to split 
 *  filename and extension.
 */
enum ESplitMode {
    eSplitMode_FirstDot, ///< Extension starts at the first dot found in the filename
    eSplitMode_LastDot,  ///< Extension starts at the last dot found in the filename
    eSplitMode_CustomDot ///< Extension starts at a user defined dot in the filename
};

class KRenameFile {
    typedef struct TFileDescription {
        QString filename;
        QString extension;
        QString directory;
        
        KUrl    url;

        const TFileDescription & operator=( const TFileDescription & rhs ) 
        {
            filename  = rhs.filename;
            extension = rhs.extension;
            directory = rhs.directory;
            url       = rhs.url;

            return *this;
        }
    };

 public:
    /** A list of KRenameFile objects
     */
    typedef QVector<KRenameFile> List;

    /** Empty default constructor
     *  which creates an invalid KRenameFile.
     *
     *  \see isValid
     */
    KRenameFile()
        : m_bValid( false )
    {
    }

    /** Construct a new KRenameFile from an url.
     *  
     *  The url will be tested for existance
     *  and isValid() returns only true
     *  if the url is existing.
     *
     *  \param src an url of a file or directory
     *  \param eSplitMode splitmode which is used to separate
     *                    filename and extension
     *  \param dot dot to use as separator for eSplitMode_CustomDot
     *  \see isValid()
     */
    KRenameFile( KUrl src, ESplitMode eSplitMode = eSplitMode_FirstDot, unsigned int dot = 1 );

    /** Construct a new KRenameFile from an url.
     *
     *  The url is expected to exist and is not 
     *  tested for existance. This is much faster than
     *  the other constructor.
     *
     *  \param src an url of a file or directory
     *  \param directory must be true if the url referes
     *                   to a directory.
     *  \param eSplitMode splitmode which is used to separate
     *                    filename and extension
     *  \param dot dot to use as separator for eSplitMode_CustomDot
     */
    KRenameFile( KUrl src, bool directory, ESplitMode eSplitMode = eSplitMode_FirstDot, unsigned int dot = 1 );

    /** Copy constructor
     *  \param rhs KRenameFile to copy
     */
    KRenameFile( const KRenameFile & rhs );

    /** Set the splitmode to separate filename from fileextension
     *  
     *  \param eSplitMode splitmode which is used to separate
     *                    filename and extension
     *  \param dot dot to use as separator for eSplitMode_CustomDot
     *
     *  \see srcFilename() 
     *  \see srcExtension()
     */
    void setCurrentSplitMode( ESplitMode eSplitMode, unsigned int dot = 1 );

    /** Convert the KRenameFile into a string
     *  that can be displayed to the user.
     *
     *  \returns original source url as string representation
     */
    inline const QString toString() const
    {
        return m_src.url.prettyUrl();
    }        

    /** Assigns another KRenameFile to this KRenameFile
     *  \param rhs object to assign
     */
    const KRenameFile & operator=( const KRenameFile & rhs );

    /** 
     * \returns true if this file references 
     *               an existing file or directory
     */
    inline bool isValid() const
    {
        return m_bValid;
    }

    inline const QString & srcFilename() const 
    {
        return m_src.filename;
    }

    inline const QString & srcExtension() const 
        {
            return m_src.extension;
        }

    inline const QString & srcDirectory() const 
        {
            return m_src.directory;
        }

    inline const KUrl & srcUrl() const 
        {
            return m_src.url;
        }

    inline void setDstFilename( const QString & filename ) 
        {
            m_dst.filename = filename;
        }

    inline const QString & dstFilename() const 
        {
            return m_dst.filename;
        }

    inline void setDstExtension( const QString & extension ) 
        {
            m_dst.extension = extension;
        }

    inline const QString & dstExtension() const 
        {
            return m_dst.extension;
        }

    inline void setDstDirectory( const QString & directory ) 
        {
            m_dst.directory = directory;
        }

    inline const QString & dstDirectory() const 
        {
            return m_dst.directory;
        }

    inline void setDstUrl( const KUrl & url ) 
        {
            m_dst.url = url;
        }

    inline const KUrl & dstUrl() const 
        {
            return m_dst.url;
        }

    inline bool isDirectory() const
        {
            return m_bDirectory;
        }

 private:
    void initFileDescription( TFileDescription & rDescription, const KUrl & url, ESplitMode eSplitMode, unsigned int dot ) const;

 private:
    TFileDescription m_src;
    TFileDescription m_dst;

    bool             m_bDirectory;
    bool             m_bValid;
};

#endif // _KRENAME_FILE_H_
