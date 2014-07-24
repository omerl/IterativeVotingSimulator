//
//  IterativeGame.cpp
//  RangeEquilibria
//
//  Created by Omer Lev on 28/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "IterativeGame.h"

IterativeGame::IterativeGame (int voterNum, IterativeVoter** gameVoters) {
    if (voterNum<=0) {
        throw illegalPreferenceList();
    }
    voterNumber=voterNum;
    candidateNumber=gameVoters[0]->getVote()->getCandidateNumber();
    voters=new IterativeVoter* [voterNumber];
    for (int i=0; i<voterNumber; i++) {
        voters[i]=gameVoters[i];
        const PrefList *pf=gameVoters[i]->getVote();
        
        votes.push_back(*pf);
    }
    history.push_back(votes);
    condercetWinner=-1;
    truthtfulWinner=-1;
}


IterativeGame::~IterativeGame() {
    delete (voters);
    
}

void IterativeGame::setDistributionType(distributionTypes typeLa) {
    disType=typeLa;
}

void IterativeGame::setWinnerAndCondercet(vector<PrefList> v) {
    truthtfulWinner=getWinnerFromVotes(v);
    
    condercetWinner=getCondorcetWinnerFromVotes(v);
    pluralityWinner=getPluralityWinnerFromVotes(v);
    bordaWinner=getBordaWinnerFromVotes(v);
    maximinWinner=getMaximinWinnerFromVotes(v);
    copelandWinner=getCopelandWinnerFromVotes(v);
    pluralityDuvergerGap=getPluralityDuvergerGapFromVotes(v);
    pluralityDuvergerGap2=getPluralityDuvergerGap2FromVotes(v);
    pluralityDuvergerGap3=getPluralityDuvergerGap3FromVotes(v);
    toFirstTwo=getToFirstTwoFromVotes(v);
    
    if (disType==luce) {
        luceInfo.bordaWinner=v[0].getRankForCandidate(bordaWinner);
        luceInfo.copelandWinner=v[0].getRankForCandidate(copelandWinner);
        luceInfo.maximinWinner=v[0].getRankForCandidate(maximinWinner);
        luceInfo.pluralityWinner=v[0].getRankForCandidate(pluralityWinner);
        if (condercetWinner!=-1) {
            luceInfo.condorcetWinner=v[0].getRankForCandidate(condercetWinner);
        }
        
    }
}


int IterativeGame::getPluralityWinnerFromVotes(vector<PrefList> prefs) {
    int scores[candidateNumber];
    for (int i=0; i<candidateNumber; i++) {
        scores[i]=0;
    }
    for (long i=0; i<prefs.size(); i++) {
        if (prefs[i].isAbstained()) {
            continue;
        }
        scores[(prefs[i])[0]]+=1;
    }
    int maxScore=-1;
    for (int i=0; i<candidateNumber; i++) {
        if (scores[i]>maxScore) {
            maxScore=scores[i];
        }
    }
    vector<int> winners;
    for (int i=0; i<candidateNumber; i++) {
        if (scores[i]==maxScore) {
            winners.push_back(i);
        }
    }
    
    if (winners.size()==1) {
        return winners[0];
    }
    
    return breakTies(winners);
}

int IterativeGame::getCondorcetWinnerFromVotes(vector<PrefList> prefs) {
    int bar=((int)floor(((double)voterNumber)/2))+1;
    for (int i=0; i<candidateNumber; i++) {
        bool allGood=true;
        for (int j=0;j<candidateNumber;j++) {
            int counter=0;
            if (i==j) {
                continue;
            }
            for (int s=0; s<prefs.size(); s++) {
                if (prefs[s].getRankForCandidate(i)<prefs[s].getRankForCandidate(j)) {
                    counter++;
                }
            }
            if (counter<bar) {
                allGood=false;
                break;
            }
        }
        if (allGood==true) {
            return i;
            break;
        }
    }
    return -1;
}

