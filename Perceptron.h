class Perceptron {
    public:
    
    int n;  //차원의 수
    float *w, *before_w, th;   // 가중치, 학습 전 가중치, 임계점
    
    void registerWeight();
    int trainingDateset(int length, int **inputs, int *outputs, bool feedback);
    void Feedback(int *input, int output, int expect);

    Perceptron(int n);
    int calculate(int *input);
    int train(int length, int **input, int *output);
    void printWeight();
};

// 현재 가중치 값을 학습 전에 저장한다
void Perceptron::registerWeight() {
    for (int i = 0; i < n; i++) {
        before_w[i] = w[i];
    }
}

// error 갯수 출력
int Perceptron::trainingDateset(int length, int **inputs, int *outputs, bool feedback) {
    int error;
    int *input;
    int output;
    int expect;

    // 각각의 트레이닝 데이터
    for (error = 0; error < length; error++) {
        // 계산
        input = inputs[error];
        output = calculate(input);
        expect = outputs[error];

        // 기댓값이랑 결과가 다를 시 가중치 재조정
        if (output != expect) {
            error++;
            if(feedback) {
                Feedback(input,output,expect);
            }
        }
    }
    return error;
}

// 학습 결과에 따라 가중치를 재조정 함
int Perceptron::Feedback(int *input, int output, int expect) {
    for (int i = 0; i < n; i++) {
        w[i] += (expect - output) * input[i];
    }
}


Perceptron::Perceptron(int n) {
    for (int i = 0; i < n; i++) {
        w[i] = (rand()%1001) / 500f - 1;    
    }
    th = (rand()%1001) / 1000f;
}

// 퍼셉트론을 이용한 연산
int Perceptron::calculate(int *input) {
    float net = -th;
    for (int i = 0; i < n; i++) {
        net += input[i] * w[i];
    return (net > 0) ? 1 : 0;
    }
}

int Perceptron::train(int length, int **inputs, int *outputs) {
    bool trainable;
    int error, round;

    if (length < 1) {
        cout << "data가 입력되지 않았습니다." << endl;
        exit();
    }
    cout << "th: " << th << endl;
    printWeight();
    error = trainingDateset(length, inputs, outputs, false);
    cout << "error: " << error << endl;

    round = 1;
    trainable = true;
    while (trainable) {
        cout << "[round " << round++ << "]" << endl;
        registerWeight();
        trainingDateset(length, inputs, outputs, true);
        printWeight();
        error = trainingDateset(length, inputs, outputs, false);
        cout << "error 갯수: " << error << endl;

        // 학습 성공시
        if (error == 0) {
            cout << "학습 성공" << endl;
            return 0;
        } 
        else {
            trainable = false;
            for (int i = 0; i < n; i++) {
                if(w[i] != before_w[i]) {
                    trainable = true;
                }
            }
        }
    }
    cout << "학습 실패" << endl;
    return 1;
}

void Perceptron::printWeight() {
    for (int i = 0; i < n; i++) {
        cout << "가중치: " << w[i] << endl;
    }
}


