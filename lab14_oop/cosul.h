
#include <QtWidgets>
#include <cstdlib>
#include "service.h"
#include "CosFilme.h"
#include "observator.h"

class Cosul : public QWidget, public Observator {

public:

    Cosul(Service& service, CosInchirieriFilme& cos) : service(service), cos(cos) {
        initCosul();
        initConnect();
        loadLista(cos.getAllCosInchirieri());
        cos.adaugaObservator(this);
    };

private:

    Service& service;

    CosInchirieriFilme& cos;

    QListWidget* lista = new QListWidget;

    QPushButton* btnAdd = new QPushButton(" &Adauga ");
    QPushButton* btnGoleste = new QPushButton(" &Golire ");
    QPushButton* btnRandom = new QPushButton(" Generare &Random ");

    QLineEdit* titluEdit = new QLineEdit;
    QLineEdit* anAparitieEdit = new QLineEdit;
    QLineEdit* actorPrincipalEdit = new QLineEdit;
    QLineEdit* txtActor = new QLineEdit;
    QLineEdit* nrFilme = new QLineEdit;


    void initCosul() {

        setWindowTitle("Cos Filme");

        auto* lyMain = new QHBoxLayout;
        setLayout(lyMain);

        auto* lyButoane = new QHBoxLayout;

        lyButoane->addWidget(btnAdd);
        lyButoane->addWidget(btnGoleste);
        lyButoane->addWidget(btnRandom);

        auto layout_campuri = new QFormLayout;

        layout_campuri->addRow("Titlu", titluEdit);
        layout_campuri->addRow("Gen", anAparitieEdit);
        layout_campuri->addRow("An", actorPrincipalEdit);
        layout_campuri->addRow("Actor", txtActor);
        layout_campuri->addRow("Nr filme Random: ", nrFilme);

        auto* lyDreapta = new QVBoxLayout;

        lyDreapta->addLayout(layout_campuri);
        lyDreapta->addLayout(lyButoane);

        lyMain->addWidget(lista);
        lyMain->addLayout(lyDreapta);

    }


    void loadLista(const vector<Film>& filme) {

        lista->clear();
        QString titlu, gen, an, actor;

        for (const auto& film : filme) {

            QString element;

            titlu = (QString::fromStdString(film.getTitluFilm()));
            gen = (QString::fromStdString(film.getGenFilm()));
            an = (QString::number(film.getAnAparitie()));
            actor = (QString::fromStdString(film.getActorPrincipal()));

            element = titlu + " | " + gen + " | " + an + " | " + actor;
            lista->addItem(element);
        }

    }


    void initConnect() {

        QObject::connect(btnAdd, &QPushButton::clicked, [&]() {

            auto titlu = titluEdit->text().toStdString();
            auto gen = anAparitieEdit->text().toStdString();
            auto an = actorPrincipalEdit->text().toInt();
            auto actor = txtActor->text().toStdString();

            if (service.cautaFilm(titlu)) {

                Film film{ titlu, gen, an, actor };
                cos.adaugaCosInchirieri(film);

                vector<Film> filme = cos.getAllCosInchirieri();
                loadLista(filme);

            }

            else {
                QMessageBox::critical(this, "Eroare", "Cartea nu exista!");
            }

            titluEdit->clear();
            anAparitieEdit->clear();
            actorPrincipalEdit->clear();
            txtActor->clear();

            });

        QObject::connect(btnGoleste, &QPushButton::clicked, [&]() {

            cos.golesteCosInchirieri();
            lista->clear();

            });

        QObject::connect(btnRandom, &QPushButton::clicked, [&]() {

            if (nrFilme->text().isEmpty()) {
                QMessageBox::critical(this, "Eroare", "Numarul de filme nu poate fi vid!");
                return;
            }

            cos.golesteCosInchirieri();
            int nr = nrFilme->text().toInt();
            cos.umpleRandomCosInchirieri(nr, service.getAll());

            vector<Film> filme = cos.getAllCosInchirieri();
            loadLista(filme);

            nrFilme->clear();

            });


    }

    void updateaza() override {
        loadLista(cos.getAllCosInchirieri());
    }

};