Flat profile:

Each sample counts as 0.01 seconds.
  %   cumulative   self              self     total           
 time   seconds   seconds    calls   s/call   s/call  name    
 37.56     10.64    10.64       12     0.89     2.29  Cell::iterateMD(Solver&, Cell&)
 27.96     18.57     7.92 402604032     0.00     0.00  Cell::getOldNumDens(unsigned long)
 25.52     25.80     7.23 301965312     0.00     0.00  k(unsigned long, unsigned long)
  5.93     27.48     1.68 201424909     0.00     0.00  Solver::getN()
  1.16     27.81     0.33                             Solver::isCoagOn()
  1.09     28.12     0.31                             nIn(unsigned long, unsigned long)
  0.81     28.35     0.23        1     0.23     0.23  Solver::getOut()
  0.00     28.35     0.00    49152     0.00     0.00  Cell::setNumDens(unsigned long, double)
  0.00     28.35     0.00    49152     0.00     0.00  Cell::getInDist(unsigned long)
  0.00     28.35     0.00      624     0.00     0.00  MTRand::hiBit(unsigned long) const
  0.00     28.35     0.00      624     0.00     0.00  MTRand::loBit(unsigned long) const
  0.00     28.35     0.00      624     0.00     0.00  MTRand::magic(unsigned long) const
  0.00     28.35     0.00      624     0.00     0.00  MTRand::twist(unsigned long, unsigned long, unsigned long) const
  0.00     28.35     0.00      624     0.00     0.00  MTRand::loBits(unsigned long) const
  0.00     28.35     0.00      624     0.00     0.00  MTRand::mixBits(unsigned long, unsigned long) const
  0.00     28.35     0.00       55     0.00     0.00  __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > >::operator->() const
  0.00     28.35     0.00       52     0.00     0.00  std::abs(double)
  0.00     28.35     0.00       17     0.00     0.00  Solver::getNoCells()
  0.00     28.35     0.00       14     0.00     0.00  std::ios_base::setf(std::_Ios_Fmtflags)
  0.00     28.35     0.00       14     0.00     0.00  std::ios_base::precision(long)
  0.00     28.35     0.00       14     0.00     0.00  std::operator|=(std::_Ios_Fmtflags&, std::_Ios_Fmtflags)
  0.00     28.35     0.00       14     0.00     0.00  std::operator|(std::_Ios_Fmtflags, std::_Ios_Fmtflags)
  0.00     28.35     0.00       13     0.00     0.00  Cell::calculateMoments()
  0.00     28.35     0.00       12     0.00     0.00  Cell::getMoments()
  0.00     28.35     0.00       12     0.00     0.00  Cell::updateDist()
  0.00     28.35     0.00       12     0.00     0.00  Solver::writeMoments(int, double*)
  0.00     28.35     0.00       12     0.00     0.00  Solver::isNumberDensityRep()
  0.00     28.35     0.00       12     0.00     0.00  Solver::getL()
  0.00     28.35     0.00       12     0.00     0.00  Solver::getMaxRes()
  0.00     28.35     0.00       12     0.00     0.00  __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > >::operator*() const
  0.00     28.35     0.00       12     0.00     0.00  std::ios_base::width(long)
  0.00     28.35     0.00       10     0.00     0.00  __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > >::base() const
  0.00     28.35     0.00        9     0.00     0.00  __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > >::__normal_iterator(Cell* const&)
  0.00     28.35     0.00        6     0.00     0.00  std::basic_string<char, std::char_traits<char>, std::allocator<char> > std::operator+<char, std::char_traits<char>, std::allocator<char> >(std::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> > const&)
  0.00     28.35     0.00        4     0.00     0.00  Cell* std::__addressof<Cell>(Cell&)
  0.00     28.35     0.00        3     0.00     0.00  Cell::~Cell()
  0.00     28.35     0.00        3     0.00     0.00  bool __gnu_cxx::operator!=<Cell*, std::vector<Cell, std::allocator<Cell> > >(__gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > > const&, __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > > const&)
  0.00     28.35     0.00        3     0.00     0.00  std::vector<Cell, std::allocator<Cell> >::end()
  0.00     28.35     0.00        3     0.00     0.00  std::vector<Cell, std::allocator<Cell> >::begin()
  0.00     28.35     0.00        2     0.00     0.00  Cell::initMoments()
  0.00     28.35     0.00        2     0.00     0.00  Cell::initDist(mfaAnalytic::distributions)
  0.00     28.35     0.00        2     0.00     0.00  Cell::Cell(Cell const&)
  0.00     28.35     0.00        2     0.00     0.00  __gnu_cxx::new_allocator<Cell>::~new_allocator()
  0.00     28.35     0.00        2     0.00     0.00  __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > >::operator++(int)
  0.00     28.35     0.00        2     0.00     0.00  __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > >::difference_type __gnu_cxx::operator-<Cell*, std::vector<Cell, std::allocator<Cell> > >(__gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > > const&, __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > > const&)
  0.00     28.35     0.00        2     0.00     0.00  std::allocator<Cell>::~allocator()
  0.00     28.35     0.00        2     0.00     0.00  std::_Vector_base<Cell, std::allocator<Cell> >::_M_get_Tp_allocator()
  0.00     28.35     0.00        2     0.00     0.00  void std::_Construct<Cell, Cell>(Cell*, Cell const&)
  0.00     28.35     0.00        2     0.00     0.00  void std::_Destroy<Cell>(Cell*)
  0.00     28.35     0.00        2     0.00     0.00  std::basic_string<char, std::char_traits<char>, std::allocator<char> > std::operator+<char, std::char_traits<char>, std::allocator<char> >(std::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, char const*)
  0.00     28.35     0.00        2     0.00     0.00  operator new(unsigned long, void*)
  0.00     28.35     0.00        1     0.00     0.00  _GLOBAL__sub_I__ZN11mfaAnalytic10kernelTypeE
  0.00     28.35     0.00        1     0.00     0.00  _GLOBAL__sub_I__ZN4CellC2Ev
  0.00     28.35     0.00        1     0.00     0.00  _GLOBAL__sub_I__ZN6SolverC2Ev
  0.00     28.35     0.00        1     0.00     0.00  _GLOBAL__sub_I_main
  0.00     28.35     0.00        1     0.00     0.00  __static_initialization_and_destruction_0(int, int)
  0.00     28.35     0.00        1     0.00     0.00  __static_initialization_and_destruction_0(int, int)
  0.00     28.35     0.00        1     0.00     0.00  __static_initialization_and_destruction_0(int, int)
  0.00     28.35     0.00        1     0.00     0.00  __static_initialization_and_destruction_0(int, int)
  0.00     28.35     0.00        1     0.00     0.00  __static_initialization_and_destruction_0(int, int)
  0.00     28.35     0.00        1     0.00     0.00  Cell::initInDist(double*)
  0.00     28.35     0.00        1     0.00     0.00  Cell::getDist()
  0.00     28.35     0.00        1     0.00     0.00  Cell::Cell(double, double, unsigned long)
  0.00     28.35     0.00        1     0.00     0.00  MTRand::initialize(unsigned long)
  0.00     28.35     0.00        1     0.00     0.00  MTRand::seed(unsigned long*, unsigned long)
  0.00     28.35     0.00        1     0.00     0.00  MTRand::seed()
  0.00     28.35     0.00        1     0.00     0.00  MTRand::reload()
  0.00     28.35     0.00        1     0.00     0.00  MTRand::MTRand()
  0.00     28.35     0.00        1     0.00     0.00  Solver::getIn()
  0.00     28.35     0.00        1     0.00     0.00  Solver::setup()
  0.00     28.35     0.00        1     0.00     0.00  Solver::delta_x()
  0.00     28.35     0.00        1     0.00     0.00  Solver::parseArgs(int, char**)
  0.00     28.35     0.00        1     0.00     0.00  Solver::Solver()
  0.00     28.35     0.00        1     0.00     0.00  Solver::~Solver()
  0.00     28.35     0.00        1     0.00     0.00  __gnu_cxx::new_allocator<Cell>::deallocate(Cell*, unsigned long)
  0.00     28.35     0.00        1     0.00     0.00  __gnu_cxx::new_allocator<Cell>::allocate(unsigned long, void const*)
  0.00     28.35     0.00        1     0.00     0.00  __gnu_cxx::new_allocator<Cell>::new_allocator(__gnu_cxx::new_allocator<Cell> const&)
  0.00     28.35     0.00        1     0.00     0.00  __gnu_cxx::new_allocator<Cell>::new_allocator()
  0.00     28.35     0.00        1     0.00     0.00  __gnu_cxx::new_allocator<Cell>::max_size() const
  0.00     28.35     0.00        1     0.00     0.00  __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > >::operator-(long const&) const
  0.00     28.35     0.00        1     0.00     0.00  std::allocator<Cell>::allocator(std::allocator<Cell> const&)
  0.00     28.35     0.00        1     0.00     0.00  std::allocator<Cell>::allocator()
  0.00     28.35     0.00        1     0.00     0.00  void std::_Destroy_aux<false>::__destroy<Cell*>(Cell*, Cell*)
  0.00     28.35     0.00        1     0.00     0.00  std::_Vector_base<Cell, std::allocator<Cell> >::_M_allocate(unsigned long)
  0.00     28.35     0.00        1     0.00     0.00  std::_Vector_base<Cell, std::allocator<Cell> >::_Vector_impl::_Vector_impl(std::allocator<Cell> const&)
  0.00     28.35     0.00        1     0.00     0.00  std::_Vector_base<Cell, std::allocator<Cell> >::_Vector_impl::~_Vector_impl()
  0.00     28.35     0.00        1     0.00     0.00  std::_Vector_base<Cell, std::allocator<Cell> >::_M_deallocate(Cell*, unsigned long)
  0.00     28.35     0.00        1     0.00     0.00  std::_Vector_base<Cell, std::allocator<Cell> >::_Vector_base(unsigned long, std::allocator<Cell> const&)
  0.00     28.35     0.00        1     0.00     0.00  std::_Vector_base<Cell, std::allocator<Cell> >::~_Vector_base()
  0.00     28.35     0.00        1     0.00     0.00  void std::__uninitialized_fill_n<false>::__uninit_fill_n<Cell*, unsigned long, Cell>(Cell*, unsigned long, Cell const&)
  0.00     28.35     0.00        1     0.00     0.00  std::vector<Cell, std::allocator<Cell> >::_M_fill_initialize(unsigned long, Cell const&)
  0.00     28.35     0.00        1     0.00     0.00  std::vector<Cell, std::allocator<Cell> >::vector(unsigned long, Cell const&, std::allocator<Cell> const&)
  0.00     28.35     0.00        1     0.00     0.00  std::vector<Cell, std::allocator<Cell> >::~vector()
  0.00     28.35     0.00        1     0.00     0.00  void std::uninitialized_fill_n<Cell*, unsigned long, Cell>(Cell*, unsigned long, Cell const&)
  0.00     28.35     0.00        1     0.00     0.00  void std::__uninitialized_fill_n_a<Cell*, unsigned long, Cell, Cell>(Cell*, unsigned long, Cell const&, std::allocator<Cell>&)
  0.00     28.35     0.00        1     0.00     0.00  __gnu_cxx::__promote_2<int, unsigned int, __gnu_cxx::__promote<int, std::__is_integer<int>::__value>::__type, __gnu_cxx::__promote<unsigned int, std::__is_integer<unsigned int>::__value>::__type>::__type std::pow<int, unsigned int>(int, unsigned int)
  0.00     28.35     0.00        1     0.00     0.00  void std::_Destroy<Cell*>(Cell*, Cell*)
  0.00     28.35     0.00        1     0.00     0.00  void std::_Destroy<Cell*, Cell>(Cell*, Cell*, std::allocator<Cell>&)
  0.00     28.35     0.00        1     0.00     0.00  std::operator|(std::_Ios_Openmode, std::_Ios_Openmode)

 %         the percentage of the total running time of the
