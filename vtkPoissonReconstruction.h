#ifndef __vtkPoissonReconstruction_h
#define __vtkPoissonReconstruction_h

#include "vtkPolyDataAlgorithm.h"

class vtkPoissonReconstruction : public vtkPolyDataAlgorithm 
{
public:
  vtkTypeRevisionMacro(vtkPoissonReconstruction,vtkPolyDataAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);

  static vtkPoissonReconstruction *New();
	  
  vtkSetMacro(Verbose, int);
  
  vtkSetMacro(NoClipTree, int);
  
  vtkSetMacro(Confidence, int);
    
  vtkSetMacro(Depth, int);
  
  vtkSetMacro(NoResetSamples, int);
  
  vtkSetMacro(Refine, int);
  
  vtkSetMacro(KernelDepth, int);
  
  vtkSetMacro(SamplesPerNode, float);
  
  vtkSetMacro(Scale, float);
  
  vtkSetMacro(IsoDivide, int);
  
  vtkSetMacro(SolverDivide, int);
  
protected:
  vtkPoissonReconstruction();
  
  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);

private:
  vtkPoissonReconstruction(const vtkPoissonReconstruction&);  // Not implemented.
  void operator=(const vtkPoissonReconstruction&);  // Not implemented.

  int Verbose;
  int NoResetSamples;
  int NoClipTree;
  int Confidence;
  
  int Depth;
  int SolverDivide;
  int IsoDivide;
  int Refine;
  
  int KernelDepth;
  float SamplesPerNode;
  float Scale;
  
};

#endif
