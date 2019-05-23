
//
//  vf_boostodeint.cpp
//
//  This file defines the VectorField::PrintBoostOdeint method.
//
//
//  Copyright (C) 2019 Warren Weckesser
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License, Version 2, as
//  published by the Free Software Foundation.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License along
//  with this program.  The file LICENSE-GPL2 in the VFGEN source directory
//  contains a copy. You may also obtain a copy by writing to the Free Software
//  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//

#include <fstream>
#include <sstream>
#include <string>
#include <ginac/ginac.h> 

#include "vf.h"
#include "vf_utils.h"

using namespace std;
using namespace GiNaC;


/*
 * Idea:
 * if method is default:
 *     if there are no parameters
 *         system is defined using a function
 *     else
 *         system is defined using a class with operator()
 * elif method is implicit
 *     if there are no parameters
 *         system is defined with two functions
 *     else
 *         system is defined with a class, with two member functions
 *         called vf and jac.  To create the system argument (a pair),
 *         first create an instance of the class, and then create the
 *         pair using lambdas. For example, something like this:
 *             auto lor = lorenz(3, 5, 7);
 *             auto vf = [&lor](...args...) {return lor.vf(...args...);};
 *             auto jac = [&lor](...args...) {return lor.jac(...args...);}
 *             auto sys = make_pair(vf, jac)
 *         Then pass sys to the integration function.
 */

//
// PrintBoostOdeint -- The Boost Odeint Code Generator.
//

void VectorField::PrintBoostOdeint(map<string,string> options)
{
    int np;
    //int nc, nv, na, nf;

    symbol t(IndependentVariable);
    np = parname_list.nops();
    //nc = conname_list.nops();
    //nv = varname_list.nops();
    //na = exprname_list.nops();
    //nf = funcname_list.nops();

    if ((options["system"] != "default") && (options["system"] != "")) {
        cerr << "Sorry, only 'system=default' is implemented.\n";
        exit(-1);
    }
    string filename = Name()+"_vf.cpp";
    ofstream fout;
    fout.open(filename.c_str());
    fout << csrc << left;

    string pfilename = Name()+"_vf.h";
    ofstream pout;
    pout.open(pfilename.c_str());
    pout << csrc << left;

    //
    //  Print the class method definitions to fout.
    //
    fout << "//" << endl;
    fout << "//  " << filename << endl;
    fout << "//" << endl;
    fout << "//  Method definitions for the vector field named: " << Name() << endl;
    fout << "//" << endl;
    PrintVFGENComment(fout, "//  ");
    fout << "//" << endl;
    fout << endl;

    fout << "#include \"" << pfilename << "\"" << endl;
    fout << endl;
    fout << "void " << Name() << "_vf";
    if (np > 0) {
        fout << "::operator()";
    }
    fout << "(const state_type &x_, state_type &dxdt_, const double t_)" << endl;
    fout << "{" << endl;
    if (HasPi) {
        fout << "    const double Pi = M_PI;\n";
    }
    AssignNameValueLists(fout, "    const double ", conname_list, "=", convalue_list, ";");
    CDeclare_double(fout, varname_list);
    CDeclare_double(fout, exprname_list);
    fout << endl;
    GetFromVector(fout, "    ", varname_list, "=", "x_", "[]", 0, ";");
    fout << endl;
    AssignNameValueLists(fout, "    ", exprname_list, "=", exprformula_list, ";");
    SetVectorFromNames(fout, "    ", "dxdt_", varvecfield_list, "[]", 0, ";");
    fout << "}" << endl;
    fout << endl;

    //
    // Print the class declaration to pout.
    //
    pout << "//" << endl;
    pout << "//  " << pfilename << endl;
    pout << "//" << endl;
    pout << "//  Class definition for the vector field " << Name() << endl;
    pout << "//" << endl;
    PrintVFGENComment(pout,"//  ");
    pout << "//" << endl;
    pout << endl;

    pout << "#ifndef " << Name() << "_VF_H" << endl;
    pout << "#define " << Name() << "_VF_H" << endl;
    pout << endl;
    pout << "#include <vector>" << endl;
    pout << "#include <math.h>" << endl;
    pout << endl;
    pout << "typedef std::vector<double> state_type;" << endl;
    pout << endl;
    //
    //  Print the vector field class.
    //
    pout << "//" << endl;
    pout << "//  The vector field." << endl;
    pout << "//" << endl;
    pout << endl;
    if (np > 0) {
        pout << "class " << Name() << "_vf" << endl;
        pout << "{" << endl;
        CDeclare_double(pout, parname_list);
        pout << endl;
        pout << "public:" << endl;
        pout << "    " << Name() + "_vf" << "(";
        PrintTransformedList(pout, "double $_", parname_list);
        pout << ") : ";
        PrintTransformedList(pout, "$($_)", parname_list);
        pout << " {}" << endl;
        pout << endl;
    }
    if (np > 0) {
        pout << "    void operator()";
    }
    else {
        pout << "void " << Name() + "_vf";
    }
    pout << "(const state_type &x_, state_type &dxdt_, const double t_);" << endl;
    if (np > 0) {
        pout << "};" << endl;
    }
    pout << endl;
    pout << "#endif" << endl;

    fout.close();
    pout.close();

    if (options["demo"] == "yes") {
        string tfilename = Name()+"_demo.cpp";
        ofstream tout;
        tout.open(tfilename.c_str());
        tout << "#include <iostream>" << endl;
        tout << "#include <vector>" << endl;
        tout << "#include <cmath>" << endl;
        tout << "#include <boost/numeric/odeint.hpp>" << endl;
        tout << "#include <boost/numeric/odeint/stepper/bulirsch_stoer_dense_out.hpp>" << endl;
        tout << endl;
        tout << "#include \"" << Name() << "_vf.h\"" << endl;
        tout << endl;
        tout << "using namespace std;" << endl;
        tout << "using namespace boost::numeric::odeint;" << endl;
        tout << endl;
        tout << "void writer(const state_type &y, const double t)" << endl;
        tout << "{" << endl;
        tout << "    cout << t;" << endl;
        tout << "    for (auto v : y) {" << endl;
        tout << "        cout << \" \" << v;" << endl;
        tout << "    }" << endl;
        tout << "    cout << endl;" << endl;
        tout << "}" << endl;
        tout << endl;
        tout << "int main(int argc, char *argv[])" << endl;
        tout << "{" << endl;

        if (HasPi) {
            tout << "    const double Pi = M_PI;\n";
        }
        AssignNameValueLists(tout, "    const double ", conname_list, "=", convalue_list, ";");

        tout << "    state_type y_{";
        PrintList(tout, vardefic_list);
        tout << "};" << endl;
        tout << "    double t0 = 0.0;" << endl;
        tout << "    double tfinal = 100.0;" << endl;
        tout << "    double dt = 0.01;" << endl;

        tout << endl;
        tout << "    bulirsch_stoer_dense_out<state_type> stepper(1e-9, 1e-9, 1.0, 0.0);" << endl;
        
        if (np > 0) {
            tout << "    auto " << Name() << " = " << Name() + "_vf(";
            PrintList(tout, pardefval_list);
            tout << ");" << endl;
        }

        tout << "    integrate_const(stepper, ";
        if (np > 0) {
            tout << Name();
        }
        else {
            tout << Name() + "_vf";
        }
        tout << ", y_, t0, tfinal, dt, writer);" << endl;
        tout << "}" << endl;
        tout.close(); 
    }
}