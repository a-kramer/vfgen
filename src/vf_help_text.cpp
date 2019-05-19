#include <string>
#include <map>

using namespace std;


const string help_adolc =
"use: vfgen adolc vector_field_file.vf\n\n"
"This command creates a C++ function that can be used with the ADOL-C library.\n"
"Two files are created:\n"
"    [name]_adolc.cpp\n"
"    [name]_adolc.h\n"
"The file [name]_adolc.cpp contains the function\n"
"    [name]_vf(short int tag, double *y_, double *f_, double *params_)\n"
"The code in this function uses the ADOL-C data types adouble and adoublev,\n"
"and wraps the actual computation of the vector field inside trace_on(tag)\n"
"and trace_off(tag) statement.\n\n"
"Options: none.\n";

const string help_auto =
"use:  vfgen auto vector_field_file.vf\n\n"
"This command generates a C or FORTRAN file to be used with the AUTO\n"
"continuation software.  A single file is created, called [name]_avf.c\n"
"(or [name]_avf.f if the option lang=fortran is used) where [name] is the\n"
"Name attribute of the VectorField entity in the vector field file.\n\n"
"Options: (default is listed first)\n"
"lang=c|fortran\n"
"    Specify the language in which to write the AUTO equations file.\n"
"    For AUTO2000, use C (the default).  For AUTO07p, either C or FORTRAN\n"
"    may be used.\n";

const string help_check =
"use: vfgen check vector_field_file.vf\n\n"
"This command prints information from the vector field file.  It can be used to\n"
"to check for errors before using another command.\n\n"
"Options: none.\n";

const string help_cvode =
"use: vfgen cvode vector_field_file.vf\n"
"     vfgen cvode:option=value,...,option=value vector_field_file.vf\n\n"
"This command generates code to be used with the CVODE library (which is part\n"
"of the SUNDIALS suite).\n"
"With no options, two files are created:\n"
"    [name]_cv.c\n"
"    [name]_cv.h\n"
"where [name] is the Name attribute of the VectorField entity in the vector\n"
"field file.  The file [name]_cv.c will define the C functions [name]_vf() and\n"
"[name]_jac().\n\n"
"Options: (default is listed first)\n"
"version=2.7.0|2.6.0|2.5.0|2.4.0|2.3.0\n"
"    This option determines of version of CVODE for which code is generated.\n"
"func=no|yes\n"
"    By default, any user function defined in the vector field file is not\n"
"    defined in [name]_cv.c.  If the option func=yes is given, the function\n"
"    [name]_func() will be defined.  This function will fill in an array with\n"
"    values that are the user defined functions.\n"
"demo=no|yes\n"
"    If the option demo=yes is given, two more files are created:\n"
"        [name]_cvdemo.c\n"
"        Makefile-[name]_cvdemo\n"
"    where [name] is the Name attribute of the VectorField entity in the\n"
"    vector field file.  This program provides a simple command-line solver.\n"
"    It takes arguments in the form name=value, where name can be a state\n"
"    variable (to give an initial condition), a parameter (to give the value\n"
"    of a parameter), or one of abserr, relerr or stoptime, to control the ODE\n"
"    solver.  The output of the program consists of columns of numbers; the\n"
"    first column is the time, and the rest are the state variables.\n";

const string help_dde23 =
"use: vfgen dde23 vector_field_file.vf\n"
"     vfgen dde23:option=value,...,option=value vector_field_file.vf\n\n"
"This command creates a MATLAB file that can be used with the DDE23 delay\n"
"equation solver.  The file is [name]_dde23.m, where [name] is the Name\n"
"attribute of the VectorField entity in the vector field file.\n\n"
"Options: (default is listed first)\n"
"parstyle=vector|list\n"
"    This option controls how parameters are passed to the function defined in\n"
"    the file [name]_dde23.m.  By default (parstyle=vector), the parameters are\n"
"    stored in a single array.  If the option parstyle=list is given, the\n"
"    parameters are all listed separately as arguments.\n"
"demo=no|yes\n"
"    If the option demo=yes is given, the file [name]_dde23_demo.m is created.\n"
"    This defines the MATLAB function [name]_dde23_demo(stoptime), which uses\n"
"    the DDE23 function with the default parameter values and initial conditions\n"
"    to plot a solution to the system.\n";

