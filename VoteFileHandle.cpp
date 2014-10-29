//
//  VoteFileHandle.cpp
//  RangeEquilibria
//
//  Created by Omer Lev on 2/3/14.
//
//

#include "VoteFileHandle.h"

string cands="cand";
string voters="voters";
string dist="dist";
string rounds="rounds";
string maxSteps="step";
string gameNumberString="game";
string sched="scheduler";
string header="head";
string falseS="start";
string vType="voter type";
string rS="r:";
string kS="k:";
string rkS="(r,k)";
string wordDelimiter=":";
string partDelimiter=";";
string listDelimiter=",";
string prefDelimiter=">";



VoteFileHandle::VoteFileHandle (const char* fileName) {
    handleFile(fileName);
}

VoteFileHandle::VoteFileHandle (string fileName) {
    handleFile(fileName.c_str());
}

VoteFileHandle::~VoteFileHandle() {
    for (int i=0; i<allVoters.size(); i++) {
        delete (allVoters[i]);
    }

}

void VoteFileHandle::handleFile(const char* f) {
    
    ifstream myReadFile;
    myReadFile.open(f);
    string line;
    bool start=true;
    if (myReadFile.is_open()) {
        while (getline(myReadFile,line)) {
            if (line.empty()==true) {
                continue;
            }
            if (start==true) {
                if (line.find_first_not_of("0123456789 ")==string::npos) {
                    myReadFile.close();
                    handlePrefLibFile (f);
                    return;
                }
                start=false;
            }
            
            if (line.find(cands)!=string::npos) {
                long ind=line.find(wordDelimiter,line.find(cands));
                if ( ! (istringstream(trim(line.substr(ind+1,line.find(partDelimiter)))) >> candNum) ){
                    candNum=-1;
                }
            }
            
            if (line.find(rounds)!=string::npos) {
                long ind=line.find(wordDelimiter,line.find(rounds));
                if ( ! (istringstream(trim(line.substr(ind+1,line.find(partDelimiter)))) >> roundNum) ){
                    roundNum=-1;
                }
            }
            
            if (line.find(maxSteps)!=string::npos) {
                long ind=line.find(wordDelimiter,line.find(maxSteps));
                if ( ! (istringstream(trim(line.substr(ind+1,line.find(partDelimiter)))) >> maxStep) ){
                    maxStep=-1;
                }
            }
            
            if (line.find(gameNumberString)!=string::npos) {
                long ind=line.find(wordDelimiter,line.find(gameNumberString));
                if ( ! (istringstream(trim(line.substr(ind+1,line.find(partDelimiter)))) >> gameNumber) ){
                    gameNumber=200;
                }
            }
            
            if (line.find(sched)!=string::npos) {
                sType=scheduler;
            }
            
            if (line.find(falseS)!=string::npos) {
                falseStart=true;
            }
            
            if (line.find(header)!=string::npos) {
                long ind=line.find(wordDelimiter,line.find(header));
                sHeader=line.substr(ind+1,line.find(partDelimiter));
            }
            
            if (line.find(rS)!=string::npos) {
                string temp=trim(line.substr(line.find(rS)+2,line.find(partDelimiter)));
                while (temp.length()>0) {
                    string temp2=trim(temp.substr(0,temp.find(listDelimiter)));
                    if (temp.find(listDelimiter)==string::npos) {
                        temp="";
                    }
                    double d;
                    if ((istringstream(temp2)) >> d){
                        rs.push_back(d);
                    }
                    temp=trim(temp.substr(temp.find(listDelimiter)+1));
                }
            }
            
            if (line.find(kS)!=string::npos) {
                string temp=trim(line.substr(line.find(kS)+2,line.find(partDelimiter)));
                while (temp.length()>0) {
                    string temp2=trim(temp.substr(0,temp.find(listDelimiter)));
                    if (temp.find(listDelimiter)==string::npos) {
                        temp="";
                    }
                    double d;
                    if ((istringstream(temp2)) >> d){
                        ks.push_back(d);
                    }
                    temp=trim(temp.substr(temp.find(listDelimiter)+1));
                }
            }
            
            
            if (line.find(rkS)!=string::npos) {
                string temp=trim(line.substr(line.find(rkS),line.find(partDelimiter)));
                while (temp.length()>0) {
                    string temp2=trim(temp.substr(0,temp.find(partDelimiter)));
                    double d1,d2;
                    temp2=trim(temp.substr(temp.find("(")+1));
                    string temp3=trim(temp2.substr(0,temp2.find(listDelimiter)));
                    if (!((istringstream(temp3)) >> d1)){
                        continue;
                    }
                    temp3=trim(temp2.substr(temp2.find(listDelimiter)+1,temp.find(")")));
                    if (!((istringstream(temp3)) >> d2)){
                        continue;
                    }
                    
                    rks.push_back(make_pair(d1,d2));
                    temp=trim(temp.substr(temp.find(partDelimiter)+1));
                }
            }
            
            if (line.find(vType)!=string::npos) {
                if ((line.find("true")!=string::npos) || (line.find("truth")!=string::npos)) {
                    rt=truthful;
                }
                if (line.find("lazy")!=string::npos) {
                    rt=lazy;
                }
                if (line.find("mult")!=string::npos) {
                    vRType=mult;
                }
            }
            
            if (line.find(dist)!=string::npos) {
                long ind=line.find(wordDelimiter,line.find(dist));
                distString=trim(line.substr(ind+1,line.find(partDelimiter)));
                std::transform(distString.begin(), distString.end(), distString.begin(), ::tolower);
            }
            
            if (line.find(voters)!=string::npos) {
                long ind=line.find(wordDelimiter,line.find(voters));
                
                if ( ! ((trim(line.substr(ind+1,line.find(partDelimiter))).length()>0) && (istringstream(trim(line.substr(ind+1,line.find(partDelimiter)))) >> voterNum))){
                }
                
                handleVoterList(&myReadFile);
                break;
                
            }
        }
    }
    myReadFile.close();
}

