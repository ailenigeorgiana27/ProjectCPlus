#pragma once
#include "service.h"
#include "observator.h"
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qmessagebox.h>
#include <qtablewidget.h>
#include <qdebug.h>
#include <QFormLayout>
#include <qfont.h>
#include <QTextEdit>
#include <vector>
#include <string>

class CosCRUDGUI : public QWidget, public Observator {
public:
    CosCRUDGUI(Service& service, CosInchirieriFilme& cos) : service{ service }, cos{ cos } {
        initGUI();
        loadData();
        initConnect();
        cos.adaugaObservator(this);
    }



private:
    Service& service;
    CosInchirieriFilme& cos;


    QListWidget* listaInchirieri = new QListWidget;
    QPushButton* butonAdaugareInCos = new QPushButton{ "&Adaugă în cos" };
    QPushButton* butonGolireCos = new QPushButton{ "&Golește cosul" };
    QPushButton* butonAdaugareRandomInCos = new QPushButton{ "&Adaugă random în cos" };


    QLineEdit* titluEdit = new QLineEdit;
    QLineEdit* anAparitieEdit = new QLineEdit;
    QLineEdit* txtActor = new QLineEdit;
    QLineEdit* actorPrincipalEdit = new QLineEdit;
    QLineEdit* nrFilme = new QLineEdit;

    void initGUI() {
        setWindowTitle("Cos filme crud");
        auto layoutPrincipalCos = new QVBoxLayout;
        auto layoutButoaneCosInchirieri = new QHBoxLayout;
        auto layout_campuri = new QFormLayout;

        layoutButoaneCosInchirieri->addWidget(butonAdaugareInCos);
        layoutButoaneCosInchirieri->addWidget(butonAdaugareRandomInCos);
        layoutButoaneCosInchirieri->addWidget(butonGolireCos);

        setLayout(layoutPrincipalCos);

        layout_campuri->addRow("Titlu", titluEdit);
        layout_campuri->addRow("Gen", anAparitieEdit);
        layout_campuri->addRow("An", actorPrincipalEdit);
        layout_campuri->addRow("Actor", txtActor);
        layout_campuri->addRow("Nr filme Random: ", nrFilme);

        auto* lyDreapta = new QVBoxLayout;
        lyDreapta->addLayout(layout_campuri);
        lyDreapta->addLayout(layoutButoaneCosInchirieri);

        layoutPrincipalCos->addWidget(listaInchirieri);
        layoutPrincipalCos->addLayout(lyDreapta);
    }

    void loadData() {
        vector<Film> filme = cos.getAllCosInchirieri();
        listaInchirieri->clear();
        QString titlu, gen, an, actor;

        for (const auto& film : filme) {
            titlu = QString::fromStdString(film.getTitluFilm());
            gen = QString::fromStdString(film.getGenFilm());
            an = QString::fromStdString(to_string(film.getAnAparitie()));
            actor = QString::fromStdString(film.getActorPrincipal());
            listaInchirieri->addItem(titlu + " - " + gen + " - " + an + " - " + actor);
        }

    }

    void initConnect() {
        QObject::connect(butonAdaugareInCos, &QPushButton::clicked, [&]() {
            auto titlu = titluEdit->text().toStdString();
            auto gen = anAparitieEdit->text().toStdString();
            auto an = actorPrincipalEdit->text().toInt();
            auto actor = txtActor->text().toStdString();

            if (service.cautaFilm(titlu)) {
                Film film{ titlu, gen, an, actor };
                cos.adaugaCosInchirieri(film);

                vector<Film> filme = cos.getAllCosInchirieri();
                loadData();
            }
            else
                QMessageBox::warning(this, "Atenție!", "Filmul nu există în baza de date!");
            titluEdit->clear();
            anAparitieEdit->clear();
            actorPrincipalEdit->clear();
            txtActor->clear();

            });

        QObject::connect(butonGolireCos, &QPushButton::clicked, [&]() {
            cos.golesteCosInchirieri();
            listaInchirieri->clear();
            });

        QObject::connect(butonAdaugareRandomInCos, &QPushButton::clicked, [&]() {
            if (nrFilme->text().isEmpty()) {
                QMessageBox::critical(this, "Eroare", "Numarul de filme nu poate fi vid!");
                return;
            }

            cos.golesteCosInchirieri();
            int nr = nrFilme->text().toInt();
            cos.umpleRandomCosInchirieri(nr, service.getAll());

            vector<Film> filme = cos.getAllCosInchirieri();
            loadData();

            nrFilme->clear();

            });
    }

    void updateaza() override {
        loadData();
    }
};