cmake_minimum_required(VERSION 3.5)

project(ATM VERSION 0.1 LANGUAGES CXX)

#set(QT_DIR "C:/Qt/6.2.0/mingw81_64/lib/cmake/Qt6")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Test Sql REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Test Sql REQUIRED)
#find_package(QT NAMES Qt6 Qt5 COMPONENTS Test REQUIRED)
#find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Test REQUIRED)

enable_testing(false)

set(PROJECT_SOURCES
        main.cpp
        view/widget.cpp view/widget.h view/widget.ui
        model/entity.h model/entity.cpp
        model/userentity.h model/userentity.cpp
        model/cardentity.h model/cardentity.cpp
        repository/repository.h repository/repository.cpp
        repository/cardrepository.h repository/cardrepository.cpp
        repository/vector_impl/cardrepositoryvectorimpl.h repository/vector_impl/cardrepositoryvectorimpl.cpp
        service/cardservice.h service/cardservice.cpp
        exception/notfoundexception.h exception/notfoundexception.cpp
        exception/incorrectcardauthinfoexception.h exception/incorrectcardauthinfoexception.cpp
        exception/customexception.h exception/customexception.cpp
        repository/userrepository.h repository/userrepository.cpp
        model/transactionentity.h model/transactionentity.cpp
        model/automatictransactionentity.h model/automatictransactionentity.cpp
        repository/transactionrepository.h repository/transactionrepository.cpp
        repository/automatictransactionrepository.h repository/automatictransactionrepository.cpp
        repository/vector_impl/userrepositoryvectorimpl.h repository/vector_impl/userrepositoryvectorimpl.cpp
        repository/vector_impl/transactionrepositoryvectorimpl.h repository/vector_impl/transactionrepositoryvectorimpl.cpp
        repository/vector_impl/automatictransactionrepositoryvectorimpl.h repository/vector_impl/automatictransactionrepositoryvectorimpl.cpp
        util/utils.h util/utils.cpp
        exception/logicconflictexception.h exception/logicconflictexception.cpp
        service/transactionservice.h service/transactionservice.cpp
        view/qcardnumberedit.h view/qcardnumberedit.cpp
        service/automatictransactionservice.h service/automatictransactionservice.cpp
        exception/notenoughmoney.h exception/notenoughmoney.cpp
        #view/qintegervalueedit.h view/qintegervalueedit.cpp
        view/qtransactionitem.h view/qtransactionitem.cpp
        #view/qautomatictransactionitem.h view/qautomatictransactionitem.cpp
        #view/qpinedit.h view/qpinedit.cpp
        #view/qamountedit.h view/qamountedit.cpp
        view/qpinedit.h view/qpinedit.cpp
        view/qamountedit.h view/qamountedit.cpp
        exception/circulardependancyexception.h exception/circulardependancyexception.cpp
        dbmanager.h dbmanager.cpp
        repository/db_impl/cardrepositorydbimpl.h repository/db_impl/cardrepositorydbimpl.cpp
        repository/db_impl/transactionrepositorydbimpl.h repository/db_impl/transactionrepositorydbimpl.cpp
        repository/db_impl/automatictransactiondbimpl.h repository/db_impl/automatictransactiondbimpl.cpp
        repository/db_impl/userrepositorydbimpl.h repository/db_impl/userrepositorydbimpl.cpp
        exception/sqlexception.h exception/sqlexception.cpp
        tests/unittests.h tests/unittests.cpp
        view/qautotransactionitem.h view/qautotransactionitem.cpp
        config.h
)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ATM
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ATM APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(ATM SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(ATM
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(ATM PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)

set_target_properties(ATM PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ATM)
endif()
