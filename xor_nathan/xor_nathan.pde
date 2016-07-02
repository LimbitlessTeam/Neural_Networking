
// The Nature of Code
// Daniel Shiffman
// http://natureofcode.com

// XOR Multi-Layered Neural Network Example
// Neural network code is all in the "code" folder


ArrayList inputs;  // List of training input values
Network nn;        // Neural Network Object
int count;         // Total training interations
//Landscape land;    // Solution space
float theta = 0.0; // Angle of rotation
PFont f;           // Font


void setup() {
  frameRate(60);
  size(900, 700);
  println("stuff");

  // Create a landscape object
  println("why");


//  land = new Landscape(20, 300, 300);


  f = createFont("Courier", 12, true);

  nn = new Network(10,10,4);

  // Create a list of 4 training inputs
  inputs = new ArrayList();
  float[] input = new float[2];
  input[0] = 1; 
  input[1] = 0;  
  inputs.add((float []) input.clone());
  input[0] = 0; 
  input[1] = 1;  
  inputs.add((float []) input.clone());
  input[0] = 1; 
  input[1] = 1;  
  inputs.add((float []) input.clone());
  input[0] = 0; 
  input[1] = 0;  
  inputs.add((float []) input.clone());
}

void draw() {

  int trainingIterationsPerFrame = 5;

  for (int i = 0; i < trainingIterationsPerFrame; i++) {
    // Pick a random training input
    int pick = int(random(inputs.size()));
    // Grab that input
    float[] inp = (float[]) inputs.get(pick); 
    // Compute XOR
    float[] known = {1};
    if ((inp[0] == 1.0 && inp[1] == 1.0) || (inp[0] == 0 && inp[1] == 0)) 
    {
      known[0] = 0;
    }
    // Train that sucker!
    float[] result = nn.train(inp, known);
    count++;
  }

  background(175);
 /* // Ok, visualize the solution space
  background(175);
  pushMatrix();
  translate(width/5, height/5+20, -160);
  rotateX(PI/3);
  rotateZ(theta);

  // Put a little BOX on screen
  pushMatrix();
  stroke(50);
  noFill();
  translate(-10, -10, 0);
  box(280);
*/
/*  // Draw the landscape
  popMatrix();
  land.calculate(nn);
  land.render(); 
  theta += 0.0025;
  popMatrix();
*/
  // Display overal neural net stats
//  networkStatus();
  
  
    //nathan edits
  ellipseMode(CENTER);
 // rectMode(CENTER);
  fill(0,0,0);
  //nodes
  
  

  for(int i=0;i<nn.input.length-1;i++){
      for(int j=0;j<nn.hidden.length-1;j++){
          for(int k=0;k<nn.output.length;k++){
         //input node positions based on array length   
         float inputX=1*width/4;
         float inputY=i*(height/nn.input.length)+(height/nn.input.length);
         float inputNode = 100/log(nn.input.length);
         //hidden node positions based on array length(length-1?)
         float hiddenX=2*width/4;
         float hiddenY=j*(height/nn.hidden.length)+(height/nn.hidden.length);
         float hiddenNode = 100/log(nn.hidden.length);
         //output node positions based on array length 
         float outputX=3*width/4;
         float outputY=k*(height/nn.output.length)+(height/nn.output.length)/2;
         float outputNode = 100/log(nn.output.length);
         println("THE OUTPUT NODE SIZE IS:");
         println(100/log(nn.output.length));
     //need quick check bc if a node list == 1 then log(1)=0 and size of that node will be 0, reset to some medium size   
        if(inputNode==100/log(1)){
        inputNode=100;
        }
        if(hiddenNode==100/log(1)){
        hiddenNode=100;
        }
        if(outputNode==100/log(1)){
        outputNode=100;
        }        

        
   fill(177,0,240);
   strokeWeight(1.5);
   stroke(0);
   
   
  //create line from input to hidden nodes
  line(inputX,inputY,hiddenX,hiddenY);
  //create line from hidden to output nodes
  line(hiddenX,hiddenY,outputX,outputY);

  //draw input nodes       
  ellipse(inputX,inputY,inputNode,inputNode);
  //draw hidden nodes
  ellipse(hiddenX,hiddenY,hiddenNode,hiddenNode);
  //draw ouput nodes
  ellipse(outputX,outputY,outputNode,outputNode);
  //create line thickness


  
  
  
    }//
  }//
}//end of triple for loop

//end of draw
}

void networkStatus() {
  float mse = 0.0;

  textFont(f);
  fill(0);
  text("Your friendly neighborhood neural network solving XOR.", 10, 20);
  text("Total iterations: " + count, 10, 40);

  for (int i = 0; i < inputs.size(); i++) {
    float[] inp = (float[]) inputs.get(i); 
    float known = 1;
    if ((inp[0] == 1.0 && inp[1] == 1.0) || (inp[0] == 0 && inp[1] == 0)) known = 0;
    float[] result = nn.feedForward(inp);
    //System.out.println("For: " + inp[0] + " " + inp[1] + ":  " + result);
    mse += (result[0] - known)*(result[0] - known);
  }

  float rmse = sqrt(mse/4.0);
  text("Root mean squared error: " + nf(rmse, 1, 5), 10, 60);
}
