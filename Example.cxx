#include <vtkSmartPointer.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkXMLPolyDataWriter.h>

#include "vtkPoissonReconstruction.h"

int main(int argc, char *argv[])
{
  //vtkstd::string inputFileName = argv[1];
  vtkstd::string inputFileName = "horsePoints.vtp";
  vtkstd::string outputFileName = "horse.vtp";
  
  vtkSmartPointer<vtkXMLPolyDataReader> reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
  reader->SetFileName(inputFileName.c_str());
  reader->Update();
  
  vtkSmartPointer<vtkPoissonReconstruction> poissonFilter = 
      vtkSmartPointer<vtkPoissonReconstruction>::New();
  poissonFilter->SetDepth(10);
  poissonFilter->SetInputConnection(reader->GetOutputPort());
  poissonFilter->Update();
  
  vtkSmartPointer<vtkXMLPolyDataWriter> writer =
    vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetInputConnection(poissonFilter->GetOutputPort());
  writer->SetFileName(outputFileName.c_str());
  writer->Update();
  
  return EXIT_SUCCESS;
}
