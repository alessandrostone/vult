#include "moog_filter.h"

_ctx_type_0 _ctx_type_0_init(){
   _ctx_type_0 _ctx;
   _ctx.pre_x = 0.f;
   return _ctx;
}

_ctx_type_0 change_init(){ return _ctx_type_0_init();}

uint8_t change(_ctx_type_0 &_ctx, float x){
   uint8_t v = (_ctx.pre_x != x);
   _ctx.pre_x = x;
   return v;
}

float min(float a, float b){
   return ((a < b)?a:b);
}

float max(float a, float b){
   return ((a > b)?a:b);
}

float clip(float value, float low, float high){
   return fmin(fmax(low,value),high);
}

float samplerate(){
   return 44100.f;
}

float PI(){
   return 3.14159265359f;
}

float thermal(){
   return (1.f / 1.22070313f);
}

_ctx_type_7 _ctx_type_7_init(){
   _ctx_type_7 _ctx;
   _ctx.tw2 = 0.f;
   _ctx.tw1 = 0.f;
   _ctx.tw0 = 0.f;
   _ctx.dw3 = 0.f;
   _ctx.dw2 = 0.f;
   _ctx.dw1 = 0.f;
   _ctx.dw0 = 0.f;
   return _ctx;
}

_ctx_type_7 moog_step_init(){ return _ctx_type_7_init();}

float moog_step(_ctx_type_7 &_ctx, float input, float resFixed, float tune, float output){
   float i0 = (input - (resFixed * output));
   float w0 = (_ctx.dw0 + (tune * (tanhf((i0 * thermal())) - _ctx.tw0)));
   _ctx.tw0 = tanhf((w0 * thermal()));
   float w1 = ((_ctx.dw1 + (tune * _ctx.tw0)) - _ctx.tw1);
   _ctx.tw1 = tanhf((w1 * thermal()));
   float w2 = ((_ctx.dw2 + (tune * _ctx.tw1)) - _ctx.tw2);
   _ctx.tw2 = tanhf((w2 * thermal()));
   float w3 = ((_ctx.dw3 + (tune * _ctx.tw2)) - tanhf((_ctx.dw3 * thermal())));
   _ctx.dw0 = w0;
   _ctx.dw1 = w1;
   _ctx.dw2 = w2;
   _ctx.dw3 = w3;
   return w3;
}

_ctx_type_8 _ctx_type_8_init(){
   _ctx_type_8 _ctx;
   _ctx.tune = 0.f;
   _ctx.resFixed = 0.f;
   _ctx.filter = _ctx_type_7_init();
   _ctx.dx1 = 0.f;
   _ctx._inst1 = _ctx_type_0_init();
   _ctx._inst0 = _ctx_type_0_init();
   return _ctx;
}

_ctx_type_8 moog_init(){ return _ctx_type_8_init();}

float moog(_ctx_type_8 &_ctx, float input, float cut, float res){
   if(change(_ctx._inst0,cut) || change(_ctx._inst1,res)){
      res = clip_float(res,0.f,1.f);
      cut = clip_float(cut,1.f,samplerate());
      float fc = (cut / samplerate());
      float x_2 = (fc / 2.f);
      float x2 = (fc * fc);
      float x3 = (fc * x2);
      float fcr = ((((1.873f * x3) + (0.4955f * x2)) - (0.649f * fc)) + 0.9988f);
      float acr = ((((- 3.9364f) * x2) + (1.8409f * fc)) + 0.9968f);
      _ctx.tune = ((1.f - expf((- (((2.f * PI()) * x_2) * fcr)))) / thermal());
      _ctx.resFixed = ((4.f * res) * acr);
   }
   float x0 = moog_step(_ctx.filter,input,_ctx.resFixed,_ctx.tune,_ctx.dx1);
   float x1 = moog_step(_ctx.filter,input,_ctx.resFixed,_ctx.tune,x0);
   _ctx.dx1 = x1;
   return ((x0 + x1) / 2.f);
}

int n = 0;
while((n < 44100)){
   float kk = moog(_ctx.x,1.f,2000.f,0.1f);
   n = (n + 1);
}
return 0;

