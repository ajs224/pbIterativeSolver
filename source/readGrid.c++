#include<iostream>
#include<fstream>
#include<assert.h>
#include<sstream>
#include<vector>
#include "Solver.h"
#include "Cell.h"


std::vector<std::vector<double> > Solver::readGrid(std::vector<Cell> & reactor)
{
  std::ifstream gridFile(gridFileName.c_str(), std::ios::in);
  if(!gridFile.is_open())
	assert("Cannot find grid file"); 
  
  std::cout << "Initialising Solution from CFD grid: " << gridFileName << std::endl;  
  //  std::cout << "reactor size = " << reactor.size() << std::endl;

  /*
	std::streampos begin,end;
  begin = gridFile.tellg();
  gridFile.seekg (0, std::ios::end);
  end = gridFile.tellg();
  gridFile.close();
  std::cout << "size is: " << (end-begin) << " bytes.\n";
  */

  double x,xp, delta_x = 0.0;
  double U;
  double in, out;
  std::string line;
  int cellsRead = 0;

  std::vector<std::vector<double> > cfdGrid;

  // Read header
  std::getline(gridFile, line); // junk header
  std::cout<< "Read header: " << line<<std::endl;

  // Read first line of grid
  std::stringstream gridLine(line);
  std::getline(gridFile, line);
  gridLine >> xp >> u;
  //std::cout<< "xp = " << xp << std::endl;

  
  while(!gridFile.eof())
	{
	  //std::cout<< "x = " << x << "\t u = " << u << "\tdx = " << delta_x << std::endl;
	  //xp = x;
	  
	  // Read next line of grid
	  std::getline(gridFile, line);
	  if(line == "")
		break;
	  
	  std::stringstream gridLine(line);
	  gridLine >> x >> U;
	  
	  // Update delta_x and noCells
	  delta_x = x-xp;
	  //std::cout<< "xp = " << xp << "\tx = " << x << "\t u = " << u << "\tdx = " << delta_x << std::endl;

	  xp = x;
	  cellsRead++;
	  
	  std::vector<double> gridData = {x, U, delta_x};
	  cfdGrid.push_back(gridData);
	  /*
	  std::cout << "Adding cell " <<  cellsRead << " with properties: Cell("<< delta_x/U << ", " << delta_x/U << ", "<< N <<")\t";
	  std::cout<< "x = " << x << "\t U = " << U << "\tdx = " << delta_x;
	  std::cout << " to reactor."<< std::endl;
	  std::cin.sync();
	  std::cin.get();
	  */  
	  
	  reactor.push_back(Cell(delta_x/U, delta_x/U, N));
	  
	  
	  /*
	  //std::cout<< line<<std::endl;
	  std::vector<double> x_u ={x, u};
	  
	  for (auto iter=x_u.begin() ; iter != x_u.end(); ++iter)
		std::cout<< "comp = " << *iter  <<std::endl;
	  */

	  
	}
  gridFile.close();

  std::cout << "Read " << cellsRead << " from cells from grid."<< std::endl<< std::endl;


  // Update number of cells
  noCells = cellsRead;
  
  /*
  std::cout << "Dump grid:" << std::endl;
  for ( std::vector<std::vector<double> >::iterator lineIter = cfdGrid.begin(); lineIter != cfdGrid.end(); ++lineIter)
	{
	  for(std::vector<double>::iterator dataIter = lineIter->begin(); dataIter != lineIter->end(); ++dataIter )
		{
		  std::cout << *dataIter << "\t";
		  }
	  std::cout << std::endl;
	}
  */

  return cfdGrid;

}