const string help_ddebiftool =
"use: vfgen ddebiftool vector_field_file.vf\n"
"     vfgen ddebiftool:path=/path/to/ddebiftool vector_field_file.vf\n\n"
"This command creates the files sys_init.m, sys_rhs.m, sys_deri.m and sys_tau.m,\n"
"to be used with the MATLAB software package DDE-BIFTOOL.\n"
"Note: Currently, VFGEN only generates DDE-BIFTOOL files for systems with\n"
"constant delays.\n\n"
"Options:\n"
"path=/path/to/ddebiftool\n"
"    The 'path' option allows the user to specify a directory that is added to\n"
"    the MATLAB search path in the file sys_init.m.\n";

const string help_dde_solver =
"use: vfgen dde_solver vector_field_file.vf\n"
"     vfgen dde_solver:demo=yes vector_field_file.vf\n\n"
"This command creates a Fortran 90 file that can be used with the DDE solver\n"
"written by S. Thompson and L. F. Shampine.  The file created is [name].f90.\n\n"
"Options: (default is listed first)\n"
"demo=no|yes\n"
"    If the option demo=yes is given, the file [name]_demo.f90 is created.\n"
"    This program will use [name].f90 to generate a solution to the delay\n"
"    equations.\n";

const string help_delay2ode =
"use: vfgen delay2ode vector_field_file.vf\n"
"     vfgen delay2ode:option=value,...,option=value vector_field_file.vf\n\n"
"This command generates a new vector field file that is a finite dimensional\n"
"approximation to a delay equation.  The approximation is created by dividing\n"
"each delay into N smaller delays, and then approximating each fractional\n"
"delay with an Taylor series truncated at order p.\n\n"
"The new vector field file is written to 'standard output', so to use this\n"
"command, one usually redirects the output to a file. For example,\n"
"    vfgen delay2ode mydelay.vf > mydelay_2ode.vf\n\n"
"Options:\n"
"p=1|2|3\n"
"    The order of the Taylor approximation of the fractional delay step.\n"
"    The default is p=1.\n"
"N=integer\n"
"    The number of fractional delay steps into which each delay is split.\n"
"    The default is N=10.\n";

const string help_dstool =
"use: vfgen dstool vector_field_file.vf\n\n"
"This command creates a C definition file for the vector field to be used\n"
"with DSTOOL. The name of the file is [name]_def.c.\n\n"
"Options: none.\n";

const string help_evf =
"use: vfgen evf vector_field_file.vf\n\n"
"This command generates a new vector field file, in which the original vector\n"
"field has been extended with its variational equations.\n\n"
"The new vector field file is written to 'standard output', so to use this\n"
"command, one usually redirects the output to a file. For example,\n"
"    vfgen evf system.vf > system_evf.vf\n\n"
"Options:\n"
"par=p\n"
"    p must be the Name of a Parameter in the vector field file.\n"
"    If this option is given, the extension of the vector field is the variation\n"
"    with respect to the parameter.  That is, the vector field F(x) is extended\n"
"    with\n"
"        v' = (DF(x)/dx)v + DF(x)/dp\n"
"    This extended system allows for computing the sensitivity of a solution\n"
"    with respect to a parameter.\n"
"    If this option is not given, the vector field is simply extended with\n"
"        v' = (DF(x)/dx)v\n";

const string help_gsl =
"use: vfgen gsl vector_field_file.vf\n"
"     vfgen gsl:option=value,...,option=value vector_field_file.vf\n\n"
"This command generates a C file containing functions to be used with the\n"
"GNU Scientific Library (GSL) ODE suite.  The files that it creates are:\n"
"    [name]_gvf.c\n"
"    [name]_gvf.h\n"
"where [name] is the Name attribute of the VectorField entity in the vector\n"
"field file.  The file [name]_gvf.c will define the C functions [name]_vf(),\n"
"[name]_jac(), and [name]_jacp(). These compute the vector field, its Jacobian\n"
"matrix, and the derivatives of the vector field with respect to the parameters.\n\n"
"Options: (default is listed first)\n"
"func=no|yes\n"
"    If the option func=yes is given, the user functions defined in the\n"
"    vector field file are implemented as C functions in [name]_gvf.c.\n"
"    The name of the function will be [name]_[funcname](), where [name]\n"
"    is the Name attribute of the VectorField entity, and [funcname] is\n"
"    the Name attribute of the Function entity.\n"
"demo=no|yes\n"
"    If the option demo=yes is given, two more files are created:\n"
"        [name]_solver.c\n"
"        Makefile-[name]\n"
"    where [name] is the Name attribute of the VectorField entity in the\n"
"    vector field file.  This program provides a simple command-line solver.\n"
"    It takes arguments in the form name=value, where name can be a state\n"
"    variable (to give an initial condition), a parameter (to give the value\n"
"    of a parameter), or one of abserr, relerr or stoptime, to control the ODE\n"
"    solver.  The output of the program consists of columns of numbers; the\n"
"    first column is the time, and the rest are the state variables.\n";

