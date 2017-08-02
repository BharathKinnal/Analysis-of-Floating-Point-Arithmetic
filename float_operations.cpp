#include<bits/stdc++.h>

using namespace std;

#define bias 127
#define M 23

// To define a structured datatype consisting of 3 members - sign, exponent, and mantissa
struct floatComp{
    int sign;
    int exp[8];
    int man[23];
}one,two,result;

floatComp addab(int,floatComp ,floatComp );
floatComp multiplyab(int,floatComp ,floatComp );
floatComp inverse(floatComp );

// To represent a real number in the form of
// a structured variable of type floatComp
void floatRep(floatComp &no,float x){
    unsigned int a=*((unsigned int *)&x);
    for(int i=31;i>=0;i--)
    {
        int j=pow(2,i);
        cout<<(int)(a/j);
        if(i==31 || i==23)
            cout<<' ';
        if(i==31)               //MSB holds sign of number
            no.sign=a/j;
        else if(i>22)           //Next 8 bits represents the exponent value
            no.exp[30-i]=a/j;
        else                    //Rest of the bits store the value of the mantissa
            no.man[22-i]=a/j;
        a%=(unsigned int)pow(2,i);  //To process each of the 32 bits used to store a real number
    }
}

// To extract and return the real number represented
// by the structured variable of type floatComp
float floatNum(floatComp no)
{
    unsigned int x=0;

    //To display the representation of a real number
    cout<<"\nRepresentation of resulting float - ";
    for(int i=0;i<32;i++)
    {
        // To add all the bits to an unsigned int variable one by one
        x*=2;
        if(i==0){
            x+=no.sign;
            cout<<no.sign<<' ';
        }
        else if(i<9){
            x+=no.exp[i-1];
            cout<<no.exp[i-1];
        }
        else{
            x+=no.man[i-9];
            cout<<no.man[i-9];
        }
        if(i==8)
            cout<<' ';

    }
    cout<<endl;

    //Return the floating point equivalent of the computer representation
    return(*(float *)&x);
}

//The main function for performing arithmetic operations

int basic_operations()
{
    float A,B;
    char op;
    cout<<"Enter the expression (num1 op num2) - ";
    cin>>A>>op>>B;

    cout<<"1st number representation - ";
    floatRep(one,A);
    cout<<"\nOperator - "<<op<<endl;
    cout<<"2nd number representation - ";
    floatRep(two,B);
    cout<<endl;

    switch(op)
    {
        case '+':
            addab(0,one,two);
            break;
        case '-':
            addab(1,one,two);
            break;
        case '*':
            multiplyab(0,one,two);
            break;
        case '/':
            multiplyab(1,one,two);
            break;

    }
    return 0;
}
//#endif // BUILD_DEBUG
//using namespace basic;

// For finding the mantissa from a floatComp variable and multiplying it by a constant (2^23)
// so as to store it as an integer, adding the hidden bit (1) in the beginning
long long unsigned int findMan(floatComp &one)
{
    long long unsigned int x=1;
    for(int i=0;i<M;i++)
        x=(x*2)+one.man[i];
    return x;
}

// For storing the mantissa represented as an integer into a floatComp variable
// excluding the hidden bit (1)
void displayMan(floatComp &result,long long unsigned int res)
{
    cout<<"Resulting mantissa - ";
    for(int i=23;i>=0;i--)
    {
            long long unsigned int j=pow(2,i);
            if(i<23)
                result.man[22-i]=(int)(res/j);
            cout<<(int)(res/j);
            if(i==23)
                cout<<'.';
            res%=j;

    }cout<<endl;

}

// For finding the (biased) exponent from a floatComp variable by storing it as an integer
int findExp(floatComp &one)
{
    int x=0;
    for(int i=0;i<8;i++)
        x=(x*2)+one.exp[i];
    return x;
}

