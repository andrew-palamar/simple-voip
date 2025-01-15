#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "backend.hpp"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
	// Fix for Luckfox 5" display. Without it Screen.width and so on sizes will be twice lower. For example 360*360px instead 720*720px
	QCoreApplication::setAttribute(Qt::AA_DisableHighDpiScaling);
	// QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
	QGuiApplication app(argc, argv);
	app.setOrganizationName("Github");
	app.setOrganizationDomain("github.com");
	app.setApplicationName("simple-voip");
	BackEnd backend;
	QQmlApplicationEngine engine;

	QQmlContext *context = engine.rootContext();
	context->setContextProperty("backend", &backend);
	// engine.rootContext()->setContextProperty("applicationDirPath", QGuiApplication::applicationDirPath());

	const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
	QObject::connect(
		&engine, &QQmlApplicationEngine::objectCreated, &app,
		[url](QObject *obj, const QUrl &objUrl) {
			if (!obj && url == objUrl)
				QCoreApplication::exit(-1);
		},
		Qt::QueuedConnection);
	backend.start();
	engine.load(url);
	// Exit
	QObject::connect(&backend, SIGNAL(wantToQuit()), &app, SLOT(quit()));

	return app.exec();
}
