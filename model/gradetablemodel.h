#ifndef GRADETABLEMODEL_H
#define GRADETABLEMODEL_H

#include <QAbstractTableModel>
#include <QDebug>

#include "exceptions/nullpointerexception.h"
#include "studycourse.h"

using std::vector;

class GradeTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit GradeTableModel(QObject *parent = 0);

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation,
                                int role) const override;

    void populate(const StudyCourse *studyCourse) throw (NullPointerException);

protected:
    vector<vector<QVariant> > mColumns;
};

#endif // GRADETABLEMODEL_H