// For storing the biased exponent represented as an integer into a floatComp variable
void displayExp(floatComp &result,int x)
{
    cout<<"Resulting exponent - ";
        for(int i=7;i>=0;i--)
        {
            int j=pow(2,i);
            result.exp[7-i]=(int)(x/j);
            x%=j;
            cout<<result.exp[7-i];
        }
        cout<<endl;
}

// To add or subtract 2 floating point numbers, represented as floatComp variables
floatComp addab(int adsub,floatComp one,floatComp two){

    if(adsub)
        cout<<"\nSubtraction is being performed\n";
    else cout<<"\nAddition is being performed\n";
    //Checking which number has a greater exponent
    int x=findExp(one),y=findExp(two);
    int expdiff=x-y;

    int m=findMan(one),n=findMan(two);

    //Making the exponents equal, by modifying the mantissa of the smaller number accordingly
    if(expdiff<=0){
        m/=(int)pow(2,y-x);
        x=y;
    }
    else{
        n/=(int)pow(2,expdiff);
        y=x;
    }

    m*=pow(-1,one.sign);                 //adsub represents addition or subtraction
    n*=pow(-1,two.sign^adsub);           //  (0 -> +)  ;   (1 -> -)

    int res;
    res=m+n;                            //Adding the 2 integers (m,n)

    if(res<0)                           //To check if the resulting sum is negative or not
    {
        res*=-1;
        result.sign=1;
    }
    else result.sign=0;

    cout<<"\nSign of result - "<<result.sign<<endl;

    //For normalizing the exponent
    //May occur only if the result is not 0
    if(res!=0){

        //If the 2 numbers have equal sign, then the sum may have a greater exponent
        //So the resulting mantissa is reduced to have a fixed size, while the exponent is normalized accordingly
        if(one.sign==two.sign^adsub)
            while(res/pow(2,24)>=1 && x!=0)
            {
                res/=2;
                x++;
            }
        //If the 2 numbers have opposite sign, then the sum may have smaller exponent
        //So the resulting mantissa is increased to have a fixed size, while the exponent is normalized accordingly
        else
            while(res/pow(2,23)<1)
            {
                res*=2;
                x--;
            }
    }
    //If the resulting sum is 0, then the final resulting floating point will also be 0.
    else
        x=0;

    //In case the exponent goes out of bounds
    if(x>255)
        x=255;

    displayMan(result,res);
    displayExp(result,x);


    printf("\nResulting sum - %f",floatNum(result));

    return result;
}

// To multiply or divide 2 floating point numbers, represented as floatComp variables
floatComp multiplyab(int muldiv,floatComp one,floatComp two){

    if(muldiv)
        cout<<"\nDivision is being performed\n";
    else cout<<"\nMultiplication is being performed\n";
    //The resulting sign of the product will be XOR of the signs of the 2 numbers
    result.sign=one.sign^two.sign;
    cout<<"\nResult sign - "<<result.sign<<endl;

    if(muldiv)                  //muldiv represents either multiplication or division
    {
        cout<<"\nFinding multiplicative inverse of 2nd number\n";
        two=inverse(two);             //    (0 -> *)  ;   (1 -> /)
    }

    int normalize=0;

    long long unsigned int x=findMan(one),y=findMan(two),z;
    int a=findExp(one),b=findExp(two),res;

    //If any of the real numbers is 0, then the product is 0
    if(a==0 && x==0x00800000)
        x=0;
    if(b==0 && y==0x00800000)
        y=0;

    //To represent the 2 mantissa
    long long unsigned int m=x,n=y;
    cout<<"\nMantissa of 1st number - ";
    for(int i=M;i>=0;i--)
    {
        int j=pow(2,i);
        cout<<m/j;
        if(i==M)
            cout<<'.';
        m%=j;
    }
    cout<<endl<<"Mantissa of 2nd number - ";

    for(int i=M;i>=0;i--)
    {
        int j=pow(2,i);
        cout<<n/j;

        if(i==M)
            cout<<'.';
        n%=j;
    }
    cout<<endl;

    //Normal multiplication of the integral representations of the 2 mantissa is done
    z=x*y;

    // In case mantissa is >= 2, normalization is done
    if((int)(z/pow(2,2*M+1))==1)
    {
        z/=2;
        normalize++;
    }
    z/=pow(2,M);                    //To reduce the mantissa by M bits, since it will originally have 2M bits

    //To calculate the resulting exponent as the sum of the 2 exponent values
    res=a+b-bias+normalize;             //To get a biased exponent

    //In case the exponent goes out of bounds...
    if(res>255)
        res=255;
    if(res<0)
        res=0;

    displayMan(result,z);
    cout<<endl;
    displayExp(result,res);

    printf("\nResulting product - %0.9f",floatNum(result));

    return result;
}

