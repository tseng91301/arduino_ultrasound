#include "bottom_func.h"
#include"oled_setup.h"
#include "ultrasound.h"
#include "touch_button.h"

#define shortpress_t 170
#define longpress_t 2000
#define record_num 2

Ults ultrasound1(D5,D6);

TouchButton button1(D3,1);

Oled oled1;

int button_state(){
    static int nowtime=millis();
    static int reset_flag=0;
    int delta=millis()-nowtime;
    if(reset_flag){
        reset_flag=0;
        nowtime=millis();
        return 0;
    }
    Serial.println(delta);
    if(!button1.getval()){
        if(delta<shortpress_t){
            nowtime=millis();
            return 0;
        }else if(delta>=shortpress_t&&delta<longpress_t){
            nowtime=millis();
            return 1;
        }
    }else if(delta>=longpress_t){
        nowtime=millis();
        reset_flag=1;
        return 2;
    }
    return 0;
}

void update_val(double *rec,double add){
    for(int a=record_num-1;a>0;a--){
        rec[a]=rec[a-1];
    }
    rec[0]=add;
}

void init_val(double *rec){
    Serial.println("aaa");
    for(int a=0;a<record_num;a++){
        rec[a]=0.0;
    }
}

double *rec_vals=new double[record_num];
void setup() {
    init_val(rec_vals);
    Serial.begin(115200);
    oled1.txt("Welcome!");
    oled1.show(1000);
}
void loop() {
    int but_s=button_state();
    if(but_s==1){
        update_val(rec_vals,ultrasound1.get_val());
    }else if(but_s==2){
        init_val(rec_vals);
    }
    String txtout="Distance: "+String(ultrasound1.get_val())+"cm\n";
    for(int a=0;a<record_num;a++){
        txtout+="  Rec"+String(a+1)+": "+String(rec_vals[a])+"cm\n";
    }
    oled1.txt(txtout);
    oled1.show();

    if(but_s==2){
        delay(500);
    }
}
