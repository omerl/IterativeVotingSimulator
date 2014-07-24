//
//  TestScenario.cpp
//  RangeEquilibria
//
//  Created by Omer Lev on 23/2/14.
//
//

#include "TestScenario.h"

void TestScenario::setHeader(string head) {
    scenHeader=head;
}

void TestScenario::setFilePath(string path) {
    filePath=path;
}

void TestScenario::setFalseStart(bool fs) {
    falseStart=fs;
}

void TestScenario::setDistributionType(distributionTypes dT) {
    dType=dT;
    distGiven=true;
}

void TestScenario::setTruePrefs(vector<vector<PrefList> > prefs,voterRType rT, rangeTypes ranT) {
    for (int i=0; i<prefs.size(); i++) {
        vector<PrefList> pl;
        int candNum=prefs[i][0].getCandidateNumber();
        for (int j=0; j<prefs[i].size(); j++) {
            if (prefs[i][j].getCandidateNumber()!=candNum) {
                throw illegalPreferenceList();
            }
            pl.push_back(prefs[i][j]);
        }
        truePrefs.push_back(pl);
    }
    rType=rT;
    ranType=ranT;
}

void TestScenario::setTypes(voterRType rT, rangeTypes ranT) {
    rType=rT;
    ranType=ranT;
}


void TestScenario::setVoters(vector<vector<IterativeVoter*> > vot) {
    for (int i=0; i<vot.size(); i++) {
        vector<IterativeVoter *> pl;
        int candNum=vot[i][0]->getVote()->getCandidateNumber();
        for (int j=0; j<vot[i].size(); j++) {
            if (vot[i][j]->getVote()->getCandidateNumber()!=candNum) {
                throw illegalPreferenceList();
            }
            pl.push_back(vot[i][j]);
        }
        voters.push_back(pl);
    }
    
}

void TestScenario::setRK(vector<pair<double, double> > rk) {
    map<double,vector<double> > ord;
    for (int i=0; i<rk.size(); i++) {
        if (ord.find(rk[i].first)==ord.end()) {
            vector<double> k;
            k.push_back(rk[i].second);
            ord[rk[i].first]=k;
        }
        else {
            if (find(ord[rk[i].first].begin(),ord[rk[i].first].end(),rk[i].second)!=ord[rk[i].first].end()) {
                continue;
            }
            ord[rk[i].first].push_back(rk[i].second);
        }
    }
    
    for (map<double, vector<double> >::iterator i = ord.begin(); i != ord.end(); i++) {
        vector<double> k=i->second;
        sort(k.begin(), k.end());
        for (int j=0; j<k.size(); j++) {
            double r=i->first;
            pair<double, double> p=make_pair(r, k[j]);
            RKs.push_back(p);
        }
    }
}

string TestScenario::go() {
    if ((truePrefs.size()==0) && (voters.size()==0)) {
        return "";
    }
    if (RKs.size()==0) {
        return goRK(0,1);
    }
    string s;
    for (int i=0; i<RKs.size(); i++) {
        s.append(goRK(RKs[i].first,RKs[i].second));
    }
    
    return s;
}


string TestScenario::goRK(double r,double k) {
    if (voters.size()==0) {
        createVotersFromPrefs(r, k);
    } else {
        if (RKs.size()!=0) {
            updateVoters(r,k);
        }
    }
    string s=getStartString(r,k,(int)voters[0].size(),voters[0][0]->getVote()->getCandidateNumber());
    ofstream dataFile;
    resultFormat* rs=new resultFormat;
    dataFile<<s;
    dataFile.open (getFileName(r,k,(int)voters[0].size(),voters[0][0]->getVote()->getCandidateNumber()).c_str(), std::ofstream::app);
    for (int i=0; i<voters.size(); i++) {
        resultFormat* rsGame=goScenario(r,k, voters[i]);
        dataFile<<printResults(rsGame);
        integrateRS(i,rs,rsGame);
    }
    
    s.append(printResults(rs));
    delete (rs);
    
    dataFile.close();
    return s;
}

