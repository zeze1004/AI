
// 퍼셉트론을 정의한다
class Perceptron { 
    public:
    
    // 4개의 속성(또는 멤버데이터라 배운 그것)이 있다.
    int n;  //차원의 수
    float *w, *before_w, th;   // 가중치, 학습 전 가중치, 임계점
    
    // 7개의 함수가 정의되어 있다.
    void registerWeight();
    int trainingDateset(int length, int **inputs, int *outputs, bool feedback);
    void Feedback(int *input, int output, int expect);

    // 그 중, 리턴값이 적혀있지 않은 이 Perceptron 이란 함수는 바로.. 생성자이다.
    Perceptron(int n);
    // 즉, 나중에 FirstHomeWork.cpp에서 new Perceptron(3) 이런식으로 쓸거다.
    // 메인에 그것? 123 ~ 125줄 new로 안 했지만 암튼 그것이다

    // 마치 int a = 1; 또는 int a = new int(1); 처럼
    // Perceptron a; 또는 new Perceptron() ㅜ머 이런거기 하다 암튼


    int calculate(int *input);
    // 퍼셉트론의 가장 핵심 함수, 주어진 인풋에 대해 아웃풋을 리턴하는 바로 그 함수이다.
    // 이것부터 먼저 살펴보자. (88줄)

    int train(int length, int **input, int *output);
    void printWeight();
};

// 현재 가중치 값을 학습 전에 저장한다
// registerWeight 함수는 현재 weight값을 저장한다. 즉, 복사본을 만든다.
// before_w에 현재 w를 그대로 복사하는 것이다. 
void Perceptron::registerWeight() {
    for (int i = 0; i < n; i++) {
        before_w[i] = w[i];
    }
}

// error 갯수 출력 
// trainingDateset 함수는 일단 이름이 마음에 안 든다.
// 이름만 보고 뭘 하는 함수인지 알 수가 없다.
// 이름을 잘못 지었다.
// 이 함수는, 주어진 input, output을 가지고 학습을 하거나, 오류를 계산한다.
// 두 역할이 한 함수에 있다니, 애초에 글러먹은 설계다.
// 4번째 매개변수 feedback이 이 두 역할을 구분한다.
// feedback이 true이면, 오류 계산만 한다. weight를 변경하지는 않는다.
// feedback이 false이면, 오류는 몰겠고 그냥 학습한다. 즉, weight를 {오류가 0이 되는 방향으로} {적절히} 변경한다.
// 첫 번째 매개변수 length는 그냥 input과 output의 개수다. train 함수와 같다. ?ㅅ? 그럼 train 함수 써두 대?
// train은 그저, 학습이 잘 완료될 때까지 trainingDateset을 반복해서 부르는 것이다. 그래서 출첵은 안하시는거징? 안대 확인하고와 ㅠㅠ 오늘 출첵 앱은 다 휴강이라고 뜨긴한다 
// 그러다가 더이상 학습을 할 필요가 없거나, 가망이 없으면 그만둔다.
// trainingDateset 함수는 그저, 단 한 번 그것(학습 또는 오류계산)을 실제로 수행한다.
int Perceptron::CalculateTrainingDataset(int length, int **inputs, int *outputs, bool feedback)
{
	int i, error;
	int *input;
	int output;
	int expect;

    // GitHub에서 가져왓다. 혹시 이전의 함수들도 잘못 되어이"ㅆ나? 내가 한땀한땀 써서 잘 못 되었을 확률이 매우 높다 ...ㅠ 모가 틀린고지?ㅅ? 아닝 너거보고했오
	// 그렇군,, 잘못된 것이 있다.
    // 꽤 많다.
    // 대체 왜지? 다른 것을 보고 했나?
    // https://github.com/gunhoflash/Project_AI/blob/master/homework2/Perceptron.h 이거 보고 한거 맞아? 웅 이름도 같자나 아 그 define C 그건 안했어 뭔 말인지 모르니껜 ㅎ
    // 너무 다른데... 암튼 
    // 음... 상당히 다르군..... 
    // 일단 계속하겠다 이 코드를 기준으로 ㅖ속하겠다
    // 적어도 지금 이 함수의 내용은, 기존의 것은 잘못 작성되어 있어 버그가 있기 때문에 내 GitHub코드르 가져왔다.
    // for each training data,
	for (i = error = 0; i < length; i++)
	{
		// calculate
		input  = inputs[i]; // i번째 인풋으로
		output = Calculate(input); // output을 계산한다.
		expect = outputs[i]; // 그런 다음, 예상했던 값과 
        // expect가 { 0, 1, 1, 1 } 이런 정답?이얌? ㅇㅇ 요걸 어케 넣은거지 신기하ㅇ
 
		// if wrong,
		if (output != expect) // 서로 비교한다.
		{
            // 예상했던 값이 아니면 (즉, 틀렸으면, 즉, 학습이 필요하면, 즉, 에러가 있으면)
			// count error up
			error++; // 에러 개수를 1 늘린다.
			// and readjust the weight values
			if (feedback) // 만약 이 함수를 부를 때 feedback을 true라고 했었다면, feedback 한다.
            // 즉, 경사하강법 뭐시기 그걸 한다.
				Feedback(input, output, expect);
                // 그럼 아마 weight가 변경되었을 것이다.
		}
	}

    // 암튼 length개의 input에 대한 output과의 비교가 모두 종료되면 error를 리턴한다.
    // feedback을 true로 했었다면, 이 error값은 의미가 없다. 왜일까? <- 시간 남으면 하는 과제 ?ㅅ?
	// return the number of errors
	return error;
}

