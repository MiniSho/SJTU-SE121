#include "common.h"
#include <ctime>

using namespace std;

double score = 0;
ifstream input_file1;
ifstream ans_file1;

ifstream input_file2;
ifstream ans_file2;

ifstream input_file3;
ifstream ans_file3;

fstream ans_output;
class Data1 {
public:
    int amount;
    vector<int> coins;

    Data1(){
        amount = 0;
        coins.clear();
    }
};

class Data2 {
public:
    int amount;
    vector< vector<int> > conquer;

    Data2(){
        amount = 0;
        for(unsigned int i = 0;i<conquer.size();i++){
            conquer[i].clear();
        }
        conquer.clear();
    }
};

class Data3 {
public:
    int n,hp;
    vector<int> damage;
    vector<int> edges;

    Data3(){
        n = 0;
        hp = 0;
        damage.clear();
        edges.clear();
    }
};

int func1(int amount, vector<int>& coins);
int func2(int amount, vector< vector<int> >& conquer);
double func3(int n,int hp, vector<int>& damage, vector<int>& edges);

int input_data1(vector<int>& coins)
{
    int amount;
    if(input_file1>>amount){
         int num;
        input_file1>>num;
        for(int i = 0 ; i < num; i++){
            int t;
            if(input_file1>>t)
            coins.push_back(t);
        }

        return amount;
    }
    return -1;
}

int input_data2(vector< vector<int> >& conquer)
{
    int amount;
    if(input_file2>>amount) {
        for(int i = 0 ; i < amount; i++){
            vector<int> temp;
            temp.clear();
            for(int j = 0; j < amount;j++){
                int t;
                if(input_file2>>t)
                temp.push_back(t);
            }
            conquer.push_back(temp);
        }
        return amount;
    }

    return -1;
}


void input_data3(Data3* data)
{
    int m;

    if(input_file3 >> data->n){
        input_file3 >> data->hp;
        input_file3 >> m;

        for(int i = 0; i < data->n; i++){
            int t;
            input_file3>>t;
            data->damage.push_back(t);
        }

        for(int i = 0; i < 2*m; i++){
            int t;
            input_file3>>t;
            data->edges.push_back(t);
        }
    }

}

bool test1(Data1* data,int ans)
{
    int answer = func1(data->amount, data->coins);
    return answer == ans;

}

bool test2(Data2* data,int ans)
{
    int answer = func2(data->amount, data->conquer);
    return answer == ans;

}

bool test3(Data3* data,double ans)
{
    double answer = func3(data->n,data->hp,data->damage,data->edges);
    ans_output.setf(ios::showpoint);
    ans_output.precision(8);
    ans_output<<answer<<endl;
    return fabs(ans - answer) <= 1e-8;
}

int main()
{

    // input test data
    ans_output.open("answer.txt");
    // open file
    input_file1.open("test/test1.txt");
    if(!input_file1.is_open())
    {
        cout<<"Open test1 file error!"<<endl;
        exit(-1);
    }

    ans_file1.open("answer/answer1.txt");
    if(!ans_file1.is_open())
    {
        cout<<"Open answer1 file error!"<<endl;
        exit(-1);
    }
    //end open file

    //read file
    vector<Data1*> data1s;
    data1s.clear();

    while( !input_file1.eof() ){
        Data1* data1 = new Data1();
        data1->amount = input_data1(data1->coins);
        if(data1->amount > 0)
            data1s.push_back(data1);

    }
    //data1s.pop_back();

    vector<int> ans1;
    ans1.clear();

    while( !ans_file1.eof() ){
        int t;
	if(ans_file1>>t) ans1.push_back(t);

    }
    //end read file

    // open file
    input_file2.open("test/test2.txt");
    if(!input_file2.is_open())
    {
        cout<<"Open test2 file error!"<<endl;
        exit(-1);
    }

    ans_file2.open("answer/answer2.txt");
    if(!ans_file2.is_open())
    {
        cout<<"Open answer2 file error!"<<endl;
        exit(-1);
    }
    //end open file

    //read file
    vector<Data2*> data2s;
    data2s.clear();

    while( !input_file2.eof() ){
        Data2* data2 = new Data2();
        data2->amount = input_data2(data2->conquer);
        if(data2->amount > 0)
                data2s.push_back(data2);
    }


    vector<int> ans2;
    ans2.clear();

    while( !ans_file2.eof() ){
        int t;
	if(ans_file2>>t) ans2.push_back(t);

    }
    //end read file

    // open file
    input_file3.open("test/test3.txt");
    if(!input_file3.is_open())
    {
        cout<<"Open test3 file error!"<<endl;
        exit(-1);
    }

    ans_file3.open("answer/answer3.txt");
    if(!ans_file3.is_open())
    {
        cout<<"Open answer3 file error!"<<endl;
        exit(-1);
    }
    //end open file

    //read file
    vector<Data3*> data3s;
    data3s.clear();

    while( !input_file3.eof() ){
        Data3* data3 = new Data3();
        input_data3(data3);
        if(data3->n > 0)
            data3s.push_back(data3);
    }

    vector<double> ans3;
    ans3.clear();

    while( !ans_file3.eof() ){
        double t;
	    if(ans_file3>>t) ans3.push_back(t);

    }
    //end read file


    //test
    for(unsigned int i = 0;i < data1s.size();i++){

	if(test1(data1s[i],ans1[i]))
	    {
		score += 25.00/data1s.size();
		cout<<"Pass part1-case"<<i+1<<endl;
	    }
	    else
	    {
		cout<<"Fail part1-case"<<i+1<<endl;
	    }
    }
    float score_part1 = score;
    if(fabs(score_part1-25.00) <= 1e-15) cout<<"Pass part1!"<<endl;


    for(unsigned int i = 0;i < data2s.size();i++){

	if(test2(data2s[i],ans2[i]))
	    {
		score += 25.00/data2s.size();
		cout<<"Pass part2-case"<<i+1<<endl;
	    }
	    else
	    {
		cout<<"Fail part2-case"<<i+1<<endl;
	    }
    }
    float  score_part2 = score;
    if(fabs(score_part2-score_part1-25.00) <= 1e-15) cout<<"Pass part2!"<<endl;

    for(unsigned int i = 0;i < data3s.size();i++){

	if(test3(data3s[i],ans3[i]))
	    {
		score += 25.00/data3s.size();
		cout<<"Pass part3-case"<<i+1<<endl;
	    }
	    else
	    {
		cout<<"Fail part3-case"<<i+1<<endl;
	    }
    }
    float  score_part3 = score;
    if(fabs(score_part3-score_part2-25.00) <= 1e-15) cout<<"Pass part3!"<<endl;


    input_file1.close();
    ans_file1.close();
    input_file2.close();
    ans_file2.close();
    input_file3.close();
    ans_file3.close();
    for(unsigned int i = 0; i< data1s.size(); i++){
	delete data1s[i];
    }
    for(unsigned int i = 0; i< data2s.size(); i++){
	delete data2s[i];
    }
    for(unsigned int i = 0; i< data3s.size(); i++){
	delete data3s[i];
    }

    cout.setf(ios::showpoint);
    cout.precision(4);
    cout<<"Your score:"<<score<<"/75.00"<<endl;
    return 0;
}





