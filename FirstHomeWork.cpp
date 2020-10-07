#include <time.h>
#include <iostream>
#include <vector>
#include <math.h>
//#include "Perceptron.h"

using namespace std;
/*
int n;                  // n 개의 input
vector<float> weight;   // 가중치 값을 벡터로 받는다
float th;               // 임계값

// perceptron 구현 함수
int perceptron(vector<int> input)
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


int main() {
    cout << "input 값 개수입력하시오" << endl;
    cin >> n;
    //AND gate 에서 틀린 수 저장
    int count = 0;
    // 임계값 랜덤 받기
    srand(time(NULL));
    th = ((float)rand()) / ((float)RAND_MAX);
    // input 입력받기
    for (int i = 0; i < n; i++) {
        // weight 랜덤 값 생성 후 벡터에 저장
        float RandomWeight = ((float)rand()) / ((float)RAND_MAX);
        weight.push_back(RandomWeight);
    }

    while(1) {
        // AND GATE에 넣을  n을 bit 값으로 바꾸어 어느 수를 넣든 2^n-1 은 AND GATE 통과하게 하기
        // 0 ~ 2^n-2은 AND GATE 통과 X
        vector<int> var(n); // n개 bit를 넣을 변수
        for(int j = 0; j <= pow(2,n)-2; j++) {
            // n개의 bit를 만들기
            for(int k = 0; k < n; k++) {
                var[k] = (j >> k) &1;
            }
            if(perceptron(var) != 0){
                count ++;
                //cout << count <<" 망했다 " << endl;
            } 
        }
        
        // 1로만 구성된 벡터 만들기
        for(int k = 0; k < n; k++) {
            var[k] = 1;
        }
        
        if(perceptron(var) != 1){
            count ++;
            //cout << count <<" 나는 왜 안걸려 " << endl;
        }
        
        
        
        
        cout << "# of wrong: " << count << '\n';
        // 다 맞으면 반복문 탈출
        if (count == 0)
            break;
        // weight 값 입력
        float newWeight;
        cout << n << " enter" << '\n';
        for (int j = 0; j < n; j++)
        {
            cin >> newWeight;
            weight[j] = newWeight;
        }
        count = 0;
    }

    return 0;
}
*/

int main(void)
{
    // 먼저 입력과, 입력에 따른 원하는 결과값을 미리 적어두고
	// Dataset for training 아항데이터셋이 이런거얌
	int *training_input[4] = {
		new int[2]{ 0, 0 },
		new int[2]{ 0, 1 },
		new int[2]{ 1, 0 },
		new int[2]{ 1, 1 }
	};
	int training_output_AND[4] = { 0, 0, 0, 1 };
	int training_output_OR[4]  = { 0, 1, 1, 1 };
	int training_output_XOR[4] = { 1, 0, 0, 1 };

	// To set perceptrons's weights and threshold randomly, perform srand() on main()
	srand(time(NULL));
	rand();

	// Initialize perceptrons
    // 3개의 퍼셉트론을 각각 만든 다음, (이때 입력이 2개라고 알려줌으로써 2개의 weight를 준비하게 함)
    // 모듈은 개념적인 말이고
    // 일단 과제에서 말하는 모듈은 그냥 헤더파일로 따로 구현하란거고
    // 우리는 그 모듈이란 것을(헤더파일을) 가져와서 쓰는거야
    // 그 안에 정의된 Perceptron이라는 클래스를 사용한거야
    // 일단 이건 C언어 문법이랑 '클래스' 개념이 부족해서 그런거야
    // 인공지능 내용이 문제가 아니야..
    // 고거는 너의 선택에 달린거고
    // 암튼 C언어 공부를 계소 해야하는건 맞아
    // 그것도 일단 원하는 것을 구현하는 능력이 뒷받침되지 못해서 어려운 거라고 생각해
    // 알고리즘적인 원리를 떠나서, 내가 A를 구현하겠다! 하면 구현할 ㅅ ㅜ있어ㅑ 하는데
    // 거기서 막힌다고 봐 프로그래머스 1단계 문제나 백준 브론즈티어나 [단계별로 풀어보기] 추천
    // 암튼 난 더이상 인공지능 들어라말라 안 할거야 :( 그래도 그렇게 생각하는거 같아서
    // 확실히 말해야겠어
    // 드랍이나 수강은 너의 자유야(상처받았어 )
    // 몰랑이는 내꺼야 <-- 확신 저아
    Perceptron perceptron_AND(2);  
	Perceptron perceptron_OR(2); 
	Perceptron perceptron_XOR(2);

	// Train AND-gate 
    // 먼저 AND게이트를 훈련시키자. 훈련에 필요한 데이터셋은 입력은 위의 training_input이고, 결과는 training_output_AND야
	printf("Train AND\n");
	perceptron_AND.train(4, training_input, training_output_AND); //여기서 쓰는거구낭 >///<

	// Train OR-gate
	printf("Train OR\n"); // 나머지는 동일
	perceptron_OR.train(4, training_input, training_output_OR);

	// Train XOR-gate
	printf("Train XOR\n"); // 나머지는 동일
	perceptron_XOR.train(4, training_input, training_output_XOR);

	// Wait for end 끗
	printf("Enter to exit\n");
	getchar();
}