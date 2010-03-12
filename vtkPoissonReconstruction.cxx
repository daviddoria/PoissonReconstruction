#include "vtkPoissonReconstruction.h"

#include "vtkObjectFactory.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkInformationVector.h"
#include "vtkInformation.h"
#include "vtkDataObject.h"
#include "vtkSmartPointer.h"
#include "vtkTriangle.h"
#include "vtkCellArray.h"

#include "MultiGridOctest.h"
#include "MultiGridOctreeData.h"
//#include "MemoryUsage.h"

vtkCxxRevisionMacro(vtkPoissonReconstruction, "$Revision: 1.70 $");
vtkStandardNewMacro(vtkPoissonReconstruction);

vtkPoissonReconstruction::vtkPoissonReconstruction()
{
  
  this->Depth = 8;
  this->KernelDepth = 6;
  
  this->SolverDivide = 8;
  this->IsoDivide = 8;
  this->Refine = 3;
  
  this->SamplesPerNode = 1.0;
  this->Scale = 1.25;
  
  this->Verbose = 0;
  this->Confidence = 0;
  
  this->NoResetSamples = 0;
  this->NoClipTree = 0;
  this->Refine = 0;
  
}

int vtkPoissonReconstruction::RequestData(vtkInformation *vtkNotUsed(request),
                                             vtkInformationVector **inputVector,
                                             vtkInformationVector *outputVector)
{
  
  // get the info objects
  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);
  vtkInformation *outInfo = outputVector->GetInformationObject(0);
    
  // get the input and ouptut
  vtkPolyData *input = vtkPolyData::SafeDownCast(
      inInfo->Get(vtkDataObject::DATA_OBJECT()));
  
  vtkPolyData *output = vtkPolyData::SafeDownCast(
      outInfo->Get(vtkDataObject::DATA_OBJECT()));
    
  const int Degree = 2;
  
  double t;

  Point3D<float> center;
  Real scale=1.0;
  Real isoValue=0;
  Octree<Degree> tree;
  PPolynomial<Degree> reconstructionFunction = PPolynomial<Degree>::GaussianApproximation();

  center.coords[0] = 0;
  center.coords[1] = 0;
  center.coords[2] = 0;
  
  TreeOctNode::SetAllocator(MEMORY_ALLOCATOR_BLOCK_SIZE);

  this->KernelDepth = this->Depth - 2;
  
  tree.setFunctionData(reconstructionFunction,this->Depth,0,Real(1.0)/(1<<this->Depth));
  //DumpOutput("Function Data Set In: %lg\n",Time()-t);
  //size_t memoryusage = MemoryInfo::Usage();
  //DumpOutput("Memory Usage: %.3f MB\n",float(memoryusage)/(1<<20));
  if(this->KernelDepth > this->Depth)
    {
    fprintf(stderr,"KernelDepth can't be greater than Depth: %d <= %d\n",this->KernelDepth,this->Depth);
    return EXIT_FAILURE;
    }

  tree.setTree(input,this->Depth,this->KernelDepth,Real(this->SamplesPerNode),this->Scale,center,scale,!this->NoResetSamples,this->Confidence);

  //DumpOutput("Leaves/Nodes: %d/%d\n",tree.tree.leaves(),tree.tree.nodes());
  //DumpOutput("   Tree Size: %.3f MB\n",float(sizeof(TreeOctNode)*tree.tree.nodes())/(1<<20));
  //DumpOutput("Memory Usage: %.3f MB\n",float(MemoryInfo::Usage())/(1<<20));

  if(!NoClipTree)
    {
    tree.ClipTree();
    //DumpOutput("Tree Clipped In: %lg\n",Time()-t);
    //DumpOutput("Leaves/Nodes: %d/%d\n",tree.tree.leaves(),tree.tree.nodes());
    //DumpOutput("   Tree Size: %.3f MB\n",float(sizeof(TreeOctNode)*tree.tree.nodes())/(1<<20));
    }

  tree.finalize1(this->Refine);
  //DumpOutput("Finalized 1 In: %lg\n",Time()-t);
  //DumpOutput("Leaves/Nodes: %d/%d\n",tree.tree.leaves(),tree.tree.nodes());
  //DumpOutput("Memory Usage: %.3f MB\n",float(MemoryInfo::Usage())/(1<<20));

