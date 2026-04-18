#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QUrl>
#include <QQuickWindow>
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
    
    if (manager)
    {
        manager->setImageProvider(imageProvider);

        if (app.arguments().size() > 1)
        {
            manager->setURL(QUrl::fromUserInput(app.arguments()[1]));
        }
        else
        {
            qWarning() << "no arguments provided";
        }
    }
    else
    {
        qWarning() << "nullptr";
    }

    return app.exec();
}