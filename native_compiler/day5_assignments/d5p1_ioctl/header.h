#define magic_number 'k'

#define OPERATOR _IOW(magic_number,6,char)
#define number1 _IOW(magic_number,7,int)
#define number2 _IOW(magic_number,8,int)
#define RD_DATA _IOR(magic_number,9,int)