// 학습 결과에 따라 가중치를 재조정 함
// 학습 후, input과 그에 대한 계산 결과(output), 예상했던 값(expect)을 바탕으로
// weight를 조정한다.
void Perceptron::Feedback(int *input, int output, int expect) {
    // 각 입력값에 대해, weight를 수정한다. 왜...?
    // 얼마나? (예상값 - 실제값) * 인풋 만큼큼ㅇㅋ
    // 아 더 쉬운 이해를 위해
    // 만약 활성화 함수가 지금처럼 [net이 "1" 초과면 1, 아니면 0] 인거라 치자
    // 두 인풋이 있다고 가정하고 각각 0.2 0.8 이라 치자
    // 각 가중치는 1.1, 1.5 라고 치자. 웅웅
    // 그럼 net 값은 0.2*1.1 + 0.8*1.5 = 1.44
    // 활성화 함수를 거친 후는 1 (왜냐하면 net이 1보다 크면 1이라고 했으니까)
    // 근데 만약 원했던 답이 0이었다면, 우리는 net을 더 줄여야겠지?
    // 그럼 두 weight를 줄여야 할거야 ㅇㅋ?
    // 근데 똑같이 줄이면 사실 weight를 여러 개 둔 의미가 없지
    // 더 net을 많이 증가시키는데 기여한 weight를 더 많이 줄여야 할거야
    // 그건 딱 이 인풋에 대해서는 괜찮지만, 다른 인풋에 대ㅐ서는 올바르지 않은 방법이야
    // 당장 AND게이트만 해도 인풋이 4종류 인걸 00입력을 위해 두 가중치를 0으로 하면 01 10 11은 오또케..
    // 그저 현재의 예시에 대해서는 net이 1.44에서 1미만으로만 줄어들면 되는거야
    // 1.44라는 값을 만들때 가장 큰 공헌을 한 weight는 바로 0.8이라는 weight야
    // 왜냐하면, 0.2라는 weight는 1.1과 곱해져서 0.22가 되었고
    //           0.8라는 weight는 1.5과 곱해져서 1.2가 되었기 때무에 
    // 1.44를 만든 주요 원인은 0.8 <-- 이 놈이라고 할 수 이찌
    // 근데 다시 생각해보면, 이게 다 가중치 0.8에 대한 입력이 무려 1.5가 들어와서 그렇거든
    // 만약 0.8가중치한테 입력값이 0.01이 들어왔으면, 그걸로는 net한테 겨우 0.008바껭 안 줘쓸거야
    // 그러니까 가중치에 대한 입력값이 중요해
    // 입력이 컸다면, net에 많은 공헌을 했으니까, 그만큼 weight를 줄여서 공헌을 조금만 하게 하는거지
    // 즉, 0.2는 그대로 두고, 0.8만 0.5로 낮추면
    // 0.2*1.1 + 0.5*1.5 = 0.22+0.75=0.97 < 1 우왕똑똑해
    // 되는거야
    // 즉 weight을 얼마나 조정할 거신가? 는, 그weight에 얼마나 큰 입력이 곱해져서 얼마나 크게 net에 기여했는가?
    // 에 따라 결정되는거야 웅웅
    그래서 아ㅐ 코드를 보면, weight를 조정할 때 input을 곱하고 있어
    input이 컸으면 weight가 만ㅇ히 바뀌겠지!
    // 물론 그렇다고 해서 0.2 가중치한테 책임이 아예 없는건 아니니까 0.2  가중치도 조금 변경은 될거야
    하지만 그 정도가 0.8가중치에 비해서는 작겠지

    더 나아가서, 만약 0.8가중치에 대한입력이 0이었으면, 이 가중치는 변경되지 않고 그대로 0.8로 남아있을거야
    왜냐하면, 어차피 0.8에 대한 입력이 0이라서 곱하면 0이니까 net에 0만큼 기여를 한 셈이고
    0.8을 어떻게 바꾸든 입력이 0이면 결국 0이니까 소용없는거지
    
    만약, 0.8에 대한 입력이 -1이었다면 (오히려 음수였다면) net을 줄이는데 큰 기여를 했으니까
    더 줄일 수 있게 0.8을 더 큰 값으로 바꿔야 했을거야 (예를 들면 0.9나 1.1, 1.5 처럼)
    그것도 생각해보면 input이 음수였기 때문에 그렇지
    
    즉, weight를 변경할 때는 그 가중치에 곱해진 입력이 뭐였냐에 따라 달라져 웅웅 기억할겝!
    
    나머지는 차차 배워가도록 하고, 일단 그래서 이 함수느, weight를 조절하는 함수야! 웅!
    끗 이제 FirstHomeWork로 가보자
    for (int i = 0; i < n; i++) {
        w[i] += (expect - output) * input[i];
    }
}