time       program used by this function.

cumulative a running sum of the number of seconds accounted
 seconds   for by this function and those listed above it.

 self      the number of seconds accounted for by this
seconds    function alone.  This is the major sort for this
           listing.

calls      the number of times this function was invoked, if
           this function is profiled, else blank.
 
 self      the average number of milliseconds spent in this
ms/call    function per call, if this function is profiled,
	   else blank.

 total     the average number of milliseconds spent in this
ms/call    function and its descendents per call, if this 
	   function is profiled, else blank.

name       the name of the function.  This is the minor sort
           for this listing. The index shows the location of
	   the function in the gprof listing. If the index is
	   in parenthesis it shows where it would appear in
	   the gprof listing if it were to be printed.

		     Call graph (explanation follows)


granularity: each sample hit covers 2 byte(s) for 0.04% of 28.35 seconds

index % time    self  children    called     name
                                                 <spontaneous>
[1]     97.7    0.00   27.71                 main [1]
               10.64   16.84      12/12          Cell::iterateMD(Solver&, Cell&) [2]
                0.23    0.00       1/1           Solver::getOut() [8]
                0.00    0.00       1/201424909     Solver::getN() [5]
                0.00    0.00      55/55          __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > >::operator->() const [21]
                0.00    0.00      17/17          Solver::getNoCells() [23]
                0.00    0.00      13/13          Cell::calculateMoments() [28]
                0.00    0.00      12/12          Cell::getMoments() [29]
                0.00    0.00      12/12          Solver::writeMoments(int, double*) [31]
                0.00    0.00      12/12          Cell::updateDist() [30]
                0.00    0.00      12/12          Solver::isNumberDensityRep() [32]
                0.00    0.00      12/12          __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > >::operator*() const [35]
                0.00    0.00      12/12          Solver::getL() [33]
                0.00    0.00      12/12          Solver::getMaxRes() [34]
                0.00    0.00       3/3           std::vector<Cell, std::allocator<Cell> >::begin() [44]
                0.00    0.00       3/3           std::vector<Cell, std::allocator<Cell> >::end() [43]
                0.00    0.00       3/3           bool __gnu_cxx::operator!=<Cell*, std::vector<Cell, std::allocator<Cell> > >(__gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > > const&, __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > > const&) [42]
                0.00    0.00       2/2           __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > >::difference_type __gnu_cxx::operator-<Cell*, std::vector<Cell, std::allocator<Cell> > >(__gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > > const&, __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > > const&) [50]
                0.00    0.00       2/2           Cell::initDist(mfaAnalytic::distributions) [46]
                0.00    0.00       2/2           Cell::initMoments() [45]
                0.00    0.00       2/2           __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > >::operator++(int) [49]
                0.00    0.00       1/1           MTRand::MTRand() [73]
                0.00    0.00       1/1           Solver::Solver() [78]
                0.00    0.00       1/1           Solver::parseArgs(int, char**) [77]
                0.00    0.00       1/1           Solver::setup() [75]
                0.00    0.00       1/1           Solver::delta_x() [76]
                0.00    0.00       1/1           Solver::getIn() [74]
                0.00    0.00       1/1           std::allocator<Cell>::allocator() [87]
                0.00    0.00       1/1           Cell::Cell(double, double, unsigned long) [68]
                0.00    0.00       1/1           std::vector<Cell, std::allocator<Cell> >::vector(unsigned long, Cell const&, std::allocator<Cell> const&) [97]
                0.00    0.00       1/3           Cell::~Cell() [41]
                0.00    0.00       1/2           std::allocator<Cell>::~allocator() [51]
                0.00    0.00       1/1           __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > >::operator-(long const&) const [85]
                0.00    0.00       1/1           Cell::getDist() [67]
                0.00    0.00       1/1           Cell::initInDist(double*) [66]
                0.00    0.00       1/1           std::vector<Cell, std::allocator<Cell> >::~vector() [98]
                0.00    0.00       1/1           Solver::~Solver() [79]
