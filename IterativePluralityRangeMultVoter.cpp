//
//  IterativePluralityRangeMultVoter.cpp
//  RangeEquilibria
//
//  Created by Omer Lev on 6/2/14.
//
//

#include "IterativePluralityRangeMultVoter.h"


IterativeVoter* IterativePluralityRangeMultVoter::copy() const {
    return new IterativePluralityRangeMultVoter(*this);
}


void IterativePluralityRangeMultVoter::setR (double ra) {
    r=ra;
}

void IterativePluralityRangeMultVoter::setK (double ka) {
    k=ka;
}

void IterativePluralityRangeMultVoter::setRangeType(rangeTypes typeRa) {
    typeR=typeRa;
}

bool IterativePluralityRangeMultVoter::makeMove() {
    int winner=game->getWinner();
    if (winner==truePrefs[0]) {
        return false;
    }
    int* scores=((IterativePluralityGame *)game)->getScores();
    
    
    bool foundWinner=false;
    bool foundPublicVote=false;
    
    int realPublicRank=truePrefs.getRankForCandidate(publicPrefs[0]);
    
    if ((scores[publicPrefs[0]]*(1+r))>=scores[winner]) {
        for (int i=realPublicRank+1; i<candidateNumber; i++) {
            if (scores[truePrefs[i]]==0) {
                break;
            }
            
            if (((scores[winner]/scores[truePrefs[i]])+(scores[winner]/scores[publicPrefs[0]]))<(1+r)) {
                delete (scores);
                return false;
            }
            if (((scores[winner]/scores[truePrefs[i]])+(scores[winner]/scores[publicPrefs[0]]))>(1+r)) {
                break;
            }
            
            bool publicWinsTie=false;
            vector<int> ties;
            ties.push_back(truePrefs[i]);
            ties.push_back(publicPrefs[0]);
            ties.push_back(winner);
            int tieWinner=game->breakTies(ties);
            if (tieWinner==publicPrefs[0]) {
                publicWinsTie=true;
            }
            
            
            if ((((scores[winner]/scores[truePrefs[i]])+(scores[winner]/scores[publicPrefs[0]]))==(1+r)) && (publicWinsTie==true)) {
                delete (scores);
                return false;
            }
        }
    }
    
    
    for (int i=0;(i<candidateNumber) && (foundWinner==false);i++) {
        if (truePrefs[i]==publicPrefs[0]) {
            foundPublicVote=true;
        }
        
        if (truePrefs[i]==winner) {
            foundWinner=true;
            continue;
        }
        
        if (scores[truePrefs[i]]==0) {
            break;
        }
        
        //double diff=((double)scores[winner])/((double)scores[truePrefs[i]]);
        bool winnerWinsTie=false;
        if (((double)scores[winner])/((double)scores[truePrefs[i]]+1)==(1+r)) {
            vector<int> ties;
            ties.push_back(truePrefs[i]);
            ties.push_back(winner);
            int tieWinner=game->breakTies(ties);
            if (tieWinner==winner) {
                winnerWinsTie=false;
            }
        }
        
        if ((((double)scores[winner])/((double)scores[truePrefs[i]]+1)<(1+r)) || ((((double)scores[winner])/((double)scores[truePrefs[i]]+1)==(1+r)) && (winnerWinsTie==false))) {
            if (publicPrefs[0]==truePrefs[i]) {
                if ((((double)scores[winner])/((double)scores[truePrefs[i]])<(1+r)) || ((((double)scores[winner])/((double)scores[truePrefs[i]])==(1+r)) && (winnerWinsTie==false))) {
                    delete (scores);
                    return false;
                }
                else {
                    continue;
                }
            }
            for (int j=0; j<candidateNumber; j++) {
                if (publicPrefs[j]==truePrefs[i]) {
                    if (foundPublicVote==false) {
                        ((IterativePluralityGame*)game)->improvedScore();
                    }
                    publicPrefs[j]=publicPrefs[0];
                    publicPrefs[0]=truePrefs[i];
                    
                    break;
                }
            }
            delete (scores);
            return true;
        }
    }
    
    if (foundWinner==true) {
        int secondScore=-1;
        int secondScoreCand=-1;
        for (int i=0; i<candidateNumber; i++) {
            if (i==winner) {
                continue;
            }
            if (scores[i]>secondScore) {
                secondScore=scores[i];
                secondScoreCand=i;
            }
        }
        if (!(secondScore==0)) {
            
            bool winTie=true;
            if (((double)scores[winner])/((double)secondScore)==(1+r)) {
                vector<int> ties;
                ties.push_back(secondScoreCand);
                ties.push_back(winner);
                int tieWinner=game->breakTies(ties);
                if (tieWinner==secondScoreCand) {
                    winTie=false;
                }
            }
            
            //int diff=scores[winner]-secondScore;
            if ((((double)scores[winner])/((double)secondScore)<(1+r)) || ((((double)scores[winner])/((double)secondScore)==(1+r)) && (winTie==false))) {
                if (publicPrefs[0]==winner) {
                    delete (scores);
                    return false;
                }
                for (int j=0; j<candidateNumber; j++) {
                    if (publicPrefs[j]==winner) {
                        if (foundPublicVote==false) {
                            ((IterativePluralityGame*)game)->improvedScore();
                        }
                        publicPrefs[j]=publicPrefs[0];
                        publicPrefs[0]=winner;
                        break;
                    }
                }
                delete (scores);
                return true;
            }
        }
        
        if (typeR!=basic) {
            vector<int> ties;
            ties.push_back(publicPrefs[0]);
            ties.push_back(winner);
            int tieWinner=game->breakTies(ties);
            
            if ((((double)scores[winner])/((double)scores[publicPrefs[0]])<(1+k)) || ((((double)scores[winner])/((double)scores[publicPrefs[0]])<=(1+k)) && (tieWinner==publicPrefs[0]))) {
                delete (scores);
                return false;
            }
        }
        
        if (typeR==truthful) {
            if (publicPrefs[0]==truePrefs[0]) {
                delete (scores);
                return false;
            }
            resetVoter();
            delete (scores);
            return true;
        }
        
        if (typeR==lazy) {
            abstainVoter();
            delete (scores);
            return true;
        }
        
    }
    
    
    delete(scores);
    return false;
}

double IterativePluralityRangeMultVoter::getR() {
    return r;
}

double IterativePluralityRangeMultVoter::getK() {
    return k;
}