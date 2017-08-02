#include<bits/stdc++.h>
#include"float_operations.cpp"

using namespace std;

floatComp x;

floatComp exponential(floatComp);
floatComp logarithm(floatComp);
void trigonometricfn(floatComp);
void hyperbolicfn(floatComp);

floatComp sine(floatComp);
floatComp cosine(floatComp);
floatComp tangent(floatComp);
floatComp cosecant(floatComp);
floatComp secant(floatComp);
floatComp cotangent(floatComp);
floatComp sineh(floatComp);
floatComp cosineh(floatComp);
floatComp tangenth(floatComp);
floatComp cosecanth(floatComp);
floatComp secanth(floatComp);
floatComp cotangenth(floatComp);

#define pi 3.14159265


// The main function to perform mathematical transcendental functions
//#if !float_operations//system(tasklist /FI "IMAGENAME eq myapp.exe" 2>NUL | find /I /N "myapp.exe">NUL)//; if "%ERRORLEVEL%"=="0" echo Program is running)
int main()
{
    //cout<<floatNum(inverse(intToFloat(0)));
    int ch;
    float no;
    cout<<"\n\n\t1.Basic arithmetic operations\n\t2.e^x\n\t3.log x\n\t4.Trigonometric function\n\t5.Hyperbolic function\n\t\tEnter your choice - ";
    cin>>ch;
    if(ch<4 && ch>1)
    {
        cout<<"\tx = ";
        cin>>no;

        floatRep(x,no);
    }

    switch(ch)
    {
        case 1:
            cout<<"\n\t";
            basic_operations();
            break;

        case 2:
            exponential(x);
            break;
        case 3:
            {
            float l=floatNum(logarithm(x));
            cout<<"\n\nlog x = "<<l<<endl;
            break;
            }
        case 4:
            trigonometricfn(x);
            break;
        case 5:
            hyperbolicfn(x);
            break;
    }
    return 0;
}
//#endif // float_operations

// To find e^x, given a real number x
floatComp exponential(floatComp x)
{
    /*
                    e^x is given by the Maclaurin series
                    In any Maclaurin series -> f(x) = f(0) + f'(x).(x^1 / 1!) + f"(x).(x^2 / 2!) + ...
                    So for f(x)=e^x, we get -

                            e^x = 1 + x + (x^2 / 2!) + (x^3 / 3!) + ...
    */

    floatComp e,t;
    cout<<endl<<endl;
    floatRep(t,1);
    cout<<endl<<endl;
    floatRep(e,1);
    cout<<endl<<endl;

    //For gaining more accurate results, the number is brought in the range of -2 <= x < 2
    //The value of e^x is updated accordingly
    while(compare(x,-2)==-1)
    {
        e=intMultiply(1,e,54.5981500331);           //54.5981500331 = e^4
        x=intAdd(0,x,4);
    }
    while(compare(x,2)!=-1)
    {
        e=intMultiply(0,e,54.5981500331);
        x=intAdd(1,x,4);
    }

    floatComp temp;
    floatRep(temp,1);

    for(int i=1;i<21;i++)
    {
        t=multiplyab(0,t,x);            //t is multiplied by x each time, so as to have x^n in the nth term
        cout<<endl<<endl;
        cout<<endl<<endl;

        t=intMultiply(1,t,i);           //t is divided by i each time, so as to have 1/n! in the nth term
        cout<<endl<<endl;
        cout<<endl<<endl;

        temp=addab(0,temp,t);
    }

    e=multiplyab(0,e,temp);

    cout<<"\n\n\te^x = "<<floatNum(e)<<endl;
    return e;
}

