#ifndef LEGCLASS
#define LEGCLASS

#include "steering_engine.h"
#include "utils.h"

//足底曲线的规划方向与车身的实际的方向可能不一样  比如车身的前后腿对称安装的时候  前后腿的前方向是反的
#define PI 3.1415926



class LegClass
{
public:
  //c1与c4对应的舵机下标  _start_ang_c/c4起始的角度  _reverse转向是否反向  当电机对称安装时，转向相反发
	void legInit(int _id_c1,int _id_c4,float _start_ang_c1=80,float _start_ang_c4=80,bool _reverse = false);
	void legInit(float _L1,float _L2,float _L3,float _L4,float _L5,float _L6,float _ALP,float _c10,float _c40);

	//更新  真正更新电机位置的地方
	void update(float _dt);
  //通过setSteerRad直接设定角度的更新
  void updateByRad();
  //设定足端坐标 
  //false为坐标超出工作限定范围
  bool setPos(float _x,float _y);
  //设定速度运动到目标位置 _use_t_long:移动使用时长/ms： 返回false为坐标超出工作限定范围  
  bool moveToPos(float _target_x,float _target_y,float _use_t_long);
  //直接设定转角  单位：弧度
  void setSteerRad(float _c1,float _c4);
  float get_c1(){return c1;};
  float get_c4(){return c4;};
  float get_x(){return x;};
  float get_y(){return y;};
  float get_L5();
private:
  float c1,c4;             //对应角度   弧度
  float x,y;               //足底曲线坐标    mm
  float c10,c40;         //上电初始角度
  bool reverse;          //转向是否反向  当电机对称安装时，转向相反发
  //机构参数

  //正解  由(c1,c4))求(x,y)
	void Zjie(float _c1,float _c4);
  //逆解 由(x,y)求(c1,c4)
  void Njie();
  //闭链五杆的逆解
  void nije_5( float *c1, float *c4, float x1,float y1,float l1,float l2,float l3,float l4,float l5);

  SteeringEngine engine_c1,engine_c4;
  
  float target_x,target_y; //目标位置
  float start_x,start_y;  //设定目标位置时的起始位置
  float use_t_long;    //运动到目标时长  ms
  float use_t;   //移动已经使用时长
 
  bool set_move_to_pos;

   //求解的局部参数
  // float A,B,C,a,b,c;
  // float m,n,x1,y1;
};





#endif