resultFormat* TestScenario::goScenario(double r, double k, vector<IterativeVoter*> vot) {
    ostringstream sStream(ostringstream::out);
    int voterNumber=(int)vot.size();
    IterativeVoter * gameVoters[voterNumber];
    int loopCounter=0;
    for (int i=0; i<voterNumber; i++) {
        gameVoters[i]=vot[i];
    }
    IterativeGame * bg;
    
    //Setting the appropriate game for the scenario
    if (falseStart==true) {
        if (scenType==regular) {
            bg=new IterativePluralityFalseStartGame (voterNumber,(IterativeVoter **)&gameVoters);
        }
        if (scenType==scheduler) {
            bg=new IterativePluralityScheduledFalseStartGame (voterNumber,(IterativeVoter **)&gameVoters);
        }
    }
    else {
        if (scenType==regular) {
            bg=new IterativePluralityGame (voterNumber,(IterativeVoter **)&gameVoters);
        }
        if (scenType==scheduler) {
            bg=new IterativePluralityScheduledGame (voterNumber,(IterativeVoter **)&gameVoters);
        }
    }
    
    if (distGiven==true) {
        bg->setDistributionType(dType);
    }
    
    
    for (int i=0; i<voterNumber; i++) {
        gameVoters[i]->setGame(bg);
    }
    
    //Running the games
    
    for (int i=0; i<gameRounds; i++) {
        int stepNumber=0;
        
        for (stepNumber=0; stepNumber<maxStep; stepNumber++) {
            if (bg->playStage()==false) {
                bg->gameEnd();
                break;
            }
            if (bg->hasStageHappened()==true) {
                cout<<"found loop!\n";
                //cout<<bg->printHistory();
                loopCounter+=1;
                break;
            }
        }
        
        if (stepNumber==0) {
            bg->resetGame();
            break;
        }
        if (stepNumber==maxStep) {
            cout<<"didn't finish in "<<maxStep<<" steps\n";
            cout<<bg->printHistory();
            
        }
        //cout<<bg->printHistory();
        bg->resetGame();
    }
    
    resultFormat * rs=new resultFormat();
    bg->printGame(rs);
    rs->looped=(loopCounter)/(gameRounds);
    delete bg;
    
    return rs;
}


void TestScenario::createVotersFromPrefs(double r, double k) {
    for (int i=0; i<truePrefs.size(); i++) {
        vector<IterativeVoter *> votVec;
        for (int j=0;j<truePrefs[i].size();j++) {
            IterativeVoter * iv;
            if (r>=0) {
                if (rType==additive) {
                    int ka= k*(truePrefs[i].size());
                    int ra=r*(truePrefs[i].size());
                    if (ra==ka) {
                        ka+=1;
                    }
                    iv=new IterativePluralityRangeVoter(&truePrefs[i][j],ra,ka,ranType);
                }
                if (rType==mult) {
                    iv=new IterativePluralityRangeMultVoter(&truePrefs[i][j],r,k,ranType);
                }
            }
            if (r<0) {
                if (rType==additive) {
                    int t=floor((double)truePrefs[i].size()/(double)truePrefs[i][j].getCandidateNumber());
                    int ra=rand()%t;
                    int ka=rand()%(truePrefs[i].size())+ra;
                    if (ra==ka) {
                        ka+=1;
                    }
                    if (ka>truePrefs[i].size()) {
                        ka=(int)truePrefs[i].size();
                    }
                    iv=new IterativePluralityRangeVoter(&truePrefs[i][j],ra,ka,ranType);
                }
                if (rType==mult) {
                    double ra=(((double)rand())/RAND_MAX);
                    double ka=(((double)rand())/RAND_MAX)+ra;
                    if (ra==ka) {
                        ka+=1/(truePrefs[i].size());
                    }
                    iv=new IterativePluralityRangeMultVoter(&truePrefs[i][j],ra,ka,ranType);
                }
            }
            if (falseStart==true) {
                PrefList pub=createRandomPrefList(truePrefs[i][j].getCandidateNumber());
                iv->setPublicVoter(&pub);
            }
            votVec.push_back(iv);
        }
        voters.push_back(votVec);
    }
}