-----------------------------------------------
               10.64   16.84      12/12          main [1]
[2]     96.9   10.64   16.84      12         Cell::iterateMD(Solver&, Cell&) [2]
                7.92    0.00 402604032/402604032     Cell::getOldNumDens(unsigned long) [3]
                7.23    0.00 301965312/301965312     k(unsigned long, unsigned long) [4]
                1.68    0.00 201424908/201424909     Solver::getN() [5]
                0.00    0.00   49152/49152       Cell::getInDist(unsigned long) [14]
                0.00    0.00   49152/49152       Cell::setNumDens(unsigned long, double) [13]
-----------------------------------------------
                7.92    0.00 402604032/402604032     Cell::iterateMD(Solver&, Cell&) [2]
[3]     27.9    7.92    0.00 402604032         Cell::getOldNumDens(unsigned long) [3]
-----------------------------------------------
                7.23    0.00 301965312/301965312     Cell::iterateMD(Solver&, Cell&) [2]
[4]     25.5    7.23    0.00 301965312         k(unsigned long, unsigned long) [4]
-----------------------------------------------
                0.00    0.00       1/201424909     main [1]
                1.68    0.00 201424908/201424909     Cell::iterateMD(Solver&, Cell&) [2]
[5]      5.9    1.68    0.00 201424909         Solver::getN() [5]
-----------------------------------------------
                                                 <spontaneous>
[6]      1.2    0.33    0.00                 Solver::isCoagOn() [6]
-----------------------------------------------
                                                 <spontaneous>
[7]      1.1    0.31    0.00                 nIn(unsigned long, unsigned long) [7]
-----------------------------------------------
                0.23    0.00       1/1           main [1]
[8]      0.8    0.23    0.00       1         Solver::getOut() [8]
-----------------------------------------------
                0.00    0.00   49152/49152       Cell::iterateMD(Solver&, Cell&) [2]
[13]     0.0    0.00    0.00   49152         Cell::setNumDens(unsigned long, double) [13]
-----------------------------------------------
                0.00    0.00   49152/49152       Cell::iterateMD(Solver&, Cell&) [2]
[14]     0.0    0.00    0.00   49152         Cell::getInDist(unsigned long) [14]
-----------------------------------------------
                0.00    0.00     624/624         MTRand::mixBits(unsigned long, unsigned long) const [20]
[15]     0.0    0.00    0.00     624         MTRand::hiBit(unsigned long) const [15]
-----------------------------------------------
                0.00    0.00     624/624         MTRand::magic(unsigned long) const [17]
[16]     0.0    0.00    0.00     624         MTRand::loBit(unsigned long) const [16]
-----------------------------------------------
                0.00    0.00     624/624         MTRand::twist(unsigned long, unsigned long, unsigned long) const [18]
[17]     0.0    0.00    0.00     624         MTRand::magic(unsigned long) const [17]
                0.00    0.00     624/624         MTRand::loBit(unsigned long) const [16]
-----------------------------------------------
                0.00    0.00     624/624         MTRand::reload() [72]
[18]     0.0    0.00    0.00     624         MTRand::twist(unsigned long, unsigned long, unsigned long) const [18]
                0.00    0.00     624/624         MTRand::mixBits(unsigned long, unsigned long) const [20]
                0.00    0.00     624/624         MTRand::magic(unsigned long) const [17]
-----------------------------------------------
                0.00    0.00     624/624         MTRand::mixBits(unsigned long, unsigned long) const [20]
[19]     0.0    0.00    0.00     624         MTRand::loBits(unsigned long) const [19]
-----------------------------------------------
                0.00    0.00     624/624         MTRand::twist(unsigned long, unsigned long, unsigned long) const [18]
[20]     0.0    0.00    0.00     624         MTRand::mixBits(unsigned long, unsigned long) const [20]
                0.00    0.00     624/624         MTRand::hiBit(unsigned long) const [15]
                0.00    0.00     624/624         MTRand::loBits(unsigned long) const [19]
-----------------------------------------------
                0.00    0.00      55/55          main [1]
[21]     0.0    0.00    0.00      55         __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > >::operator->() const [21]
-----------------------------------------------
                0.00    0.00      52/52          Cell::calculateMoments() [28]
[22]     0.0    0.00    0.00      52         std::abs(double) [22]
-----------------------------------------------
                0.00    0.00      17/17          main [1]
[23]     0.0    0.00    0.00      17         Solver::getNoCells() [23]
-----------------------------------------------
                0.00    0.00       2/14          Solver::setup() [75]
                0.00    0.00      12/14          Solver::writeMoments(int, double*) [31]
[24]     0.0    0.00    0.00      14         std::ios_base::setf(std::_Ios_Fmtflags) [24]
                0.00    0.00      14/14          std::operator|=(std::_Ios_Fmtflags&, std::_Ios_Fmtflags) [26]
-----------------------------------------------
                0.00    0.00       2/14          Solver::setup() [75]
                0.00    0.00      12/14          Solver::writeMoments(int, double*) [31]
[25]     0.0    0.00    0.00      14         std::ios_base::precision(long) [25]
-----------------------------------------------
                0.00    0.00      14/14          std::ios_base::setf(std::_Ios_Fmtflags) [24]
