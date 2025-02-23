#include "Secondary_window.h"

Secondary_window::Secondary_window(Mylist_table_model* model, QWidget* parent) : model{model}, QWidget(parent)
{
	ui.setupUi(this);
	ui.mylist_table_view->setModel(model);
	
}

Secondary_window::~Secondary_window()
{
}
