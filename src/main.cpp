// SPDX-FileCopyrightText: 2026 Alex Huber <alex.huber743@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QUrl>
#include <QQuickWindow>
#include <KDBusService>
#include <KLocalizedContext>
#include <KLocalizedString>
#include <KIconTheme>

#include "backend/WindowManager.h"

int main(int argc, char* argv[])
{
    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);
    
    KIconTheme::initTheme();

    QApplication app(argc, argv);
    QApplication::setOrganizationName  (QStringLiteral("FluxMusic"));
    QApplication::setOrganizationDomain(QStringLiteral("FluxMusic.github.io"));
    QApplication::setApplicationName   (QStringLiteral("Maki"));

    QApplication::setStyle(QStringLiteral("breeze"));

    QQmlApplicationEngine engine;

    MakiImageProvider* imageProvider = new MakiImageProvider();
    
    engine.addImageProvider(QStringLiteral("Maki"), imageProvider);
    engine.rootContext()->setContextObject(new KLocalizedContext(&engine));
    engine.loadFromModule("io.github.FluxMusic.Maki", "Main");
    
    WindowManager* manager = engine.singletonInstance<WindowManager*>("io.github.FluxMusic.Maki", "WindowManager");

    //Only one instance should exist at a time
    KDBusService service(KDBusService::Unique);

    QObject::connect(&service, &KDBusService::activateRequested, 
        [manager, &app, imageProvider](const QStringList& args, const QString&) {
            if (manager) {
                manager->initApp(&app);
                manager->setImageProvider(imageProvider);

                if (args.size() > 1) {
                    manager->setURL(QUrl::fromUserInput(args[1]));
                } else {
                    qWarning() << "no arguments provided";
                }
            } else {
                qWarning() << "nullptr";
            }
        });

    if (manager) {
        manager->initApp(&app);
        manager->setImageProvider(imageProvider);

        if (app.arguments().size() > 1) {
            manager->setURL(QUrl::fromUserInput(app.arguments()[1]));
        } else {
            qWarning() << "no arguments provided";
        }
    } else {
        qWarning() << "nullptr";
    }

    return app.exec();
}