[26]     0.0    0.00    0.00      14         std::operator|=(std::_Ios_Fmtflags&, std::_Ios_Fmtflags) [26]
                0.00    0.00      14/14          std::operator|(std::_Ios_Fmtflags, std::_Ios_Fmtflags) [27]
-----------------------------------------------
                0.00    0.00      14/14          std::operator|=(std::_Ios_Fmtflags&, std::_Ios_Fmtflags) [26]
[27]     0.0    0.00    0.00      14         std::operator|(std::_Ios_Fmtflags, std::_Ios_Fmtflags) [27]
-----------------------------------------------
                0.00    0.00      13/13          main [1]
[28]     0.0    0.00    0.00      13         Cell::calculateMoments() [28]
                0.00    0.00      52/52          std::abs(double) [22]
-----------------------------------------------
                0.00    0.00      12/12          main [1]
[29]     0.0    0.00    0.00      12         Cell::getMoments() [29]
-----------------------------------------------
                0.00    0.00      12/12          main [1]
[30]     0.0    0.00    0.00      12         Cell::updateDist() [30]
-----------------------------------------------
                0.00    0.00      12/12          main [1]
[31]     0.0    0.00    0.00      12         Solver::writeMoments(int, double*) [31]
                0.00    0.00      12/14          std::ios_base::precision(long) [25]
                0.00    0.00      12/14          std::ios_base::setf(std::_Ios_Fmtflags) [24]
                0.00    0.00      12/12          std::ios_base::width(long) [36]
-----------------------------------------------
                0.00    0.00      12/12          main [1]
[32]     0.0    0.00    0.00      12         Solver::isNumberDensityRep() [32]
-----------------------------------------------
                0.00    0.00      12/12          main [1]
[33]     0.0    0.00    0.00      12         Solver::getL() [33]
-----------------------------------------------
                0.00    0.00      12/12          main [1]
[34]     0.0    0.00    0.00      12         Solver::getMaxRes() [34]
-----------------------------------------------
                0.00    0.00      12/12          main [1]
[35]     0.0    0.00    0.00      12         __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > >::operator*() const [35]
-----------------------------------------------
                0.00    0.00      12/12          Solver::writeMoments(int, double*) [31]
[36]     0.0    0.00    0.00      12         std::ios_base::width(long) [36]
-----------------------------------------------
                0.00    0.00       4/10          __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > >::difference_type __gnu_cxx::operator-<Cell*, std::vector<Cell, std::allocator<Cell> > >(__gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > > const&, __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > > const&) [50]
                0.00    0.00       6/10          bool __gnu_cxx::operator!=<Cell*, std::vector<Cell, std::allocator<Cell> > >(__gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > > const&, __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > > const&) [42]
[37]     0.0    0.00    0.00      10         __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > >::base() const [37]
-----------------------------------------------
                0.00    0.00       1/9           __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > >::operator-(long const&) const [85]
                0.00    0.00       2/9           __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > >::operator++(int) [49]
                0.00    0.00       3/9           std::vector<Cell, std::allocator<Cell> >::begin() [44]
                0.00    0.00       3/9           std::vector<Cell, std::allocator<Cell> >::end() [43]
[38]     0.0    0.00    0.00       9         __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > >::__normal_iterator(Cell* const&) [38]
-----------------------------------------------
                0.00    0.00       6/6           Solver::setup() [75]
[39]     0.0    0.00    0.00       6         std::basic_string<char, std::char_traits<char>, std::allocator<char> > std::operator+<char, std::char_traits<char>, std::allocator<char> >(std::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> > const&) [39]
-----------------------------------------------
                0.00    0.00       2/4           void std::_Destroy_aux<false>::__destroy<Cell*>(Cell*, Cell*) [88]
                0.00    0.00       2/4           void std::__uninitialized_fill_n<false>::__uninit_fill_n<Cell*, unsigned long, Cell>(Cell*, unsigned long, Cell const&) [95]
[40]     0.0    0.00    0.00       4         Cell* std::__addressof<Cell>(Cell&) [40]
-----------------------------------------------
                0.00    0.00       1/3           main [1]
                0.00    0.00       2/3           void std::_Destroy<Cell>(Cell*) [54]
[41]     0.0    0.00    0.00       3         Cell::~Cell() [41]
-----------------------------------------------
                0.00    0.00       3/3           main [1]
[42]     0.0    0.00    0.00       3         bool __gnu_cxx::operator!=<Cell*, std::vector<Cell, std::allocator<Cell> > >(__gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > > const&, __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > > const&) [42]
                0.00    0.00       6/10          __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > >::base() const [37]
-----------------------------------------------
                0.00    0.00       3/3           main [1]
[43]     0.0    0.00    0.00       3         std::vector<Cell, std::allocator<Cell> >::end() [43]
                0.00    0.00       3/9           __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > >::__normal_iterator(Cell* const&) [38]
-----------------------------------------------
                0.00    0.00       3/3           main [1]
[44]     0.0    0.00    0.00       3         std::vector<Cell, std::allocator<Cell> >::begin() [44]
                0.00    0.00       3/9           __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > >::__normal_iterator(Cell* const&) [38]
-----------------------------------------------
                0.00    0.00       2/2           main [1]
[45]     0.0    0.00    0.00       2         Cell::initMoments() [45]
-----------------------------------------------
                0.00    0.00       2/2           main [1]
[46]     0.0    0.00    0.00       2         Cell::initDist(mfaAnalytic::distributions) [46]
-----------------------------------------------
                0.00    0.00       2/2           void std::_Construct<Cell, Cell>(Cell*, Cell const&) [53]
[47]     0.0    0.00    0.00       2         Cell::Cell(Cell const&) [47]
-----------------------------------------------
                0.00    0.00       2/2           std::allocator<Cell>::~allocator() [51]
[48]     0.0    0.00    0.00       2         __gnu_cxx::new_allocator<Cell>::~new_allocator() [48]
-----------------------------------------------
                0.00    0.00       2/2           main [1]
[49]     0.0    0.00    0.00       2         __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > >::operator++(int) [49]
                0.00    0.00       2/9           __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > >::__normal_iterator(Cell* const&) [38]
-----------------------------------------------
                0.00    0.00       2/2           main [1]
[50]     0.0    0.00    0.00       2         __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > >::difference_type __gnu_cxx::operator-<Cell*, std::vector<Cell, std::allocator<Cell> > >(__gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > > const&, __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > > const&) [50]
                0.00    0.00       4/10          __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > >::base() const [37]
-----------------------------------------------
                0.00    0.00       1/2           main [1]
                0.00    0.00       1/2           std::_Vector_base<Cell, std::allocator<Cell> >::_Vector_impl::~_Vector_impl() [91]
[51]     0.0    0.00    0.00       2         std::allocator<Cell>::~allocator() [51]
                0.00    0.00       2/2           __gnu_cxx::new_allocator<Cell>::~new_allocator() [48]
-----------------------------------------------
                0.00    0.00       1/2           std::vector<Cell, std::allocator<Cell> >::~vector() [98]
                0.00    0.00       1/2           std::vector<Cell, std::allocator<Cell> >::_M_fill_initialize(unsigned long, Cell const&) [96]
