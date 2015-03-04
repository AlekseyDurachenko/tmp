// Copyright 2015, Durachenko Aleksey V. <durachenko.aleksey@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
#ifndef CBOOKMARKFILTERDATAMODEL_H
#define CBOOKMARKFILTERDATAMODEL_H

#include <QObject>
class CBookmarkMgr;
class CBookmarkItem;
class CAbstractBookmarkFilter;


class CBookmarkFilterDataModel : public QObject
{
    Q_OBJECT
public:
    explicit CBookmarkFilterDataModel(CBookmarkMgr *bookmarkMgr,
                                      QObject *parent = 0);
    virtual ~CBookmarkFilterDataModel();

    inline CBookmarkMgr *bookmarkMgr() const;
    void setBookmarkMgr(CBookmarkMgr *bookmarkMgr);

    inline CAbstractBookmarkFilter *filter() const;
    void setFilter(CAbstractBookmarkFilter *filter);

    inline int count() const;
    inline int indexOf(CBookmarkItem *item) const;
    inline CBookmarkItem *at(int index) const;
    inline QList<CBookmarkItem *> bookmarks() const;
signals:
    void inserted(int first, int last);
    void removed(int first, int last);
    void dataChanged(int first, int last);
    void reseted();
private:
    void invalidate();
    void invalidate(CBookmarkItem *item, bool hasDataChanges = false);
    void insert(CBookmarkItem *item);
    void remove(int index);
private slots:
    void filter_changed();
    void filter_destroyed();
    void bookmarkMgr_inserted(int first, int last);
    void bookmarkMgr_aboutToBeRemoved(int first, int last);
    void bookmarkMgr_dataChanged(CBookmarkItem *item);
    void bookmarkMgr_tagsChanged(CBookmarkItem *item);
    void bookmarkMgr_destroyed();
private:
    CBookmarkMgr *m_bookmarkMgr;
    QList<CBookmarkItem *> m_bookmarks;
    CAbstractBookmarkFilter *m_filter;
};

CBookmarkMgr *CBookmarkFilterDataModel::bookmarkMgr() const
{
    return m_bookmarkMgr;
}

CAbstractBookmarkFilter *CBookmarkFilterDataModel::filter() const
{
    return m_filter;
}

int CBookmarkFilterDataModel::count() const
{
    return m_bookmarks.count();
}

int CBookmarkFilterDataModel::indexOf(CBookmarkItem *item) const
{
    return m_bookmarks.indexOf(item);
}

CBookmarkItem *CBookmarkFilterDataModel::at(int index) const
{
    return m_bookmarks.at(index);
}

QList<CBookmarkItem *> CBookmarkFilterDataModel::bookmarks() const
{
    return m_bookmarks;
}


#endif // CBOOKMARKFILTERDATAMODEL_H