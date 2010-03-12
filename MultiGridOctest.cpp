/*
Copyright (c) 2006, Michael Kazhdan and Matthew Bolitho
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list of
conditions and the following disclaimer. Redistributions in binary form must reproduce
the above copyright notice, this list of conditions and the following disclaimer
in the documentation and/or other materials provided with the distribution. 

Neither the name of the Johns Hopkins University nor the names of its contributors
may be used to endorse or promote products derived from this software without specific
prior written permission. 

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO THE IMPLIED WARRANTIES 
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
TO, PROCUREMENT OF SUBSTITUTE  GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
DAMAGE.
*/

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <float.h>
#include "MarchingCubes.h"
#include "Octree.h"
#include "SparseMatrix.h"
#include "FunctionData.h"
#include "MultiGridOctest.h"
#include "MultiGridOctreeData.h"

#define SCALE 1.25

#include <stdarg.h>

char* outputFile=NULL;
int echoStdout=0;

void DumpOutput(const char* format,...)
{
  if(outputFile)
    {
      FILE* fp=fopen(outputFile,"a");
      va_list args;
      va_start(args,format);
      vfprintf(fp,format,args);
      fclose(fp);
      va_end(args);
    }
	if(echoStdout)
    {
    va_list args;
    va_start(args,format);
    vprintf(format,args);
    va_end(args);
    }
}

void DumpOutput2(char* str,const char* format,...)
{
	if(outputFile)
      {
      FILE* fp=fopen(outputFile,"a");
      va_list args;
      va_start(args,format);
      vfprintf(fp,format,args);
      fclose(fp);
      va_end(args);
      }
	if(echoStdout)
    {
		va_list args;
		va_start(args,format);
		vprintf(format,args);
		va_end(args);
	}
	va_list args;
	va_start(args,format);
	vsprintf(str,format,args);
	va_end(args);
	if(str[strlen(str)-1]=='\n'){str[strlen(str)-1]=0;}
}


void ShowUsage(char* ex)
{
	printf("Usage: %s\n",ex);
	printf("\t--in  <input points>\n");

	printf("\t--out <ouput triangle mesh>\n");

	printf("\t[--depth <maximum reconstruction depth>]\n");
	printf("\t\t Running at depth d corresponds to solving on a 2^d x 2^d x 2^d\n");
	printf("\t\t voxel grid.\n");

	printf("\t[--scale <scale factor>]\n");
	printf("\t\t Specifies the factor of the bounding cube that the input\n");
	printf("\t\t samples should fit into.\n");

	printf("\t[--binary]\n");
	printf("\t\t If this flag is enabled, the point set is read in in\n");
	printf("\t\t binary format.\n");

	printf("\t[--solverDivide <subdivision depth>]\n");
	printf("\t\t The depth at which a block Gauss-Seidel solver is used\n");
	printf("\t\t to solve the Laplacian.\n");

	printf("\t[--samplesPerNode <minimum number of samples per node>\n");
	printf("\t\t This parameter specifies the minimum number of points that\n");
	printf("\t\t should fall within an octree node.\n");

	printf("\t[--confidence]\n");
	printf("\t\t If this flag is enabled, the size of a sample's normals is\n");
	printf("\t\t used as a confidence value, affecting the sample's\n");
	printf("\t\t constribution to the reconstruction process.\n");

	printf("\t[--verbose]\n");
}

