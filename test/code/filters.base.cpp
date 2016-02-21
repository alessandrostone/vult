#include "filters.h"

float samplerate(){
   return 44100.f;
}

float pi(){
   return 3.1416f;
}

float min(float a, float b){
   return ((a < b)?a:b);
}

float max(float a, float b){
   return ((a > b)?a:b);
}

float clip(float low, float high, float value){
   return fmin(fmax(low,value),high);
}

_ctx_type_5 _ctx_type_5_init(){
   _ctx_type_5 _ctx;
   _ctx.pre_x = 0.f;
   return _ctx;
}

_ctx_type_5 change_init(){ return _ctx_type_5_init();}

uint8_t change(_ctx_type_5 &_ctx, float x){
   uint8_t v = (_ctx.pre_x != x);
   _ctx.pre_x = x;
   return v;
}

_ctx_type_6 _ctx_type_6_init(){
   _ctx_type_6 _ctx;
   _ctx.w2 = 0.f;
   _ctx.w1 = 0.f;
   return _ctx;
}

_ctx_type_6 biquad_init(){ return _ctx_type_6_init();}

float biquad(_ctx_type_6 &_ctx, float x, float b0, float b1, float b2, float a1, float a2){
   float w0 = ((x - (a1 * _ctx.w1)) - (a2 * _ctx.w2));
   float y0 = (((b0 * w0) + (b1 * _ctx.w1)) + (b2 * _ctx.w2));
   float _tmp_0 = _ctx.w1;
   float _tmp_1 = w0;
   _ctx.w2 = _tmp_0;
   _ctx.w1 = _tmp_1;
   return y0;
}

_ctx_type_7 _ctx_type_7_init(){
   _ctx_type_7 _ctx;
   _ctx.k = 0.f;
   _ctx.fc = 0.f;
   _ctx._inst1 = _ctx_type_6_init();
   _ctx._inst0 = _ctx_type_5_init();
   return _ctx;
}

_ctx_type_7 lp6_init(){ return _ctx_type_7_init();}

float lp6(_ctx_type_7 &_ctx, float x, float fc){
   if(change(_ctx._inst0,_ctx.fc)){
      _ctx.fc = clip_float(_ctx.fc,0.f,samplerate());
      _ctx.k = tanf(((pi() * _ctx.fc) / samplerate()));
   }
   float b0 = (_ctx.k / (_ctx.k + 1.f));
   float b1 = (_ctx.k / (_ctx.k + 1.f));
   float a1 = ((_ctx.k - 1.f) / (_ctx.k + 1.f));
   return biquad(_ctx._inst1,x,b0,b1,0.f,a1,0.f);
}

_ctx_type_8 _ctx_type_8_init(){
   _ctx_type_8 _ctx;
   _ctx.b2 = 0.f;
   _ctx.b1 = 0.f;
   _ctx.b0 = 0.f;
   _ctx.a2 = 0.f;
   _ctx.a1 = 0.f;
   _ctx._inst2 = _ctx_type_6_init();
   _ctx._inst1 = _ctx_type_5_init();
   _ctx._inst0 = _ctx_type_5_init();
   return _ctx;
}

_ctx_type_8 lp12_init(){ return _ctx_type_8_init();}

float lp12(_ctx_type_8 &_ctx, float x, float fc, float q){
   if(change(_ctx._inst0,fc) || change(_ctx._inst1,q)){
      float qc = fmax(sqrt(2.f),(q + sqrt(2.f)));
      fc = clip_float(fc,0.f,samplerate());
      float k = tanf(((pi() * fc) / samplerate()));
      float den = ((((k * k) * qc) + k) + qc);
      _ctx.b0 = (((k * k) * qc) / den);
      _ctx.b1 = (2.f * _ctx.b0);
      _ctx.b2 = _ctx.b0;
      _ctx.a1 = (((2.f * qc) * ((k * k) - 1.f)) / den);
      _ctx.a2 = (((((k * k) * qc) - k) + qc) / den);
   }
   return biquad(_ctx._inst2,x,_ctx.b0,_ctx.b1,_ctx.b2,_ctx.a1,_ctx.a2);
}

_ctx_type_9 _ctx_type_9_init(){
   _ctx_type_9 _ctx;
   _ctx._inst0 = _ctx_type_6_init();
   return _ctx;
}

_ctx_type_9 hp6_init(){ return _ctx_type_9_init();}

float hp6(_ctx_type_9 &_ctx, float x, float fc){
   fc = clip_float(fc,0.f,samplerate());
   float k = tanf(((pi() * fc) / samplerate()));
   float b0 = (1.f / (k + 1.f));
   float b1 = ((- 1.f) / (k + 1.f));
   float a1 = ((k - 1.f) / (k + 1.f));
   return biquad(_ctx._inst0,x,b0,b1,0.f,a1,0.f);
}

_ctx_type_10 _ctx_type_10_init(){
   _ctx_type_10 _ctx;
   _ctx._inst0 = _ctx_type_6_init();
   return _ctx;
}

_ctx_type_10 allp6_init(){ return _ctx_type_10_init();}

float allp6(_ctx_type_10 &_ctx, float x, float fc){
   fc = clip_float(fc,0.f,samplerate());
   float k = tanf(((pi() * fc) / samplerate()));
   float b0 = ((k - 1.f) / (k + 1.f));
   float b1 = 1.f;
   float a1 = ((k - 1.f) / (k + 1.f));
   return biquad(_ctx._inst0,x,b0,b1,0.f,a1,0.f);
}

_ctx_type_11 _ctx_type_11_init(){
   _ctx_type_11 _ctx;
   _ctx.b2 = 0.f;
   _ctx.b1 = 0.f;
   _ctx.b0 = 0.f;
   _ctx.a2 = 0.f;
   _ctx.a1 = 0.f;
   _ctx._inst2 = _ctx_type_6_init();
   _ctx._inst1 = _ctx_type_5_init();
   _ctx._inst0 = _ctx_type_5_init();
   return _ctx;
}