string VoteFileHandle::runIt(string directory) {
    if (rs.size()>0) {
        for (int i=0; i<rs.size(); i++) {
            bool rUsed=false;
            for (int j=0;j<ks.size();j++) {
                if (ks[j]<=rs[i]) {
                    continue;
                }
                rks.push_back(make_pair(rs[i],ks[j]));
                rUsed=true;
            }
            if (rUsed==false) {
                rks.push_back(make_pair(rs[i],rs[i]+1));
            }
        }
    }
    
    if (distString.size()==0) {
        TestScenario ts=TestScenario(roundNum,maxStep,sType);
        if (sHeader.length()>0) {
            ts.setHeader(sHeader);
        }
        ts.setFalseStart(falseStart);
        ts.setRK(rks);
        ts.setTypes(vRType, rt);
        vector<vector<IterativeVoter*> > pack;
        vector<IterativeVoter*> selectedVoters;
        if (voterNum>0) {
            for (int i=0; i<voterNum; i++) {
                int loc=rand()%(allVoters.size()-i);
                selectedVoters.push_back(allVoters[loc]->copy());
            }
            pack.push_back(selectedVoters);
        } else {
        pack.push_back(allVoters);
        }
        ts.setVoters(pack);
        return ts.go();
    }
    else {
        map<distributionTypes,vector<vector<PrefList> > > m;
        string s;
        for (distributionTypes i=distFirst; i<=distLast; i++) {
            string tmp=printDistributionType(i);
            std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
            if ((distString.find("all")!=string::npos) || (distString.find(tmp)!=string::npos)) {
                for (int j=0; j<gameNumber; j++) {
                    m[i].push_back(*buildPrefs(i, voterNum, candNum));
                }
                TestScenario ts= TestScenario(roundNum, maxStep, sType);
                ts.setDistributionType(i);
                ts.setFilePath(directory);
                if (sHeader.length()>0) {
                    ts.setHeader(sHeader);
                }
                ts.setFalseStart(falseStart);
                ts.setRK(rks);
                ts.setTruePrefs(m[i], vRType, rt);
                
                s.append(ts.go());
            }
        }
        return s;
    }
    return "";
}

void VoteFileHandle::handlePrefLibFile (const char* fileName) {
    ifstream myReadFile;
    myReadFile.open(fileName);
    string line;
    rks.push_back(make_pair(0, 1));
    if (myReadFile.is_open()) {
        map<string,int> *candNames=new map<string,int>();
        getline(myReadFile,line);
        if ( ! (istringstream(line) >> candNum) ){
            candNum=-1;
        }
        
        for (int i=0; i<(candNum+1); i++) {
            getline(myReadFile,line);
        }
        while (getline(myReadFile,line)) {
            int numberVoterPref;
            if ( ! (istringstream(trim(line.substr(0,line.find(",")))) >> numberVoterPref) ){
                numberVoterPref=1;
            }
            int prefs[candNum];
            for (int i=0; i<candNum; i++) {
                prefs[i]=-1;
            }
            setPrefArrayFromString(line.substr(line.find(",")+1), prefs, candNames, ",{}");
            for (int i=0; i<numberVoterPref; i++) {
                IterativeVoter* v;
                if (vRType==additive) {
                    v=new IterativePluralityRangeVoter(new PrefList(candNum,prefs));
                    ((IterativePluralityRangeVoter*)v)->setRangeType(rt);
                } else {
                    v=new IterativePluralityRangeMultVoter(new PrefList(candNum,prefs));
                    ((IterativePluralityRangeMultVoter*)v)->setRangeType(rt);
                }
                
                allVoters.push_back(v);
            }
        }
        delete (candNames);
        
    }
}

