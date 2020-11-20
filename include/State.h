#ifndef __STATE__
#define __STATE__


#include "3DTlib/math/point.h"
#include "3DTlib/math/matrix/matrix.h"
//#include <ignition/math/Pose3.hh>
#include <math.h>

using namespace _3dtlib;
using namespace std;

class State : public Matrixd
{
public:

  State(){};

  State( vector<double> pv)
  {
    if(pv.size() > 4)
    {
      Point _v(pv[3],pv[4],pv[5]);
      Point _p(pv[0],pv[1],pv[2]);
      this->vel = _v;
      this->pos = _p;
      rows = 6;
      cols = 1;
    }
    else
    {
      Point _v(pv[2],pv[3]);
      Point _p(pv[0],pv[1]);
      this->vel = _v;
      this->pos = _p;
      rows = 4;
      cols = 1;
    }

    for(double pvi : pv)
      elements.push_back(pvi);


  }

  State(Point p_, Point v_)
  {
    pos = p_;
    vel  = v_;
    rows = 4;
    cols = 1;

    this->elements.push_back(p_[0]);
    this->elements.push_back(p_[1]);
    if(p_.c() > 2 || p_.r() > 2)
    {
      this->elements.push_back(p_[2]);
      rows = 6;
    }

    this->elements.push_back(v_[0]);
    this->elements.push_back(v_[1]);
    if(v_.c() > 2 || v_.r() > 2)
      this->elements.push_back(v_[2]);


  }

  State(double px, double py,
        double vx, double vy)
  {

    this->elements.push_back(px);
    this->elements.push_back(py);

    Point p_(px,py);
    this->pos = p_;

    this->elements.push_back(vx);
    this->elements.push_back(vy);

    Point v_(vx,vy);
    this->vel = v_;

    rows = 4;
    cols = 1;

  }
  State(double px, double py, double pz,
        double vx, double vy, double vz)
  {
    this->elements.push_back(px);
    this->elements.push_back(py);
    this->elements.push_back(pz);

    Point p_(px,py,pz);
    this->pos = p_;

    this->elements.push_back(vx);
    this->elements.push_back(vy);
    this->elements.push_back(vz);

    Point v_(vx,vy,vz);
    this->vel = v_;

    rows = 6;
    cols = 1;
  }

  State(const Matrix<double>& M)
      :
    Matrix<double> (M) {};
  /*
  State operator+(State lhs, const& State rhs)
  {
    for(int i=0; i<lhs.size(); i++)
    {
      lhs[i] += rhs[i]
    }
  }
  */

  bool
  operator<(State &s_comp)
  {
    //TODO: implement cases for s1,s2.size() = 2
    for(unsigned int i=0; i<3; i++)
    {
      if(abs(this->pos[i] - s_comp.p()[i]) > 1e-3)
      {
      return false;
      }
    }

    return true;

  }

  Point p(void);
  Point v(void);
  std::vector<double> get_elements(void);
  double pnorm(void);
  //ignition::math::Vector3d<double>
  Point get_acc(double n = 0.00113);

protected:
  Point vel;
  Point pos;
};
#endif
