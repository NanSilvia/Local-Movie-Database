#include "Mylist_table_model.h"
#include "Domain.h"

int Mylist_table_model::rowCount(const QModelIndex& parent) const
{
    return this->repository->get_length();
}

int Mylist_table_model::columnCount(const QModelIndex& parent) const
{
    return NUMBER_OF_COLUMNS;
}

QVariant Mylist_table_model::data(const QModelIndex& index, int role) const
{
    int row = index.row();
    int column = index.column();
    Movie current_movie = this->repository->get_all()[row];
    if (role == Qt::DisplayRole) {
        switch (column)
        {
        case 0:
            return QString::fromStdString(current_movie.get_title());
        case 1:
            return QString::fromStdString(current_movie.get_genre());
        case 2:
            return QString::number(current_movie.get_year_of_release());
        case 3:
            return QString::number(current_movie.get_number_of_likes());
        case 4:
            return QString::fromStdString(current_movie.get_trailer());
        default:
            break;
        }
    }
    return QVariant();
}

QVariant Mylist_table_model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if(orientation == Qt::Horizontal)
            switch (section)
            {
            case 0:
                return QString("Title");
            case 1:
                return QString("Genre");
            case 2:
                return QString("Year of release");;
            case 3:
                return QString("Number of likes");;
            case 4:
                return QString("Trailer");
            default:
                break;
            }
        }

    return QVariant();
}
