#include "State.h"

Point
State::
p(void)
{
  if( this->elements.size() > 4)
  {
    Point p_(this->elements[0],
             this->elements[1],
             this->elements[2]);

    this->pos = p_;

  }
  else
  {
    Point p_(this->elements[0],
             this->elements[1]);

    this->pos = p_;
  }


  return this->pos;
}

Point
State::
v(void)
{
  if( this->elements.size() > 4)
  {
    Point v_(this->elements[3],
             this->elements[4],
             this->elements[5]);

    this->vel = v_;
  }
  else
  {
    Point v_(this->elements[2],
             this->elements[3]);
    this->vel = v_;
  }

  return this->vel;
}

std::vector<double>
State::
get_elements(void)
{
  return this->elements;
}

double
State::
pnorm(void)
{
  return sqrt((double)pow(this->pos[0],2)+ (double)pow(this->pos[1],2)+(double)pow(this->pos[2],2));
}


//ignition::math::Vector3d<double>
Point
State::
get_acc( double n )
{
  Matrixd A = { { 0,         0,          0,     1,     0,    0},
                { 0,         0,          0,     0,     1,    0},
                { 0,         0,          0,     0,     0,    1},
                { 3 * pow(n,2),          0,     0,   2*n,    0},
                { 0,         0,          0,  -2*n,     0,    0},
                { 0,         0,  -pow(n,2),     0,     0,    0}};

//Derivative of state
 State sd = A * (*this);
 //To get the acceleration => put derivative of velocity
 Point acc(sd.v()[0],sd.v()[1],sd.v()[2]);

 //ignition::math::Vector3d<double> acc(sd.v()[0],sd.v()[1],sd.v()[2]);

 return acc;
}
