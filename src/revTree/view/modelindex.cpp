#include "modelindex.h"

ModelIndex::ModelIndex() :
    mRow(-1),
    mColumn(-1),
    mValid(false)
{
}

ModelIndex::ModelIndex(int row, int column) :
    mRow(row),
    mColumn(column),
    mValid(true)
{
}
