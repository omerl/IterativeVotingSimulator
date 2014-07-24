//
//  refList.cpp
//  RangeEquilibria
//
//  Created by Omer Lev on 28/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "PrefList.h"

PrefList::PrefList() {
    candidateNumber=-1;
    abstension=false;
}

PrefList::PrefList (const int candNum, const int newVote[]) {
    if (candNum<=0) {
        throw illegalPreferenceList();
    }
    candidateNumber=candNum;
    vote=new int [candidateNumber];
    abstension=false;
    populateVoteArray(newVote);
}

PrefList::PrefList (const PrefList & rhs) {
    abstension=rhs.abstension;
    candidateNumber=rhs.getCandidateNumber();
    vote=new int [candidateNumber];
    populateVoteArray(rhs.getVote());
    
}

void PrefList::populateVoteArray(const int * newVote) {
    bool usedCandidates[candidateNumber];
    for (int i=0;i<candidateNumber;i++) {
        usedCandidates[i]=false;
    }
    
    for (int i=0; i<candidateNumber; i++) {
        if ((newVote[i]>candidateNumber)|| (newVote[i]<0) || (usedCandidates[newVote[i]]==true)) {
            throw illegalPreferenceList();
        }
        usedCandidates[newVote[i]]=true;
        vote[i]=newVote[i];
    }
}

int PrefList::operator [](const int b) const {
    return vote[b];
}

int& PrefList::operator[] (const int b) {
    return vote[b];
}

PrefList::~PrefList() {
    delete (vote);
}

const int* const PrefList::getVote() const {
    return vote;
}

int PrefList::distanceFromPref(PrefList& a) const {
    int sum=0;
    for (int i=0; i<candidateNumber; i++) {
        for (int j=0; j<candidateNumber; j++) {
            if (vote[i]==a.getVote()[j]) {
                sum+=abs(i-j);
            }
        }
    }
    return sum;
}

bool PrefList::operator!= (const PrefList& rhs) const {
    bool isSame=true;
    if (candidateNumber!=rhs.getCandidateNumber()) {
        return false;
    }
    for (int i=0; i<candidateNumber; i++) {
        if (rhs.getVote()[i]!=vote[i]) {
            isSame=false;
        }
    }
    bool isDiffrent=!isSame;
    return isDiffrent;
}

bool PrefList::operator<(const PrefList &rhs) const {
    if (!(operator!=(rhs))) {
        return true;
    }
    for (int i=0; i<candidateNumber; i++) {
        if (vote[i]!=rhs.getVote()[i]) {
            return (vote[i]<rhs.getVote()[i]);
        }
    }
    return false;
}

const PrefList& PrefList::operator=(const PrefList &rhs)
{
    if (this == &rhs) {
        return *this;
    }
    delete (vote);
    candidateNumber=rhs.getCandidateNumber();
    vote=new int[candidateNumber];
    for (int i=0; i<candidateNumber; i++) {
        vote[i]=rhs.getVote()[i];
    }
    return *this;
}

std::ostream& operator<< (std::ostream& stream, PrefList& pref) {
    const int *list=pref.getVote();
    int candNum=pref.getCandidateNumber();
    for (int i=0; i<candNum; i++) {
        stream<<"\t"<<list[i];

    }
    if (pref.isAbstained()==true) {
        stream<<"abstained";
    }
    
    return stream;
}

int PrefList::getRankForCandidate(int c) {
    for (int i=0; i<candidateNumber; i++) {
        if (vote[i]==c) {
            return i;
        }
    }
    return -1;
}

void PrefList::abstain() {
    abstension=true;
}

void PrefList::rejoin() {
    abstension=false;
}

bool PrefList::isAbstained() const {
    return abstension;
}

int PrefList::getCandidateNumber() const {
    return candidateNumber;
}