Perceptron::Perceptron(int n) {
    for (int i = 0; i < n; i++) {
        w[i] = (rand()%1001) / (float)500 - 1;    
    }
    th = (rand()%1001) / (float)1000;
}

// 퍼셉트론을 이용한 연산
int Perceptron::calculate(int *input) { // 인풋을 매개변수로 받는다. 이때,
// 인풋의 개수는 한 개가 아니기 때문에, 배열로 받아야 하며,
// 따라서 int * 타입으로 매개변수를 받는다. 
// 입력의 개수 ㅇ
// 예를 들어 3개의 입력을 받는 퍼셉트론이면
// int input[3] = { 1, 0, 1 }; 
// calculate(input);
// 요렇게 썼을 것
// 암튼

    float net = -th;
    // w0 x0 개념을 잘 모르고 짠 코드라서 threshold가 따로 있다.
    
    // n개의 입력 각각에 대해, 가중치를 곱하고, 그 결과를 net에 더한다.
    for (int i = 0; i < n; i++) {
        net += input[i] * w[i];

    // net 값이 0보다 크면 1을 리턴하고, 그렇지 않으면 0을 리턴한다.
    // 내가 과제를 할 당시에는, 퍼셉트론의 activation function (활성화 함수)을 무조건
    // binary step으로만 설정하라고 하였기에
    // 이 코드는 이대로 두었다.
    // 만약 활성화함수를 자유롭게 설정할 수 있었다면
    // 적어도 sigmoid는 쓰지 않았을까 싶다.
    }
    // 시그모이드 식은 절대 이렇지 않다.

    // 여기 미리 시그모이드의 식을 써보자
    // net이 주어질 때, sigmoid(net) = ?
    // 아마 시그모이드 식이 내 기억 상으로는
    // 1 / (1 + e^(-x)) 이다. 어렵따
    // 따라서, 이 코드를 sigmoid를 사용하는 퍼셉트론으로 변경하려면
    // 아래의 return 문은
    /* 잠시만 확실히 보고 오게따 맞네 훔 전화를 사용할 수 업는 상황인가 
        
        return 1 / (1 + Math.exp(-net));

    */
    // 이렇게 작성했을 것이다.
     
    // 이것은 단지 binary step일 뿐이다.
    // binary step이 무엇인지 잘 기억나지 않는다면 강의나 위키피디아 activation function 을 찾아보면 바로 알 수 있다.
    return (net > 0) ? 1 : 0; // 아 마따 어려운거 수식 앙대 
}

