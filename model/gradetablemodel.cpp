#include "gradetablemodel.h"

GradeTableModel::GradeTableModel(QObject *parent) :
    QAbstractTableModel(parent),
    mColumns(vector<vector<QVariant> >())
{
    mColumns.push_back(vector<QVariant>());
}

int GradeTableModel::rowCount(const QModelIndex &parent) const
{
    return mColumns[0].size();
}

int GradeTableModel::columnCount(const QModelIndex &parent) const
{
    return mColumns.size();
}

QVariant GradeTableModel::data(const QModelIndex &index, int role) const
{
    return (role == Qt::DisplayRole)
            ? mColumns[index.column()][index.row()]
            : QVariant::Invalid;
}

QVariant GradeTableModel::headerData(int section, Qt::Orientation orientation,
                                     int role) const
{
    if (!role == Qt::DisplayRole)
        return QVariant::Invalid;

    if (orientation == Qt::Horizontal) {
        return QString("H%1").arg(section);
    } else if (orientation == Qt::Vertical) {
        return QString("V%1").arg(section);
    }
}

void GradeTableModel::populate(const StudyCourse *studyCourse)
    throw (NullPointerException)
{
    if (!studyCourse)
        throw NullPointerException("Given studyCourse it null pointer");

    mColumns.clear();

    QList<Course *> courses = studyCourse->getCourses();
    foreach (Course *c, courses) {
        vector<QVariant> col;
        col.push_back(c->getSemester());
        col.push_back(QString("%1 (%2)").arg(c->getName()).arg(c->getShortname()));
        col.push_back(c->getEcts());
        col.push_back(c->getGrade());
        mColumns.push_back(col);
    }
}
