#include "apibase.h"

ApiBase::~ApiBase()=default;

ApiBase::ApiBase(QObject *parent) :
    QObject(parent){}