_ctx_type_11 hp12_init(){ return _ctx_type_11_init();}

float hp12(_ctx_type_11 &_ctx, float x, float fc, float q){
   if(change(_ctx._inst0,fc) || change(_ctx._inst1,q)){
      float qc = fmax(sqrt(2.f),(q + sqrt(2.f)));
      fc = clip_float(fc,0.f,samplerate());
      float k = tanf(((pi() * fc) / samplerate()));
      float den = ((((k * k) * qc) + k) + qc);
      _ctx.b0 = (qc / den);
      _ctx.b1 = (((- 2.f) * qc) / den);
      _ctx.b2 = (qc / den);
      _ctx.a1 = (((2.f * qc) * ((k * k) - 1.f)) / den);
      _ctx.a2 = (((((k * k) * qc) - k) + qc) / den);
   }
   return biquad(_ctx._inst2,x,_ctx.b0,_ctx.b1,_ctx.b2,_ctx.a1,_ctx.a2);
}

_ctx_type_12 _ctx_type_12_init(){
   _ctx_type_12 _ctx;
   _ctx.b2 = 0.f;
   _ctx.b1 = 0.f;
   _ctx.b0 = 0.f;
   _ctx.a2 = 0.f;
   _ctx.a1 = 0.f;
   _ctx._inst2 = _ctx_type_6_init();
   _ctx._inst1 = _ctx_type_5_init();
   _ctx._inst0 = _ctx_type_5_init();
   return _ctx;
}

_ctx_type_12 bp12_init(){ return _ctx_type_12_init();}

float bp12(_ctx_type_12 &_ctx, float x, float fc, float q){
   if(change(_ctx._inst0,fc) || change(_ctx._inst1,q)){
      float qc = fmax(sqrt(2.f),(q + sqrt(2.f)));
      fc = clip_float(fc,0.f,samplerate());
      float k = tanf(((pi() * fc) / samplerate()));
      float den = ((((k * k) * qc) + k) + qc);
      _ctx.b0 = (k / den);
      _ctx.b1 = 0.f;
      _ctx.b2 = ((- k) / den);
      _ctx.a1 = (((2.f * qc) * ((k * k) - 1.f)) / den);
      _ctx.a2 = (((((k * k) * qc) - k) + qc) / den);
   }
   return biquad(_ctx._inst2,x,_ctx.b0,_ctx.b1,_ctx.b2,_ctx.a1,_ctx.a2);
}

_ctx_type_13 _ctx_type_13_init(){
   _ctx_type_13 _ctx;
   _ctx.b2 = 0.f;
   _ctx.b1 = 0.f;
   _ctx.b0 = 0.f;
   _ctx.a2 = 0.f;
   _ctx.a1 = 0.f;
   _ctx._inst2 = _ctx_type_6_init();
   _ctx._inst1 = _ctx_type_5_init();
   _ctx._inst0 = _ctx_type_5_init();
   return _ctx;
}

_ctx_type_13 notch12_init(){ return _ctx_type_13_init();}

float notch12(_ctx_type_13 &_ctx, float x, float fc, float q){
   if(change(_ctx._inst0,fc) || change(_ctx._inst1,q)){
      float qc = fmax(sqrt(2.f),(q + sqrt(2.f)));
      fc = clip_float(fc,0.f,samplerate());
      float k = tanf(((pi() * fc) / samplerate()));
      float den = ((((k * k) * qc) + k) + qc);
      _ctx.b0 = ((qc * (1.f + (k * k))) / den);
      _ctx.b1 = (((2.f * qc) * ((k * k) - 1.f)) / den);
      _ctx.b2 = _ctx.b0;
      _ctx.a1 = (((2.f * qc) * ((k * k) - 1.f)) / den);
      _ctx.a2 = (((((k * k) * qc) - k) + qc) / den);
   }
   return biquad(_ctx._inst2,x,_ctx.b0,_ctx.b1,_ctx.b2,_ctx.a1,_ctx.a2);
}

_ctx_type_14 _ctx_type_14_init(){
   _ctx_type_14 _ctx;
   _ctx.b2 = 0.f;
   _ctx.b1 = 0.f;
   _ctx.b0 = 0.f;
   _ctx.a2 = 0.f;
   _ctx.a1 = 0.f;
   _ctx._inst2 = _ctx_type_6_init();
   _ctx._inst1 = _ctx_type_5_init();
   _ctx._inst0 = _ctx_type_5_init();
   return _ctx;
}

_ctx_type_14 allp12_init(){ return _ctx_type_14_init();}

float allp12(_ctx_type_14 &_ctx, float x, float fc, float q){
   if(change(_ctx._inst0,fc) || change(_ctx._inst1,q)){
      float qc = fmax(sqrt(2.f),(q + sqrt(2.f)));
      fc = clip_float(fc,0.f,samplerate());
      float k = tanf(((pi() * fc) / samplerate()));
      float den = ((((k * k) * qc) + k) + qc);
      _ctx.b0 = (((((k * k) * qc) - k) + qc) / den);
      _ctx.b1 = (((2.f * qc) * ((k * k) - 1.f)) / den);
      _ctx.b2 = 1.f;
      _ctx.a1 = (((2.f * qc) * ((k * k) - 1.f)) / den);
      _ctx.a2 = (((((k * k) * qc) - k) + qc) / den);
   }
   return biquad(_ctx._inst2,x,_ctx.b0,_ctx.b1,_ctx.b2,_ctx.a1,_ctx.a2);
}

allp12(_ctx._inst3,0.f,100.f,0.5f);

