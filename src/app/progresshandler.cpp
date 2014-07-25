#include "progresshandler.h"

#include <QCoreApplication>

ProgressHandler *ProgressHandler::mInstance = 0;

ProgressHandler::ProgressHandler(QObject *parent) :
    QObject(parent),
    mStageCount(0)
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

void ProgressHandler::setCurrentStageProgress(int progress)
{
    if ((progress >= 0) && (progress <= 100))
    {
        mStageProgress = progress;
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