[52]     0.0    0.00    0.00       2         std::_Vector_base<Cell, std::allocator<Cell> >::_M_get_Tp_allocator() [52]
-----------------------------------------------
                0.00    0.00       2/2           void std::__uninitialized_fill_n<false>::__uninit_fill_n<Cell*, unsigned long, Cell>(Cell*, unsigned long, Cell const&) [95]
[53]     0.0    0.00    0.00       2         void std::_Construct<Cell, Cell>(Cell*, Cell const&) [53]
                0.00    0.00       2/2           operator new(unsigned long, void*) [56]
                0.00    0.00       2/2           Cell::Cell(Cell const&) [47]
-----------------------------------------------
                0.00    0.00       2/2           void std::_Destroy_aux<false>::__destroy<Cell*>(Cell*, Cell*) [88]
[54]     0.0    0.00    0.00       2         void std::_Destroy<Cell>(Cell*) [54]
                0.00    0.00       2/3           Cell::~Cell() [41]
-----------------------------------------------
                0.00    0.00       2/2           Solver::setup() [75]
[55]     0.0    0.00    0.00       2         std::basic_string<char, std::char_traits<char>, std::allocator<char> > std::operator+<char, std::char_traits<char>, std::allocator<char> >(std::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, char const*) [55]
-----------------------------------------------
                0.00    0.00       2/2           void std::_Construct<Cell, Cell>(Cell*, Cell const&) [53]
[56]     0.0    0.00    0.00       2         operator new(unsigned long, void*) [56]
-----------------------------------------------
                0.00    0.00       1/1           __libc_csu_init [125]
[57]     0.0    0.00    0.00       1         _GLOBAL__sub_I__ZN11mfaAnalytic10kernelTypeE [57]
                0.00    0.00       1/1           __static_initialization_and_destruction_0(int, int) [62]
-----------------------------------------------
                0.00    0.00       1/1           __libc_csu_init [125]
[58]     0.0    0.00    0.00       1         _GLOBAL__sub_I__ZN4CellC2Ev [58]
                0.00    0.00       1/1           __static_initialization_and_destruction_0(int, int) [64]
-----------------------------------------------
                0.00    0.00       1/1           __libc_csu_init [125]
[59]     0.0    0.00    0.00       1         _GLOBAL__sub_I__ZN6SolverC2Ev [59]
                0.00    0.00       1/1           __static_initialization_and_destruction_0(int, int) [65]
-----------------------------------------------
                0.00    0.00       1/1           __libc_csu_init [125]
[60]     0.0    0.00    0.00       1         _GLOBAL__sub_I_main [60]
                0.00    0.00       1/1           __static_initialization_and_destruction_0(int, int) [61]
-----------------------------------------------
                0.00    0.00       1/1           _GLOBAL__sub_I_main [60]
[61]     0.0    0.00    0.00       1         __static_initialization_and_destruction_0(int, int) [61]
-----------------------------------------------
                0.00    0.00       1/1           _GLOBAL__sub_I__ZN11mfaAnalytic10kernelTypeE [57]
[62]     0.0    0.00    0.00       1         __static_initialization_and_destruction_0(int, int) [62]
-----------------------------------------------
                                   1             __static_initialization_and_destruction_0(int, int) [63]
                0.00    0.00       1/1           __libc_csu_init [125]
[63]     0.0    0.00    0.00       1+1       __static_initialization_and_destruction_0(int, int) [63]
                                   1             __static_initialization_and_destruction_0(int, int) [63]
-----------------------------------------------
                0.00    0.00       1/1           _GLOBAL__sub_I__ZN4CellC2Ev [58]
[64]     0.0    0.00    0.00       1         __static_initialization_and_destruction_0(int, int) [64]
-----------------------------------------------
                0.00    0.00       1/1           _GLOBAL__sub_I__ZN6SolverC2Ev [59]
[65]     0.0    0.00    0.00       1         __static_initialization_and_destruction_0(int, int) [65]
-----------------------------------------------
                0.00    0.00       1/1           main [1]
[66]     0.0    0.00    0.00       1         Cell::initInDist(double*) [66]
-----------------------------------------------
                0.00    0.00       1/1           main [1]
[67]     0.0    0.00    0.00       1         Cell::getDist() [67]
-----------------------------------------------
                0.00    0.00       1/1           main [1]
[68]     0.0    0.00    0.00       1         Cell::Cell(double, double, unsigned long) [68]
-----------------------------------------------
                0.00    0.00       1/1           MTRand::seed(unsigned long*, unsigned long) [70]
[69]     0.0    0.00    0.00       1         MTRand::initialize(unsigned long) [69]
-----------------------------------------------
                0.00    0.00       1/1           MTRand::seed() [71]
[70]     0.0    0.00    0.00       1         MTRand::seed(unsigned long*, unsigned long) [70]
                0.00    0.00       1/1           MTRand::initialize(unsigned long) [69]
                0.00    0.00       1/1           MTRand::reload() [72]
-----------------------------------------------
                0.00    0.00       1/1           MTRand::MTRand() [73]
[71]     0.0    0.00    0.00       1         MTRand::seed() [71]
                0.00    0.00       1/1           MTRand::seed(unsigned long*, unsigned long) [70]
-----------------------------------------------
                0.00    0.00       1/1           MTRand::seed(unsigned long*, unsigned long) [70]
[72]     0.0    0.00    0.00       1         MTRand::reload() [72]
                0.00    0.00     624/624         MTRand::twist(unsigned long, unsigned long, unsigned long) const [18]
-----------------------------------------------
                0.00    0.00       1/1           main [1]
[73]     0.0    0.00    0.00       1         MTRand::MTRand() [73]
                0.00    0.00       1/1           MTRand::seed() [71]
-----------------------------------------------
                0.00    0.00       1/1           main [1]
[74]     0.0    0.00    0.00       1         Solver::getIn() [74]
-----------------------------------------------
                0.00    0.00       1/1           main [1]
[75]     0.0    0.00    0.00       1         Solver::setup() [75]
                0.00    0.00       6/6           std::basic_string<char, std::char_traits<char>, std::allocator<char> > std::operator+<char, std::char_traits<char>, std::allocator<char> >(std::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> > const&) [39]
                0.00    0.00       2/2           std::basic_string<char, std::char_traits<char>, std::allocator<char> > std::operator+<char, std::char_traits<char>, std::allocator<char> >(std::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, char const*) [55]
                0.00    0.00       2/14          std::ios_base::precision(long) [25]
                0.00    0.00       2/14          std::ios_base::setf(std::_Ios_Fmtflags) [24]
                0.00    0.00       1/1           std::operator|(std::_Ios_Openmode, std::_Ios_Openmode) [104]
-----------------------------------------------
                0.00    0.00       1/1           main [1]
[76]     0.0    0.00    0.00       1         Solver::delta_x() [76]
-----------------------------------------------
                0.00    0.00       1/1           main [1]
