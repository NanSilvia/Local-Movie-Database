#pragma once
#include <qabstractitemdelegate.h>
#include "Repository_interface.h"
#include <qvariant.h>

#define NUMBER_OF_COLUMNS 5

class Mylist_table_model : public QAbstractTableModel
{
private:
	Repository_interface* repository;

public:
	Mylist_table_model(Repository_interface* repository) : repository{ repository } {};

	int rowCount(const QModelIndex& parent = QModelIndex()) const;

	int columnCount(const QModelIndex& parent = QModelIndex()) const;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
};