int IterativeGame::getBordaWinnerFromVotes(vector<PrefList> prefs) {
    int scores[candidateNumber];
    for (int i=0; i<candidateNumber; i++) {
        scores[i]=0;
    }
    for (long i=0; i<prefs.size(); i++) {
        if (prefs[i].isAbstained()) {
            continue;
        }
        for (int j=0; j<candidateNumber; j++) {
            scores[(prefs[i])[j]]+=(candidateNumber-1)-j;
        }
    }
    int maxScore=-1;
    for (int i=0; i<candidateNumber; i++) {
        if (scores[i]>maxScore) {
            maxScore=scores[i];
        }
    }
    vector<int> winners;
    for (int i=0; i<candidateNumber; i++) {
        if (scores[i]==maxScore) {
            winners.push_back(i);
        }
    }
    
    if (winners.size()==1) {
        return winners[0];
    }
    
    return breakTies(winners);
}

int IterativeGame::getMaximinWinnerFromVotes(vector<PrefList> prefs) {
    int maximinScores[candidateNumber];
    for (int i=0; i<candidateNumber; i++) {
        maximinScores[i]=candidateNumber;
    }
    
    for (int i=0; i<candidateNumber; i++) {
        for (int j=0;j<candidateNumber;j++) {
            if (i==j) {
                continue;
            }
            int counter=0;
            for (int s=0; s<prefs.size(); s++) {
                if (prefs[s].getRankForCandidate(i)<prefs[s].getRankForCandidate(j)) {
                    counter++;
                }
            }
            if (maximinScores[i]>counter) {
                maximinScores[i]=counter;
            }
        }
    }
    
    int maxScore=-1;
    for (int i=0; i<candidateNumber; i++) {
        if (maximinScores[i]>maxScore) {
            maxScore=maximinScores[i];
        }
    }
    vector<int> winners;
    for (int i=0; i<candidateNumber; i++) {
        if (maximinScores[i]==maxScore) {
            winners.push_back(i);
        }
    }
    
    if (winners.size()==1) {
        return winners[0];
    }
    return breakTies(winners);
}

int IterativeGame::getCopelandWinnerFromVotes(vector<PrefList> prefs) {
    int copelandScores[candidateNumber];
    int bar=((int)floor(((double)voterNumber)/2));
    for (int i=0; i<candidateNumber; i++) {
        copelandScores[i]=0;
    }
    
    for (int i=0; i<candidateNumber; i++) {
        for (int j=0;j<candidateNumber;j++) {
            if (i==j) {
                continue;
            }
            int counter=0;
            for (int s=0; s<prefs.size(); s++) {
                if (prefs[s].getRankForCandidate(i)<prefs[s].getRankForCandidate(j)) {
                    counter++;
                }
            }
            if (counter>bar) {
                copelandScores[i]+=1;
            } else {
                if (counter<bar) {
                    copelandScores[i]-=1;
                } else {
                    vector<int> ties;
                    if (i<j) {
                        ties.push_back(i);
                        ties.push_back(j);
                    } else {
                        ties.push_back(j);
                        ties.push_back(i);
                    }
                    if (i==breakTies(ties)) {
                        copelandScores[i]+=1;
                    } else {
                        copelandScores[i]-=1;
                    }
                }
            }
        }
    }
    
    
    int maxScore=-1;
    for (int i=0; i<candidateNumber; i++) {
        if (copelandScores[i]>maxScore) {
            maxScore=copelandScores[i];
        }
    }
    vector<int> winners;
    for (int i=0; i<candidateNumber; i++) {
        if (copelandScores[i]==maxScore) {
            winners.push_back(i);
        }
    }
    
    if (winners.size()==1) {
        return winners[0];
    }
    return breakTies(winners);
}