[77]     0.0    0.00    0.00       1         Solver::parseArgs(int, char**) [77]
                0.00    0.00       1/1           __gnu_cxx::__promote_2<int, unsigned int, __gnu_cxx::__promote<int, std::__is_integer<int>::__value>::__type, __gnu_cxx::__promote<unsigned int, std::__is_integer<unsigned int>::__value>::__type>::__type std::pow<int, unsigned int>(int, unsigned int) [101]
-----------------------------------------------
                0.00    0.00       1/1           main [1]
[78]     0.0    0.00    0.00       1         Solver::Solver() [78]
-----------------------------------------------
                0.00    0.00       1/1           main [1]
[79]     0.0    0.00    0.00       1         Solver::~Solver() [79]
-----------------------------------------------
                0.00    0.00       1/1           std::_Vector_base<Cell, std::allocator<Cell> >::_M_deallocate(Cell*, unsigned long) [92]
[80]     0.0    0.00    0.00       1         __gnu_cxx::new_allocator<Cell>::deallocate(Cell*, unsigned long) [80]
-----------------------------------------------
                0.00    0.00       1/1           std::_Vector_base<Cell, std::allocator<Cell> >::_M_allocate(unsigned long) [89]
[81]     0.0    0.00    0.00       1         __gnu_cxx::new_allocator<Cell>::allocate(unsigned long, void const*) [81]
                0.00    0.00       1/1           __gnu_cxx::new_allocator<Cell>::max_size() const [84]
-----------------------------------------------
                0.00    0.00       1/1           std::allocator<Cell>::allocator(std::allocator<Cell> const&) [86]
[82]     0.0    0.00    0.00       1         __gnu_cxx::new_allocator<Cell>::new_allocator(__gnu_cxx::new_allocator<Cell> const&) [82]
-----------------------------------------------
                0.00    0.00       1/1           std::allocator<Cell>::allocator() [87]
[83]     0.0    0.00    0.00       1         __gnu_cxx::new_allocator<Cell>::new_allocator() [83]
-----------------------------------------------
                0.00    0.00       1/1           __gnu_cxx::new_allocator<Cell>::allocate(unsigned long, void const*) [81]
[84]     0.0    0.00    0.00       1         __gnu_cxx::new_allocator<Cell>::max_size() const [84]
-----------------------------------------------
                0.00    0.00       1/1           main [1]
[85]     0.0    0.00    0.00       1         __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > >::operator-(long const&) const [85]
                0.00    0.00       1/9           __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > >::__normal_iterator(Cell* const&) [38]
-----------------------------------------------
                0.00    0.00       1/1           std::_Vector_base<Cell, std::allocator<Cell> >::_Vector_impl::_Vector_impl(std::allocator<Cell> const&) [90]
[86]     0.0    0.00    0.00       1         std::allocator<Cell>::allocator(std::allocator<Cell> const&) [86]
                0.00    0.00       1/1           __gnu_cxx::new_allocator<Cell>::new_allocator(__gnu_cxx::new_allocator<Cell> const&) [82]
-----------------------------------------------
                0.00    0.00       1/1           main [1]
[87]     0.0    0.00    0.00       1         std::allocator<Cell>::allocator() [87]
                0.00    0.00       1/1           __gnu_cxx::new_allocator<Cell>::new_allocator() [83]
-----------------------------------------------
                0.00    0.00       1/1           void std::_Destroy<Cell*>(Cell*, Cell*) [102]
[88]     0.0    0.00    0.00       1         void std::_Destroy_aux<false>::__destroy<Cell*>(Cell*, Cell*) [88]
                0.00    0.00       2/4           Cell* std::__addressof<Cell>(Cell&) [40]
                0.00    0.00       2/2           void std::_Destroy<Cell>(Cell*) [54]
-----------------------------------------------
                0.00    0.00       1/1           std::_Vector_base<Cell, std::allocator<Cell> >::_Vector_base(unsigned long, std::allocator<Cell> const&) [93]
[89]     0.0    0.00    0.00       1         std::_Vector_base<Cell, std::allocator<Cell> >::_M_allocate(unsigned long) [89]
                0.00    0.00       1/1           __gnu_cxx::new_allocator<Cell>::allocate(unsigned long, void const*) [81]
-----------------------------------------------
                0.00    0.00       1/1           std::_Vector_base<Cell, std::allocator<Cell> >::_Vector_base(unsigned long, std::allocator<Cell> const&) [93]
[90]     0.0    0.00    0.00       1         std::_Vector_base<Cell, std::allocator<Cell> >::_Vector_impl::_Vector_impl(std::allocator<Cell> const&) [90]
                0.00    0.00       1/1           std::allocator<Cell>::allocator(std::allocator<Cell> const&) [86]
-----------------------------------------------
                0.00    0.00       1/1           std::_Vector_base<Cell, std::allocator<Cell> >::~_Vector_base() [94]
[91]     0.0    0.00    0.00       1         std::_Vector_base<Cell, std::allocator<Cell> >::_Vector_impl::~_Vector_impl() [91]
                0.00    0.00       1/2           std::allocator<Cell>::~allocator() [51]
-----------------------------------------------
                0.00    0.00       1/1           std::_Vector_base<Cell, std::allocator<Cell> >::~_Vector_base() [94]
[92]     0.0    0.00    0.00       1         std::_Vector_base<Cell, std::allocator<Cell> >::_M_deallocate(Cell*, unsigned long) [92]
                0.00    0.00       1/1           __gnu_cxx::new_allocator<Cell>::deallocate(Cell*, unsigned long) [80]
-----------------------------------------------
                0.00    0.00       1/1           std::vector<Cell, std::allocator<Cell> >::vector(unsigned long, Cell const&, std::allocator<Cell> const&) [97]
[93]     0.0    0.00    0.00       1         std::_Vector_base<Cell, std::allocator<Cell> >::_Vector_base(unsigned long, std::allocator<Cell> const&) [93]
                0.00    0.00       1/1           std::_Vector_base<Cell, std::allocator<Cell> >::_Vector_impl::_Vector_impl(std::allocator<Cell> const&) [90]
                0.00    0.00       1/1           std::_Vector_base<Cell, std::allocator<Cell> >::_M_allocate(unsigned long) [89]
-----------------------------------------------
                0.00    0.00       1/1           std::vector<Cell, std::allocator<Cell> >::~vector() [98]
[94]     0.0    0.00    0.00       1         std::_Vector_base<Cell, std::allocator<Cell> >::~_Vector_base() [94]
                0.00    0.00       1/1           std::_Vector_base<Cell, std::allocator<Cell> >::_M_deallocate(Cell*, unsigned long) [92]
                0.00    0.00       1/1           std::_Vector_base<Cell, std::allocator<Cell> >::_Vector_impl::~_Vector_impl() [91]
-----------------------------------------------
                0.00    0.00       1/1           void std::uninitialized_fill_n<Cell*, unsigned long, Cell>(Cell*, unsigned long, Cell const&) [99]
[95]     0.0    0.00    0.00       1         void std::__uninitialized_fill_n<false>::__uninit_fill_n<Cell*, unsigned long, Cell>(Cell*, unsigned long, Cell const&) [95]
                0.00    0.00       2/4           Cell* std::__addressof<Cell>(Cell&) [40]
                0.00    0.00       2/2           void std::_Construct<Cell, Cell>(Cell*, Cell const&) [53]