// To find multiplicative inverse of a given number, represented by a floatComp variable
floatComp inverse(floatComp two)
{
    int x=findExp(two);
    long long unsigned int m=findMan(two),extra=pow(2,23);

    //If the number is 0, it's inverse will be (+/-)infinity
    if(m==pow(2,23) && x==0)
    {
        x=255;
    }
    else{
        x=(2*bias)-x;       //To get the biased exponent of the inverse

        //If mantissa isn't 1, then the resulting exponent e' = (-e) - 1
        if(m>pow(2,23)){
            x-=1;
            extra*=2;
        }
        //Mantissa is given as -> m' = extra/m
        m=(extra*pow(2,23))/m;
    }
    cout<<endl;
    displayMan(two,m);
    displayExp(two,x);
    return two;
}

// To compare a floatComp structured variable with a real constant
int compare(floatComp x,float num)
{
    floatComp y;
    floatRep(y,num);            //Store the real number in a floatComp variable

    x=addab(1,x,y);             //Find the difference between the 2 real numbers
    float f=floatNum(x);

    if(f>0)
        return 1;
    else if(f<0)
        return -1;
    else
        return 0;
}

// To add or subtract a floatComp variable with a floating point constant
floatComp intAdd(int adsub,floatComp &x,float y)
{
    floatComp rep;
    floatRep(rep,y);            //Store the real constant in a floatComp variable

    return addab(adsub,x,rep);
}

// To multiply or divide a floatComp variable with a floating point constant
floatComp intMultiply(int muldiv,floatComp x,float y)
{
    floatComp rep;
    floatRep(rep,y);            //Store the real constant in a floatComp variable

    return multiplyab(muldiv,x,rep);
}

// To convert an integer constant to a floating point number
// by storing the given value in a floatComp structure
floatComp intToFloat(long long int n)
{
    floatComp f;
    if(n<0){
        n*=-1;
        f.sign=1;
    }
    else f.sign=0;

    long long unsigned int exp=127,man=(int)(n*pow(2,23));

    while(man>=pow(2,24))
    {
        man/=2;
        exp++;
    }
    if(man==0)
        exp=0;
    displayExp(f,exp);
    displayMan(f,man);

    return f;
}

// To find an integral power of a real number, represented by a floatComp variable
floatComp power(floatComp x,int n){
    floatComp y;
    floatRep(y,1);

    // For positive powers of the real number
    for(;n>0;n--)
            y=multiplyab(0,y,x);
    // For negative powers of the real number
    for(;n<0;n++)
            y=multiplyab(1,y,x);

    return y;
}

// To find the square root of a real number, represented by a floatComp variable
floatComp sqroot(floatComp x)
{
    //         y' = sqroot(x) = 1/2 (y + x/y)
    // This is applied for a certain number of times (in this case, 10 times)
    floatComp y;
    floatRep(y,1);

    for(int i=0;i<10;i++)
    {
        y=addab(0,y,multiplyab(1,x,y));
        y=intMultiply(1,y,2);
    }

    return y;
}
