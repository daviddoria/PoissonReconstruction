#include <vtkSmartPointer.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkXMLPolyDataWriter.h>

#include "vtkPoissonReconstruction.h"

int main(int argc, char *argv[])
{
  if( argc < 4 )
    {
    cout << "PoissonReconstruction takes 3 arguments: " << endl;
    cout << "1-Input file (*.vtp)" << endl;
    cout << "2-Depth" << endl;
    cout << "3-Output file (*.vtp)" << endl;
    return EXIT_FAILURE;
    }

  vtkstd::string inputFileName = argv[1];//"horsePoints.vtp";
  vtkstd::string outputFileName = argv[3];//"horse.vtp";
  int depth = atoi( argv[2] );
  
  vtkSmartPointer<vtkXMLPolyDataReader> reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
  reader->SetFileName(inputFileName.c_str());
  reader->Update();
  
  vtkSmartPointer<vtkPoissonReconstruction> poissonFilter = 
      vtkSmartPointer<vtkPoissonReconstruction>::New();
  poissonFilter->SetDepth( depth );
  poissonFilter->SetInputConnection(reader->GetOutputPort());
  poissonFilter->Update();
  
  vtkSmartPointer<vtkXMLPolyDataWriter> writer =
    vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetInputConnection(poissonFilter->GetOutputPort());
  writer->SetFileName(outputFileName.c_str());
  writer->Update();
  
  return EXIT_SUCCESS;
}