double IterativeGame::getPluralityDuvergerGapFromVotes(vector<PrefList> prefs) {
    int scores[candidateNumber];
    for (int i=0; i<candidateNumber; i++) {
        scores[i]=0;
    }
    for (long i=0; i<prefs.size(); i++) {
        if (prefs[i].isAbstained()) {
            continue;
        }
        scores[(prefs[i])[0]]+=1;
    }
    vector<int> scoreVals;
    for (int i=0; i<candidateNumber; i++) {
        scoreVals.push_back(scores[i]);
    }
    std::sort(scoreVals.begin(),scoreVals.end());
    
    if (scoreVals[candidateNumber-2]==0) {
        return -1;
    }
    
    
    return ((double)scoreVals[candidateNumber-1])/((double)scoreVals[candidateNumber-2]);
}

double IterativeGame::getPluralityDuvergerGap2FromVotes(vector<PrefList> prefs) {
    int scores[candidateNumber];
    for (int i=0; i<candidateNumber; i++) {
        scores[i]=0;
    }
    for (long i=0; i<prefs.size(); i++) {
        if (prefs[i].isAbstained()) {
            continue;
        }
        scores[(prefs[i])[0]]+=1;
    }
    vector<int> scoreVals;
    for (int i=0; i<candidateNumber; i++) {
        scoreVals.push_back(scores[i]);
    }
    std::sort(scoreVals.begin(),scoreVals.end());
    
    if (scoreVals[candidateNumber-3]==0) {
        return -1;
    }
    
    return ((double)scoreVals[candidateNumber-2])/((double)scoreVals[candidateNumber-3]);
}

double IterativeGame::getPluralityDuvergerGap3FromVotes(vector<PrefList> prefs) {
    int scores[candidateNumber];
    for (int i=0; i<candidateNumber; i++) {
        scores[i]=0;
    }
    for (long i=0; i<prefs.size(); i++) {
        if (prefs[i].isAbstained()) {
            continue;
        }
        scores[(prefs[i])[0]]+=1;
    }
    vector<int> scoreVals;
    for (int i=0; i<candidateNumber; i++) {
        scoreVals.push_back(scores[i]);
    }
    std::sort(scoreVals.begin(),scoreVals.end());
    
    if (scoreVals[candidateNumber-2]==0) {
        return -1;
    }
    
    
    return ((double)scoreVals[candidateNumber-1]*(double)scoreVals[candidateNumber-3])/((double)scoreVals[candidateNumber-2]*(double)scoreVals[candidateNumber-2]);
}

double IterativeGame::getToFirstTwoFromVotes(vector<PrefList> prefs) {
    int scores[candidateNumber];
    for (int i=0; i<candidateNumber; i++) {
        scores[i]=0;
    }
    for (long i=0; i<prefs.size(); i++) {
        if (prefs[i].isAbstained()) {
            continue;
        }
        scores[(prefs[i])[0]]+=1;
    }
    vector<int> scoreVals;
    for (int i=0; i<candidateNumber; i++) {
        scoreVals.push_back(scores[i]);
    }
    std::sort(scoreVals.begin(),scoreVals.end());
    
    int sum=0;
    for (int i=0; i<scoreVals.size(); i++) {
        sum+=scoreVals[i];
    }
    
    return (((double)scoreVals[candidateNumber-1]+scoreVals[candidateNumber-2])/((double)sum));
}


int IterativeGame::getWinner() const {
    return getWinnerFromVotes(votes);
}

int IterativeGame::getWinnerSwitch(IterativeVoter * player, PrefList list) const {
    int playerNum=-1;
    for (int i=0; (playerNum<0) && (i<voterNumber); i++) {
        if (voters[i]==player) {
            playerNum=i;
        }
    }
    
    vector<PrefList> vec=votes;
    vec[playerNum]=list;
    int winner=getWinnerFromVotes(vec);
    return winner;
}


