/*
 * Copyright (C) 2023 Mehri Bagheri-Mohmadi-Pour
 *  
 * This file is part of nftbart.
 * nftdart.h
 *
 * nftbart is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * nftbart is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Author contact information: mehri@uwm.edu
 *
 */

// A C++ class definition named nftdart. This class defines various member functions and data members.

#ifndef GUARD_nftdart_h
#define GUARD_nftdart_h

class nftdart {
public:
  nftdart() { } //The class has a default constructor nftdart(), which initializes the class.
  void setdart(double _a, double _b, int *_grp, bool _aug, bool _dart,
               double _rho=0., double _theta=0., double _omega=1.) { grp= new double[p];
      for(size_t i=0; i<p; ++i) grp[i]=_grp[i];
      if(_rho==0.) for(size_t i=0; i<p; ++i) _rho += 1./grp[i];
      this->setdart(_a, _b, _rho, _aug, _dart, _theta, _omega);} //A member function.
  void setdart(double _a, double _b, double _rho, bool _aug, bool _dart,
         double _theta=0., double _omega=1.) {
      this->a=_a; this->b=_b; this->rho=_rho; this->aug=_aug;
      this->dart=_dart; this->omega=_omega;
      if(_theta==0.){
        this->const_theta=false;
        this->theta=1.;
      }
      else{
        this->const_theta=true;
        this->theta=_theta;
      }
 }
  void startdart() {this->dartOn=!(this->dartOn);}
  double gettheta(void) { return theta; } //Returns a double value, theta.
   std::vector<size_t>& getnv() {return nv;} // Returns a reference to a std::vector of size_t values, named nv.
   std::vector<double>& getpv() {return pv;} // Returns a reference to a std::vector of double values, named pv.
   void setpv(double *varprob) { // A member function for setting the pv vector based on an input array varprob.
     for(size_t j=0;j<p;j++) pv[j]=varprob[j];
   }
  //draw function
protected:
    //Member Variables
int p;
bool dart,dartOn,aug,const_theta;
double a,b,rho,theta,omega;  
double *grp;
   std::vector<size_t> nv; // std::vector containers, which hold size_t
   std::vector<double> pv, lpv; // std::vector containers, which hold double values
};

////------------------
////constructor
//bart::bart():m(200),t(m),pi(),p(0),n(0),x(0),y(0),xi(),allfit(0),r(0),ftemp(0),di(),dartOn(false),accept(0.),grp(0) {}
//bart::bart(size_t im):m(im),t(m),pi(),p(0),n(0),x(0),y(0),xi(),allfit(0),r(0),ftemp(0),di(),dartOn(false),accept(0.),grp(0) {}
//bart::bart(const bart& ib):m(ib.m),t(m),pi(ib.pi),p(0),n(0),x(0),y(0),xi(),allfit(0),r(0),ftemp(0),di(),dartOn(false),accept(0.),grp(0)
//{
//   this->t = ib.t;
//}
//bart::~bart()
//{
//   if(allfit) delete[] allfit;
//   if(r) delete[] r;
//   if(ftemp) delete[] ftemp;
//   if(grp) delete[] grp;
//}
////------------------
//void bart::draw(double sigma, rn& gen)
//{
//   size_t i=0;
//   for(size_t j=0;j<m;j++) {
//      fit(t[j],xi,p,n,x,ftemp);
//      for(size_t k=0;k<n;k++) {
//         allfit[k] = allfit[k]-ftemp[k];
//         r[k] = y[k]-allfit[k];
//      }
//      if(bd(t[j],xi,di,pi,sigma,nv,pv,aug,gen)) i++;
//      drmu(t[j],xi,di,pi,sigma,gen);
//      fit(t[j],xi,p,n,x,ftemp);
//      for(size_t k=0;k<n;k++) allfit[k] += ftemp[k];
//   }
//   accept=i/(double)m;
//   if(dartOn) {
//     if(grp) draw_s_grp(nv,lpv,theta,gen,grp,rho);
//     else draw_s(nv,lpv,theta,gen);
//     draw_theta0(const_theta,theta,lpv,a,b,rho,gen);
//     for(size_t j=0;j<p;j++) pv[j]=::exp(lpv[j]);
//   }
//}
////------------------
////public functions
//void bart::pr() //print to screen
//{
//   cout << "*****bart object:\n";
//   cout << "m: " << m << std::endl;
//   cout << "t[0]:\n " << t[0] << std::endl;
//   cout << "t[m-1]:\n " << t[m-1] << std::endl;
//   cout << "prior and mcmc info:\n";
//   pi.pr();
//   if(dart){
//     cout << "*****dart prior (On):\n";
//     cout << "a: " << a << std::endl;
//     cout << "b: " << b << std::endl;
//     cout << "rho: " << rho << std::endl;
//     cout << "augmentation: " << aug << std::endl;
//   }
//   else cout << "*****dart prior (Off):\n";
//   if(p) cout << "data set: n,p: " << n << ", " << p << std::endl;
//   else cout << "data not set\n";
//}
#endif