void TestScenario::updateVoters(double r, double k) {
    for (int i=0; i<voters.size(); i++) {
        for (int j=0;j<voters[i].size();j++) {
            if (r>=0) {
                if (rType==additive) {
                    int ka= k*(voters[i].size());
                    int ra=r*(voters[i].size());
                    if (ra==ka) {
                        ka+=1;
                    }
                    voters[i][j]->setK(ka);
                    voters[i][j]->setR(ra);
                }
                if (rType==mult) {
                    voters[i][j]->setR(r);
                    voters[i][j]->setK(k);
                }
            }
            if (r<0) {
                if (rType==additive) {
                    int t=floor((double)voters[i].size()/(double)voters[i][j]->getVote()->getCandidateNumber());
                    int ra=rand()%(voters[i].size());
                    if (t>0) {
                        ra=rand()%t;
                    }
                    int ka=rand()%(voters[i].size())+ra;
                    if (ra==ka) {
                        ka+=1;
                    }
                    if (ka>voters[i].size()) {
                        ka=(int)voters[i].size();
                    }
                    voters[i][j]->setK(ka);
                    voters[i][j]->setR(ra);
                }
                if (rType==mult) {
                    double ra=(((double)rand())/RAND_MAX);
                    double ka=(((double)rand())/RAND_MAX)+ra;
                    if (ra==ka) {
                        ka+=1/(voters[i].size());
                    }
                    voters[i][j]->setR(r);
                    voters[i][j]->setK(k);
                }
            }
        }
    }
}

string TestScenario::getFileName(double r, double k, int voterNum, int candNum) {
    ostringstream fileName(ostringstream::out);
    int voterNumber=voterNum;
    int candidateNumber=candNum;
    
    fileName<<filePath<<scenHeader;
    if (distGiven==true) {
        fileName<<printDistributionType(dType);
    }
    fileName<<voterNumber<<candidateNumber<<printRangeType(ranType)<<printScenarioType(scenType);
    if (rType==additive) {
        fileName<<"Add";
    }
    if (rType==mult) {
        fileName<<"Mult";
    }
    
    if (r<0) {
        fileName<<"RandomR+K";
    }
    else {
        fileName<<r<<k;
    }
    
    return fileName.str();
}

string TestScenario::getStartString(double r,double k,int voterNum, int candNum) {
    ostringstream sStream(ostringstream::out);
    int voterNumber=voterNum;
    int candidateNumber=candNum;
    
    sStream<<scenHeader;
    if (distGiven==true) {
        sStream<<printDistributionType(dType);
    }
    sStream<<"\t candidates:\t"<<candidateNumber<<"\t voters:\t"<<voterNumber<<"\t"<<printRangeType(ranType)<<"\t"<<printScenarioType(scenType)<<"\t";
    
    if (r<0) {
        sStream<<"Random R/K \t";
    }
    else {
        double ra=r;
        double ka=k;
        if (rType==additive) {
            ra=r*voterNumber;
            ka=k*voterNumber;
        }
        sStream<<"r: \t"<<ra<<"\t k:\t"<<ka<<"\t";
    }
    return sStream.str();
    
}

