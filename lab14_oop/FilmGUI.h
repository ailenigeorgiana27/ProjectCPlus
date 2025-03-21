#pragma once
#include "service.h"
#include "CosCRUDGUI.h"
#include "CosReadOnlyGUI.h"
#include <QApplication>
#include <QTextEdit>
#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QFormLayout>
#include <qdebug.h>
#include <qmessagebox.h>
#include <qmainwindow.h>
#include <qmenubar.h>
#include <qcombobox.h>
#include <qheaderview.h>
#include <qtablewidget.h>
#include <qfont.h>
#include <qscrollarea.h>
#include <qsplitter.h>
#include <vector>
#include <string>
#include "cosul.h"
#include "TableModel.h"

using std::vector;
using std::string;



class FilmGUI : public QWidget, public Observabil {
public:
    FilmGUI(Service& service) : service{ service } {
        initGUI();
        loadData(service.getAll());
        initConnect();
    }
private:
    Service& service;
    CosInchirieriFilme cos;


    //CosCRUDGUI* cosCRUDGUI = new CosCRUDGUI();
    //CosReadOnlyGUI* cosReadOnlyGUI = new CosReadOnlyGUI();

   // QListView* lista ;
    QTableView* tabelFilme ;
    TableModel* model;
    Film film_selectat;

    QLineEdit* titluEdit = new QLineEdit;
    QLineEdit* genEdit = new QLineEdit;
    QLineEdit* anAparitieEdit = new QLineEdit;
    QLineEdit* actorPrincipalEdit = new QLineEdit;
    QLineEdit* nrFilme = new QLineEdit;


    QPushButton* butonStergereTitlu = new QPushButton{ "&Șterge" };
    QPushButton* butonStergereGen = new QPushButton{ "&Șterge" };
    QPushButton* butonStergereAnAparitie = new QPushButton{ "&Șterge" };
    QPushButton* butonStergereActorPrincipal = new QPushButton{ "&Șterge" };
    QPushButton* butonStergere = new QPushButton{ "&Șterge toate câmpurile" };

    QPushButton* butonExit = new QPushButton{ "&Exit" };
    QPushButton* btnCos = new QPushButton{ "&Cos" };
    QPushButton* btnCosCrud = new QPushButton{ "&Cos CRUD" };
    QPushButton* btnCosReadOnly = new QPushButton{ "&Cos ReadOnly" };

    QPushButton* butonAdauga = new QPushButton{ "&Adaugă" };
    QPushButton* butonSterge = new QPushButton{ "&Șterge" };
    QPushButton* butonModifica = new QPushButton{ "&Modifică" };
    QPushButton* butonCauta = new QPushButton{ "&Caută" };
    QPushButton* butonFiltreaza = new QPushButton{ "&Filtrează" };
    QPushButton* butonSorteaza = new QPushButton{ "&Sortează" };


    QPushButton* butonAdaugareInCos = new QPushButton{ "&Adaugă în coș" };
    QPushButton* butonGolireCos = new QPushButton{ "&Golește cosul" };
    QPushButton* butonAdaugareRandomInCos = new QPushButton{ "&Adaugă random în cos" };

    QPushButton* butonExportInCSV = new QPushButton{ "&Exportă coșul în CSV" };
    QPushButton* butonExportInHTML = new QPushButton{ "&Exportă coșul în HTML" };


    QLabel* numarFilmeLabel = new QLabel("Număr de filme: ");
    QString numarFilme = QString::number(service.getAll().size());

