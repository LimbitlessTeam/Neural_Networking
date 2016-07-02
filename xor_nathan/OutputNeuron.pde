

public class OutputNeuron extends Neuron {
  float deltaOutput;

  public float getDeltaOutput()
  {
    return deltaOutput;
  }

  public void setDeltaOutput(float newDeltaOutput)
  {
    deltaOutput = newDeltaOutput;
  }

  public OutputNeuron() {
    super();
  }
}