#include <time.h>
#include <iostream>
#include <vector>
#include <math.h>
#include "Perceptron.h"


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
	// Dataset for training
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
	Perceptron perceptron_AND(2);
	Perceptron perceptron_OR(2);
	Perceptron perceptron_XOR(2);

	// Train AND-gate
	printf("Train AND\n");
	perceptron_AND.train(4, training_input, training_output_AND);

	// Train OR-gate
	printf("Train OR\n");
	perceptron_OR.train(4, training_input, training_output_OR);

	// Train XOR-gate
	printf("Train XOR\n");
	perceptron_XOR.train(4, training_input, training_output_XOR);

	// Wait for end
	printf("Enter to exit\n");
	getchar();
}