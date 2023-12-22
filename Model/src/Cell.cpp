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


bool Cell::isCaseNumbre() const {
    return (reveled_ && !marked_ &&(index_ > 0));
}

int Cell::getCaseID() const {
    if(isCaseNumbre())
        return index_ - 1;

    if(reveled_) {
        if(index_ == -2)
            return ExplodedMine;
        if(!marked_) {
            if(index_ == 0)
                return noMineAround;
            return Mine;
        }
        if(index_ != -1)
            return MarkedNoMine;
        std::cerr << "Error Impossible case" << std::endl;
        exit(1);
    }
    if(marked_)
        return Marked;
    return Uncheck;

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
