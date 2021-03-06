#include "progresshandler.h"

#include <QCoreApplication>

ProgressHandler *ProgressHandler::mInstance{nullptr};

ProgressHandler::ProgressHandler(QObject *parent) :
    QObject(parent),
    mStage(0),
    mStageCount(0),
    mStageProgress(0)
{
    resetProgress();
}

void ProgressHandler::calculateProgress()
{
    int lProgress = 0;

    double lStageStep = 100.0 / mStageCount;
    lProgress = lStageStep * mStage + lStageStep * (0.01 * mStageProgress);

    emit progress(lProgress);
}

void ProgressHandler::resetProgress()
{
    mStage = 0;
    mStageProgress = 0;
}

void ProgressHandler::addStage()
{
    ++mStageCount;
    resetProgress();
}

void ProgressHandler::setStageCount(int pStageCount)
{
    mStageCount = pStageCount;
}

void ProgressHandler::setCurrentStageProgress(int pProgress)
{
    if ((pProgress >= 0) && (pProgress <= 100))
    {
        mStageProgress = pProgress;
        calculateProgress();
    }
}

void ProgressHandler::finishStage()
{
    if (mStage < mStageCount)
    {
        ++mStage;
        calculateProgress();
    }
}

void ProgressHandler::finish()
{
    mStage = mStageCount - 1;
    mStageProgress = 100;
    calculateProgress();
}

ProgressHandler *ProgressHandler::instance()
{
    if (!mInstance)
    {
        mInstance = new ProgressHandler(qApp);
    }

    return mInstance;
}