const string help_help =
"use: vfgen help <command>\n\n"
"The help command will print a short description of the given <command>.\n"
"For example,\n"
"    vfgen help cvode\n"
"prints a description of the cvode command.\n";

const string help_javascript =
"use: vfgen javascript vector_field_file.vf\n"
"     vfgen javascript:option=value,... vector_field_file.vf\n\n"
"This command creates Javascript functions for computing a Taylor polynomial\n"
"approximation of the solution to the differential equations.\n"
"The file created is [name].js, where [name] is the Name attribute of the\n"
"VectorField entity in the vector field file.  The Javascript file contains\n"
"the functions [name]_vf and [name]_evaltaylor[r], where [r] is the order of\n"
"the Taylor polynomial. The first computes the vector field, and the second\n"
"computes the Taylor approximation. Also defined in the Javascript file are the\n"
"functions [name]_diff[k], for k=1, 2, ..., r-1. These functions compute the\n"
"k-linear differentials DkF(X)[V1,...,Vk]. These could be useful in programs\n"
"that analyze bifurcations or that compute invariant manifolds.\n\n"
"Options: (default is listed first)\n"
"demo=no|yes\n"
"    If the option demo=yes is given, two additional files are created:\n"
"    [name].html and [name]_solverdemo.js.  The code in [name]_solverdemo.js\n"
"    uses the functions defined in [name].js to implement a Taylor method solver\n"
"    with an adaptive step size.  The HTML file [name].html creates an interface\n"
"    to this solver.  The interfaces provides a form for defining the parameters\n"
"    and initial conditions, and allows some additional solver parameters to be\n"
"    changed.  It also has a graphical display of a phase-space projection of the\n"
"    solution.  The demo should work in any browser that has Javascript enabled\n"
"    and that supports the <canvas> tag in HTML.\n"
"order=[integer]\n"
"    The order of the Taylor polynomial. The default is order=5.\n";

const string help_latex =
"use: vfgen latex vector_field_file.vf\n\n"
"This command generate a LaTeX fragment for the vector field, in a file called\n"
"[name].tex, where [name] is the Name attribute of the VectorField entity in\n"
"the vector field file. The vector field will be defined inside nested\n"
"'equation' and 'split' environments. (The 'split' environment is provided\n"
"by the AMSMATH LaTeX package.)\n\n"
"Options: none.\n";

const string help_lsoda =
"use: vfgen lsoda vector_field_file.vf\n"
"     vfgen lsoda:option=value,option=value,... vector_field_file.vf\n\n"
"This command creates the Fortran file [name]_rhs.f, which defines the vector\n"
"field and its Jacobian in subroutines to be used with the Fortran 77 ODE solvers\n"
"LSODA, LSODAR or LSODE from the ODEPACK suite.  The subroutines defined in the\n"
"file are\n"
"    [name]_rhs    The vector field\n"
"    [name]_jac    The Jacobian of the vector field\n\n"
"Options: (default is listed first)\n"
"func=no|yes\n"
"    If the option func=yes is given, VFGEN creates a subroutine that computes\n"
"    the values of any Functions that were defined in the vector field file. The\n"
"    subroutine is designed to be used with the rootfinding capability of the\n"
"    LSODAR solver.\n"
"demo=no|yes\n"
"    If the option demo=yes is given, the file [name]_demo.f is also created.\n"
"    This program provides a sample driver for the LSODA subroutine. The initial\n"
"    conditions and parameter values are the default values defined in the vector\n"
"    field file.\n"
"parstyle=after|common\n"
"    There are two methods for passing parameters to the vector field and\n"
"    Jacobian functions:  include them in the array that holds the state\n"
"    variables, or put them in a named common block. The parstyle option\n"
"    indicates which method to use. If the option parstyle=common is given, the\n"
"    parameters are put in a common block with the name [name]_parameters, where\n"
"    [name] is the name of the vector field. If the option parstyle=after is\n"
"    given, the parameters are included in the state variable vector, beginning\n"
"    just after the last state variable.\n";