bool IterativeGame::playStage() {
    bool played[voterNumber];
    
    int chosen=0;
    
    for (int i=0; i<voterNumber; i++) {
        if (voters[i]->isAbstained()==true) {
            played[i]=true;
            chosen++;
        } else {
            played[i]=false;
        }
    }
    
    
    
    while (chosen<voterNumber) {
        int playerLocation=rand() % (voterNumber-chosen);
        int player=playerLocation;
        for (int i=0; (i<voterNumber) && (playerLocation>=0); i++) {
            if (played[i]==false) {
                playerLocation--;
            } else {
                player++;
            }
        }
        chosen++;
        if ((voters[player]->makeMove())==true) {
            votes[player]=*(voters[player]->getVote());
            history.push_back(votes);
            return true;
        } else {
            played[player]=true;
        }
    }
    return false;
}


bool IterativeGame::hasStageHappened() const {
    
    for (long i=history.size()-1; i>0; i--) {
        bool isSame=true;
        for (int j=0; j<voterNumber; j++) {
            if (((history[i-1])[j]!=votes[j]) || ((history[i-1])[j].isAbstained()==votes[j].isAbstained())) {
                isSame=false;
            }
            
        }
        if (isSame==true) {
            return true;
        }
    }
    return false;
}

string IterativeGame::printStage() const {
    return printVotes(votes);
}

string IterativeGame::printVotes(vector<PrefList > vec) const {
    ostringstream sStream(ostringstream::out);
    sStream<<"Winner is: "<<getWinnerFromVotes(vec)<<"\n";
    for (int i=0; i<voterNumber; i++) {
        sStream<<"Voter "<<i<<": ";
        sStream<<vec[i]<<"\n";
    }
    sStream.flush();
    return sStream.str();
}

string IterativeGame::printHistory() const {
    ostringstream sStream(ostringstream::out);
    /*
    for (int i=0; i<voterNumber; i++) {
        sStream<<"voter "<<i<<voters[i]->getR()<<", ";
    }
     */
    for (long i=0;i<history.size(); i++) {
        sStream<<"Stage "<<i<<"\n\t";
        sStream<<printVotes(history[i]);
        sStream<<"************\n";
    }
    return sStream.str();
}

void IterativeGame::resetGame() {
    votes.clear();
    history.clear();
    
    for (int i=0;i<voterNumber;i++) {
        voters[i]->resetVoter();
        
        const PrefList *pf=voters[i]->getVote();
        votes.push_back(*pf);
    }
    if (truthtfulWinner==-1) {
        setWinnerAndCondercet(votes);
    }
   
    history.push_back(votes);
}

void IterativeGame::gameEnd() {
    
    if (playStage()!=false) {
        return;
    }
    
    int currWinner=getWinner();

    if(winners.find(currWinner) == winners.end()) {
        winners.insert(std::pair<int,int> (currWinner,1));
    }
    else {
        winners.at(currWinner)=winners[currWinner]+1;
    }
    
    bool hasKey=false;
    
    map<vector<PrefList>,double>::iterator iterAvg=avgStepsToFinal.begin();
    for(map<vector<PrefList>,int>::iterator iter = finalStates.begin(); (iter !=finalStates.end()) && (hasKey==false); ++iter)
    {
        vector<PrefList> k =  iter->first;
        if (getWinnerFromVotes(k)!=getWinner()) {
            ++iterAvg;
            continue;
        }
        bool hasMatch=true;
        for (int i=0; i<voterNumber; i++) {
            if ((k[i])[0]!=(votes[i])[0]) {
                hasMatch=false;
                break;
            }
        }
        
        if (hasMatch==false) {
            ++iterAvg;
            continue;
        }
        
        iterAvg->second=(iterAvg->second*iter->second+history.size())/(iter->second+1);
        iter->second=iter->second+1;
        
        hasKey=true;
        ++iterAvg;
        //ignore value
        //Value v = iter->second;
    }
    
    if (hasKey==false) {
        finalStates.insert(std::pair<vector<PrefList>,int>(votes,1));
        avgStepsToFinal.insert(std::pair<vector<PrefList>,double>(votes,history.size()));
        duvergerGap.insert(std::pair<vector<PrefList>,double>(votes,getPluralityDuvergerGapFromVotes(votes)));
        duvergerGap2.insert(std::pair<vector<PrefList>,double>(votes,getPluralityDuvergerGap2FromVotes(votes)));
        duvergerGap3.insert(std::pair<vector<PrefList>,double>(votes,getPluralityDuvergerGap3FromVotes(votes)));
    }
    if (disType==luce) {
        if (luceInfo.luceRank<0) {
            luceInfo.luceRank=0;
        }
        luceInfo.luceRank=luceInfo.luceRank+voters[0]->getTrueCandidateRank(currWinner);
    }
    
    if (disType==peaked) {
        if (luceInfo.luceRank<0) {
            luceInfo.luceRank=0;
        }
        int location=voters[0]->getTrueCandidateRank(currWinner);
        if (location>(candidateNumber-1)/2) {
            luceInfo.luceRank=luceInfo.luceRank+location-ceil((candidateNumber-1)/2);
        } else {
        luceInfo.luceRank=luceInfo.luceRank+ceil((candidateNumber-1)/2)-location;
        }
    }
    
    if (disType==curved) {
        if (luceInfo.luceRank<0) {
            luceInfo.luceRank=0;
        }
        int location=voters[0]->getTrueCandidateRank(currWinner);
        if ((location!=0) && (location%2==0)) {
            luceInfo.luceRank+=(location/2)-1;
        } else {
            luceInfo.luceRank+=(location/2);
        }
    }
    toFirstTwo+=getToFirstTwoFromVotes(votes);
    
}

