#include <QCoreApplication>
#include <QCommandLineParser>

#include <QDebug>

static const QLatin1String OPTION_CLIENT_ID_NAME("id");
static const QLatin1String OPTION_CLIENT_ID_DESCRIPTION("SL provider connection id");
static const QLatin1String OPTION_CLIENT_ID_VALUE_NAME("id");

static const char RETURN_CODE_GENERAL_ERROR(-1);
static const char RETURN_CODE_INVALID_ARGUMENTS(-2);

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName(QStringLiteral("Source Line Client"));
    QCoreApplication::setApplicationVersion(QStringLiteral("0.1"));

    QCoreApplication application(argc, argv);

    // Defining command line agruments
    QCommandLineOption idOption(OPTION_CLIENT_ID_NAME, OPTION_CLIENT_ID_DESCRIPTION,
        OPTION_CLIENT_ID_VALUE_NAME);

    QCommandLineParser parser;
    parser.setApplicationDescription(QStringLiteral("SourceLine puppet process for command process execution and plugin isolation"));
    parser.addOptions({idOption});
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

    return application.exec();
}

