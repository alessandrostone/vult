#include "state_variable.h"

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

_ctx_type_1 _ctx_type_1_init(){
   _ctx_type_1 _ctx;
   _ctx.dlow = 0.f;
   _ctx.dband = 0.f;
   return _ctx;
}

_ctx_type_1 svf_step_init(){ return _ctx_type_1_init();}

float svf_step(_ctx_type_1 &_ctx, float input, float g, float q, int sel){
   float low = (_ctx.dlow + (g * _ctx.dband));
   float high = ((input - low) - (q * _ctx.dband));
   float band = ((g * high) + _ctx.dband);
   float notch = (high + low);
   _ctx.dband = clip_float(band,(- 1.f),1.f);
   _ctx.dlow = clip_float(low,(- 1.f),1.f);
   float output = ((sel == 0)?low:((sel == 1)?high:((sel == 2)?band:notch)));
   return output;
}

_ctx_type_2 _ctx_type_2_init(){
   _ctx_type_2 _ctx;
   _ctx.step = _ctx_type_1_init();
   _ctx.g = 0.f;
   _ctx._inst0 = _ctx_type_0_init();
   return _ctx;
}

_ctx_type_2 svf_init(){ return _ctx_type_2_init();}

float svf(_ctx_type_2 &_ctx, float input, float fc, float q, int sel){
   fc = clip_float(fc,0.f,1.f);
   q = clip_float(q,0.f,1.f);
   float fix_q = (2.f * (1.f - q));
   if(change(_ctx._inst0,fc)){
      _ctx.g = (fc / 2.f);
   }
   float x1 = svf_step(_ctx.step,input,_ctx.g,fix_q,sel);
   float x2 = svf_step(_ctx.step,input,_ctx.g,fix_q,sel);
   return ((x1 + x2) / 2.f);
}


