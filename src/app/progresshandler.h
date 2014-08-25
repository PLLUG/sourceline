#ifndef PROGRESSHANDLER_H
#define PROGRESSHANDLER_H

#include <QObject>

class ProgressHandler : public QObject
{
    Q_OBJECT
public:
    void addStage();
    void setStageCount(int pStageCount);
    void setCurrentStageProgress(int progress);

    void finishStage();
    void finish();

    void resetProgress();

public:
    static ProgressHandler *instance();

signals:
    void progress(int);

private:
    explicit ProgressHandler(QObject *parent = 0);

    void calculateProgress();

private:
    int mStage;
    int mStageCount;
    int mStageProgress;

private:
    static ProgressHandler *mInstance;
};

#endif // PROGRESSHANDLER_H
