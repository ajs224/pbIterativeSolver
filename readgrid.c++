#include<iostream>
#include<fstream>
#include<assert.h>
#include<sstream>
#include<vector>


void readGrid(std::string gridFileName)
{
  std::ifstream gridFile(gridFileName, std::ios::in);
  if(!gridFile.is_open())
	assert("Cannot find grid file"); 

  
  std::cout << "Reading grid file: " << gridFileName << std::endl;
  
  /*
	std::streampos begin,end;
  begin = gridFile.tellg();
  gridFile.seekg (0, std::ios::end);
  end = gridFile.tellg();
  gridFile.close();
  std::cout << "size is: " << (end-begin) << " bytes.\n";
  */


  double x,xp=0.0, delta_x = 0.0;
  double u;
  double in, out;
  std::string line;
  int noCells = 0;

  // Read header
  std::getline(gridFile, line); // junk header
  std::cout<< "Header: " << line<<std::endl;

  // Read first line of grid
  //std::stringstream gridLine(line);
  //gridLine >> xp >> u;
  
  while(!gridFile.eof())
	{
	  //std::cout<< "x = " << x << "\t u = " << u << "\tdx = " << delta_x << std::endl;
	  //xp = x;
	  
	  // Read next line of grid
	  std::getline(gridFile, line);
	  if(line == "")
		break;
	  
	  std::stringstream gridLine(line);
	  gridLine >> x >> u;
	  
	  // Update delta_x and noCells
	  delta_x = x-xp;
	  xp = x;
	  noCells++;
	  

	   std::cout<< "x = " << x << "\t u = " << u << "\tdx = " << delta_x << std::endl;
	 
	  /*
	  //std::cout<< line<<std::endl;
	  std::vector<double> x_u ={x, u};
	  
	  for (auto iter=x_u.begin() ; iter != x_u.end(); ++iter)
		std::cout<< "comp = " << *iter  <<std::endl;
	  */

	  
	}
  gridFile.close();

  std::cout << "Read " << noCells << " from grid files." << std::endl;
  

}



int main(int arfc, char * argv[])
{

  std::vector< std::vector<double> > cells;
  std::vector<double> x_u ={2, 3};
  

  

  readGrid("grid2.dat");
  

  return 0;

/*
double x;
double u;

 while(!gridFile.eof())
	{
	  gridFile.getline(gridLine);
	  gridLine >> x >> u; 
	}
  

  return 0;
  */
}

