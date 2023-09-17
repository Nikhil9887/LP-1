#include <iostream>
#include<bits/stdc++.h>
using namespace std;


int found(vector<pair<string,int>>s,string key){
	for(int i=0;i<s.size();i++){
		if(s[i].first==key){
			return i+1;
		}
	}
	return -1;
}

int main() {

	map<string,pair<string,int>> memo;
	memo["STOP"]={"IS",00};
	memo["ADD"]={"IS",01};
	memo["SUB"]={"IS",02};
	memo["MULT"]={"IS",03};
	memo["MOVER"]={"IS",04};
	memo["MOVEM"]={"IS",05};
	memo["COMP"]={"IS",06};
	memo["BC"]={"IS",07};
	memo["DIV"]={"IS",8};
	memo["READ"]={"IS",9};
	memo["PRINT"]={"IS",10};
	memo["START"]={"AD",01};
	memo["END"]={"AD",02};
	memo["ORIGIN"]={"AD",03};
	memo["EQU"]={"AD",04};
	memo["LTORG"]={"AD",05};
	memo["DS"]={"DL",02};
	memo["DC"]={"DL",01};

	map<string,int> reg;
	reg["AREG"]=1;
	reg["BREG"]=2;
	reg["CREG"]=3;
	reg["DREG"]=4;

	map<string,int> concode;
	concode["LT"]=1;
	concode["LE"]=2;
	concode["EQ"]=3;
	concode["GT"]=4;
	concode["GE"]=5;
	concode["ANY"]=6;


	fstream fin,icout,stout,ltout,pout;
    fin.open("sourcecode.txt",ios::in);
    if(!fin){
    	cout<<"acg"<<endl;
    }else{ cout<<"Opened Succ"<<endl;}
    icout.open("InterMCode.txt",ios::out);
    stout.open("symTable.txt",ios::out);
    ltout.open("litTable.txt",ios::out);
    pout.open("poolTable.txt",ios::out);


    vector<pair<string,int>>sym;
    vector<pair<string,int>>lit;
    vector<int>pol;
    int address=0;
    int count=-2;
    int litcount=0;
	while(!fin.eof()){
        count++;
		string buffer;
		icout<<address+count<<"\t";
		getline(fin,buffer);
//        cout<<1<<endl;

		vector<string> words;
		string word="";
		buffer+=" ";
		for(auto x:buffer){

			if(x==' '){
			   words.push_back(word);
			   word="";
			}
			else{
				word+=x;
			}
		}
		for(auto x:words){
			cout<<x<< " ";
		}
		cout<<endl;

		if(words.size()==4){
					string lable,memoni,op1,op2;
					lable=words[0];
					memoni=words[1];
					op1=words[2];
					op2=words[3];
		         if(found(sym,lable)!=-1){
						 sym[found(sym,lable)-1].second=address+count;
//					      icout<<"(S,"<<found(sym,lable)<<")";
					 }

					 else if(found(sym,lable)==-1){
					   	sym.push_back({lable,-1});
//						 icout<<"(S,"<<found(sym,lable)<<")";
		      	}

		         icout<<"("<<memo[memoni].first<<","<<memo[memoni].second<<")\t";
		         icout<<"("<<reg[op1]<<")(S,";

		        if(found(sym,op2)!=-1){
						 sym[found(sym,op2)-1].second=address+count;
					     icout<<found(sym,op2)<<")\t"<<endl;
					 }
					 else if(found(sym,op2)==-1){
					   	sym.push_back({op2,-1});
						icout<<found(sym,op2)<<")\t"<<endl;
					     	}



				}
		else if(words.size()==3 ){

			string memoni,op1,op2;
			memoni=words[0];
			op1=words[1];
			op2=words[2];

			if(memo.find(memoni)!=memo.end() && memoni!="EQU"){
			icout<<"("<<memo[memoni].first<<","<<memo[memoni].second<<")\t";

			if(memoni=="BC"){
				icout<<"("<<concode[op1]<<")\t";
			}
			else{
			icout<<"("<<reg[op1]<<")\t";
			}
			if(found(sym,op2)!=-1){
				 sym[found(sym,op2)-1].second=address+count;
			     icout<<found(sym,op2)<<")\t"<<endl;
			 }
			 else if(found(sym,op2)==-1){
				if(op2[0]=='='){
				       lit.push_back({op2,-1});
				       icout<<"(L,"<<found(lit,op2)<<")"<<endl;
				       litcount++;
				}
				else{
			   	sym.push_back({op2,-1});
				icout<<"(S,"<<found(sym,op2)<<")"<<endl;
				}
			     	}
			}


			else{
				string lable,mem,cons;
				  lable=memoni;
				  mem=op1;
				  cons=op2;
				  if(mem=="EQU"){

                      sym.push_back({lable,sym[found(sym,cons)-1].second});
                      icout<<"\t("<<memo[mem].first<<","<<memo[mem].second<<")\t";
                      icout<<"(S,"<<found(sym,cons)<<")"<<endl;
				  }
				  else{
				 if(found(sym,lable)!=-1){
		           sym[found(sym,lable)-1].second=address+count;
				//  icout<<"(S,"<<found(sym,lable)<<")";
					}

				 else if(found(sym,lable)==-1){
				  	sym.push_back({lable,-1});
				//icout<<"(S,"<<found(sym,lable)<<")";
			}

				 icout<<"("<<memo[mem].first<<","<<memo[mem].second<<")\t(C,"<<cons<<")"<<endl;
			}

			}


		}
		else if(words.size()==2){
            string memoni,lable;
            memoni=words[0];
            lable=words[1];
            if(memoni=="START"){
            	address=stoi(lable);
            	icout<<"("<<memo[memoni].first<<","<<memo[memoni].second<<")\t(C,"<<address<<")"<<endl;
            }
            else if(memoni=="ORIGIN"){
                address=sym[found(sym,lable)-1].second;
                count=-1;
            	icout<<"("<<memo[memoni].first<<","<<memo[memoni].second<<")\t(S,"<<found(sym,lable)<<")"<<endl;
            }
            else{
//            	sym.push_back({lable,-1});
            	icout<<"("<<memo[memoni].first<<","<<memo[memoni].second<<")\t(S,";
            	if(found(sym,lable)!=-1){
            		icout<<found(sym,lable)<<")"<<endl;
            	}
            	else if(found(sym,lable)==-1){
            		sym.push_back({lable,-1});
            		icout<<found(sym,lable)<<")"<<endl;

            	}
            }
		}
		else if(words.size()==1){
			string memoni;
			   memoni=words[0];
			   if(memoni=="LTORG"){
				   icout<<"("<<memo[memoni].first<<","<<memo[memoni].second<<")\t";
				   int x=address+count-1;
				   if(litcount!=0){
					   if(pol.empty()){
						   pol.push_back(1);
						   for(int i=0;i<litcount;i++){
							   lit[i].second=x+1;
						   }
						   count=lit[lit.size()-1].second-address;
						   pol.push_back(litcount);
					   }
					   else{
						   for(int i=pol[pol.size()-1];i<litcount;i++){
							   lit[i].second=x+1;
						   }
						   count=lit[lit.size()-1].second-address;
						   pol.push_back(pol[pol.size()-1]+litcount);

					   }

				   }
			   }


			   else if(memoni=="END" || memoni=="STOP"){
				  icout<<"("<<memo[memoni].first<<","<<memo[memoni].second<<")"<<endl;
				  cout<<"Check the Output Files for the Answer."<<endl;

			               }

		}
		else{
			cout<<"Syntax Error at line "<<count<<endl;

		}



	}
	for(int i=0;i<sym.size();i++){
	      stout<<sym[i].first<<","<<sym[i].second<<endl;
	   }
	for(int i=0;i<lit.size();i++){
		ltout<<lit[i].first<<","<<lit[i].second<<endl;
	}
	for(int i=0;i<pol.size();i++){
			pout<<pol[i]<<endl;
		}
	fin.close();






	return 0;
}