
class Neurode {
  float[] weights;
  float learnConst = 0.01;
  static final float e = 2.718281828459;
  
  Neurode(int numOfInputs){
    weights = new float[numOfInputs];
    for(int i = 0; i < numOfInputs; i++){
      weights[i] = .5;
    }
  }
  
  float weightedAve(float[] inputs){
    float sum = 0;
    for(int i = 0; i < weights.length; i++)
    {
      sum = sum + (weights[i] * inputs[i]);
    }
    return sum;
  }
  
  float ActivationFunction(float Ave)
  {
    float y = 1 / (1+ pow(e, -1 * Ave));
    return y;
  }
  
  float feedForward(float [] inputs)
  {
    float Ave = weightedAve(inputs);
    return ActivationFunction(Ave);
  }

  void train(float[] inputs, float desired)
  {
    float guess = feedForward(inputs);
    float error = .5 * pow((desired - guess), 2);
    float dMing = desired - guess;
    
    
    for(int i = 0; i < weights.length; i++) {
      weights[i] += learnConst * dMing * guess * (1 - guess) * inputs[i]; 
    }
    
  }
}

class Trainer 
{
  float[] inputs;
  float answer;
    
  Trainer(float x, float y, float a) {
    inputs = new float[3];
    inputs[0] = x;
    inputs[1] = y;
    inputs[2] = 1;
    answer = a;
  }
}


float f(float x)
{
  return 2 * x;
}

Neurode pTron;
Trainer[] training = new Trainer[2000];
int count = 0;

void setup() {
  size(640, 360);
 
  pTron = new Neurode(2);
  
  for (int i = 0; i < training.length; i++) {
    float x = random(-width/2, width/2);
    float y = random(-height/2, height/2);
    
    float desired = 1;
    if(y > f(x))
    {
      desired = 1;
    } else {
      desired = 0;
    }
    
    training[i] = new Trainer(x,y,desired);
  }
}

void draw() {
  background(255);
  translate(width/2, height/2);
  line(-100, f(-100), 100, f(100));
  
  pTron.train(training[count].inputs, training[count].answer);
  count = (count + 1) % training.length;
  
  for ( int i = 0; i < count; i++) {
    stroke(0);
    float guess = pTron.feedForward(training[i].inputs);
    if ( guess > .5) 
    {
      noFill();
    } else {
      fill(0);
    }
    
    ellipse(training[i].inputs[0], training[i].inputs[1], 8, 8);
    
    rect(0, 120, 30, 20);
    textSize(10);
    text("w2 "+pTron.weights[1], 10, 90);
    text("w1 "+pTron.weights[0], 10, 30);
    
  }
  
  
}