const string help_matcont =
"use: vfgen matcont vector_field_file.vf\n\n"
"This command generates a MATLAB file to be used with the MATCONT and\n"
"CL_MATCONT programs.  The name of the file is [name].m, where [name]\n"
"is the Name attribute of the VectorField entity in the vector field file.\n\n"
"Options: none.\n";

const string help_matlab =
"use: vfgen matlab vector_field_file.vf\n"
"     vfgen matlab:option=value,...,option=value vector_field_file.vf\n\n"
"This command generates MATLAB files to be used with the MATLAB ODE solvers.\n"
"The files created are:\n"
"    [name]_vf.m     The vector field\n"
"    [name]_jac.m    The Jacobian of the vector field\n"
"    [name]_jacp.m   Derivatives of the vector field with resperct to the\n"
"                    parameters.\n"
"    [name]_hess.m   The Hessians of the vector field\n"
"    [name]_der3.m   The third order derivatives of the vector field\n"
"where [name] is the Name attribute of the VectorField entity in the\n"
"vector field file. (Only the first two are actually used by MATLAB's\n"
"ODE solvers.)\n\n"
"Options: (default is listed first)\n"
"parstyle=vector|list\n"
"    This option controls how parameters are passed to the functions. By\n"
"    default (parstyle=vector), the parameters are in a single array.\n"
"    If the option parstyle=list is given, the parameters are all listed\n"
"    separately as arguments.\n"
"demo=no|yes\n"
"    If the option demo=yes is given, the file [name]_demo.m is created.\n"
"    This defines the MATLAB function [name]_demo, which creates a simple\n"
"    user interface with fields for the parameter values and initial\n"
"    conditions, and a button that will generate and plot a solution.\n"
"func=no|yes\n"
"    If the option func=yes is given, the file [name]_[funcname].m will be\n"
"    created for each user function.\n"
"evf=no|yes\n"
"    If the option evf=yes is given, the file [name]_evf.m is created. This\n"
"    file defines a function that computes the extended vector field consisting\n"
"    of the original vector field and the variational equations. This returns a\n"
"    2N dimensional column vector. (Note: The EVF command is probably a better\n"
"    alternative, because you can then use VFGEN to create the Jacobian of the\n"
"     extended vector field.)\n";

const string help_octave =
"use: vfgen octave vector_field_file.vf\n"
"     vfgen octave:option=value,...,option=value vector_field_file.vf\n\n"
"This command generates an OCTAVE file, [name].m, to be used with the OCTAVE\n"
"ODE solver lsode, where [name] is the Name attribute of the VectorField defined\n"
"in the vector field file. The file contains functions for the vector field, the\n"
"Jacobian, and, if the option func=yes was given, the user-defined functions.\n\n"
"Options: (default is listed first)\n"
"parstyle=global|vector|list\n"
"    This option controls how parameters are passed to the vector field and\n"
"    Jacobian functions. By default (parstyle=global), a global variable is used.\n"
"    If parstyle=vector, the parameters passed to the functions in a single array.\n"
"    If parstyle=list, the parameters are passed as separate arguments.\n"
"demo=no|yes\n"
"    If the option demo=yes is given, the file [name]_demo.m is created.\n"
"    This OCTAVE script generates a plot of a solution to the differential\n"
"    equations.  The default parameter values and initial conditions are\n"
"    used.\n"
"func=no|yes\n"
"    If the option func=yes is given, the file [name].m will define a\n"
"    function for each user function given in the vector field file.\n";

const string help_pddecont =
"use: vfgen pddecont vector_field_file.vf\n\n"
"This command creates the file sys-[name].cpp to be used with the PDDE-CONT\n"
"software package.  PDDE-CONT does continuation and bifurcation computations\n"
"for delay differential equations.\n\n"
"Options: none.\n";

const string help_pydstool =
"use: vfgen pydstool vector_field_file.vf\n"
"     vfgen pydstool:demo=yes vector_field_file.vf\n\n"
"This command creates a Python file that can be used to define a differential\n"
"equation for the software package PyDSTool.  The file [name].py defines the\n"
"function args(), which creates an 'args' object for the vector field.\n\n"
"Options: (default is list first)\n"
"demo=no|yes\n"
"    If the option demo=yes is given, the file [name]_dst.py is also created.\n"
"    This file contains a script that uses the function defined in [name].py\n"
"    to generate and plot a solution to the differential equation.\n";