void TestScenario::integrateRS (int gameNumber, resultFormat* master, resultFormat* newGame) {
    master->extraWinnerDetail="";
    master->stableStateNumber=(master->stableStateNumber*gameNumber+newGame->stableStateNumber)/(gameNumber+1);
    master->winnerNumber=(master->winnerNumber*gameNumber+newGame->winnerNumber)/(gameNumber+1);
    master->stepNumber=(master->stepNumber*gameNumber+newGame->stepNumber)/(gameNumber+1);
    master->winnerRanking=(master->winnerRanking*gameNumber+newGame->winnerRanking)/(gameNumber+1);
    master->pluralityWinner=(master->pluralityWinner*gameNumber+newGame->pluralityWinner)/(gameNumber+1);
    master->bordaWinner=(master->bordaWinner*gameNumber+newGame->bordaWinner)/(gameNumber+1);
    master->maximinWinner=(master->maximinWinner*gameNumber+newGame->maximinWinner)/(gameNumber+1);
    master->copelandWinner=(master->copelandWinner*gameNumber+newGame->copelandWinner)/(gameNumber+1);
    
    if (newGame->duverger2Gap>0.01) {
        master->duverger2Gap=(master->duverger2Gap*(gameNumber-(master->noDuverger2*gameNumber))+newGame->duverger2Gap*(1-newGame->noDuverger2))/((double)(gameNumber-(master->noDuverger2*gameNumber))+(1-newGame->noDuverger2));
    }
    if (newGame->duvergerGap>0.01) {
        master->duvergerGap=(master->duvergerGap*(gameNumber-(master->noDuverger*gameNumber))+newGame->duvergerGap*(1-newGame->noDuverger))/((double)(gameNumber-(master->noDuverger*gameNumber))+(1-newGame->noDuverger));
        master->duverger3Gap=(master->duverger3Gap*(gameNumber-(master->noDuverger*gameNumber))+newGame->duverger3Gap*(1-newGame->noDuverger))/((double)(gameNumber-(master->noDuverger*gameNumber))+(1-newGame->noDuverger));
    }
    master->noDuverger=(master->noDuverger*gameNumber+newGame->noDuverger)/(gameNumber+1);
    master->noDuverger2=(master->noDuverger2*gameNumber+newGame->noDuverger2)/(gameNumber+1);
    if (newGame->condorcetWinner>-0.1) {
        master->condorcetWinner=(master->condorcetWinner*(gameNumber-(master->noCondorcet*gameNumber))+newGame->condorcetWinner)/(gameNumber-(master->noCondorcet*gameNumber)+1);
        master->noCondorcet=((double)master->noCondorcet*gameNumber)/((double)(gameNumber+1));
    }
    else {
        master->noCondorcet=((double)master->noCondorcet*gameNumber+1)/((double)(gameNumber+1));
    }
    
    master->looped=((master->looped*gameNumber)+newGame->looped)/(gameNumber+1);
    master->firstTwoRatio=((master->firstTwoRatio*gameNumber)+newGame->firstTwoRatio)/(gameNumber+1);
    master->improvedScore=((master->improvedScore*gameNumber)+newGame->improvedScore)/(gameNumber+1);
    
    master->winnerDifusion=((master->winnerDifusion*gameNumber)+newGame->winnerDifusion)/(gameNumber+1);
    master->winnerDifusion2=((master->winnerDifusion2*gameNumber)+newGame->winnerDifusion2)/(gameNumber+1);
    
    if (distGiven==true) {
        if (dType==luce) {
            master->lucy.bordaWinner=(master->lucy.bordaWinner*gameNumber+newGame->lucy.bordaWinner)/(gameNumber+1);
            master->lucy.copelandWinner=(master->lucy.copelandWinner*gameNumber+newGame->lucy.copelandWinner)/(gameNumber+1);
            master->lucy.maximinWinner=(master->lucy.maximinWinner*gameNumber+newGame->lucy.maximinWinner)/(gameNumber+1);
            master->lucy.pluralityWinner=(master->lucy.pluralityWinner*gameNumber+newGame->lucy.pluralityWinner)/(gameNumber+1);
            if (newGame->lucy.condorcetWinner>-0.1) {
                master->lucy.condorcetWinner=(master->lucy.condorcetWinner*gameNumber+newGame->lucy.condorcetWinner)/(gameNumber+1);
            }
            
        }
        
        
        if ((dType==peaked) ||(dType==curved) || (dType==luce)) {
            master->lucy.luceRank=(master->lucy.luceRank*gameNumber+newGame->lucy.luceRank)/(gameNumber+1);
        }
    }
    
}

