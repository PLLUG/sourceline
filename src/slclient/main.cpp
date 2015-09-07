#ifdef DEBUG
    #include <QApplication> // Use GUI for debugging purposes
#else
    #include <QCoreApplication>
#endif
#include <QCommandLineParser>

#include <QDebug>

#include "sourcelineclient.h"

static const QLatin1String OPTION_CLIENT_ID_NAME("id");
static const QLatin1String OPTION_CLIENT_ID_DESCRIPTION("SL provider connection id");
static const QLatin1String OPTION_CLIENT_ID_VALUE_NAME("id");

static const QLatin1String OPTION_CLIENT_DEBUG_NAME("debug");
static const QLatin1String OPTION_CLIENT_DEBUG_DESCRIPTION("Show client debugging window (debug mode only).");

static const char RETURN_CODE_GENERAL_ERROR(-1);
static const char RETURN_CODE_INVALID_ARGUMENTS(-2);

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName(QStringLiteral("Source Line Client"));
    QCoreApplication::setApplicationVersion(QStringLiteral("0.1"));

#ifdef DEBUG
    QApplication application(argc, argv);
#else
    QCoreApplication application(argc, argv);
#endif

    // Defining command line agruments
    QCommandLineOption idOption(OPTION_CLIENT_ID_NAME, OPTION_CLIENT_ID_DESCRIPTION,
        OPTION_CLIENT_ID_VALUE_NAME);
    QCommandLineOption debugOption(OPTION_CLIENT_DEBUG_NAME, OPTION_CLIENT_DEBUG_DESCRIPTION);

    QCommandLineParser parser;
    parser.setApplicationDescription(QStringLiteral("SourceLine puppet process for command process execution and plugin isolation"));
    parser.addOption(idOption);
    parser.addOption(debugOption);
    parser.addHelpOption();
    parser.addVersionOption();

    // Processing command line options passed to programm
    parser.process(application);

    if (!parser.isSet(idOption))
    {
#ifdef DEBUG
        parser.showHelp(RETURN_CODE_INVALID_ARGUMENTS);
#else
        return RETURN_CODE_INVALID_ARGUMENTS;
#endif
    }

    SourceLineClient client(parser.value(idOption));
#ifdef DEBUG
     if (parser.isSet(debugOption))
     {
        client.showDebugWindow();
     }
#endif
    client.start();

    return application.exec();
}