const string help_pygsl =
"use: vfgen pygsl vector_field_file.vf\n"
"     vfgen pygsl:option=value,...,option=value vector_field_file.vf\n\n"
"This command creates Python files that can be used with the PyGSL Python\n"
"library. The files created are [name].py and, if the option demo=yes option\n"
"is given, [name]_demo.py, where [name] is the Name attribute of the VectorField\n"
"entity in the vector field file. The Python file [name].py will contain the\n"
"functions vectorfield(...), jacobian(...), and, if the func=yes option is\n"
"given, a function for each user-defined function.\n\n"
"Options: (default is listed first)\n"
"func=no|yes\n"
"    If the option func=yes is given, VFGEN also converts any user-defined\n"
"    functions in the vector field file into functions in the Python file.\n"
"    The names of the functions will be the same as those given in the vector\n"
"    field file.\n"
"demo=no|yes\n"
"    If the option demo=yes is given, the file [name]_demo.py will contain a\n"
"    Python script for a command-line ODE solver for the vector field. The\n"
"    initial conditions and parameters can be specified on the command line.\n"
"    The program will print the solution data to the console.\n";

const string help_r =
"use: vfgen r vector_field_file.vf\n\n"
"This command creates the file [name].R, which defines the vector field\n"
"and its Jacobian in subroutines to be used with the R package deSolve.\n"
"The subroutines defined in the file are\n"
"    [name]       The vector field\n"
"    [name]_jac   The Jacobian of the vector field\n"
"\n"
"Options: (default is listed first)\n"
"func=no|yes\n"
"    If the option func=yes is given, the file [name].R will define two\n"
"    functions for each user-defined function in the vector field file.\n"
"    The functions are:\n"
"        [name]_sol_[funcname](sol, parameters)\n"
"            Arguments are a solution and the vector field parameters.\n"
"            Returns a vector containing the function values at each point\n"
"            in the solution.\n"
"        [name]_[funcname](t, state, parameters)\n"
"            Returns the function at a specific time and state.\n"
"demo=no|yes\n"
"    If the option demo=yes is given, the file [name]_demo.R is also created.\n"
"    This file contains a simple demonstration of the use of the functions\n"
"    defined in [name].R\n";

const string help_radau5 =
"use: vfgen radau5 vector_field_file.vf\n"
"     vfgen radau5:demo=yes vector_field_file.vf\n\n"
"This command creates the file [name]_rhs.f, which defines the vector field\n"
"and its Jacobian in subroutines to be used with the Fortran 77 ODE solver\n"
"RADAU5.  The subroutines defined in the file are\n"
"    [name]_rhs    The vector field\n"
"    [name]_jac    The Jacobian of the vector field\n"
"    [name]_sol    A subroutine that prints a point of the solution.\n\n"
"Options: (default is listed first)\n"
"demo=no|yes\n"
"    If the option demo=yes is given, the file [name]_dr5.f is also created.\n"
"    This program provides a driver that will generated a solution to equations\n"
"    by calling RADAU5.  The initial conditions and parameters of the solution\n"
"    are the default values given in the vector field file.\n";

const string help_scilab =
"use: vfgen scilab vector_field_file.vf\n"
"     vfgen scilab:option=value,...,option=value vector_field_file.vf\n\n"
"This command creates files to be used with Scilab. The main file created\n"
"is [name].sci, where [name] is the Name attribute of the VectorField\n"
"entity in the vector field file. The Scilab functions in this file are\n"
"    [name]_vf(t,x,p)\n"
"    [name]_jac(t,x,p)\n\n"
"Options: (default is listed first)\n"
"parstyle=vector|list\n"
"    The method by which parameters are passed to the Scilab functions\n"
"    generated by VFGEN is controlled by the parstyle option. When\n"
"    parstyle=list is given as\n"
"        $ vfgen scilab:parstyle=list vector_field_file.vf\n"
"    each parameter is listed explicitly as an argument of Scilab functions.\n"
"    That is, instead of [name]_vf(t,x,p), the vector field function will be\n"
"    [name]_vf(t,x,param1,param2,...,paramM).\n"
"func=no|yes\n"
"    If the option func=yes is given, a Scilab function will be created for\n"
"    each user-defined function.\n"
"demo=no|yes\n"
"    If the option demo=yes is given, a second file is created called\n"
"    [name]_demo.sce. This is a script that when run provides a simple GUI\n"
"    interface to the initial conditions, system parameters, and the ODE\n"
"    solver parameters. It will call the odeint function and plot the\n"
"    solution. Run the script in Scilab with the command\n"
"        -->exec [name]_demo.sce;\n";

