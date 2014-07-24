//
//  IterativeVoter.cpp
//  RangeEquilibria
//
//  Created by Omer Lev on 28/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "IterativeVoter.h"
#include "IterativeGame.h"

IterativeVoter::IterativeVoter (PrefList * list, IterativeGame * theGame):truePrefs(*list),publicPrefs(*list), game(theGame)  {
    candidateNumber=list->getCandidateNumber();
    abstain=false;
}

IterativeVoter::IterativeVoter (PrefList * list):truePrefs(*list),publicPrefs(*list)  {
    candidateNumber=list->getCandidateNumber();
    abstain=false;
}

IterativeVoter::IterativeVoter (const IterativeVoter& v) {
    candidateNumber=v.candidateNumber;
    truePrefs=PrefList(v.truePrefs);
    publicPrefs=PrefList(v.publicPrefs);
    game=v.game;
    abstain=v.abstain;
}

void IterativeVoter::setGame (IterativeGame * theGame) {
    game=theGame;
}

const IterativeGame * IterativeVoter::getGame() const {
    return game;
}

IterativeVoter::~IterativeVoter() {
}

const PrefList* const IterativeVoter::getVote() const {
    return &publicPrefs;
}

void IterativeVoter::resetVoter() {
    for (int i=0;i<candidateNumber;i++) {
        publicPrefs[i]=truePrefs[i];
    }
    publicPrefs.rejoin();
}

void IterativeVoter::abstainVoter() {
    publicPrefs.abstain();
}

bool IterativeVoter::isAbstained() {
    return publicPrefs.isAbstained();
}

int IterativeVoter::getTrueCandidateRank(int c) {
    return publicPrefs.getRankForCandidate(c);
}

void IterativeVoter::setPublicVoter(PrefList * list) {
    if (list->getCandidateNumber()!=candidateNumber) {
        throw illegalPreferenceList();
    }
    publicPrefs=PrefList(*list);
}