#include "tableModel.h"
#include <QMessageBox>

TableModel::TableModel(QObject* parent) : QAbstractTableModel(parent) {};

QVariant TableModel::data(const QModelIndex& index, int role) const {
	const int row = index.row();
	const int column = index.column();
	if (role == Qt::DisplayRole)
	{
		switch (column)
		{
		case 0: return QString::fromStdString(listaFilme.at(row).getTitluFilm());
		case 1: return QString::fromStdString(listaFilme.at(row).getGenFilm());
		case 2: return QString::number(listaFilme.at(row).getAnAparitie());
		case 3: return QString::fromStdString(listaFilme.at(row).getActorPrincipal());
		}
		return QString("R%1, C%2").arg(index.row() + 1).arg(index.column() + 1);
	}
	return QVariant();
}

int TableModel::rowCount(const QModelIndex&) const {
	return (int)(listaFilme.size());
}
int TableModel::columnCount(const QModelIndex&) const {
	return 4;
}
QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal)
		{
			switch (section)
			{
			case 0: return QString("Titlu");
			case 1: return QString("Gen");
			case 2: return QString("An");
			case 3: return QString("Actor");

			}
			return QString("col %1").arg(section);
		}
		else {
			return QString("%1").arg(section);
		}
	}
	return QVariant();
}
void TableModel::setList(const vector<Film>& _carList)
{
	this->listaFilme = _carList;
	const QModelIndex topLeft = createIndex(0, 0);
	const QModelIndex bottomRight = createIndex(rowCount(), columnCount());
	dataChanged(topLeft, bottomRight);
	layoutChanged();
}