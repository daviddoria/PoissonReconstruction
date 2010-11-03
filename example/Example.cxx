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
#include <vtkSmartPointer.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkXMLPolyDataWriter.h>

#include "vtkPoissonReconstruction.h"

int main(int argc, char *argv[])
{
  if ( argc < 4 )
    {
    cout << "PoissonReconstruction takes 3 arguments: " << endl;
    cout << "1-Input file (*.vtp)" << endl;
    cout << "2-Depth" << endl;
    cout << "3-Output file (*.vtp)" << endl;
    return EXIT_FAILURE;
    }

  vtkstd::string inputFileName = argv[1];  //"horsePoints.vtp";
  vtkstd::string outputFileName = argv[3]; //"horse.vtp";
  int            depth = atoi(argv[2]);

  vtkSmartPointer< vtkXMLPolyDataReader > reader =
    vtkSmartPointer< vtkXMLPolyDataReader >::New();
  reader->SetFileName( inputFileName.c_str() );
  reader->Update();

  vtkSmartPointer< vtkPoissonReconstruction > poissonFilter =
    vtkSmartPointer< vtkPoissonReconstruction >::New();
  poissonFilter->SetDepth(depth);
  poissonFilter->SetInputConnection( reader->GetOutputPort() );
  poissonFilter->Update();

  vtkSmartPointer< vtkXMLPolyDataWriter > writer =
    vtkSmartPointer< vtkXMLPolyDataWriter >::New();
  writer->SetInputConnection( poissonFilter->GetOutputPort() );
  writer->SetFileName( outputFileName.c_str() );
  writer->Update();

  return EXIT_SUCCESS;
}