-----------------------------------------------
                0.00    0.00       1/1           std::vector<Cell, std::allocator<Cell> >::vector(unsigned long, Cell const&, std::allocator<Cell> const&) [97]
[96]     0.0    0.00    0.00       1         std::vector<Cell, std::allocator<Cell> >::_M_fill_initialize(unsigned long, Cell const&) [96]
                0.00    0.00       1/2           std::_Vector_base<Cell, std::allocator<Cell> >::_M_get_Tp_allocator() [52]
                0.00    0.00       1/1           void std::__uninitialized_fill_n_a<Cell*, unsigned long, Cell, Cell>(Cell*, unsigned long, Cell const&, std::allocator<Cell>&) [100]
-----------------------------------------------
                0.00    0.00       1/1           main [1]
[97]     0.0    0.00    0.00       1         std::vector<Cell, std::allocator<Cell> >::vector(unsigned long, Cell const&, std::allocator<Cell> const&) [97]
                0.00    0.00       1/1           std::_Vector_base<Cell, std::allocator<Cell> >::_Vector_base(unsigned long, std::allocator<Cell> const&) [93]
                0.00    0.00       1/1           std::vector<Cell, std::allocator<Cell> >::_M_fill_initialize(unsigned long, Cell const&) [96]
-----------------------------------------------
                0.00    0.00       1/1           main [1]
[98]     0.0    0.00    0.00       1         std::vector<Cell, std::allocator<Cell> >::~vector() [98]
                0.00    0.00       1/2           std::_Vector_base<Cell, std::allocator<Cell> >::_M_get_Tp_allocator() [52]
                0.00    0.00       1/1           void std::_Destroy<Cell*, Cell>(Cell*, Cell*, std::allocator<Cell>&) [103]
                0.00    0.00       1/1           std::_Vector_base<Cell, std::allocator<Cell> >::~_Vector_base() [94]
-----------------------------------------------
                0.00    0.00       1/1           void std::__uninitialized_fill_n_a<Cell*, unsigned long, Cell, Cell>(Cell*, unsigned long, Cell const&, std::allocator<Cell>&) [100]
[99]     0.0    0.00    0.00       1         void std::uninitialized_fill_n<Cell*, unsigned long, Cell>(Cell*, unsigned long, Cell const&) [99]
                0.00    0.00       1/1           void std::__uninitialized_fill_n<false>::__uninit_fill_n<Cell*, unsigned long, Cell>(Cell*, unsigned long, Cell const&) [95]
-----------------------------------------------
                0.00    0.00       1/1           std::vector<Cell, std::allocator<Cell> >::_M_fill_initialize(unsigned long, Cell const&) [96]
[100]    0.0    0.00    0.00       1         void std::__uninitialized_fill_n_a<Cell*, unsigned long, Cell, Cell>(Cell*, unsigned long, Cell const&, std::allocator<Cell>&) [100]
                0.00    0.00       1/1           void std::uninitialized_fill_n<Cell*, unsigned long, Cell>(Cell*, unsigned long, Cell const&) [99]
-----------------------------------------------
                0.00    0.00       1/1           Solver::parseArgs(int, char**) [77]
[101]    0.0    0.00    0.00       1         __gnu_cxx::__promote_2<int, unsigned int, __gnu_cxx::__promote<int, std::__is_integer<int>::__value>::__type, __gnu_cxx::__promote<unsigned int, std::__is_integer<unsigned int>::__value>::__type>::__type std::pow<int, unsigned int>(int, unsigned int) [101]
-----------------------------------------------
                0.00    0.00       1/1           void std::_Destroy<Cell*, Cell>(Cell*, Cell*, std::allocator<Cell>&) [103]
[102]    0.0    0.00    0.00       1         void std::_Destroy<Cell*>(Cell*, Cell*) [102]
                0.00    0.00       1/1           void std::_Destroy_aux<false>::__destroy<Cell*>(Cell*, Cell*) [88]
-----------------------------------------------
                0.00    0.00       1/1           std::vector<Cell, std::allocator<Cell> >::~vector() [98]
[103]    0.0    0.00    0.00       1         void std::_Destroy<Cell*, Cell>(Cell*, Cell*, std::allocator<Cell>&) [103]
                0.00    0.00       1/1           void std::_Destroy<Cell*>(Cell*, Cell*) [102]
-----------------------------------------------
                0.00    0.00       1/1           Solver::setup() [75]
