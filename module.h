#include <iostream>
#include <vector>
#include <time.h>
#include <math.h>

using namespace std;

class module {
    private:
    int n;                      // n 개의 input
    vector<float> weight, before_weight;   // 가중치 값을 벡터로 받는다
    float th;                   // 임계값

    int perceptron(vector<int> &input);
    int CalculateTrainingDataset(int length, int **inputs, int *outputs, bool feedback);
	void Feedback(int *input, int output, int expect);
    void randomWeight(int n, vector<float> &weight);
    int numError(int count); 
    int changeInput(int n, vector<int> &var);
    
};


// perceptron 구현 함수
int module::perceptron(vector<int> &input)
{
    int output;
    float net = 0;
    // net 값 생성
    for (int i = 0; i < n; i++)
    {
        net += weight[i] * input[i];
    }
    // net 값이 임계값 보다 높은 경우
    if (net > th)
    {
        cout << "[output = 1]"
             << "net: " << net << " "
             << "th: " << th << '\n';
        output = 1;
    }
    // net 값이 임계값 보다 낮은 경우
    else
    {
        cout << "[output = 0]"
             << "net: " << net << " "
             << "th: " << th <<'\n'; 
        output = 0;
    }
    return output;
}

int module::numError(int count) {
    return count++;
}

// input 값을 비트 값으로 변환하는 함수
int module::changeInput(int n, vector<int> &var) {
    int count = 0;
    // AND GATE에 넣을  n을 bit 값으로 바꾸어 어느 수를 넣든 2^n-1 은 AND GATE 통과하게 하기
    // 0 ~ 2^n-2은 AND GATE 통과 X
    vector<int> var(n); // n개 bit를 넣을 변수
    for(int j = 0; j <= pow(2,n)-2; j++) {
        // n개의 bit를 만들기
        for(int k = 0; k < n; k++) {
            var[k] = (j >> k) &1;
        }
        if(perceptron(var) != 0){
            numError(count);
        } 
    }
    
    // 1로만 구성된 벡터 만들기
    for(int k = 0; k < n; k++) {
        var[k] = 1;
    }
    
    if(perceptron(var) != 1){
        numError(count);
    }

    cout << "# of wrong: " << count << '\n';
    // 다 맞으면 반복문 탈출
    if (numError(count) == 0)
        return 1;
    // **** 에러 있으면(count != 0) weight 랜덤 값으로 변경****
    randomWeight(n, weight);
    // count = 0; <- 어차피 맨 위에서 초기화 하니깐
}


void module::randomWeight(int n, vector<float> &weight) {
    for (int i = 0; i < n; i++) {
        // weight 랜덤 값 생성 후 벡터에 저장
        float RandomWeight = ((float)rand()) / ((float)RAND_MAX);
        weight.push_back(RandomWeight);
    }
}