double IterativeGame::getCandidateRank(int c) {
    double score=0;
    for (int i=0;i<voterNumber;i++) {
        int voterScore=voters[i]->getTrueCandidateRank(c);
        if (voterScore==-1) {
            return -1;
        }
        score+=voterScore;
    }
    return (score/voterNumber);
}

string IterativeGame::printGame(resultFormat* rs) {
    ostringstream sStream(ostringstream::out);
    ostringstream winnerDesc(ostringstream::out);
    sStream<<"state number\t"<<finalStates.size()<<"\t";
    sStream<<"number of winners\t"<<winners.size()<<"\t";
    
    rs->stableStateNumber=finalStates.size();
    rs->winnerNumber=winners.size();
    
    double avgStepNum=0;
    double avgGrade=0;
    int numberOfStates=0;
    double dg=0;
    double dg2=0;
    double dg3=0;
    map<vector<PrefList>,int>::iterator iterFinal = finalStates.begin();
    for(map<vector<PrefList>,double>::iterator iter = avgStepsToFinal.begin(); iter !=avgStepsToFinal.end(); ++iter) {
        avgStepNum=(avgStepNum*numberOfStates+iter->second*iterFinal->second)/(numberOfStates+iterFinal->second);
        
        
        numberOfStates+=iterFinal->second;
        ++iterFinal;
    }
    
    numberOfStates=0;
    iterFinal=finalStates.begin();
    map<vector<PrefList>,double>::iterator iter3=duvergerGap3.begin();
    map<vector<PrefList>,double>::iterator iter2=duvergerGap2.begin();
    for (map<vector<PrefList>,double>::iterator iter=duvergerGap.begin(); iter!=duvergerGap.end(); ++iter) {
        if (iter->second<-0.1) {
            noDuverger+=iterFinal->second;
        } else {
            dg=(dg*numberOfStates+iter->second*iterFinal->second)/(numberOfStates+iterFinal->second-noDuverger);
            dg3=(dg3*numberOfStates+iter3->second*iterFinal->second)/(numberOfStates+iterFinal->second-noDuverger);
        }
        if (iter2->second<-0.1) {
            noDuverger2+=iterFinal->second;
        } else {
            dg2=(dg2*numberOfStates+iter2->second*iterFinal->second)/(numberOfStates+iterFinal->second-noDuverger);
        }
        numberOfStates+=iterFinal->second;
        ++iterFinal;
        ++iter2;
        ++iter3;
    }
    sStream<<"Avg step number\t"<<avgStepNum<<"\t";
    
    rs->stepNumber=avgStepNum;
    rs->duvergerGap=dg;
    rs->duverger2Gap=dg2;
    rs->duverger3Gap=dg3;
    rs->noDuverger=noDuverger/numberOfStates;
    rs->noDuverger2=noDuverger2/numberOfStates;
    
    numberOfStates=0;
    double diffusion=0;
    double diffusion2=0;
    for (int i=0;i<candidateNumber;i++) {
        if((winners.find(i) == winners.end()) || (winners[i]==0)) {
            continue;
        }
        if (diffusion<=winners[i]) {
            diffusion2=diffusion;
            diffusion=winners[i];
        } else {
            if (diffusion2<winners[i]) {
                diffusion2=winners[i];
            }
        }
        winnerDesc<<"candidate "<<i<<":\t"<<winners[i]<<"\t";
        avgGrade=(avgGrade*numberOfStates+winners[i]*getCandidateRank(i))/(numberOfStates+winners[i]);
        numberOfStates+=winners[i];
    }
    sStream<<winnerDesc.str();
    rs->extraWinnerDetail=winnerDesc.str();
    sStream<<"\t";
    if (winners.size()>1) {
        //    sStream<<"hmm";
    }
    
    sStream<<"average winner ranking\t"<<avgGrade<<"\t";
    sStream<<"truthful ratio\t"<<((double)winners[truthtfulWinner])/((double)numberOfStates)<<"\t";
    sStream<<"borda ratio\t"<<((double)winners[bordaWinner])/((double)numberOfStates)<<"\t";
    sStream<<"maximin ratio\t"<<((double)winners[maximinWinner])/((double)numberOfStates)<<"\t";
    sStream<<"copeland ratio\t"<<((double)winners[copelandWinner])/((double)numberOfStates)<<"\t";
    sStream<<"duverger gap\t"<<dg<<"\t";
    sStream<<"duverger gap2\t"<<dg2<<"\t";
    sStream<<"duverger gap3\t"<<dg3<<"\t";
    sStream<<"No duverger\t"<<noDuverger<<"\t No duverger2\t"<<noDuverger2<<"\t";
    
    rs->winnerDifusion=((double)diffusion)/((double)numberOfStates);
    rs->winnerDifusion2=((double)diffusion2)/((double)numberOfStates);
    rs->winnerRanking=avgGrade;
    rs->pluralityWinner=((double)winners[truthtfulWinner])/((double)numberOfStates);
    rs->bordaWinner=((double)winners[bordaWinner])/((double)numberOfStates);
    rs->maximinWinner=((double)winners[maximinWinner])/((double)numberOfStates);
    rs->copelandWinner=((double)winners[copelandWinner])/((double)numberOfStates);
    rs->firstTwoRatio=((double)toFirstTwo)/((double)numberOfStates);
    if (disType==luce) {
    rs->lucy.bordaWinner=luceInfo.bordaWinner;
    rs->lucy.copelandWinner=luceInfo.copelandWinner;
    rs->lucy.maximinWinner=luceInfo.maximinWinner;
    rs->lucy.pluralityWinner=luceInfo.pluralityWinner;
    rs->lucy.condorcetWinner=luceInfo.condorcetWinner;
    rs->lucy.luceRank=luceInfo.luceRank/numberOfStates;
    }
    if ((disType==peaked) || (disType==curved)) {
        rs->lucy.luceRank=luceInfo.luceRank/numberOfStates;
    }
    
    if (condercetWinner!=-1) {
        sStream<<"condercet ratio\t"<<((double)winners[condercetWinner])/((double)numberOfStates)<<"\t";
        rs->condorcetWinner=((double)winners[condercetWinner])/((double)numberOfStates);
    }
    sStream<<"\n\n";
    rs->description=sStream.str();
    return sStream.str();
}
