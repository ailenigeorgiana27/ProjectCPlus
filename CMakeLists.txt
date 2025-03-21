cmake_minimum_required(VERSION 3.27)
project(lab14_oop)

set(CMAKE_CXX_STANDARD 14)

include_directories(lab14_oop)
include_directories(lab14_oop/x64/Debug/uic)

add_executable(lab14_oop
        lab14_oop/x64/Debug/moc/moc_lab14_oop.cpp
        lab14_oop/x64/Debug/rcc/qrc_lab14_oop.cpp
        lab14_oop/x64/Debug/uic/ui_lab14_oop.h
        lab14_oop/consola.cpp
        lab14_oop/consola.h
        lab14_oop/CosCRUDGUI.h
        lab14_oop/CosFilme.cpp
        lab14_oop/CosFilme.h
        lab14_oop/CosReadOnlyGUI.h
        lab14_oop/cosul.h
        lab14_oop/Film.cpp
        lab14_oop/Film.h
        lab14_oop/FilmGUI.h
        lab14_oop/lab14_oop.cpp
        lab14_oop/lab14_oop.h
        lab14_oop/main.cpp
        lab14_oop/observator.h
        lab14_oop/repo.cpp
        lab14_oop/repo.h
        lab14_oop/repositoryFake.cpp
        lab14_oop/repositoryFake.h
        lab14_oop/service.cpp
        lab14_oop/service.h
        lab14_oop/TableModel.cpp
        lab14_oop/TableModel.h
        lab14_oop/teste.cpp
        lab14_oop/teste.h
        lab14_oop/validator.cpp
        lab14_oop/validator.h)