string VoteFileHandle::trim(string s) {
    if (s.find_first_not_of(" \t\n")==string::npos) {
        return s;
    }
    string temp=s.substr(s.find_first_not_of(" \t\n"));
    return temp.substr(0,temp.find_last_not_of(" \t\n")+1);
}

void VoteFileHandle::handleVoterList (ifstream* str) {
    string line;
    map<string,int> *candNames=new map<string,int>();
    if (candNum<1) {
        return;
    }
    while (std::getline(*str,line)) {
        if (line.empty()==true) {
            continue;
        }
        int numberVoterPref=1;
        rangeTypes rtVoter=basic;
        voterRType vRTypeVoter=additive;
        if (line.find(partDelimiter)<line.find(prefDelimiter)) {
            if ( ! (istringstream(trim(line.substr(0,line.find(partDelimiter)))) >> numberVoterPref) ){
                numberVoterPref=1;
            }
        }
        if ((line.find("true")!=string::npos) || (line.find("truthful")!=string::npos)) {
            rtVoter=truthful;
        }
        if (line.find("lazy")!=string::npos) {
            rtVoter=lazy;
        }
        if (line.find("mult")!=string::npos) {
            vRTypeVoter=mult;
        }
        line=trim(line.substr(line.find(partDelimiter)+1));
        
        int prefPrivateVoter [candNum];
        if (line.find("private")!=string::npos) {
            long pLoc=line.find("private");
            string temp=trim(line.substr(pLoc));
            temp=trim(temp.substr(line.find(wordDelimiter)+1));
            if (temp.find(partDelimiter)!=string::npos) {
                temp=trim(temp.substr(0,temp.find(partDelimiter)));
            }
            setPrefArrayFromString(temp,prefPrivateVoter,candNames,prefDelimiter);
        } else {
            setPrefArrayFromString(line,prefPrivateVoter,candNames,prefDelimiter);
        }
        
        int prefPublicVoter[candNum];
        bool isPublic=false;
        
        if (line.find("public")!=string::npos) {
            long pLoc=line.find("public");
            string temp=trim(line.substr(pLoc));
            temp=trim(temp.substr(line.find(wordDelimiter)+1));
            if (temp.find(partDelimiter)!=string::npos) {
                temp=trim(temp.substr(0,temp.find(partDelimiter)));
            }
            setPrefArrayFromString(temp,prefPublicVoter,candNames,prefDelimiter);
            isPublic=true;
        }
        double r=-2;
        double k=-2;
        
        if (line.find(rS)!=string::npos) {
            long pLoc=line.find(rS);
            string temp=trim(line.substr(pLoc));
            temp=trim(temp.substr(line.find(wordDelimiter)+1));
            if (temp.find(partDelimiter)!=string::npos) {
                temp=temp.substr(0,temp.find(partDelimiter));
            }
            istringstream(temp) >> r;
        }
        if (line.find(kS)!=string::npos) {
            long pLoc=line.find(kS);
            string temp=trim(line.substr(pLoc));
            temp=trim(temp.substr(line.find(wordDelimiter)+1));
            if (temp.find(partDelimiter)!=string::npos) {
                temp=temp.substr(0,temp.find(partDelimiter));
            }
            istringstream(temp) >> k;
        }
        
        for (int i=0; i<numberVoterPref; i++) {
            IterativeVoter* v;
            if (vRTypeVoter==additive) {
                v=new IterativePluralityRangeVoter(new PrefList(candNum,prefPrivateVoter));
                ((IterativePluralityRangeVoter*)v)->setRangeType(rtVoter);
            } else {
                v=new IterativePluralityRangeMultVoter(new PrefList(candNum,prefPrivateVoter));
                ((IterativePluralityRangeMultVoter*)v)->setRangeType(rtVoter);
            }
            if (r!=-2) {
                v->setR(r);
            }
            if (k!=-2) {
                v->setK(k);
            }
            
            if (isPublic==true) {
                v->setPublicVoter(new PrefList(candNum,prefPublicVoter));
            }
            allVoters.push_back(v);
        }
    }
    delete (candNames);
}

void VoteFileHandle::setPrefArrayFromString(string str, int* prefs, map<string,int>*candNames, string prefsDelimiter) {
    for (int i=0; i<candNum; i++) {
        string tmp;
        if (str.find_first_of(prefsDelimiter)!=string::npos) {
            tmp=trim(str.substr(0,str.find_first_of(prefsDelimiter)));
            str=trim(str.substr(str.find_first_of(prefsDelimiter)+1));
        } else {
            tmp=trim(str.substr(0,str.find(partDelimiter)));
            str=trim(str.substr(str.find(partDelimiter)+1));
        }
        if ((*candNames).find(tmp)==(*candNames).end()) {
            (*candNames)[tmp]=((int)(*candNames).size());
        }
        prefs[i]=(*candNames)[tmp];
    }
    
}