[104]    0.0    0.00    0.00       1         std::operator|(std::_Ios_Openmode, std::_Ios_Openmode) [104]
-----------------------------------------------

 This table describes the call tree of the program, and was sorted by
 the total amount of time spent in each function and its children.

 Each entry in this table consists of several lines.  The line with the
 index number at the left hand margin lists the current function.
 The lines above it list the functions that called this function,
 and the lines below it list the functions this one called.
 This line lists:
     index	A unique number given to each element of the table.
		Index numbers are sorted numerically.
		The index number is printed next to every function name so
		it is easier to look up where the function in the table.

     % time	This is the percentage of the `total' time that was spent
		in this function and its children.  Note that due to
		different viewpoints, functions excluded by options, etc,
		these numbers will NOT add up to 100%.

     self	This is the total amount of time spent in this function.

     children	This is the total amount of time propagated into this
		function by its children.

     called	This is the number of times the function was called.
		If the function called itself recursively, the number
		only includes non-recursive calls, and is followed by
		a `+' and the number of recursive calls.

     name	The name of the current function.  The index number is
		printed after it.  If the function is a member of a
		cycle, the cycle number is printed between the
		function's name and the index number.


 For the function's parents, the fields have the following meanings:

     self	This is the amount of time that was propagated directly
		from the function into this parent.

     children	This is the amount of time that was propagated from
		the function's children into this parent.

     called	This is the number of times this parent called the
		function `/' the total number of times the function
		was called.  Recursive calls to the function are not
		included in the number after the `/'.

     name	This is the name of the parent.  The parent's index
		number is printed after it.  If the parent is a
		member of a cycle, the cycle number is printed between
		the name and the index number.

 If the parents of the function cannot be determined, the word
 `<spontaneous>' is printed in the `name' field, and all the other
 fields are blank.

 For the function's children, the fields have the following meanings:

     self	This is the amount of time that was propagated directly
		from the child into the function.

     children	This is the amount of time that was propagated from the
		child's children to the function.

     called	This is the number of times the function called
		this child `/' the total number of times the child
		was called.  Recursive calls by the child are not
		listed in the number after the `/'.

     name	This is the name of the child.  The child's index
		number is printed after it.  If the child is a
		member of a cycle, the cycle number is printed
		between the name and the index number.

 If there are any cycles (circles) in the call graph, there is an
 entry for the cycle-as-a-whole.  This entry shows who called the
 cycle (as parents) and the members of the cycle (as children.)
 The `+' recursive calls entry shows the number of function calls that
 were internal to the cycle, and the calls entry for each member shows,
 for that member, how many times it was called from other members of
 the cycle.


Index by function name

  [57] _GLOBAL__sub_I__ZN11mfaAnalytic10kernelTypeE [33] Solver::getL() [51] std::allocator<Cell>::~allocator()
  [58] _GLOBAL__sub_I__ZN4CellC2Ev [5] Solver::getN()     [88] void std::_Destroy_aux<false>::__destroy<Cell*>(Cell*, Cell*)
  [59] _GLOBAL__sub_I__ZN6SolverC2Ev [74] Solver::getIn() [89] std::_Vector_base<Cell, std::allocator<Cell> >::_M_allocate(unsigned long)
  [60] _GLOBAL__sub_I_main    [75] Solver::setup()        [90] std::_Vector_base<Cell, std::allocator<Cell> >::_Vector_impl::_Vector_impl(std::allocator<Cell> const&)
   [4] k(unsigned long, unsigned long) [8] Solver::getOut() [91] std::_Vector_base<Cell, std::allocator<Cell> >::_Vector_impl::~_Vector_impl()
   [7] nIn(unsigned long, unsigned long) [76] Solver::delta_x() [92] std::_Vector_base<Cell, std::allocator<Cell> >::_M_deallocate(Cell*, unsigned long)
  [61] __static_initialization_and_destruction_0(int, int) [6] Solver::isCoagOn() [52] std::_Vector_base<Cell, std::allocator<Cell> >::_M_get_Tp_allocator()
  [62] __static_initialization_and_destruction_0(int, int) [34] Solver::getMaxRes() [93] std::_Vector_base<Cell, std::allocator<Cell> >::_Vector_base(unsigned long, std::allocator<Cell> const&)
  [63] __static_initialization_and_destruction_0(int, int) [77] Solver::parseArgs(int, char**) [94] std::_Vector_base<Cell, std::allocator<Cell> >::~_Vector_base()
  [64] __static_initialization_and_destruction_0(int, int) [78] Solver::Solver() [95] void std::__uninitialized_fill_n<false>::__uninit_fill_n<Cell*, unsigned long, Cell>(Cell*, unsigned long, Cell const&)
  [65] __static_initialization_and_destruction_0(int, int) [79] Solver::~Solver() [96] std::vector<Cell, std::allocator<Cell> >::_M_fill_initialize(unsigned long, Cell const&)
  [29] Cell::getMoments()     [80] __gnu_cxx::new_allocator<Cell>::deallocate(Cell*, unsigned long) [43] std::vector<Cell, std::allocator<Cell> >::end()
  [66] Cell::initInDist(double*) [81] __gnu_cxx::new_allocator<Cell>::allocate(unsigned long, void const*) [44] std::vector<Cell, std::allocator<Cell> >::begin()
  [13] Cell::setNumDens(unsigned long, double) [82] __gnu_cxx::new_allocator<Cell>::new_allocator(__gnu_cxx::new_allocator<Cell> const&) [97] std::vector<Cell, std::allocator<Cell> >::vector(unsigned long, Cell const&, std::allocator<Cell> const&)
  [30] Cell::updateDist()     [83] __gnu_cxx::new_allocator<Cell>::new_allocator() [98] std::vector<Cell, std::allocator<Cell> >::~vector()
  [45] Cell::initMoments()    [48] __gnu_cxx::new_allocator<Cell>::~new_allocator() [24] std::ios_base::setf(std::_Ios_Fmtflags)
   [3] Cell::getOldNumDens(unsigned long) [38] __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > >::__normal_iterator(Cell* const&) [36] std::ios_base::width(long)
  [28] Cell::calculateMoments() [49] __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > >::operator++(int) [25] std::ios_base::precision(long)
  [67] Cell::getDist()        [50] __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > >::difference_type __gnu_cxx::operator-<Cell*, std::vector<Cell, std::allocator<Cell> > >(__gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > > const&, __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > > const&) [53] void std::_Construct<Cell, Cell>(Cell*, Cell const&)
  [46] Cell::initDist(mfaAnalytic::distributions) [42] bool __gnu_cxx::operator!=<Cell*, std::vector<Cell, std::allocator<Cell> > >(__gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > > const&, __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > > const&) [40] Cell* std::__addressof<Cell>(Cell&)
  [14] Cell::getInDist(unsigned long) [15] MTRand::hiBit(unsigned long) const [99] void std::uninitialized_fill_n<Cell*, unsigned long, Cell>(Cell*, unsigned long, Cell const&)
   [2] Cell::iterateMD(Solver&, Cell&) [16] MTRand::loBit(unsigned long) const [100] void std::__uninitialized_fill_n_a<Cell*, unsigned long, Cell, Cell>(Cell*, unsigned long, Cell const&, std::allocator<Cell>&)
  [47] Cell::Cell(Cell const&) [17] MTRand::magic(unsigned long) const [22] std::abs(double)
  [68] Cell::Cell(double, double, unsigned long) [18] MTRand::twist(unsigned long, unsigned long, unsigned long) const [101] __gnu_cxx::__promote_2<int, unsigned int, __gnu_cxx::__promote<int, std::__is_integer<int>::__value>::__type, __gnu_cxx::__promote<unsigned int, std::__is_integer<unsigned int>::__value>::__type>::__type std::pow<int, unsigned int>(int, unsigned int)
  [41] Cell::~Cell()          [19] MTRand::loBits(unsigned long) const [54] void std::_Destroy<Cell>(Cell*)
  [69] MTRand::initialize(unsigned long) [20] MTRand::mixBits(unsigned long, unsigned long) const [102] void std::_Destroy<Cell*>(Cell*, Cell*)
  [70] MTRand::seed(unsigned long*, unsigned long) [84] __gnu_cxx::new_allocator<Cell>::max_size() const [103] void std::_Destroy<Cell*, Cell>(Cell*, Cell*, std::allocator<Cell>&)
  [71] MTRand::seed()         [37] __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > >::base() const [26] std::operator|=(std::_Ios_Fmtflags&, std::_Ios_Fmtflags)
  [72] MTRand::reload()       [35] __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > >::operator*() const [27] std::operator|(std::_Ios_Fmtflags, std::_Ios_Fmtflags)
  [73] MTRand::MTRand()       [85] __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > >::operator-(long const&) const [104] std::operator|(std::_Ios_Openmode, std::_Ios_Openmode)
  [23] Solver::getNoCells()   [21] __gnu_cxx::__normal_iterator<Cell*, std::vector<Cell, std::allocator<Cell> > >::operator->() const [55] std::basic_string<char, std::char_traits<char>, std::allocator<char> > std::operator+<char, std::char_traits<char>, std::allocator<char> >(std::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, char const*)
  [31] Solver::writeMoments(int, double*) [86] std::allocator<Cell>::allocator(std::allocator<Cell> const&) [39] std::basic_string<char, std::char_traits<char>, std::allocator<char> > std::operator+<char, std::char_traits<char>, std::allocator<char> >(std::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> > const&)
  [32] Solver::isNumberDensityRep() [87] std::allocator<Cell>::allocator() [56] operator new(unsigned long, void*)