// To find log x, given any non-negative real number x
floatComp logarithm(floatComp x){

    /*
                    log x is given by the Maclaurin series
                    In any Maclaurin series -> f(x) = f(0) + f'(x).(x^1 / 1!) + f"(x).(x^2 / 2!) + ...
                    So for f(x)=log x, we get -

                            log x = t - (t^2 / 2) + (t^3 / 3) - (t^4 / 4) + ...
                                where t = x-1

                    However, this equation holds true only for 0 < x <= 2
                    Therefore, we represent x as -
                                x = (2*2*2*2*...) * x'          ,where 0 < x' <= 2

                        So log x = log((2*2*2*2*...)*(x')))
                                 = ((log 2)+(log 2)+(log 2)+(log 2)+...) + (log x')
    */
    floatComp temp,t,ftemp;
    cout<<endl<<endl;
    floatRep(t,1);
    cout<<endl<<endl;
    floatRep(temp,0);
    cout<<endl<<endl;

    //If x=0, return -infinity
    if(compare(x,0)==0)
    {
        temp=intMultiply(0,temp,-1);
        temp=inverse(temp);

        return temp;
    }

    //To minimize errors in the series, an x' is chosen such that (1/1.9) <= x' <= 1.9
    while(compare(x,1.9)==1){
        temp=intAdd(0,temp,0.64185388617);              //0.64185388617 = ln 1.9
        x=intMultiply(1,x,1.9);
    }
    while(compare(x,0.52631578947)==-1){
        temp=intAdd(0,temp,-0.64185388617);
        x=intMultiply(0,x,1.9);
    }

    // Since the series is for log (x+1), x should be reduced by 1
    x=intAdd(1,x,1);

    for(int i=1,si=1;i<21;i++,si*=-1)
    {
        t=multiplyab(0,t,x);
        cout<<endl<<endl;
        cout<<endl<<endl;

        temp=addab(0,temp,intMultiply(1,t,i*si));
        cout<<"\n\n------------------------------------------------------------------\n\n\n";

    }
    return temp;
}

void trigonometricfn(floatComp x)
{
    int ch;
    float no;
    cout<<"\n\n\t\t1. sin x\n\t\t2. cos x\n\t\t3. tan x\n\t\t4. cosec x\n\t\t5. sec x\n\t\t6. cot x\n\t\tEnter your choice - ";
    cin>>ch;

    cout<<"\tx = ";
    cin>>no;

    floatRep(x,no);

    switch(ch)
    {
        case 1:
            sine(x);
            break;
        case 2:
            cosine(x);
            break;
        case 3:
            tangent(x);
            break;
        case 4:
            cosecant(x);
            break;
        case 5:
            secant(x);
            break;
        case 6:
            cotangent(x);
            break;
    }
}

void hyperbolicfn(floatComp x)
{
    int ch;
    float no;
    cout<<"\n\n\t\t1. sinh x\n\t\t2. cosh x\n\t\t3. tanh x\n\t\t4. cosech x\n\t\t5. sech x\n\t\t6. coth x\n\t\tEnter your choice - ";
    cin>>ch;

    cout<<"\tx = ";
    cin>>no;

    floatRep(x,no);

    switch(ch)
    {
        case 1:
            sineh(x);
            break;
        case 2:
            cosineh(x);
            break;
        case 3:
            tangenth(x);
            break;
        case 4:
            cosecanth(x);
            break;
        case 5:
            secanth(x);
            break;
        case 6:
            cotangenth(x);
            break;
    }
}

// Function used to find the sine of a real number, and return it to any trigonometric function
floatComp findSine(floatComp x){

    //To bring x in the range -pi < x <= pi
    while(compare(x,-1*pi)==-1)
        x=intAdd(0,x,pi);
    while(compare(x,pi)!=-1)
        x=intAdd(1,x,pi);

    floatComp temp,y,ytemp;
    floatRep(y,0);
    cout<<endl;
    floatRep(ytemp,1);
    cout<<endl;
    temp=ytemp;

    if(compare(x,-1)==-1)
    {
        /*
            For x<-1, sin x can be approximated as follows,

                sin x = -(0.5048*(t^5))/5! - (0.8632*(t^4))/4! + (0.5048*(t^3))/3!
                        + (0.8632*(t^2))/2! - (0.5048*(t^1))/1! - 0.8632

        */

        x=intAdd(0,x,2.1);

        y=intAdd(1,y,0.8632035);

        temp=multiplyab(0,temp,x);
        temp=intMultiply(1,temp,1);
        y=addab(1,y,intMultiply(0,temp,0.504802));

        temp=multiplyab(0,temp,x);
        temp=intMultiply(1,temp,2);
        y=addab(0,y,intMultiply(0,temp,0.8632035));

        temp=multiplyab(0,temp,x);
        temp=intMultiply(1,temp,3);
        y=addab(0,y,intMultiply(0,temp,0.504802));

        temp=multiplyab(0,temp,x);
        temp=intMultiply(1,temp,4);
        y=addab(1,y,intMultiply(0,temp,0.8632035));

        temp=multiplyab(0,temp,x);
        temp=intMultiply(1,temp,5);
        y=addab(1,y,intMultiply(0,temp,0.504802));
    }
    else if(compare(x,1)==1)
    {
        x=intAdd(1,x,2.1);

        y=intAdd(0,y,0.8632035);

        temp=multiplyab(0,temp,x);
        temp=intMultiply(1,temp,1);
        y=addab(1,y,intMultiply(0,temp,0.504802));

        temp=multiplyab(0,temp,x);
        temp=intMultiply(1,temp,2);
        y=addab(1,y,intMultiply(0,temp,0.8632035));

        temp=multiplyab(0,temp,x);
        temp=intMultiply(1,temp,3);
        y=addab(0,y,intMultiply(0,temp,0.504802));

        temp=multiplyab(0,temp,x);
        temp=intMultiply(1,temp,4);
        y=addab(0,y,intMultiply(0,temp,0.8632035));

        temp=multiplyab(0,temp,x);
        temp=intMultiply(1,temp,5);
        y=addab(1,y,intMultiply(0,temp,0.504802));
    }
    else
    {
        y=addab(0,y,x);

        temp=power(x,3);
        y=addab(0,y,intMultiply(0,temp,-0.166666666666));

        temp=power(x,5);
        y=addab(0,y,intMultiply(0,temp,0.00833333333));
    }

    return y;
}