//  tree.maxMemoryUsage=0;
  tree.SetLaplacianWeights();
  //DumpOutput("Memory Usage: %.3f MB\n",float(MemoryInfo::Usage())/(1<<20));

  tree.finalize2(this->Refine);
  //DumpOutput("Finalized 2 In: %lg\n",Time()-t);
  //DumpOutput("Leaves/Nodes: %d/%d\n",tree.tree.leaves(),tree.tree.nodes());
  //DumpOutput("Memory Usage: %.3f MB\n",float(MemoryInfo::Usage())/(1<<20));

  //tree.maxMemoryUsage=0;
  tree.LaplacianMatrixIteration(this->SolverDivide);
  //DumpOutput("Memory Usage: %.3f MB\n",float(MemoryInfo::Usage())/(1<<20));

  CoredVectorMeshData mesh;
  //tree.maxMemoryUsage=0;
  isoValue=tree.GetIsoValue();
  //DumpOutput("Got average in: %f\n",Time()-t);
  //DumpOutput("Iso-Value: %e\n",isoValue);
  //DumpOutput("Memory Usage: %.3f MB\n",float(tree.MemoryUsage()));

  if(this->IsoDivide)
    {
    tree.GetMCIsoTriangles(isoValue,this->IsoDivide,&mesh);
    }
  else
    {
    tree.GetMCIsoTriangles(isoValue,&mesh);
    }
  
  //PlyWriteTriangles(Out.value,&mesh,PLY_BINARY_NATIVE,center,scale,comments,commentNum);

  //create output
  vtkSmartPointer<vtkPoints> points = 
      vtkSmartPointer<vtkPoints>::New();
  Point3D<float> p;
  
  for (unsigned int i = 0; i < static_cast< unsigned int >(mesh.inCorePoints.size()); i++)
    {
    p = mesh.inCorePoints[i];
    points->InsertNextPoint(p.coords[0]*scale + center.coords[0],
                            p.coords[1]*scale + center.coords[1],
                            p.coords[2]*scale + center.coords[2]);
    }
  for(unsigned int i = 0; i < static_cast< unsigned int >( mesh.outOfCorePointCount() ); i++)
    {
    mesh.nextOutOfCorePoint(p);
    points->InsertNextPoint(p.coords[0]*scale + center.coords[0],
                            p.coords[1]*scale + center.coords[1],
                            p.coords[2]*scale + center.coords[2]);
    }
  
  // write faces
    
  vtkSmartPointer<vtkCellArray> triangles = 
    vtkSmartPointer<vtkCellArray>::New();

  TriangleIndex tIndex;
  int inCoreFlag;
  
  unsigned int nr_faces = mesh.triangleCount();
  for(unsigned int i = 0; i < nr_faces; i++)
    {
    vtkSmartPointer<vtkTriangle> triangle = 
      vtkSmartPointer<vtkTriangle>::New();
    
  
    mesh.nextTriangle(tIndex,inCoreFlag);
    
    if(!(inCoreFlag & CoredMeshData::IN_CORE_FLAG[0]))
      {
      tIndex.idx[0]+=int(mesh.inCorePoints.size());
      }
    if(!(inCoreFlag & CoredMeshData::IN_CORE_FLAG[1]))
      {
      tIndex.idx[1]+=int(mesh.inCorePoints.size());
      }
    if(!(inCoreFlag & CoredMeshData::IN_CORE_FLAG[2]))
      {
      tIndex.idx[2]+=int(mesh.inCorePoints.size());
      }
    
    for(unsigned int j = 0; j < 3; j++)
      {
      triangle->GetPointIds()->SetId(j, tIndex.idx[j]);
      }
      
    triangles->InsertNextCell(triangle);
    }
      
  output->SetPoints(points);
  output->SetPolys(triangles);
  return 1;
}


//----------------------------------------------------------------------------
void vtkPoissonReconstruction::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}

