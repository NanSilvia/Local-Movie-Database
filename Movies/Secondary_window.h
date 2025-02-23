#pragma once

#include <QWidget>
#include "ui_Secondary_window.h"
#include "Mylist_table_model.h"

class Secondary_window : public QWidget
{
	Q_OBJECT

public:
	Secondary_window(Mylist_table_model* model, QWidget *parent = Q_NULLPTR);
	~Secondary_window();

private:
	Ui::Secondary_window ui;
	Mylist_table_model* model;

};