// To find sin x, given a real number x
floatComp sine(floatComp x)
{
    floatComp s=findSine(x);
    cout<<"\n\nSine = "<<floatNum(s)<<endl;

    return s;
}

// To find cos x, given a real number x
floatComp cosine(floatComp x){

    // cos x = sin (90 - x)

    x=intAdd(1,x,pi/2);
    x=intMultiply(0,x,-1);

    floatComp c=findSine(x);
    cout<<"\n\nCo-sine = "<<floatNum(c)<<endl;
    return c;
}

// To find tan x, given a real number x
floatComp tangent(floatComp x)
{
    // tan x = (sin x)/(cos x)

    floatComp t=(multiplyab(1,sine(x),cosine(x)));
    cout<<"\n\n\nTangent = "<<floatNum(t)<<endl;

    return t;
}

// To find cosec x, given a real number x
floatComp cosecant(floatComp x)
{
    // cosec x = 1/(sin x)

    floatComp t=(inverse(sine(x)));
    cout<<"\n\n\nCo-secant = "<<floatNum(t)<<endl;

    return t;
}

// To find sec x, given a real number x
floatComp secant(floatComp x)
{
    // sec x = 1/(cos x)

    floatComp t=(inverse(cosine(x)));
    cout<<"\n\n\nSecant = "<<floatNum(t)<<endl;

    return t;
}

// To find cot x, given a real number x
floatComp cotangent(floatComp x)
{
    // cot x = (cos x)/(sin x)

    floatComp t=(multiplyab(1,cosine(x),sine(x)));
    cout<<"\n\n\nCo-tangent = "<<floatNum(t)<<endl;

    return t;
}

floatComp sineh(floatComp x)
{
    x=exponential(x);
    cout<<"\n\n\n";
    floatComp y,temp=inverse(x);
    y=addab(1,x,temp);
    floatComp s=intMultiply(1,y,2);
    cout<<"\n\nsinh x = "<<floatNum(s)<<endl;
    return s;
}

floatComp cosineh(floatComp x)
{
    x=exponential(x);
    cout<<"\n\n\n";
    floatComp y,temp=inverse(x);
    y=addab(0,x,temp);
    floatComp s=intMultiply(1,y,2);
    cout<<"\n\ncosh x = "<<floatNum(s)<<endl;
    return s;
}

floatComp tangenth(floatComp x)
{
    floatComp t=multiplyab(1,sineh(x),cosineh(x));
    cout<<"\n\ntanh x = "<<floatNum(t)<<endl;
    return t;
}

floatComp cosecanth(floatComp x)
{
    floatComp cs=inverse(sineh(x));
    cout<<"cosech x = "<<floatNum(cs)<<endl;
    return cs;
}

floatComp secanth(floatComp x)
{
    floatComp cs=inverse(cosineh(x));
    cout<<"sech x = "<<floatNum(cs)<<endl;
    return cs;
}

floatComp cotangenth(floatComp x)
{
    floatComp cs=inverse(tangenth(x));
    cout<<"coth x = "<<floatNum(cs)<<endl;
    return cs;
}
