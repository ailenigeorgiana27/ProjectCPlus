#pragma once
#include <qwidget.h>
#include <qpainter.h>
#include <qcolor.h>
#include <QPaintEvent>
#include <ctime>
#include <cstdlib>
#include "service.h"
#include "CosFilme.h"
#include "observator.h"
#include <QRandomGenerator>


class CosReadOnlyGUI : public QWidget, public Observator {
public:
	CosReadOnlyGUI(Service& service, CosInchirieriFilme& cos) : service{ service }, cos{ cos } {
		initGUI();
		cos.adaugaObservator(this);
	}

private:
	Service& service;
	CosInchirieriFilme& cos;
	void initGUI() {
		setWindowTitle("Cos Read Only");
	}

	void paintEvent(QPaintEvent* event) override {
		QPainter painter(this);
		for (int i = 0; i < cos.get_lungime(); ++i) {

			int x = QRandomGenerator::global()->bounded(width());
			int y = QRandomGenerator::global()->bounded(height());

			int diameter = 20;
			painter.setBrush(Qt::blue);
			painter.drawEllipse(x, y, diameter, diameter);

		}
	}

	void updateaza() override {
		repaint();
	}
};