int WhatDay(int year,int month,int dday){//0是周日，1是周一，6是周六
    if(month<3){year-=1;month+=12;}
    int c=int(year/100),y=year-100*c;
    int w=int(c/4)-2*c+y+int(y/4)+(26*(month+1)/10)+dday-1;
    w=(w%7+7)%7;
    return w;
}