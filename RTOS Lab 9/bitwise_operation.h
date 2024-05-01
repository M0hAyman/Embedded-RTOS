#define Set_Bit(Register,Bit) ((Register)|=(1<<Bit))
#define Clear_Bit(Register,Bit) ((Register)&=~(1<<Bit))
//#define Get_Bit(Register,Bit)  ({uint8 retval;retval=(Register&(1<<Bit)>>Bit;retval;})

//Easier way for Get_Bit: (Need to test)
#define Get_Bit(Register,Bit) ((Register>>Bit)&1)

#define Toggle_Bit(Register,Bit)((Register)^=(1<<Bit))