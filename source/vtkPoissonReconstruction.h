/*=========================================================================
 Authors: David Doria at Rensselaer Polytechnic Institute and
   Arnaud Gelas at Harvard Medical School

 Copyright (c) 2010, David Doria at Rensselaer Polytechnic Institute and
   Arnaud Gelas at Harvard Medical School,
   All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

 Redistributions of source code must retain the above copyright notice,
 this list of conditions and the following disclaimer.
 Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
 Neither the name of the Rensselaer Polytechnic Institute and of Harvard
 Medical School nor the names of its contributors may be used to endorse
 or promote products derived from this software without specific prior
 written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
 OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
=========================================================================*/

#ifndef __vtkPoissonReconstruction_h
#define __vtkPoissonReconstruction_h

#include "vtkPoissonReconstructionConfigure.h"
#include "vtkPolyDataAlgorithm.h"
/**
 * \class vtkPoissonReconstruction
 * \brief vtk Wrapping of the Poisson Reconstruction method.
 * see http://www.midasjournal.org/browse/publication/718 for reference.
 * */
class vtkPoissonReconstruction_EXPORT vtkPoissonReconstruction:public vtkPolyDataAlgorithm
{
public:
  vtkTypeRevisionMacro(vtkPoissonReconstruction, vtkPolyDataAlgorithm);
  void PrintSelf(ostream & os, vtkIndent indent);

  static vtkPoissonReconstruction * New();

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
  vtkPoissonReconstruction(const vtkPoissonReconstruction &); // Not
                                                              // implemented.
  void operator=(const vtkPoissonReconstruction &);           // Not
                                                              // implemented.

  int Verbose;
  int NoResetSamples;
  int NoClipTree;
  int Confidence;

  int Depth;
  int SolverDivide;
  int IsoDivide;
  int Refine;

  int   KernelDepth;
  float SamplesPerNode;
  float Scale;
};

#endif
