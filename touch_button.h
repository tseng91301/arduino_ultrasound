class TouchButton{
    private:
        int inverse;
        int state;
        int pin;
    public:
        TouchButton(const int p,int inv=0){
            pinMode(p,INPUT_PULLUP);
            pin=p;
            inverse=inv;
            return; 
        }
        int getval(){
            state=digitalRead(pin);
            if(inverse){
                return(!state);
            }else{
                return(state);
            }
            
        }
};