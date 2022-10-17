



float saturated(float in, float saturation){
    float out;
    out = in ;
    if(in > saturation){
        out = saturation;
    }
    if(in < -saturation){
        out = -saturation;
    }
    return out ;
}