// 그 다음으로 중요한 함수인 train을 살펴보겠다. 
int Perceptron::train(int length, int **inputs, int *outputs) {
    // 이 함수는, 주어진 퍼셉트론을 훈련(학습)시켜 제 역할을 해내도록 만든다.
    // 예를 들어 FirstHomework에서 알 수 있듯이
    // 
    /*
    inputs를 
    {
		{ 0, 0 },
		{ 0, 1 },
		{ 1, 0 },
		{ 1, 1 }
	};
    로 하고, outputs를 { 0, 1, 1, 1 }; 로 하면
    */
        
    // 입력이 00 01 10 11 이라는 뜻이고, 각 입력에 대해 0 1 1 1의 결과가 나와야 정답이라는 소리다.

    // 이렇게 정답이 나오지 않으면, weight값을 조정(이것이 학습)하고 다시 테스트해본다.
    // 즉, 우리는 퍼셉트론을 만든 다음에 이 train 함수를 실행하면
    // 주어진 퍼셉트론이 inputs에 대해 outputs를 내도록 학습된다고 믿을 수 있다.

    // 오키 그렇다면 아래 코드를 보겠다
    bool trainable;
    int error, round;
    
    // 매개변수 length는, 학습할 데이터의 개수다.
    // 함수 정의를 보고 오자 (133줄) 오홍 꿀팁이다 하지만 난 못해...ㅠ 후움 오킹 어차피 벡터를 써도 length는 무족권 4 아냥?
    // 나중에 입력이 3, 4, 5, 6, 7, 8, ...개인 것도 있을 수 있기 때문에, 확장성을 고려하여 이렇게 작성했다. 글쿤,,,대단햇

    // 나는 이 당시 cpp은 몰랐고 c만 알았기 때문에, length를 넘겨주어야 inputs와 outputs의 개수를
    // 알 수 있었다. 만약 내가 c++로 짰고 int * 대신 vector를 받았다면
    // length는 vector의 size 함수를 이용하여 바로 구했을 것이다.
    // 암튼 이 코드는, 내가 vector나 iostream은 커녕, c++을 아예 모르고 짠 것이다.

    // 위의 예시에서는 length가 4에 속한다. 오키?

    // if 학습할 데이터가 1개도 없다면, 아무것도 안 해도 된다. 아마 오류일 것이다.
    if (length < 1) {
        cout << "data가 입력되지 않았습니다." << endl;
        exit(-1);
    }
    
    // 학습할 데이터가 있다면

    // 먼저 threshold를 출력한다. 테스트와 디버깅을 위해
    cout << "th: " << th << endl;

    // 현재의 각 weight 도 출력한다. 테스트와 디버깅을 위해
    printWeight();

    // 주어진 input과 output을 그대로 계산에 넣어보고, 오차가 얼마나 발생하는지 받아온다.
    error = trainingDateset(length, inputs, outputs, false); // trainingDateset 함수에 대한 설명은 나중에 
    // 일단은 계산만 하고 오차만 따져본다고 이해하고 진행하면 된다. 예를 들어 저번 과제에서 틀린갯수 1개 2개 3개 4개 그런 개념
    

    // 오차를 출력한다. 오차가 0이면 학습이 완벽히 적용된 것이다. 이것이 우리의 목표다.
    cout << "error: " << error << endl;
    // ...? 아하 이거 막강에 나오는거구나 막강은 안들어따!..? 모..?ㄴ
    // round 라는 변수는 수업에서 epoch라고 배운 그것이다. 학습 횟수를 나타낸다.
    // '몇 번' 학습 되었는가 에서 '몇 번'을 나타낸다. 시작은 1
    // 나는 강의에서 epoch라는 말을 분명 들어따...
    // 나는 너가 듣느 강의를 엳듣고 epoch를 들어따.....

    // 암튼, 이제 training 을 시작한다.
    round = 1;
    trainable = true;
    while (trainable) {

        // 먼저 현재 학습 단계 (epoch라고 배운 그것)를 출력하고 1 올린다.
        cout << "[round " << round++ << "]" << endl;

        // 현재 weight 값을 다른 곳에 복사해둔다 (필요가 있기 때문..)
        registerWeight();

        // 주어진 input에 대한 결과를 계산하고 output과 비교하며 weight를 수정한다.
        // 즉, 이 함수가 진짜 '학습'이다.
        trainingDateset(length, inputs, outputs, true);

        // 학습 후 변경된 상태의 weight를 출력한다.
        printWeight();

        // 학습 후 변경된 weight를 가지고 error만 확인해본다. weight를 수정하진느 않는다.
        error = trainingDateset(length, inputs, outputs, false);

        // 얼마나 틀렸나 출력해본다.
        cout << "error 갯수: " << error << endl;

        // 학습 성공시, 즉 오류가 0이면 끝낸다. 학습완료. 
        if (error == 0) {
            cout << "학습 성공" << endl;
            return 0;
        } 
        else {
            // 오류가 0이 아니면, 0이 될 때까지 학습을 반복해야 할 것이다.
            // 하지만, 특정한 몇 가지 이유로 인해 더이상 학습을 못할 때가 있다.
            // 그러므로, 더 학습을 할 수 있었는지, 즉, weight가 유의미하게 변했는지 확인해본다.
            // 쉽게 말하자면, 오류가 있음에도 불구하고 더이상 weight를 변경할 수 없는 상태인지 확인해본다.
            // 만약 weight를 변경하고 있었다면, 계속 학습하지만, weight가 변하지 못했다면
            // 이 정도 오류가 최선이라 가정하고 끝낸다.
            // 즉 오류가 항상 0이 되지 않을 수도 있다는 뜻이다.
            // 우리는 오류를 최소화해야 하지만, 특정 조건에서 오류를 0으로 만들 수 없게 되는데
            // 이때 weight는 더이상 변하지 않는다.
            // 따라서 weight가 학습 전/후에 변화했는지 확인해보고
            // 변한게 아무것도 없다면, 학습을 그냥 끝낸다.
            // 오류를 완벽이 0으로 내리지 못하고 weight가 변하지 못하는 이유는 보고서에 기술되어 있다. 봐도 모른다!
            // GitHub에 있당
            // 암튼
            // 그래서 학습 전의 weight와 학습 후의 weight를 비교해야 한다.
            // 그래서 아까 205줄에서 미리 weight를 저장했던 것이다. 오홍 before_w의 이유 헤헤 문자 설명 좋네여 
            // 그런 다음 209줄을 통해 weight가 변경된 것이다.
            // 그렇다 before_w는 학습 전registerWeight 함수를 통해 저장된 weight값들이다.
            // before_w와 현재의 weight (w)를 확인해본다.
            trainable = false;  // 여기서 무조건 탈주자나 for문은 못돌리는거야냥? 굴쿤!
            // while과 for에 대한 이해가 부족하다 ㅠ^ㅠ
            일단
            /*
                while (조건) {
                    내용
                }
                은, 이렇게 정의된다.
                "조건이 맞는가? 그렇다면 내용을 수행한다."
                "조건이 맞는가? 그렇다면 내용을 수행한다."
                "조건이 맞는가? 그렇다면 내용을 수행한다."
                "조건이 맞는가? 그렇다면 내용을 수행한다."
                "조건이 맞는가? 그렇다면 내용을 수행한다."
                "조건이 맞는가? 그렇다면 내용을 수행한다."
                "조건이 맞는가? 틀렸다면 끝낸다."
                즉, (내용) 중간에서 (조건)이 false가 되는 것은 중요하지 않다.
                (내용)을 수행한 '후', 다시 (조건)을 검사할 때가 중요하다.
                즉, 중간에 trainable이 false가 되는것은 while의 동작에 영향이 없고, 일단
                모든 (내용) 코드를 다 실행 한 후 다음 반복을 시작하기 직전에 trainable의 값이 중요한 것이다. for문에서 바뀌지 않았다면 여전히 false여서 탈주하겠꾼 학습이 끝나두 탈주징?
                
                그렇다면 while을 더이상 수행하지 않고 끝나는 것이다. 그렇다. [여기로] 코드가 실행되는 것이다. 
                앗학습이이항끝나면 221줄에서 걸려졌을 것이다. break도 아닌 return이다. 아 그렇구낭 웅웅 대단해 거노
                즉 train 함수가 바로 종료(terminate)한다.
                암튼, train 함수의 작동을 요약하자면
                
                다음을 반복한다:
                    1. 일단 weight 복사본 만든다.
                    2. 주어진 input과 output으로 학습 한 번 한다. (이 과정에서 weight가 변경될 수 있음)
                    3. 오류를 확인한다.
                    4. 오류가 0이면 바로 끝. 목표 달성
                    5. 오류가 0이 아니면, 1.에서 저장했던 weight랑 현재의 weight를 비교한다.
                    6. 아무것도 안 변했나? 그럼 더이상 변할리가 없다. 이게 최선이다. 끝
                    7. 1.부터 다시 반복한다.

                이다. 

            */
            for (int i = 0; i < n; i++) {
                if(w[i] != before_w[i]) {
                    // 다른가? 그렇다면 무엇인가 변했다는 뜻이니까, trainable을 true로 한다. trainable은 학습 중이라는 뜻이얌? 무슨 변수인지 몰게써 앗항
                    trainable = true;
                }
            }
            // 이 for문을 통해서, 단 하나의 weight라도 학습과정에서 변경되었다면, trainable이 true가 된다.
            // 그렇다. trainable은 학습중인가? 학습이 가능한가? 학습되었는가? 할만한가? 정도의 뜻이다.
            // true이면 계속 학습을 진행하고, false이면 232(또는 227줄 암튼 그정도에서 했던 얘기)줄쯤에 적어놓은 그 이유가 발생한 것이다. 즉 오류가 0이 아님에도
            // weight가 더이상 변하지 못했다는 상태다.
            // 그래서 주석을 적고 있는 이 while문의 조건이 'trainable이 참일 때'이다. 오홍 우잉 false가 되면 조건물 탈주야?
            // 199줄에서 while (trainable) { 이라는 부분이 있는데, 여기서 trainable이 false라면 while (false) 인 셈이므로
            // 반복코드를 더이상 실행하지 않고 [여기로] 간다.
        }
    }

    // [여기로]
    cout << "학습 실패" << endl;
    return 1;
}

// train과 calculate를 제외한 나머지 함수들은 핵심은 아니다.
// 이 printWeight 함수는 현재 weight를 출력한다. (디버깅이나 테스트를 위해) 
void Perceptron::printWeight() {
    for (int i = 0; i < n; i++) {
        cout << "가중치: " << w[i] << endl;
    }
}