const string help_scipy =
"use: vfgen scipy vector_field_file.vf\n"
"     vfgen scipy:option=value,...,option=value vector_field_file.vf\n\n"
"This command generates Python files to be used with the SciPy library.\n"
"The files created are [name].py and, if the option demo=yes option is\n"
"given, [name]_demo.py, where [name] is the Name attribute of the VectorField\n"
"entity in the vector field file. The Python file [name].py will contain the\n"
"functions vectorfield(...) and jacobian(...).\n\n"
"Options: (default is listed first)\n"
"func=no|yes\n"
"    If the option func=yes is given, VFGEN also converts any user-defined\n"
"    functions in the vector field file into functions in the Python file.\n"
"    The names of the functions will be the same as those given in the vector\n"
"    field file.\n"
"demo=no|yes\n"
"    If the option demo=yes is given, the file [name]_demo.py will contain a\n"
"    Python script for a command-line ODE solver for the vector field. The\n"
"    initial conditions and parameters can be specified on the command line.\n"
"    The program will print the solution data to the console.\n";

const string help_taylor =
"use: vfgen taylor vector_field_file.vf\n"
"     vfgen taylor:order=[integer] vector_field_file.vf\n\n"
"This command creates C functions for computing a Taylor polynomial\n"
"approximation of the solution to the differential equations.\n"
"The files created are [name]_taylor[r].c and [name]_taylor[r].h, where [name]\n"
"is the Name attribute of the VectorField entity in the vector field file, and\n"
"[r] is the order given with the order option.  The C file [name]_taylor[r].c\n"
"will contain the functions [name]_vf and [name]_taylor[r]. The first computes\n"
"the vector field, and the second computes the Taylor approximation. Also defined\n"
"in the C file are the functions [name]_diff[k], for k=1, 2, ..., r-1. These\n"
"functions compute the k-linear differentials DkF(X)[V1,...,Vk]. These could be\n"
"useful in programs that analyze bifurcations or that compute invariant\n"
"manifolds.\n\n"
"Options:\n"
"order=[integer]\n"
"    The order of the Taylor polynomial. The default is order=5.\n";

const string help_xml =
"use: vfgen xml vector_field_file.vf\n"
"This command regenerates an XML version of the input file and writes\n"
"it to the terminal.\n"
"Options: none.\n";

const string help_xpp =
"use: vfgen xpp vector_field_file.vf\n"
"     vfgen xpp:option=value,...,option=value vector_field_file.vf\n\n"
"This command creats a file to be used with XPP (aka XPP-AUT).\n"
"The name of the file created by this command is [name].ode, where\n"
"[name] is the Name attribute of the VectorField entity in the vector\n"
"field file.\n\n"
"Options:\n"
"extra=[text]\n"
"    The option extra=[text] allows the user to customize the ODE file with\n"
"    additional lines. The characters in text are added to a section of the\n"
"    ODE file. Any semi-colons in text are converted to newlines. For example,\n"
"    extra=\"@ total=100;@ maxstor=10000\" will add the lines\n"
"        @ total=100\n"
"        @ maxstor=10000\n"
"    to the ODE file. (A final semi-colon in text is optional.)\n"
"    Note: text must not contain any commas.\n";


map<const string, const string> help_text = {
    {"adolc",       help_adolc},
    {"auto",        help_auto},
    {"check",       help_check},
    {"cvode",       help_cvode},
    {"dde23",       help_dde23},
    {"ddebiftool",  help_ddebiftool},
    {"dde_solver",  help_dde_solver},
    {"delay2ode",   help_delay2ode},
    {"dstool",      help_dstool},
    {"evf",         help_evf},
    {"gsl",         help_gsl},
    {"help",        help_help},
    {"javascript",  help_javascript},
    {"latex",       help_latex},
    {"lsoda",       help_lsoda},
    {"matcont",     help_matcont},
    {"matlab",      help_matlab},
    {"octave",      help_octave},
    {"pddecont",    help_pddecont},
    {"pydstool",    help_pydstool},
    {"pygsl",       help_pygsl},
    {"r",           help_r},
    {"radau5",      help_radau5},
    {"scilab",      help_scilab},
    {"scipy",       help_scipy},
    {"taylor",      help_taylor},
    {"xml", 		help_xml},
    {"xpp",         help_xpp}
};
