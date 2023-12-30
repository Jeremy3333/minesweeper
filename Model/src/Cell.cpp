//
// Created by jerem on 14/12/2023.
//

#include "Cell.h"

#include <iostream>

#include "../../Utils/CaseID.h"

Cell::Cell() : reveled_(false), marked_(false), index_(0) {}

void Cell::setIndex(const int p_index) {
    index_ = p_index;
}

bool Cell::revele() {
    if(marked_)
        return false;
    reveled_ = true;
    if(index_ == -1) {
        index_ = -2;
        return true;
    }
    return false;
}

void Cell::reveleMine() {
    if(marked_)
        return;
    reveled_ = true;
}

void Cell::mark() {
    marked_ = true;
}

bool Cell::changeMark()
{
    marked_ = !marked_;
    return marked_;
}

void Cell::reset()
{
    reveled_ = false;
    marked_ = false;
    index_ = 0;
}


bool Cell::isReveled() const {
    return reveled_;
}

bool Cell::isMarked() const {
    return marked_;
}


int Cell::getIndex() const {
    return index_;
}


bool Cell::isBomb() const {
    return index_ == -1;
}