    void initGUI() {

        setWindowTitle("Filme");
        tabelFilme = new QTableView();
        model = new TableModel(model);
        tabelFilme->setModel(model);

        auto* lyMain = new QHBoxLayout{};
        setLayout(lyMain);

        // Layout-ul pt tabelFilme

        QStringList headers;
        headers << "Titlu" << "Gen" << "An" << "Actor";
        

        lyMain->addWidget(tabelFilme);

        // Layout-ul pentru Lista

        auto layout = new QVBoxLayout;

        //auto label = new QLabel{ "Lista" };

        auto hlayout = new QHBoxLayout;
        hlayout->addStretch();
        //hlayout->addWidget(label);
        hlayout->addStretch();

        layout->addLayout(hlayout);
        //layout->addWidget(lista);

        lyMain->addLayout(layout);


        // Layout-ul pentru butoanele de adaugare, stergere si modificare

        auto layout_butoane = new QVBoxLayout;

        layout_butoane->addWidget(butonAdauga);
        layout_butoane->addWidget(butonModifica);
        layout_butoane->addWidget(butonSterge);


        lyMain->addLayout(layout_butoane);


        // Layout-ul pentru campurile de titlu, autor, gen si an

        auto layout_dreapta = new QVBoxLayout;


        auto layout_campuri = new QFormLayout;

        layout_campuri->addRow("Titlu", titluEdit);
        layout_campuri->addRow("Gen", genEdit);
        layout_campuri->addRow("An", anAparitieEdit);
        layout_campuri->addRow("Actor", actorPrincipalEdit);
        layout_campuri->addRow("Nr Filme Random", nrFilme);

        layout_dreapta->addLayout(layout_campuri);

        auto aux = new QHBoxLayout;

        aux->addWidget(butonCauta);
        aux->addWidget(butonFiltreaza);
        aux->addWidget(butonSorteaza);

        layout_dreapta->addLayout(aux);

        auto ly_btn_cos = new QHBoxLayout;

        ly_btn_cos->addWidget(butonAdaugareInCos);
        ly_btn_cos->addWidget(butonGolireCos);
        ly_btn_cos->addWidget(butonAdaugareRandomInCos);

        layout_dreapta->addLayout(ly_btn_cos);

        layout_dreapta->addWidget(btnCos);
        layout_dreapta->addWidget(btnCosCrud);
        layout_dreapta->addWidget(btnCosReadOnly);
        layout_dreapta->addWidget(butonExit);

        lyMain->addLayout(layout_dreapta);

    }
    void initConnect() {

        

        
        QObject::connect(butonExit, &QPushButton::clicked, [&]() {   // se capteaza prin referinta elementul this ca sa se poata apela metode, ex close
            close();
            });

        QObject::connect(butonAdauga, &QPushButton::clicked, [&]() {

            auto titlu = titluEdit->text();
            auto gen = genEdit->text();
            auto an = anAparitieEdit->text();
            auto actor = actorPrincipalEdit->text();

            auto titlu_film = titlu.toStdString();
            auto gen_film = gen.toStdString();
            auto an_film = an.toInt();
            auto actor_film = actor.toStdString();

            Film film{ titlu_film, gen_film, an_film, actor_film };


            service.adaugaFilm(titlu_film, gen_film, an_film, actor_film);


            loadData(service.getAll());

            titluEdit->clear();
            genEdit->clear();
            anAparitieEdit->clear();
            actorPrincipalEdit->clear();

            });

        QObject::connect(butonModifica, &QPushButton::clicked, [&]() {

            if (titluEdit->text().isEmpty() or genEdit->text().isEmpty() or anAparitieEdit->text().isEmpty() or actorPrincipalEdit->text().isEmpty()) {
                QMessageBox::critical(this, "Eroare", "Date invalide!");
                return;
            }

            else {

                auto titlu = titluEdit->text().toStdString();
                auto gen = genEdit->text().toStdString();
                auto an = anAparitieEdit->text().toInt();
                auto actor = actorPrincipalEdit->text().toStdString();

                Film film_nou{ titlu, gen, an, actor };
                service.modificaFilm(titlu, gen, an, actor);

                loadData(service.getAll());

                titluEdit->clear();
                genEdit->clear();
                anAparitieEdit->clear();
                actorPrincipalEdit->clear();

                film_nou = Film();

            }

            });

        QObject::connect(butonSterge, &QPushButton::clicked, [&]() {
            auto titluFilm = titluEdit->text().toStdString();
            if (titluEdit->text().isEmpty() or genEdit->text().isEmpty() or anAparitieEdit->text().isEmpty() or actorPrincipalEdit->text().isEmpty()) {
                QMessageBox::critical(this, "Eroare", "Date invalide!");
                return;
            }

            else {

                try {
                    service.stergeFilm(titluFilm);
                }
                catch (ExceptieRepo& exceptie) {
                    QMessageBox::warning(this, "Atenție!", QString::fromStdString(exceptie.getMesaj()));
                }
                catch (ExceptieValidare& exceptie) {
                    QMessageBox::warning(this, "Atenție!", QString::fromStdString(exceptie.getMesaj()[0]));
                }

                loadData(service.getAll());

                titluEdit->clear();
                genEdit->clear();
                anAparitieEdit->clear();
                actorPrincipalEdit->clear();
            }

            });



        QObject::connect(butonCauta, &QPushButton::clicked, [&]() {

            if (titluEdit->text().isEmpty() or genEdit->text().isEmpty() or anAparitieEdit->text().isEmpty() or actorPrincipalEdit->text().isEmpty()) {
                QMessageBox::critical(this, "Eroare", "Date invalide!");
                return;
            }

            else {

                auto titlu_cautat = titluEdit->text().toStdString();
                auto gen_cautat = genEdit->text().toStdString();
                auto an_cautat = anAparitieEdit->text().toInt();
                auto actor_cautat = actorPrincipalEdit->text().toStdString();

                if (service.cautaFilm(titlu_cautat)) {

                    QString titlu = QString::fromStdString(titlu_cautat);
                    QString gen = QString::fromStdString(gen_cautat);
                    QString an = QString::number(an_cautat);
                    QString actor = QString::fromStdString(actor_cautat);

                    QString mesaj = "Titlu: " + titlu + '\n' + "Gen: " + gen + '\n' + "An: " + an + '\n' + "Actor: " + actor;

                    QMessageBox::information(this, "Film Gasit", mesaj);
                }
                else {
                    QMessageBox::information(this, "Info", "Filmul nu exista!");
                }

            }

            titluEdit->clear();
            genEdit->clear();
            anAparitieEdit->clear();
            actorPrincipalEdit->clear();

            });

        QObject::connect(butonSorteaza, &QPushButton::clicked, [&]() {
            QDialog* dialogSortare = new QDialog(this);
            dialogSortare->resize(600, 600);
            QVBoxLayout* layoutDialog = new QVBoxLayout(dialogSortare);
            QPushButton* butonSortareDialog = new QPushButton{ "&Sorteaza" };

            QLineEdit* lineEditReperSortare = new QLineEdit(dialogSortare);
            QLineEdit* lineEditOrdineSortare = new QLineEdit(dialogSortare);
            QListWidget* listaFilme = new QListWidget(dialogSortare);

            layoutDialog->addWidget(new QLabel("Sortare după (1 -> titlu / 2 -> actor / 3 -> an+gen):", dialogSortare));
            layoutDialog->addWidget(lineEditReperSortare);
            layoutDialog->addWidget(new QLabel("Ordine sortare (1 -> crescător / 2 -> descrescător):", dialogSortare));
            layoutDialog->addWidget(lineEditOrdineSortare);
            layoutDialog->addWidget(listaFilme);
            layoutDialog->addWidget(butonSortareDialog);

            QObject::connect(butonSortareDialog, &QPushButton::clicked, [=]() {
                if (lineEditReperSortare->text() != "" && lineEditOrdineSortare->text() != "") {
                    auto filme = service.sorteaza(lineEditReperSortare->text().toInt(), lineEditOrdineSortare->text().toInt());
                    listaFilme->clear();
                    for (const auto& film : filme) {
                        QString item = QString::fromStdString(film.getTitluFilm() + ", " + film.getGenFilm() + ", " +
                            std::to_string(film.getAnAparitie()) + ", " + film.getActorPrincipal());
                        listaFilme->addItem(item);
                    }
                }
                });
            dialogSortare->show();
            });
        QObject::connect(butonFiltreaza, &QPushButton::clicked, [&]() {
            QDialog* dialogFiltrare = new QDialog(this);
            dialogFiltrare->resize(600, 600);
            QVBoxLayout* layoutDialog = new QVBoxLayout(dialogFiltrare);
            QPushButton* butonFiltrareDialog = new QPushButton{ "&Filtrează" };

            QLineEdit* lineEditGen = new QLineEdit(dialogFiltrare);
            QLineEdit* lineEditAn = new QLineEdit(dialogFiltrare);
            QListWidget* listaFilme = new QListWidget(dialogFiltrare);

            layoutDialog->addWidget(new QLabel("Gen:", dialogFiltrare));
            layoutDialog->addWidget(lineEditGen);
            layoutDialog->addWidget(new QLabel("An:", dialogFiltrare));
            layoutDialog->addWidget(lineEditAn);
            layoutDialog->addWidget(listaFilme);
            layoutDialog->addWidget(butonFiltrareDialog);

            QObject::connect(butonFiltrareDialog, &QPushButton::clicked, [=]() {
                if (lineEditGen->text() != "" && lineEditAn->text() == "") {
                    auto filme = service.filtreazaDupaGen(lineEditGen->text().toStdString());
                    listaFilme->clear();
                    for (const auto& film : filme) {
                        QString item = QString::fromStdString(film.getTitluFilm() + ", " + film.getGenFilm() + ", " +
                            std::to_string(film.getAnAparitie()) + ", " + film.getActorPrincipal());
                        listaFilme->addItem(item);
                    }
                }
                if (lineEditGen->text() == "" && lineEditAn->text() != "") {
                    auto filme = service.filtreazaDupaAnAparitie(lineEditAn->text().toInt());
                    listaFilme->clear();
                    for (const auto& film : filme) {
                        QString item = QString::fromStdString(film.getTitluFilm() + ", " + film.getGenFilm() + ", " +
                            std::to_string(film.getAnAparitie()) + ", " + film.getActorPrincipal());
                        listaFilme->addItem(item);
                    }
                }
                });
            dialogFiltrare->show();
            });

        QObject::connect(btnCos, &QPushButton::clicked, [&]() {

            auto* cos_main = new Cosul(service, cos);
            cos.adaugaObservator(cos_main);
            cos_main->show();

            });

        QObject::connect(btnCosCrud, &QPushButton::clicked, [&]() {

            auto* cos_crud = new CosCRUDGUI(service, cos);
            cos.adaugaObservator(cos_crud);
            cos_crud->show();

            });

        QObject::connect(btnCosReadOnly, &QPushButton::clicked, [&]() {

            auto* cos_read = new CosReadOnlyGUI(service, cos);
            cos.adaugaObservator(cos_read);
            cos_read->show();

            });

        QObject::connect(butonAdaugareInCos, &QPushButton::clicked, [&]() {

            auto titlu = titluEdit->text().toStdString();
            auto gen = genEdit->text().toStdString();
            auto an = anAparitieEdit->text().toInt();
            auto actor = actorPrincipalEdit->text().toStdString();

            if (service.cautaFilm(titlu)) {

                Film film{ titlu, gen, an, actor };
                cos.adaugaCosInchirieri(film);

                vector<Film> filme = cos.getAllCosInchirieri();

                notifica();

            }

            else {
                QMessageBox::critical(this, "Eroare", "Cartea nu exista!");
            }

            titluEdit->clear();
            genEdit->clear();
            anAparitieEdit->clear();
            actorPrincipalEdit->clear();


            });

        QObject::connect(butonGolireCos, &QPushButton::clicked, [&]() {

            cos.golesteCosInchirieri();

            notifica();

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

            nrFilme->clear();

            notifica();

            });



    }



    void loadData(const std::vector<Film> list) {
        model->setList(list);
    }

};